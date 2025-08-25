#!/bin/bash
# Quick test script for the Virtual Stock Trading App

echo "=== Virtual Stock Trading App - Compilation Test ==="
echo

# Check if required files exist
echo "Checking for required files..."
required_files=("main.cpp" "Stock.cpp" "Stock.h" "User.cpp" "User.h" "Market.cpp" "Market.h" "TradingApp.cpp" "TradingApp.h" "Makefile")

for file in "${required_files[@]}"; do
    if [ -f "$file" ]; then
        echo "✓ $file found"
    else
        echo "✗ $file missing"
        exit 1
    fi
done

echo
echo "All files found! Ready to compile."
echo

# Compile using make
echo "Compiling using make..."
if make; then
    echo "✓ Compilation successful!"
    echo
    echo "You can now run the application with: ./trading_app"
    echo "Or use: make run"
else
    echo "✗ Compilation failed!"
    exit 1
fi
