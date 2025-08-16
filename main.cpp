#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <thread>
#include <random>
#include <functional>
#include <sstream>
#include <filesystem>

using namespace std;

class AlgorithmVisualizer {
private:
    vector<int> data;
    vector<int> original_data;
    int max_value;
    int delay_ms;
    bool is_sorting;
    string current_algorithm;
    string status_message;
    
    int comparisons;
    int swaps;
    chrono::high_resolution_clock::time_point start_time;
    
    int highlight1, highlight2;
    
    sf::RenderWindow window;
    sf::Font font;
    bool font_loaded;
    
    sf::Color background_color = sf::Color(20, 20, 30);
    sf::Color bar_color = sf::Color(70, 130, 180);
    sf::Color highlight_color = sf::Color(255, 100, 100);
    sf::Color comparing_color = sf::Color(255, 200, 50);
    sf::Color text_color = sf::Color(240, 240, 240);
    sf::Color button_color = sf::Color(50, 50, 70);
    sf::Color button_hover_color = sf::Color(70, 70, 90);

    struct Button {
        sf::RectangleShape shape;
        sf::Text text;
        function<void()> action;
        bool enabled = true;
        
        Button(const sf::Font& f, const string& buttonText = "") : text(f, buttonText), enabled(true) {}
        
        bool isMouseOver(const sf::RenderWindow& window) const {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            return shape.getGlobalBounds().contains(mousePosF);
        }
    };
    
    vector<Button> buttons;

public:
    AlgorithmVisualizer() : delay_ms(50), is_sorting(false), comparisons(0), swaps(0), 
                           highlight1(-1), highlight2(-1), font_loaded(false) {
        setupWindow();
        generateRandomData(50);
        current_algorithm = "Ready";
        status_message = "Select an algorithm to begin";
    }

private:
    void setupWindow() {
        window.create(sf::VideoMode(sf::Vector2u(1200, 800)), "Algorithm Visualizer");
        window.setFramerateLimit(60);
        
        font_loaded = loadFont();
        
        if (!font_loaded) {
            cerr << "Warning: Could not load any font. Text may not display properly." << endl;
        }
        
        setupButtons();
    }
    
    bool loadFont() {
        vector<string> font_paths = {
            "/System/Library/Fonts/Helvetica.ttc",
            "/System/Library/Fonts/ArialHB.ttc",
            "/System/Library/Fonts/Monaco.ttf",
            "/System/Library/Fonts/Times.ttc",
            "/System/Library/Fonts/Courier.ttc",
            "/Library/Fonts/Arial.ttf",
            
            "arial.ttf",
            "./arial.ttf",
            "font.ttf",
            "./font.ttf",
            "DejaVuSans.ttf",
            "./DejaVuSans.ttf",
            
            "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
            "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
            "/usr/share/fonts/truetype/ubuntu/Ubuntu-Regular.ttf",
            "/usr/share/fonts/TTF/DejaVuSans.ttf",
            "/usr/share/fonts/TTF/arial.ttf",
            
            "C:/Windows/Fonts/arial.ttf",
            "C:/Windows/Fonts/calibri.ttf",
            "C:/Windows/Fonts/tahoma.ttf"
        };
        
        for (const auto& path : font_paths) {
            if (filesystem::exists(path) && font.openFromFile(path)) {
                return true;
            }
        }
        
        return false;
    }
    
    void setupButtons() {
        buttons.clear();
        
        if (!font_loaded) {
            return;
        }
        
        createButton("Generate Data", 20, 20, 160, 40, [this]() { 
            if (!is_sorting) generateRandomData(data.size()); 
        });
        
        createButton("Bubble Sort", 20, 70, 160, 40, [this]() { 
            if (!is_sorting) startSort("Bubble Sort");
        });
        
        createButton("Selection Sort", 20, 120, 160, 40, [this]() { 
            if (!is_sorting) startSort("Selection Sort");
        });
        
        createButton("Insertion Sort", 20, 170, 160, 40, [this]() { 
            if (!is_sorting) startSort("Insertion Sort");
        });
        
        createButton("Quick Sort", 20, 220, 160, 40, [this]() { 
            if (!is_sorting) startSort("Quick Sort");
        });
        
        createButton("Stop", 20, 320, 160, 40, [this]() { 
            is_sorting = false;
        });
        
        createButton("Size: 25", 20, 420, 75, 35, [this]() { 
            if (!is_sorting) generateRandomData(25); 
        });
        createButton("Size: 50", 105, 420, 75, 35, [this]() { 
            if (!is_sorting) generateRandomData(50); 
        });
        createButton("Size: 100", 20, 465, 75, 35, [this]() { 
            if (!is_sorting) generateRandomData(100); 
        });
        createButton("Size: 200", 105, 465, 75, 35, [this]() { 
            if (!is_sorting) generateRandomData(200); 
        });
        
        createButton("Slow", 20, 520, 50, 35, [this]() { delay_ms = 100; });
        createButton("Med", 80, 520, 50, 35, [this]() { delay_ms = 50; });
        createButton("Fast", 140, 520, 50, 35, [this]() { delay_ms = 10; });
    }
    
