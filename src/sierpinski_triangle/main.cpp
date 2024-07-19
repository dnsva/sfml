#include <SFML/Graphics.hpp>

//Compile:
//cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --config Release

//Build:
//./build/bin/main

//Function
//Given a triangle at position (x, y) with size s, the function draw three triangles in the corners colored white and one in the center colored black

void drawTriangle(sf::RenderWindow& window, float x, float y, float s) {
    
    //Create the big triangle 
    sf::CircleShape triangle(s, 3);
    
    triangle.setPosition(x, y);
    window.draw(triangle);

    if(s < 1.0f) { //break condition
        triangle.setFillColor(sf::Color::Black);
        return;
    }

    //We have a triangle at x, y with size s
    
    triangle.setFillColor(sf::Color::White);

    //Now we need black triangles in each corner that also call recursive calls

    //Top triangle

    sf::CircleShape triangleTop(s / 2.0f, 3);
    triangleTop.setPosition(x + s / 2.0f, y);
    triangleTop.setFillColor(sf::Color::Blue);
    window.draw(triangleTop);

   // drawTriangle(window, x + s / 2.0f, y, s / 2.0f);


    /*Y = sqrt(s^2 - s^2/4) - sqrt(s^2/4 - s^2/16)
    Y = sqrt(3s^2 / 4) - sqrt( 3s^2 / 16)
    Y = sqrt(3/4 * s^2) - sqrt 3/16 * s^2)
    Y = s*sqrt(3/4) - s*sqrt(3/16)
    Y = s(sqrt(3/4) - sqrt(3/16))
    Y = s * 0.43301270189   */

    //Bottom left

    sf::CircleShape triangleBottomLeft(s / 2.0f, 3);
    triangleBottomLeft.setPosition(x, y + sqrt((s)*(s) - (s/2)*(s/2))); //???
    triangleBottomLeft.setFillColor(sf::Color::Blue);
    window.draw(triangleBottomLeft);

  //  drawTriangle(window, x, y + s * 0.433f, s / 2.0f);
    //Bottom right
 //   drawTriangle(window, x + s, y + s * 0.433f, s / 2.0f);
    
}


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

        //Draw the triangle
        drawTriangle(window, 0, 0, 300);
        
         //TEST
         /*
        sf::CircleShape triangle(80, 3);
        triangle.setFillColor(sf::Color::White);
        triangle.setPosition(100,800-69.3f);
        window.draw(triangle); */

//        sf::Vector2f windowSize = window.getView().getSize();

        // Display the contents of the window
        window.display();
    }

    return 0;
}
