#!/bin/bash

# Check if clang-format is in PATH
if command -v clang-format &> /dev/null; then
    FMT=$(command -v clang-format)
else
    echo "clang-format is not in PATH. Installing it using Homebrew..."
    brew install llvm

    # Check for clang-format's absolute path again
    if [ -x /opt/homebrew/opt/llvm/bin/clang-format ]; then
        FMT=/opt/homebrew/opt/llvm/bin/clang-format
    else
        echo "clang-format installation failed. Please make sure Homebrew is installed and working correctly."
        exit 1
    fi
fi

echo "Using clang-format installed at: $FMT"

format() {
    local dir="$1"
    echo "Formatting files in directory: $dir"
    
    find "$dir" -type f \( -name '*.h' -o -name '*.m' -o -name '*.mm' -o -name '*.c' -o -name '*.cpp' -o -name '*.cc' -o -name '*.hh' -o -name '*.hpp' \) -exec echo "Formatting {}" \; -exec "$FMT" -i {} \;
    
    echo "Formatting complete for directory: $dir"
}

# Check all of the arguments first to make sure they're all directories
for dir in "$@"; do
    if [ ! -d "$dir" ]; then
        echo "$dir is not a directory"
    else
        format "$dir"
    fi
done