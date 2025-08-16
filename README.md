# Algorithm Visualizer

A real-time interactive algorithm visualization tool built with C++ and SFML 3.0. Watch sorting algorithms come to life with animated bars, real-time statistics, and interactive controls.

![Algorithm Visualizer Demo](https://img.shields.io/badge/C%2B%2B-17-blue.svg) ![SFML](https://img.shields.io/badge/SFML-3.0.1-green.svg) ![Platform](https://img.shields.io/badge/platform-macOS%20%7C%20Linux%20%7C%20Windows-lightgrey.svg)

## Features

### 🔄 **Sorting Algorithms**
- **Bubble Sort** - Compare adjacent elements and swap if needed
- **Selection Sort** - Find minimum element and place it at the beginning
- **Insertion Sort** - Build sorted array one element at a time
- **Quick Sort** - Divide and conquer approach (placeholder implementation)

### 🎮 **Interactive Controls**
- **Mouse Controls** - Click buttons to start algorithms, change settings
- **Keyboard Shortcuts**:
  - `Space` - Pause/Resume current algorithm
  - `R` - Reset to original data
  - `ESC` - Stop current algorithm

### ⚡ **Customization Options**
- **Data Size**: 25, 50, 100, or 200 elements
- **Animation Speed**: Slow, Medium, or Fast
- **Real-time Statistics**: View comparisons and swaps as they happen
- **Visual Feedback**: Color-coded bars showing current operations

### 🎨 **Visual Design**
- Clean, modern dark theme interface
- Smooth 60 FPS animations
- Color-coded bars (blue=normal, red=primary comparison, yellow=secondary comparison)
- Real-time performance metrics

## Screenshots

*Add screenshots of your visualizer in action here*

## Installation

### Prerequisites

- **C++17** compatible compiler
- **CMake 3.10** or higher
- **SFML 3.0+** graphics library

### Platform-Specific Setup

#### macOS (using Homebrew)
```bash
# Install SFML
brew install sfml

# Clone the repository
git clone https://github.com/yourusername/algorithm-visualizer.git
cd algorithm-visualizer
```

#### Linux (Ubuntu/Debian)
```bash
# Install dependencies
sudo apt-get update
sudo apt-get install libsfml-dev cmake build-essential

# Clone the repository
git clone https://github.com/yourusername/algorithm-visualizer.git
cd algorithm-visualizer
```

#### Windows
1. Install [SFML 3.0+](https://www.sfml-dev.org/download.php)
2. Install [CMake](https://cmake.org/download/)
3. Clone the repository
4. Update CMakeLists.txt with your SFML path if needed

### Build and Run

```bash
# Make the build script executable (macOS/Linux)
chmod +x build.sh

# Build the project
./build.sh

# Run the visualizer
cd build
./AlgorithmVisualizer
```

### Manual Build (Alternative)
```bash
mkdir build
cd build
cmake ..
make
./AlgorithmVisualizer
```

## Usage

### Getting Started
1. Launch the application
2. Click **"Generate Data"** to create a new random dataset
3. Choose a sorting algorithm from the left panel
4. Watch the algorithm visualize in real-time!

### Controls Reference
| Control | Action |
|---------|--------|
| Mouse Click | Interact with buttons |
| `Space` | Pause/Resume algorithm |
| `R` | Reset to original data |
| `ESC` | Stop current algorithm |

### Customization
- **Change Data Size**: Click size buttons (25, 50, 100, 200)
- **Adjust Speed**: Click speed buttons (Slow, Med, Fast)
- **Try Different Algorithms**: Each algorithm has unique characteristics and performance

## Technical Details

### Architecture
- **Language**: C++17 with modern STL features
- **Graphics**: SFML 3.0 for cross-platform graphics and window management
- **Build System**: CMake for cross-platform compilation
- **Design Pattern**: Object-oriented design with separation of concerns

### Performance
- **60 FPS** smooth animations
- **Real-time rendering** of up to 200 elements
- **Efficient memory management** with STL containers
- **Responsive UI** with immediate feedback

### Font Handling
The application automatically detects and loads fonts in this priority order:
1. Local project fonts (arial.ttf, DejaVuSans.ttf, etc.)
2. System fonts (platform-specific paths)
3. Graceful fallback if no fonts are available

## Code Structure

```
algorithm-visualizer/
├── main.cpp              # Main application code
├── CMakeLists.txt        # Build configuration
├── build.sh              # Build automation script
├── README.md             # This file
├── arial.ttf             # Font file (auto-copied to build)
└── build/                # Build directory (auto-generated)
    ├── AlgorithmVisualizer   # Executable
    └── arial.ttf             # Font file (copied)
```

## Algorithm Complexity

| Algorithm | Time Complexity | Space Complexity | Stable |
|-----------|----------------|------------------|---------|
| Bubble Sort | O(n²) | O(1) | ✅ Yes |
| Selection Sort | O(n²) | O(1) | ❌ No |
| Insertion Sort | O(n²) | O(1) | ✅ Yes |
| Quick Sort* | O(n log n) | O(log n) | ❌ No |

*Quick Sort currently uses bubble sort implementation for visualization simplicity

## Contributing

Contributions are welcome! Here are some ways you can help:

### 🚀 **Enhancement Ideas**
- Implement proper Quick Sort visualization
- Add Merge Sort, Heap Sort, Radix Sort
- Add search algorithms (Binary Search, Linear Search)
- Implement graph algorithms (BFS, DFS, Dijkstra)
- Add sound effects for operations
- Add algorithm complexity information in UI

### 🐛 **Bug Reports**
Please open an issue with:
- Operating system and version
- SFML version
- Steps to reproduce the bug
- Expected vs actual behavior

### 📝 **Pull Requests**
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## Troubleshooting

### Common Issues

**"Could not load any font" warning**
- Ensure arial.ttf or other font files are in the project directory
- Check that fonts are being copied to the build directory
- Verify SFML installation supports your font formats

**Build fails with SFML errors**
- Confirm SFML 3.0+ is installed
- Update CMake cache: `rm -rf build && mkdir build`
- Check CMakeLists.txt has correct SFML paths

**Window doesn't appear**
- Verify graphics drivers are up to date
- Try running from terminal to see error messages
- Check if other SFML applications work on your system

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- **SFML Team** for the excellent multimedia library
- **Algorithm visualization community** for inspiration
- **Open source contributors** who make projects like this possible

## Author

Created with ❤️ by [Adrian Davis](https://davisadrian.github.io/Portfolio-site/)

---

⭐ **Star this repository if you found it helpful!** ⭐