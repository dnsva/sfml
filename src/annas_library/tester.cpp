#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>

//testing textfield.h
#include "textfield.h"
#include "button.h"

#include <iostream>

//Compile:
//cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --config Release

//Build:
//./build/bin/main

void button::action(){
    std::cout << "Enter pressed" << std::endl;
}

int main(){

    sf::RenderWindow window(sf::VideoMode(800, 600), "Textfield Test");

    button b("button", 100,100,500,100);
    
    while(window.isOpen()){

        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
            b.check_button_events(window, event);
        }

        window.clear();
        b.draw_button(window);
        window.display();
    }

    return 0;
}