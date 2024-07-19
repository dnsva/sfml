#include <SFML/Graphics.hpp>
#include <iostream>
//Compile:
//cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --config Release

//Build:
//./build/bin/main

long long spiral[154][154];

#define ll long long 
void createSpiral(){

    int r = 76, c = 76;

    int counter = 1;

    spiral[r][c] = counter;

    for(int i = 1; i < 77; ++i){
        int s = (i*8-4)/4;
        for(int j = 0; j < s; ++j){
            spiral[r-j][c+1] = ++counter;
        }
        spiral[r-s][c+1] = ++counter; //top right pivot
        r = r-s+1; //update r, c
        for(int j = 0; j < s; ++j){
            spiral[r-1][c-j] = ++counter;
        }
        spiral[r-1][c-s] = ++counter; //top left pivot
        c = c-s+1; //update r, c
        for(int j = 0; j < s; ++j){
            spiral[r+j][c-1] = ++counter;
        }
        spiral[r+s][c-1] = ++counter; //bottom left pivot
        r = r+s-1; //update r, c
        for(int j = 0; j < s; ++j){
            spiral[r+1][c+j] = ++counter;
        }
        spiral[r+1][c+s] = ++counter; //bottom right pivot
        r = r+1; //update r to the pivot
        c = c+s; //update c to the pivot
    }

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

void testSpiralFill(){
    createSpiral();
    for(int i = 0; i < 99; ++i){
        for(int j = 0; j < 99; ++j){
            if(spiral[i][j] < 10){
                std::cout<<"   ";
            }else if (spiral[i][j] < 100){
                std::cout<<"  ";
            }else if (spiral[i][j] < 1000){
                std::cout<<" ";
            }
            std::cout<<spiral[i][j]<<" ";
        }
        std::cout<<"\n";
    }

}

int main() {

    createSpiral();

    
    // Create the main window
//    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Red Square");

    int columns = 154;
    int rows = 154;
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


        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                grid[i][j].setSize(cellSize);

                if(isPrime(spiral[i][j])){
                    // Calculate RGB values based on i and j
                    sf::Uint8 red = static_cast<sf::Uint8>((i * 255) / columns);      // Varies red component horizontally
                    sf::Uint8 green = static_cast<sf::Uint8>((j * 255) / rows);       // Varies green component vertically
                    sf::Uint8 blue = static_cast<sf::Uint8>(128);                     // Fixed blue component for simplicity

                    // Set color
                    grid[i][j].setFillColor(sf::Color(red, green, blue));

                    grid[i][j].setPosition(j * cellSize.x + 5.0f, i * cellSize.y + 5.0f);

                    
                }else{
                    grid[i][j].setFillColor(sf::Color::Black);
                    grid[i][j].setPosition(j * cellSize.x + 5.0f, i * cellSize.y + 5.0f);
                }
                
                window.draw(grid[i][j]);
            }
        }




        // Display the contents of the window
        window.display();
    }
    
    return 0;
}
