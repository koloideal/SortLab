set windows-shell := ["cmd", "/c"]

default:
    just --list

# ── Windows ───────────────────────────────────────────────

[windows]
build:
    powershell -ExecutionPolicy Bypass -File setup.ps1

[windows]
rebuild: clean
    powershell -ExecutionPolicy Bypass -File setup.ps1

[windows]
run:
    .\build\SortLab.exe

[windows]
clean:
    if exist build rmdir /s /q build

# ── Linux / macOS ─────────────────────────────────────────

[linux]
[macos]
build:
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build -j{{num_cpus()}}

[linux]
[macos]
rebuild: clean
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build -j{{num_cpus()}}

[linux]
[macos]
run:
    ./build/SortLab

[linux]
[macos]
clean:
    rm -rf build
