$ErrorActionPreference = "Stop"
Add-Type -AssemblyName System.IO.Compression.FileSystem

$MINGW_FILE = "winlibs-x86_64-posix-seh-gcc-13.1.0-mingw-w64msvcrt-11.0.0-r5.zip"
$MINGW_URL  = "https://github.com/brechtsanders/winlibs_mingw/releases/download/13.1.0-16.0.5-11.0.0-msvcrt-r5/$MINGW_FILE"
$SFML_FILE  = "SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit.zip"
$SFML_URL   = "https://github.com/SFML/SFML/releases/download/2.6.1/$SFML_FILE"
$CMAKE_FILE = "cmake-3.28.3-windows-x86_64.zip"
$CMAKE_URL  = "https://github.com/Kitware/CMake/releases/download/v3.28.3/$CMAKE_FILE"

$ROOT  = $PSScriptRoot
$TOOLS = Join-Path $ROOT ".tools"
$MINGW = Join-Path $TOOLS "mingw64"
$SFML  = Join-Path $TOOLS "SFML-2.6.1"
$CMAKE = Join-Path $TOOLS "cmake"
$BUILD = Join-Path $ROOT "build"

function Get-File($url, $dest) {
    if (Test-Path $dest) { return }
    Write-Host "Downloading $(Split-Path $url -Leaf)..."
    $tmp = "$dest.tmp"
    try {
        $wc = New-Object System.Net.WebClient
        $wc.DownloadFile($url, $tmp)
        Move-Item $tmp $dest
    } catch {
        if (Test-Path $tmp) { Remove-Item $tmp }
        throw "Failed to download $url : $_"
    }
}

function Unzip($zip, $dest) {
    Write-Host "Extracting $(Split-Path $zip -Leaf)..."
    [System.IO.Compression.ZipFile]::ExtractToDirectory($zip, $dest)
}

function Find-InPath($cmd) {
    return Get-Command $cmd -ErrorAction SilentlyContinue
}

function Find-Make($gppPath) {
    $binDir = Split-Path $gppPath
    $candidates = @(
        (Join-Path $binDir "mingw32-make.exe"),
        (Join-Path $binDir "make.exe")
    )
    foreach ($c in $candidates) {
        if (Test-Path $c) { return $c }
    }
    $sys = Find-InPath "mingw32-make.exe"
    if ($sys) { return $sys.Source }
    $sys = Find-InPath "make.exe"
    if ($sys) { return $sys.Source }
    return $null
}

function Get-MsysRoot($gppPath) {
    if ($gppPath -match "msys64") {
        $parts = $gppPath -split "msys64"
        return $parts[0] + "msys64"
    }
    return $null
}

function Get-MsysArch($gppPath) {
    if ($gppPath -like "*ucrt64*")   { return "ucrt64" }
    if ($gppPath -like "*mingw64*")  { return "mingw64" }
    if ($gppPath -like "*mingw32*")  { return "mingw32" }
    if ($gppPath -like "*clang64*")  { return "clang64" }
    return $null
}

New-Item -ItemType Directory -Force -Path $TOOLS | Out-Null

$cmakeExe = $null
$systemCmake = Find-InPath "cmake.exe"
if ($systemCmake) {
    $ver = (& $systemCmake.Source --version 2>$null | Select-Object -First 1) -replace "cmake version ", ""
    Write-Host "Found system cmake $ver at $($systemCmake.Source)"
    $cmakeExe = $systemCmake.Source
} elseif (Test-Path (Join-Path $CMAKE "bin\cmake.exe")) {
    Write-Host "Found local cmake in .tools"
    $cmakeExe = Join-Path $CMAKE "bin\cmake.exe"
} else {
    $zip = Join-Path $TOOLS $CMAKE_FILE
    Get-File $CMAKE_URL $zip
    Unzip $zip $TOOLS
    $extracted = Get-ChildItem $TOOLS -Directory | Where-Object { $_.Name -like "cmake-3.28*" } | Select-Object -First 1
    Rename-Item $extracted.FullName $CMAKE
    $cmakeExe = Join-Path $CMAKE "bin\cmake.exe"
}

