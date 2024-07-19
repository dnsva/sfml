#include <SFML/Graphics.hpp>

//Compile:
//cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --config Release

//Build:
//./build/bin/main

long long spiral[100][100];

void createSpiral(){
    //TO DO
}

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int main() {
    // Create the main window
//    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Red Square");

    int columns = 100;
    int rows = 100;
    sf::RenderWindow window(sf::VideoMode(800, 800), "Ulam's Spiral");
    sf::RectangleShape grid[columns][rows];

    // Main loop that continues until the window is closed
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window
        window.clear();

       //set size of cells basd on window size
        sf::Vector2f windowSize = window.getView().getSize();
        sf::Vector2f cellSize(windowSize.x / columns, windowSize.y / rows);


        for (int i = 0; i < columns; i++) {
            for (int j = 0; j < rows; j++) {
                grid[i][j].setSize(cellSize);

                if(isPrime(spiral[i][j])){
                    // Calculate RGB values based on i and j
                    sf::Uint8 red = static_cast<sf::Uint8>((i * 255) / columns);      // Varies red component horizontally
                    sf::Uint8 green = static_cast<sf::Uint8>((j * 255) / rows);       // Varies green component vertically
                    sf::Uint8 blue = static_cast<sf::Uint8>(128);                     // Fixed blue component for simplicity

                    // Set color
                    grid[i][j].setFillColor(sf::Color(red, green, blue));

                    grid[i][j].setPosition(i * cellSize.x + 5.0f, j * cellSize.y + 5.0f);

                    
                }else{
                    grid[i][j].setFillColor(sf::Color::White);
                    grid[i][j].setPosition(i * cellSize.x + 5.0f, j * cellSize.y + 5.0f);
                }
                
                window.draw(grid[i][j]);
            }
        }




        // Display the contents of the window
        window.display();
    }

    return 0;
}