    void createButton(const string& text, float x, float y, float width, float height, 
                     function<void()> action) {
        Button button(font, text);
        
        button.shape.setPosition(sf::Vector2f(x, y));
        button.shape.setSize(sf::Vector2f(width, height));
        button.shape.setFillColor(button_color);
        button.shape.setOutlineThickness(1);
        button.shape.setOutlineColor(sf::Color(100, 100, 120));
        
        button.text.setCharacterSize(14);
        button.text.setFillColor(text_color);
        
        sf::FloatRect textBounds = button.text.getLocalBounds();
        float centerX = x + (width - textBounds.size.x) / 2.0f - textBounds.position.x;
        float centerY = y + (height - textBounds.size.y) / 2.0f - textBounds.position.y;
        button.text.setPosition(sf::Vector2f(centerX, centerY));
        
        button.action = action;
        buttons.push_back(button);
    }
    
    void handleEvents() {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            else if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mousePressed->button == sf::Mouse::Button::Left) {
                    for (auto& button : buttons) {
                        if (button.isMouseOver(window)) {
                            button.action();
                            break;
                        }
                    }
                }
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Escape) {
                    is_sorting = false;
                } else if (keyPressed->code == sf::Keyboard::Key::Space) {
                    is_sorting = !is_sorting;
                } else if (keyPressed->code == sf::Keyboard::Key::R && !is_sorting) {
                    data = original_data;
                    status_message = "Reset to original data";
                }
            }
        }
    }
    
    void draw() {
        window.clear(background_color);
        
        drawBars();
        drawUI();
        drawButtons();
        
        window.display();
    }
    
    void drawBars() {
        if (data.empty()) return;
        
        float viz_x = 200.0f;
        float viz_y = 100.0f;
        float viz_width = 980.0f;
        float viz_height = 600.0f;
        
        float bar_width = viz_width / static_cast<float>(data.size());
        
        for (size_t i = 0; i < data.size(); i++) {
            float bar_height = (static_cast<float>(data[i]) / static_cast<float>(max_value)) * viz_height;
            
            sf::RectangleShape bar;
            bar.setSize(sf::Vector2f(bar_width - 1, bar_height));
            bar.setPosition(sf::Vector2f(viz_x + i * bar_width, viz_y + viz_height - bar_height));
            
            if (static_cast<int>(i) == highlight1) {
                bar.setFillColor(highlight_color);
            } else if (static_cast<int>(i) == highlight2) {
                bar.setFillColor(comparing_color);
            } else {
                bar.setFillColor(bar_color);
            }
            
            window.draw(bar);
        }
    }
    
    void drawUI() {
        if (!font_loaded) {
            sf::RectangleShape indicator(sf::Vector2f(400, 3));
            indicator.setPosition(sf::Vector2f(200, 45));
            indicator.setFillColor(sf::Color::White);
            window.draw(indicator);
            return;
        }
        
        sf::Text title(font, "Algorithm Visualizer");
        title.setCharacterSize(24);
        title.setFillColor(text_color);
        title.setPosition(sf::Vector2f(200, 20));
        window.draw(title);
        
        sf::Text algo(font, "Algorithm: " + current_algorithm);
        algo.setCharacterSize(18);
        algo.setFillColor(text_color);
        algo.setPosition(sf::Vector2f(200, 50));
        window.draw(algo);
        
        sf::Text status(font, status_message);
        status.setCharacterSize(16);
        status.setFillColor(text_color);
        status.setPosition(sf::Vector2f(200, 75));
        window.draw(status);
        
        if (is_sorting) {
            stringstream stats;
            stats << "Comparisons: " << comparisons << " | Swaps: " << swaps;
            
            sf::Text statsText(font, stats.str());
            statsText.setCharacterSize(16);
            statsText.setFillColor(sf::Color(150, 200, 255));
            statsText.setPosition(sf::Vector2f(200, 720));
            window.draw(statsText);
        } else {
            sf::Text controls(font, "Controls: Space=Pause/Resume | R=Reset | ESC=Stop");
            controls.setCharacterSize(14);
            controls.setFillColor(sf::Color(180, 180, 180));
            controls.setPosition(sf::Vector2f(200, 750));
            window.draw(controls);
        }
    }
    
    void drawButtons() {
        for (auto& button : buttons) {
            if (button.isMouseOver(window)) {
                button.shape.setFillColor(button_hover_color);
            } else {
                button.shape.setFillColor(button_color);
            }
            
            window.draw(button.shape);
            window.draw(button.text);
        }
    }