$gppExe       = $null
$gccExe       = $null
$makeExe      = $null
$generator    = $null
$sfmlCmakeDir = $null
$extraCmakeArgs = @()
$isMsys2      = $false

$hasMSVC   = Find-InPath "cl.exe"
$systemGpp = Find-InPath "g++.exe"

if ($hasMSVC) {
    Write-Host "Found MSVC cl.exe"
    $vsWhere = Join-Path ${env:ProgramFiles(x86)} "Microsoft Visual Studio\Installer\vswhere.exe"
    $vsVer = $null
    if (Test-Path $vsWhere) {
        $vsVer = & $vsWhere -latest -property catalog_productLineVersion 2>$null
    }
    if ($vsVer -eq "2022")     { $generator = "Visual Studio 17 2022" }
    elseif ($vsVer -eq "2019") { $generator = "Visual Studio 16 2019" }
    else                       { $generator = "Visual Studio 17 2022" }
    $extraCmakeArgs = @("-A", "x64")
} elseif ($systemGpp) {
    $ver = (& $systemGpp.Source --version 2>$null | Select-Object -First 1) -replace ".*?(\d+\.\d+\.\d+).*", '$1'
    Write-Host "Found system g++ $ver at $($systemGpp.Source)"
    $gppExe  = $systemGpp.Source
    $gccExe  = (Find-InPath "gcc.exe").Source
    $makeExe = Find-Make $gppExe
    if (-not $makeExe) {
        throw "make.exe / mingw32-make.exe not found near $gppExe"
    }
    Write-Host "Found make at $makeExe"
    $generator = "MinGW Makefiles"

    $msysRoot = Get-MsysRoot $gppExe
    $msysArch = Get-MsysArch $gppExe
    if ($msysRoot -and $msysArch) {
        $isMsys2 = $true
        $msysSfmlDir = Join-Path $msysRoot "$msysArch\lib\cmake\SFML"
        if (-not (Test-Path (Join-Path $msysSfmlDir "SFMLConfig.cmake"))) {
            $pkg = if ($msysArch -eq "ucrt64") { "mingw-w64-ucrt-x86_64-sfml" } elseif ($msysArch -eq "mingw64") { "mingw-w64-x86_64-sfml" } else { "mingw-w64-$msysArch-sfml" }
            Write-Host "SFML not found in MSYS2, installing $pkg via pacman..."
            $pacman = Join-Path $msysRoot ("usr\bin\pacman.exe")
            if (-not (Test-Path $pacman)) {
                throw "pacman.exe not found in MSYS2 root $msysRoot"
            }
            & $pacman -S --needed --noconfirm $pkg
            if ($LASTEXITCODE -ne 0) {
                throw "pacman failed to install $pkg"
            }
        }
        if (Test-Path (Join-Path $msysSfmlDir "SFMLConfig.cmake")) {
            Write-Host "Using MSYS2 SFML at $msysSfmlDir"
            $sfmlCmakeDir = $msysSfmlDir
        } else {
            throw "SFMLConfig.cmake still not found in $msysSfmlDir after pacman install"
        }
    }

    $extraCmakeArgs = @(
        "-DCMAKE_CXX_COMPILER=$gppExe",
        "-DCMAKE_MAKE_PROGRAM=$makeExe"
    )
} elseif (Test-Path (Join-Path $MINGW "bin\g++.exe")) {
    Write-Host "Found local MinGW in .tools"
    $gppExe  = Join-Path $MINGW "bin\g++.exe"
    $gccExe  = Join-Path $MINGW "bin\gcc.exe"
    $makeExe = Join-Path $MINGW "bin\mingw32-make.exe"
    $env:PATH = (Join-Path $MINGW "bin") + ";" + $env:PATH
    $generator = "MinGW Makefiles"
    $extraCmakeArgs = @(
        "-DCMAKE_C_COMPILER=$gccExe",
        "-DCMAKE_CXX_COMPILER=$gppExe",
        "-DCMAKE_MAKE_PROGRAM=$makeExe"
    )
} else {
    $zip = Join-Path $TOOLS $MINGW_FILE
    Get-File $MINGW_URL $zip
    Unzip $zip $TOOLS
    $extracted = Get-ChildItem $TOOLS -Directory | Where-Object { $_.Name -like "mingw64*" } | Select-Object -First 1
    if ($extracted -and $extracted.FullName -ne $MINGW) {
        Rename-Item $extracted.FullName $MINGW
    }
    $gppExe  = Join-Path $MINGW "bin\g++.exe"
    $gccExe  = Join-Path $MINGW "bin\gcc.exe"
    $makeExe = Join-Path $MINGW "bin\mingw32-make.exe"
    $env:PATH = (Join-Path $MINGW "bin") + ";" + $env:PATH
    $generator = "MinGW Makefiles"
    $extraCmakeArgs = @(
        "-DCMAKE_C_COMPILER=$gccExe",
        "-DCMAKE_CXX_COMPILER=$gppExe",
        "-DCMAKE_MAKE_PROGRAM=$makeExe"
    )
}

