#include <SFML/Graphics.hpp>

//Compile:
//cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --config Release

//Build:
//./build/bin/main

//Function
//Given a triangle at position (x, y) with size s, the function draw three triangles in the corners colored white and one in the center colored black


int main() {
  
    sf::RenderWindow window(sf::VideoMode(800, 800), "Sierpinski Triangle");

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
        
         //TEST
        sf::CircleShape triangle(80, 3);
        triangle.setFillColor(sf::Color::White);
        triangle.setPosition(100,800-69.3f);
        window.draw(triangle);

//        sf::Vector2f windowSize = window.getView().getSize();

        // Display the contents of the window
        window.display();
    }

    return 0;
}
