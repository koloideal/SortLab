set windows-shell := ["cmd", "/c"]

default: 
    just --list

build:
    powershell -ExecutionPolicy Bypass -File setup.ps1

rebuild: clean
    powershell -ExecutionPolicy Bypass -File setup.ps1

run:
    .\\build\\SortLab.exe

clean:
    if exist build rmdir /s /q build