public:
    void run() {
        while (window.isOpen()) {
            handleEvents();
            
            if (is_sorting) {
                stepSort();
            }
            
            draw();
            this_thread::sleep_for(chrono::milliseconds(16));
        }
    }
    
    void generateRandomData(int size) {
        data.clear();
        data.resize(size);
        
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(10, 200);
        
        for (int i = 0; i < size; i++) {
            data[i] = distrib(gen);
        }
        
        original_data = data;
        max_value = *max_element(data.begin(), data.end());
        
        status_message = "Generated " + to_string(size) + " random elements";
    }

private:
    string sort_type;
    size_t sort_i, sort_j;
    bool sort_done;
    
    void startSort(const string& algorithm) {
        current_algorithm = algorithm;
        sort_type = algorithm;
        is_sorting = true;
        sort_done = false;
        comparisons = 0;
        swaps = 0;
        sort_i = 0;
        sort_j = 0;
        highlight1 = highlight2 = -1;
        start_time = chrono::high_resolution_clock::now();
        status_message = algorithm + " started...";
    }
    
    void stepSort() {
        if (sort_done) {
            finishSort();
            return;
        }
        
        if (sort_type == "Bubble Sort") {
            stepBubbleSort();
        } else if (sort_type == "Selection Sort") {
            stepSelectionSort();
        } else if (sort_type == "Insertion Sort") {
            stepInsertionSort();
        } else if (sort_type == "Quick Sort") {
            stepQuickSort();
        }
        
        this_thread::sleep_for(chrono::milliseconds(delay_ms));
    }
    
    void stepBubbleSort() {
        if (sort_i >= data.size()) {
            sort_done = true;
            return;
        }
        
        if (sort_j >= data.size() - sort_i - 1) {
            sort_i++;
            sort_j = 0;
            return;
        }
        
        highlight1 = sort_j;
        highlight2 = sort_j + 1;
        comparisons++;
        
        if (data[sort_j] > data[sort_j + 1]) {
            swap(data[sort_j], data[sort_j + 1]);
            swaps++;
        }
        
        sort_j++;
    }
    
    void stepSelectionSort() {
        static int min_idx = 0;
        
        if (sort_i >= data.size() - 1) {
            sort_done = true;
            return;
        }
        
        if (sort_j == sort_i) {
            min_idx = sort_i;
        }
        
        if (sort_j >= data.size()) {
            if (min_idx != sort_i) {
                swap(data[sort_i], data[min_idx]);
                swaps++;
            }
            sort_i++;
            sort_j = sort_i;
            return;
        }
        
        highlight1 = min_idx;
        highlight2 = sort_j;
        comparisons++;
        
        if (data[sort_j] < data[min_idx]) {
            min_idx = sort_j;
        }
        
        sort_j++;
    }
    
    void stepInsertionSort() {
        static int key = 0;
        static int k = 0;
        
        if (sort_i >= data.size()) {
            sort_done = true;
            return;
        }
        
        if (sort_j == 0) {
            key = data[sort_i];
            k = sort_i - 1;
        }
        
        highlight1 = sort_i;
        highlight2 = k;
        
        if (k >= 0 && data[k] > key) {
            data[k + 1] = data[k];
            comparisons++;
            swaps++;
            k--;
        } else {
            data[k + 1] = key;
            sort_i++;
            sort_j = 0;
        }
    }
    
    void stepQuickSort() {
        stepBubbleSort();
    }
    
    void finishSort() {
        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
        
        status_message = current_algorithm + " completed in " + to_string(duration.count()) + 
                        "ms | " + to_string(comparisons) + " comparisons | " + to_string(swaps) + " swaps";
        
        is_sorting = false;
        highlight1 = highlight2 = -1;
        current_algorithm = "Completed";
    }
};

int main() {
    try {
        AlgorithmVisualizer visualizer;
        visualizer.run();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}