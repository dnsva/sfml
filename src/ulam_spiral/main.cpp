#include <SFML/Graphics.hpp>
#include <iostream>

//Compile:
//cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --config Release

//Build:
//./build/bin/main

int total_rows = 200, total_cols = 200; //set default values

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

sf::Color getColor(int i, int j){ //calculate RGB values based on i and j
    sf::Uint8 red = static_cast<sf::Uint8>((static_cast<float>(j) * 128) / total_cols);
    sf::Uint8 green =static_cast<sf::Uint8>(128);
    sf::Uint8 blue = static_cast<sf::Uint8>((static_cast<float>(i) * 255) / total_rows);
    return sf::Color(red, green, blue);
}

void drawSquare(int i, int j, sf::RenderWindow &window, sf::Vector2f cell_size, bool prime){
    sf::RectangleShape cell;
    cell.setSize(cell_size);
    cell.setPosition(j * cell_size.x, i * cell_size.y);
    if(prime) cell.setFillColor(getColor(i, j));
    else cell.setFillColor(sf::Color::Black);
    window.draw(cell);
}

int main() {

    sf::RenderWindow window(sf::VideoMode(500,500), "Ulam's Spiral");

    while (window.isOpen()) { //continues until window is closed
        sf::Event event; //handle events
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }
        window.clear(); //clear the window

       //set size of cells basd on window size
        sf::Vector2f window_size = window.getView().getSize();
        sf::Vector2f cell_size(window_size.x / total_cols, window_size.y / total_rows);

        int r = total_rows/2-1, c = total_cols/2-1; //start at the center

        int counter = 1; //the actual number in the spiral

        for(int i = 1; i < ceil((total_rows - 1)/2.0); ++i){
            int s = (i*8-4)/4; //side length
            for(int j = 0; j < s; ++j){
                drawSquare(r-j, c+1, window, cell_size, isPrime(++counter));
            }
            drawSquare(r-s, c+1, window, cell_size, isPrime(++counter)); //top right pivot
            r = r-s+1; //update r, c
            for(int j = 0; j < s; ++j){
                drawSquare(r-1, c-j, window, cell_size, isPrime(++counter));
            }
            drawSquare(r-1, c-s, window, cell_size, isPrime(++counter)); //top left pivot
            c = c-s+1; //update r, c
            for(int j = 0; j < s; ++j){
                drawSquare(r+j, c-1, window, cell_size, isPrime(++counter));
            }
            drawSquare(r+s, c-1, window, cell_size, isPrime(++counter)); //bottom left pivot
            r = r+s-1; //update r, c
            for(int j = 0; j < s; ++j){
                drawSquare(r+1, c+j, window, cell_size, isPrime(++counter));
            }
            drawSquare(r+1, c+s, window, cell_size, isPrime(++counter)); //bottom right pivot
            r = r+1; //update r to the pivot
            c = c+s; //update c to the pivot
        }
        window.display(); //display the contents
    }
    return 0;
}
