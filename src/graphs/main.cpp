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
 /*
void resize_grid(vector<vector<int>> &grid, int new_size) {

   
    vector<vector<int>> new_grid(new_size, vector<int>(new_size, 0));
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid.size(); j++) {
            new_grid[i][j] = grid[i][j];
        }
    }
    grid = new_grid;
   
}
*/

pair<int,int> grid_to_pixel(int x, int y){
    return {x*50, y*50};
}

int main(){

    int cols = 100, rows = 100;
    sf::RenderWindow window(sf::VideoMode(800,800), "Graphs");

    int cell_pixel_width = window.getSize().x / cols;
    
    vector<node> nodes;

    sf::Font font;
    font.loadFromFile("src/fonts/arial.ttf");

    /*
    node n;
    n.circle_name.setFont(font);
    n.circle_name.setString("A");
    n.circle_name.setCharacterSize(24);
    n.circle_name.setFillColor(sf::Color::White);
    n.circle_name.setPosition(0, 0);

    nodes.push_back(n);
    */

    while(window.isOpen()){

        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        window.clear();

        /* THE FOLLOWING CODE DRAWS GRID LINES AND NUMBERS AT THE TOP AND SIDES */
        for(int i = 0; i < 800; i+=50){
            sf::Text col_text;
            col_text.setString(std::to_string(i));
            col_text.setFont(font);
            col_text.setCharacterSize(12);
            col_text.setFillColor(sf::Color::White);
            col_text.setPosition(i-to_string(i).length()*4.0/2, 0);
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(0.f, i),sf::Color(100,100,100)),
                sf::Vertex(sf::Vector2f(800.f, i), sf::Color(100,100,100))
            };
            window.draw(line, 2, sf::Lines);
            window.draw(col_text);
        }
        for(int i = 50; i < 800; i+=50){ //start at 50 since previous loop covered 0
            sf::Text row_text;
            row_text.setString(std::to_string(i));
            row_text.setFont(font);
            row_text.setCharacterSize(12);
            row_text.setFillColor(sf::Color::White);
            row_text.setPosition(0, i-10); 

            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(i, 0.f), sf::Color(100,100,100)),
                sf::Vertex(sf::Vector2f(i, 800.f), sf::Color(100,100,100))
            };

            window.draw(line, 2, sf::Lines);
            window.draw(row_text);
        }
        /***************************************************************************/

        /* DRAW BOX (BOTTOM LEFT) WITH THE FOLLOWING 
        - ADD NODE OPTION 
        - REMOVE NODE 
        - ADD/REMOVE EDGE
        */

       /* DRAW A BOX - BOTTOM LEFT */
        sf::RectangleShape box(sf::Vector2f(300.f, 200.f));
        box.setFillColor(sf::Color(100,100,100));
        box.setPosition(0, 600);
        window.draw(box);



        for(auto n : nodes){
            window.draw(n.circle);
            window.draw(n.circle_name);
        }

        window.display();

    }

    return 0;
}