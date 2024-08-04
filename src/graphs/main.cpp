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

void draw_grid(sf::RenderWindow& window, sf::Font& font, int cols, int rows) {
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
}

sf::Text create_text(sf::Font& font, string text, int x, int y, int size = 12, sf::Color color = sf::Color::Magenta){
    sf::Text t;
    t.setString(text);
    t.setFont(font);
    t.setCharacterSize(size);
    t.setFillColor(color);
    t.setPosition(x, y);
    return t;
}

void setup_nodes(sf::RenderWindow& window, vector<node>& nodes, sf::Font& font, int cols = 100, int rows = 100){

    /* DRAW BOX (BOTTOM LEFT) WITH THE FOLLOWING 
        - ADD NODE OPTION 
        - REMOVE NODE 
        - ADD/REMOVE EDGE
    */

    /* DRAW A BOX - BOTTOM LEFT */
        sf::RectangleShape box(sf::Vector2f(300.f, 200.f));
        box.setFillColor(sf::Color(100,100,100));
        box.setPosition(0, 600);

    /* ADD NODE OPTION
        Title (centered): "Add Node"
        Text: "Name: ", Box: (input), Text: (user input if box clicked)
        Text: "X-Coord; ", Box: (input), Text: (user input if box clicked)
        Text: "Y-Coord; ", Box: (input), Text: (user input if box clicked)
        Button: "OK" (if clicked, add node to graph)
    */
    sf::Text add_node_title = create_text(font, "Add Node", 100, 620);
    sf::Text add_node_name = create_text(font, "Name: ", 10, 650);
    sf::Text add_node_x = create_text(font, "X-Coord: ", 10, 670);
    sf::Text add_node_y = create_text(font, "Y-Coord: ", 10, 690);

    //input boxes:
    sf::RectangleShape add_node_name_box(sf::Vector2f(100.f, 20.f));
    add_node_name_box.setFillColor(sf::Color::White);
    add_node_name_box.setPosition(60, 650);

    string add_node_name_input = "juhu";
    sf::Text add_node_name_input_text = create_text(font, add_node_name_input, 60, 650);

    sf::RectangleShape x_box(sf::Vector2f(100.f, 20.f));
    x_box.setFillColor(sf::Color::White);
    x_box.setPosition(60, 670);

    string x_input = "ljlkjlkj";
    sf::Text x_input_text = create_text(font, x_input, 60, 670);

    sf::RectangleShape y_box(sf::Vector2f(100.f, 20.f));
    y_box.setFillColor(sf::Color::White);
    y_box.setPosition(60, 690);

    string y_input = "kkk";
    sf::Text y_input_text = create_text(font, y_input, 60, 690);

    //ok button:
    sf::RectangleShape add_node_ok_button(sf::Vector2f(50.f, 20.f));
    add_node_ok_button.setFillColor(sf::Color::White);
    add_node_ok_button.setPosition(60, 710);

    sf::Text add_node_ok_text = create_text(font, "OK", 50.f, 20.f);
    add_node_ok_text.setFillColor(sf::Color::Black);
    add_node_ok_text.setPosition(60,710);


    /* REMOVE NODE OPTION
        Title (centered): "Remove Node"
        Text: "Name: ", Box: (input), Text: (user input if box clicked)
        Button: "OK" (if clicked, remove node from graph)
    */
    sf::Text remove_node_title = create_text(font, "Remove Node", 100, 740);
    sf::Text remove_node_name = create_text(font, "Name: ", 10, 770);
    //input box:
    sf::RectangleShape remove_node_name_box(sf::Vector2f(100.f, 20.f));
    remove_node_name_box.setFillColor(sf::Color::White);
    remove_node_name_box.setPosition(60, 770);
    string remove_node_name_input = "";
    sf::Text remove_node_name_input_text = create_text(font, remove_node_name_input, 60, 770);
    //ok button:
    sf::RectangleShape remove_node_ok_button(sf::Vector2f(50.f, 20.f));
    remove_node_ok_button.setFillColor(sf::Color::White);
    remove_node_ok_button.setPosition(60, 790);
    sf::Text remove_node_ok_text = create_text(font, "OK", 50.f, 20.f);
    remove_node_ok_text.setFillColor(sf::Color::Black);
    remove_node_ok_text.setPosition(60, 790);
   

    /* ADD/REMOVE EDGE OPTION
        Title (centered): "Add/Remove Edge"
        Text: "Node 1: ", Box: (input), Text: (user input if box clicked)
        Text: "Node 2: ", Box: (input), Text: (user input if box clicked)
        Button: "OK" (if clicked, add edge to graph if already doesnt exist, if it does exist, remove the edge
    */
    // ADD/REMOVE EDGE OPTION
    sf::Text add_remove_edge_title = create_text(font, "Add/Remove Edge", 100, 820);
    sf::Text add_remove_edge_node1 = create_text(font, "Node 1: ", 10, 850);
    sf::Text add_remove_edge_node2 = create_text(font, "Node 2: ", 10, 870);
    // input boxes:
    sf::RectangleShape add_remove_edge_node1_box(sf::Vector2f(100.f, 20.f));
    add_remove_edge_node1_box.setFillColor(sf::Color::White);
    add_remove_edge_node1_box.setPosition(60, 850);
    string add_remove_edge_node1_input = "";
    sf::Text add_remove_edge_node1_input_text = create_text(font, add_remove_edge_node1_input, 60, 850);
    sf::RectangleShape add_remove_edge_node2_box(sf::Vector2f(100.f, 20.f));
    add_remove_edge_node2_box.setFillColor(sf::Color::White);
    add_remove_edge_node2_box.setPosition(60, 870);
    string add_remove_edge_node2_input = "";
    sf::Text add_remove_edge_node2_input_text = create_text(font, add_remove_edge_node2_input, 60, 870);
    // ok button:
    sf::RectangleShape add_remove_edge_ok_button(sf::Vector2f(50.f, 20.f));
    add_remove_edge_ok_button.setFillColor(sf::Color::White);
    add_remove_edge_ok_button.setPosition(60, 890);
    sf::Text add_remove_edge_ok_text = create_text(font, "OK", 50.f, 20.f);
    add_remove_edge_ok_text.setFillColor(sf::Color::Black);
    add_remove_edge_ok_text.setPosition(60, 890);


    while(window.isOpen()){

        sf::Event event;

        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }

        window.clear();

       // draw_grid(window, font, cols, rows);

        window.draw(box);

        //ADD NODE OPTION DRAW ------------------
        window.draw(add_node_title);
        window.draw(add_node_name);
        window.draw(add_node_x);
        window.draw(add_node_y);
        window.draw(add_node_name_box);
        window.draw(add_node_name_input_text);
        window.draw(x_box);
        window.draw(x_input_text);
        window.draw(y_box);
        window.draw(y_input_text);
        window.draw(add_node_ok_button);
        window.draw(add_node_ok_text);
        //---------------------------------------

        //REMOVE NODE OPTION DRAW ------------------
        window.draw(remove_node_title);
        window.draw(remove_node_name);
        window.draw(remove_node_name_box);
        window.draw(remove_node_name_input_text);
        window.draw(remove_node_ok_button);
        window.draw(remove_node_ok_text);
        //---------------------------------------
        
        //ADD/REMOVE EDGE OPTION DRAW ------------------
        window.draw(add_remove_edge_title);
        window.draw(add_remove_edge_node1);
        window.draw(add_remove_edge_node2);
        window.draw(add_remove_edge_node1_box);
        window.draw(add_remove_edge_node1_input_text);
        window.draw(add_remove_edge_node2_box);
        window.draw(add_remove_edge_node2_input_text);
        window.draw(add_remove_edge_ok_button);
        window.draw(add_remove_edge_ok_text);
        //---------------------------------------


     //   for(auto n : nodes){
       //     window.draw(n.circle);
         //   window.draw(n.circle_name);
        //}

        window.display();

    }

    
    
}

void choose_algorithm(){
    //Do this later
    //from here choose the graphinig algorithm to simulate 
}

void run_algorithm(){
    //Do this later
    //from here run the algorithm
}

void draw_setup(sf::RenderWindow& window, sf::RectangleShape box) {
    window.draw(box);

}

int main(){

    int cols = 100, rows = 100;
    sf::RenderWindow window(sf::VideoMode(800,800), "Graphs");

    vector<node> nodes; //important

    sf::Font font;
    font.loadFromFile("src/fonts/arial.ttf");

    setup_nodes(window, nodes, font);
  //  choose_algorithm();
    //run_algorithm();

    return 0;
}