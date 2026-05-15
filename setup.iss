#define MyAppName "SortLab"
#define MyAppVersion "1.0.0"
#define MyAppExeName "SortLab.exe"

[Setup]
AppId={{A1D8B5A2-1234-4A3D-9B1F-123456789ABC}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher=kolo
AppPublisherURL=https://коло.tech
AppCopyright=Copyright (C) 2026 kolo
AppSupportURL=https://github.com/koloideal/SortLab
AppUpdatesURL=https://github.com/koloideal/SortLab/releases
AppComments=Симулятор визуализации алгоритмов сортировки на SFML with love by kolo

DefaultDirName={autopf}\{#MyAppName}
DefaultGroupName={#MyAppName}
OutputDir=output
OutputBaseFilename=SortLab_Setup
Compression=lzma2
SolidCompression=yes
WizardStyle=modern

[Files]
Source: "build\SortLab.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\libsfml-graphics-2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\libsfml-window-2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\libsfml-system-2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "build\libsfml-audio-2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "assets\*"; DestDir: "{app}\assets"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "assets\icon.ico"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{group}\SortLab"; Filename: "{app}\SortLab.exe"
Name: "{commondesktop}\SortLab"; Filename: "{app}\SortLab.exe"; Tasks: desktopicon

[Tasks]
Name: "desktopicon"; Description: "Создать ярлык на рабочем столе"; GroupDescription: "Дополнительно:"; Flags: unchecked

[Run]
Filename: "{app}\SortLab.exe"; Description: "Запустить SortLab"; Flags: nowait postinstall skipifsilent