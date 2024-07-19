#include <SFML/Graphics.hpp>
#include <iostream>
//Compile:
//cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --config Release

//Build:
//./build/bin/main

long long spiral[154][154];

#define ll long long 
void createSpiral(){

    

//    spiral[499][499] = 1;

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

sf::Color getColor(int i, int j){
    // Calculate RGB values based on i and j
    sf::Uint8 red = static_cast<sf::Uint8>((j * 128) / 154);    // Varies red component horizontally
    sf::Uint8 green =static_cast<sf::Uint8>(128);                   // No green component (you can adjust this if needed)
    sf::Uint8 blue = static_cast<sf::Uint8>((i * 255) / 154);      // Varies blue component vertically

    return sf::Color(red, green, blue);

}

void drawSquare(int i, int j, sf::RenderWindow &window, sf::Vector2f cellSize, bool prime){
    sf::RectangleShape cell;
    cell.setSize(cellSize);
    cell.setPosition(j * cellSize.x + 5.0f, i * cellSize.y + 5.0f);
    if(prime) cell.setFillColor(getColor(i, j));
    else cell.setFillColor(sf::Color::Black);
    window.draw(cell);
}

int main() {

   // createSpiral();

    
    // Create the main window
//    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Red Square");

    int columns = 154;
    int rows = 154;
    sf::RenderWindow window(sf::VideoMode(500,500), "Ulam's Spiral");
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


        int r = 76, c = 76;

        int counter = 1;

        spiral[r][c] = counter;

        for(int i = 1; i < 77; ++i){
            int s = (i*8-4)/4;
            for(int j = 0; j < s; ++j){
                drawSquare(r-j, c+1, window, cellSize, isPrime(++counter));
            }
            drawSquare(r-s, c+1, window, cellSize, isPrime(++counter));
            r = r-s+1; //update r, c
            for(int j = 0; j < s; ++j){
                //spiral[r-1][c-j] = ++counter;
                drawSquare(r-1, c-j, window, cellSize, isPrime(++counter));
            }

            //spiral[r-1][c-s] = ++counter; //top left pivot
            drawSquare(r-1, c-s, window, cellSize, isPrime(++counter));

            c = c-s+1; //update r, c

            for(int j = 0; j < s; ++j){
                //spiral[r+j][c-1] = ++counter;
                drawSquare(r+j, c-1, window, cellSize, isPrime(++counter));
            }
            //spiral[r+s][c-1] = ++counter; //bottom left pivot
            drawSquare(r+s, c-1, window, cellSize, isPrime(++counter));

            r = r+s-1; //update r, c

            for(int j = 0; j < s; ++j){
                //spiral[r+1][c+j] = ++counter;
                drawSquare(r+1, c+j, window, cellSize, isPrime(++counter));
            }
            //spiral[r+1][c+s] = ++counter; //bottom right pivot
            drawSquare(r+1, c+s, window, cellSize, isPrime(++counter));

            r = r+1; //update r to the pivot
            c = c+s; //update c to the pivot
        }


        // Display the contents of the window
        window.display();
    }
    
    return 0;
}