if (-not $sfmlCmakeDir) {
    $sfmlInclude = Join-Path $SFML "include\SFML"
    if (!(Test-Path $sfmlInclude)) {
        $zip = Join-Path $TOOLS $SFML_FILE
        Get-File $SFML_URL $zip
        Unzip $zip $TOOLS
    } else {
        Write-Host "Found local SFML 2.6.1 in .tools"
    }
    $sfmlCmakeDir = Join-Path $SFML "lib\cmake\SFML"
}

$cacheFile = Join-Path $BUILD "CMakeCache.txt"

if (Test-Path $cacheFile) {
    $cachedGenerator = Get-Content $cacheFile |
        Where-Object { $_ -match "^CMAKE_GENERATOR:INTERNAL=" } |
        ForEach-Object { ($_ -split "=", 2)[1] }
    if ($cachedGenerator -and $cachedGenerator.Trim() -ne $generator) {
        Write-Host "Generator changed ('$($cachedGenerator.Trim())' -> '$generator'), clearing build cache..."
        Remove-Item -Recurse -Force $BUILD
    }
}

if (!(Test-Path $cacheFile)) {
    Write-Host "Configuring with generator: $generator"
    $configArgs = @(
        "-S", $ROOT,
        "-B", $BUILD,
        "-G", $generator,
        "-DSFML_DIR=$sfmlCmakeDir",
        "-DCMAKE_BUILD_TYPE=Release"
    ) + $extraCmakeArgs
    & $cmakeExe @configArgs
    if ($LASTEXITCODE -ne 0) { throw "CMake configure failed" }
}

Write-Host "Building..."
& $cmakeExe --build $BUILD --config Release -j 4
if ($LASTEXITCODE -ne 0) { throw "CMake build failed" }

if (-not $isMsys2) {
    $dllDirs = @(
        (Join-Path $SFML "bin"),
        (Join-Path $BUILD "bin"),
        (Join-Path $BUILD "Release"),
        (Join-Path $BUILD "_deps\sfml-build\lib\Release"),
        (Join-Path $BUILD "_deps\sfml-build\lib\Debug")
    )
    $copied = $false
    foreach ($dir in $dllDirs) {
        if (Test-Path (Join-Path $dir "sfml-graphics*.dll")) {
            Copy-Item (Join-Path $dir "*.dll") $BUILD -Force
            Write-Host "Copied DLLs from $dir"
            $copied = $true
            break
        }
    }
    if (-not $copied) {
        Write-Host "Warning: SFML DLLs not found, you may need to copy them manually"
    }
} else {
    Write-Host "MSYS2 build: DLLs are handled by CMake TARGET_RUNTIME_DLLS"
}

Write-Host "Done! Run: $(Join-Path $BUILD 'SortLab.exe')"