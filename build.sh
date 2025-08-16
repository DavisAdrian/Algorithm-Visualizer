#!/bin/bash


echo "🚀 Building Enhanced Algorithm Visualizer..."

if [ ! -d "build" ]; then
    echo "📁 Creating build directory..."
    mkdir build
fi

cd build

echo "⚙️  Generating build files..."
cmake ..

if [ $? -ne 0 ]; then
    echo "❌ CMake failed! Make sure SFML is installed."
    echo "Install SFML with:"
    echo "  macOS: brew install sfml"
    echo "  Ubuntu: sudo apt-get install libsfml-dev"
    exit 1
fi

echo "🔨 Building project..."
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

if [ $? -eq 0 ]; then
    echo "✅ Build successful!"
    echo "🎮 Run with: ./AlgorithmVisualizer"
    echo ""
    echo "💡 Controls:"
    echo "   Space - Pause/Resume"
    echo "   R - Reset to original"
    echo "   Esc - Stop algorithm"
    echo ""
    
    read -p "🤔 Run the visualizer now? (y/n): " -n 1 -r
    echo
    if [[ $REPLY =~ ^[Yy]$ ]]; then
        echo "🎉 Starting Algorithm Visualizer..."
        ./AlgorithmVisualizer
    fi
else
    echo "❌ Build failed!"
    exit 1
fi