#include <SFML/Graphics.hpp>

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Red Square");

    // Create a red square shape
    sf::RectangleShape redSquare(sf::Vector2f(100.f, 100.f));
    redSquare.setFillColor(sf::Color::Red);
    redSquare.setPosition(350.f, 250.f);

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

        // Draw the red square
        window.draw(redSquare);

        // Display the contents of the window
        window.display();
    }

    return 0;
}
