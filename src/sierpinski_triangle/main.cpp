#include <SFML/Graphics.hpp>

//Compile:
//cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --config Release

//Build:
//./build/bin/main

void drawTriangle(sf::RenderWindow& window, float x1, float y1, float x2, float y2, float x3, float y3, float definition) {

    if(abs(x1-x2) < definition){ //exit condition
        sf::Vertex line_a[] = {
            sf::Vertex(sf::Vector2f(x1, y1)),
            sf::Vertex(sf::Vector2f(x2, y2))
        };
        sf::Vertex line_b[] = {
            sf::Vertex(sf::Vector2f(x2, y2)),
            sf::Vertex(sf::Vector2f(x3, y3))
        };
        sf::Vertex line_c[] = {
            sf::Vertex(sf::Vector2f(x3, y3)),
            sf::Vertex(sf::Vector2f(x1, y1))
        };
        window.draw(line_a, 2, sf::Lines);
        window.draw(line_b, 2, sf::Lines);
        window.draw(line_c, 2, sf::Lines);
        return;
    }
    //TOP TRIANGLE
    drawTriangle(window, x1, y1, (x1 + x2) / 2, (y1 + y2) / 2, (x1 + x3) / 2, (y1 + y3) / 2, definition);
    //LEFT TRIANGLE
    drawTriangle(window, (x1 + x2) / 2, (y1 + y2) / 2, x2, y2, (x2 + x3) / 2, (y2 + y3) / 2, definition);
    //RIGHT TRIANGLE
    drawTriangle(window, (x1 + x3) / 2, (y1 + y3) / 2, (x2 + x3) / 2, (y2 + y3) / 2, x3, y3, definition);
}


int main(int argc, char* argv[]) {

    float definition = 1.0f;

    if(argc == 2 && std::stoi(argv[1]) > 0){
        definition = static_cast<float>(std::stoi(argv[1]));
    }

    sf::RenderWindow window(sf::VideoMode(800, 800), "Sierpinski Triangle");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(); //clear window
        drawTriangle(window, 0,800, 400,0, 800,800, definition); //every corner point
        window.display(); //display contents
    }
    return 0;
}