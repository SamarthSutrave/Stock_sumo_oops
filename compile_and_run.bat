@echo off
echo === Virtual Stock Trading App - Windows Compilation ===
echo.

echo Compiling C++ files...
g++ -std=c++14 -Wall -Wextra -O2 main.cpp Stock.cpp User.cpp Market.cpp TradingApp.cpp -o trading_app.exe

if %errorlevel% equ 0 (
    echo.
    echo ✓ Compilation successful!
    echo ✓ Executable created: trading_app.exe
    echo.
    echo Starting the application...
    echo.
    trading_app.exe
) else (
    echo.
    echo ✗ Compilation failed!
    echo Please check for errors above.
    pause
)
