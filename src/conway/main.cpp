#include <SFML/Graphics.hpp>

//Compile:
//cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --config Release

//Build:
//./build/bin/main

/* Rules - https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life#Rules

Any live cell with fewer than two live neighbours dies, as if by underpopulation.
Any live cell with two or three live neighbours lives on to the next generation.
Any live cell with more than three live neighbours dies, as if by overpopulation.
Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

*/

int main() {
    // Create the main window
//    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Red Square");

    int columns = 8;
    int rows = 8;
    sf::RenderWindow window(sf::VideoMode(800, 800), "Conways Game of Life");
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


        for(int i=0;i<columns;i++){
            for(int j=0;j<rows;j++){
                grid[i][j].setSize(cellSize);
               // grid[i][j].setOutlineColor(sf::Color::Blue);
               // grid[i][j].setOutlineThickness(5.0f);

                // Calculate color based on indices (i, j)
                // Clamp values to 0-255 range
                sf::Uint8 red = static_cast<sf::Uint8>(std::min(255, (i + j) * 10));
                sf::Uint8 green = static_cast<sf::Uint8>(std::min(255, (i + j) * 10));
                sf::Uint8 blue = static_cast<sf::Uint8>(std::min(255, (i + j) * 10));

                // Set color
                grid[i][j].setFillColor(sf::Color(red, green, blue));

                grid[i][j].setPosition(i*cellSize.x + 5.0f, j*cellSize.y + 5.0f);

                window.draw(grid[i][j]);

            }
        }



        // Display the contents of the window
        window.display();
    }

    return 0;
}
