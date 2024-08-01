
# textfield.h

This is a simple textfield class that can be used to create a textfield in the console. An action runs when the enter key is pressed.

## Example tester.cpp

```cpp
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include "textfield.h"
#include <iostream>

void textfield::action(){
    std::cout << "Enter pressed" << std::endl;
}

int main(){
    sf::RenderWindow window(sf::VideoMode(800, 600), "Textfield Test");
    textfield tf(100,100,500,100);
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
            tf.textfield::check_events(window, event);
        }
        window.clear();
        tf.textfield::draw_textfield(window);
        window.display();
    }
    return 0;
}
```