#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <vector>
#include <string>
#include <utility>
#include <iostream>

using namespace std;

//Compile:
//cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --config Release

//Build:
//./build/bin/main

struct node{
    sf::CircleShape circle;
    sf::Text circle_name;

    string name;
    int x;
    int y;

    node(){
        circle.setRadius(20.f);
        circle.setFillColor(sf::Color::Green);
        circle.setOutlineThickness(10.f);
        circle.setOutlineColor(sf::Color::Red);
    }
   
};


//IF user wants to CREATE a node outside of bounds, resize grid to fit it
void resize_grid(vector<vector<int>> &grid, int new_size) {
    vector<vector<int>> new_grid(new_size, vector<int>(new_size, 0));
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid.size(); j++) {
            new_grid[i][j] = grid[i][j];
        }
    }
    grid = new_grid;
}

pair<int,int> grid_to_pixel(int x, int y){
    return {x*50, y*50};
}

int main(){
    sf::RenderWindow window(sf::VideoMode(600, 600), "Graphs");

    vector<vector<int>> grid(600, vector<int>(600, 0));
    
    vector<node> nodes;

    sf::Font font;
    font.loadFromFile("src/fonts/arial.ttf");

    node n;
    n.circle_name.setFont(font);
    n.circle_name.setString("A");
    n.circle_name.setCharacterSize(24);
    n.circle_name.setFillColor(sf::Color::White);
    n.circle_name.setPosition(0, 0);

    nodes.push_back(n);

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        window.clear();

        for(int i = 0; i < 600; i+=50){
            sf::Text col_text;
            col_text.setString(std::to_string(i));
            col_text.setFont(font);
            col_text.setCharacterSize(24);
            col_text.setFillColor(sf::Color::White);
            col_text.setPosition(i+20, 0);

            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(0.f, i), sf::Color::Red),
                sf::Vertex(sf::Vector2f(600.f, i), sf::Color::Red)
            };

            window.draw(line, 2, sf::Lines);
            window.draw(col_text);
        }
        for(int i = 0; i < 600; i+=50){
            sf::Text row_text;
            row_text.setString(std::to_string(i));
            row_text.setFont(font);
            row_text.setCharacterSize(24);
            row_text.setFillColor(sf::Color::White);
            row_text.setPosition(0, i+20);

            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(i, 0.f), sf::Color::Red),
                sf::Vertex(sf::Vector2f(i, 600.f), sf::Color::Red)
            };

            window.draw(line, 2, sf::Lines);
            window.draw(row_text);
        }


        for(auto n : nodes){
            window.draw(n.circle);
            window.draw(n.circle_name);
        }

        window.display();
    }

    return 0;
}