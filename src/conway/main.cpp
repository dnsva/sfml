#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <vector>

using std::vector;

//Compile:
//cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --config Release

//Build:
//./build/bin/main

/* Rules - https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life#Rules */
/*void setup(vector<vector<bool>> *gen_a, int &c, int &r) {

    //


    //temp setup with random trues 

    (*gen_a)[3][3] = true;
    (*gen_a)[3][4] = true;
    (*gen_a)[3][5] = true;
    (*gen_a)[4][3] = true;
    (*gen_a)[4][4] = true;
    (*gen_a)[4][5] = true;
    (*gen_a)[5][3] = true;
    (*gen_a)[5][4] = true;
    (*gen_a)[5][5] = true;
}*/

void setup(sf::RenderWindow& window, vector<vector<bool>> *gen_a, int& c, int& r) {
    sf::Font font;
    font.loadFromFile("src/conway/arial.ttf");

    int max_x, max_y;
    //get from window
    max_x = window.getSize().x;
    max_y = window.getSize().y;

    sf::Text rows_text, cols_text, enter_text;
    rows_text.setFont(font);
    rows_text.setString("Rows:");
    rows_text.setCharacterSize(16); // Increase character size
    rows_text.setFillColor(sf::Color::Black);
    rows_text.setPosition(std::round(max_x - 250.f), std::round(max_y - 150.f));

    cols_text.setFont(font);
    cols_text.setString("Columns:");
    cols_text.setCharacterSize(16); // Increase character size
    cols_text.setFillColor(sf::Color::Black);
    cols_text.setPosition(std::round(max_x - 250.f), std::round(max_y - 130.f));

    enter_text.setFont(font);
    enter_text.setString("Enter");
    enter_text.setCharacterSize(16); // Increase character size
    enter_text.setFillColor(sf::Color::Black);
    enter_text.setPosition(std::round(max_x - 250.f), std::round(max_y - 110.f));

    sf::RectangleShape rows_box(sf::Vector2f(200.f, 15.f)), 
                       cols_box(sf::Vector2f(200.f, 15.f)),
                       enter_box(sf::Vector2f(100.f, 15.f));
    rows_box.setOutlineColor(sf::Color::Black);
    rows_box.setOutlineThickness(2.f);
    rows_box.setPosition(max_x - 250.f, max_y - 150.f);
    cols_box.setOutlineColor(sf::Color::Black);
    cols_box.setOutlineThickness(2.f);
    cols_box.setPosition(max_x - 250.f, max_y - 130.f);
    enter_box.setOutlineColor(sf::Color::Black);
    enter_box.setOutlineThickness(2.f);
    enter_box.setPosition(max_x - 250.f, max_y - 110.f);

    bool rows_focused = false;
    bool cols_focused = false;
    std::string rows_input, cols_input;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();

            } else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                // Check if mouse clicked on rows box
                if (rows_box.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    rows_focused = true;
                    cols_focused = false;
                }
                // Check if mouse clicked on cols box
                else if (cols_box.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    cols_focused = true;
                    rows_focused = false;
                }
                // Check if mouse clicked on enter button
                else if (enter_box.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    if (!rows_input.empty() && !cols_input.empty()) {
                        r = std::stoi(rows_input);
                        c = std::stoi(cols_input);
                        return;
                    }
                }
            } else if (event.type == sf::Event::TextEntered) {
                if (rows_focused) {
                    if (event.text.unicode >= 48 && event.text.unicode <= 57) {
                        rows_input += static_cast<char>(event.text.unicode);
                        rows_text.setString("Rows: " + rows_input);
                    }
                } else if (cols_focused) {
                    if (event.text.unicode >= 48 && event.text.unicode <= 57) {
                        cols_input += static_cast<char>(event.text.unicode);
                        cols_text.setString("Columns: " + cols_input);
                    }
                }
            }
        }

        
        window.draw(rows_box);
        window.draw(cols_box);
        window.draw(rows_text);
        window.draw(cols_text);
        window.draw(enter_box);
        window.draw(enter_text);       
        window.display();
    }
}

void updateGrid(vector<vector<bool>>& gen_a, vector<vector<bool>>& gen_b, int& generation, int c, int r) {
    // Update the grid
    for (int i = 0; i < c; i++) {
        for (int j = 0; j < r; j++) {
            // Check the rules
            int live_neighbours = 0;

            // Count live neighbors
            if (i - 1 >= 0 && j - 1 >= 0 && gen_a[i - 1][j - 1]) {
                live_neighbours++;
            }
            if (i - 1 >= 0 && gen_a[i - 1][j]) {
                live_neighbours++;
            }
            if (i - 1 >= 0 && j + 1 < r && gen_a[i - 1][j + 1]) {
                live_neighbours++;
            }
            if (j - 1 >= 0 && gen_a[i][j - 1]) {
                live_neighbours++;
            }
            if (j + 1 < r && gen_a[i][j + 1]) {
                live_neighbours++;
            }
            if (i + 1 < c && j - 1 >= 0 && gen_a[i + 1][j - 1]) {
                live_neighbours++;
            }
            if (i + 1 < c && gen_a[i + 1][j]) {
                live_neighbours++;
            }
            if (i + 1 < c && j + 1 < r && gen_a[i + 1][j + 1]) {
                live_neighbours++;
            }

            // Apply rules to update gen_b
            if (gen_a[i][j]) {
                if (live_neighbours < 2 || live_neighbours > 3) {
                    gen_b[i][j] = false;  // Cell dies due to underpopulation or overpopulation
                } else {
                    gen_b[i][j] = true;   // Cell survives
                }
            } else {
                if (live_neighbours == 3) {
                    gen_b[i][j] = true;   // Cell becomes alive due to reproduction
                } else {
                    gen_b[i][j] = false;  // Cell remains dead
                }
            }
        }
    }

    //update gen_a with gen_b
    gen_a = gen_b;

    // Increment the generation counter
    generation++;
}


int main() {
    // Create the main window
//    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Red Square");

    int columns = 8;
    int rows = 8;
    int generation = 1;

    sf::Clock clock;

    sf::Font font;
    font.loadFromFile("src/conway/arial.ttf");

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Blue);
    text.setPosition(10.0f, 10.0f);

    vector<vector<bool>> gen_a(columns, vector<bool>(rows, false));
    vector<vector<bool>> gen_b(columns, vector<bool>(rows, false));

   

    sf::RenderWindow window(sf::VideoMode(800, 800), "Conways Game of Life");
    sf::RectangleShape grid[columns][rows];

    setup(window, &gen_a, columns, rows);
  
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


        //PRINT GEN_A 

        for(int i=0;i<columns;i++){
            for(int j=0;j<rows;j++){
                grid[i][j].setSize(cellSize);
                if(gen_a[i][j]){
                    grid[i][j].setFillColor(sf::Color::White);
                }else{
                    grid[i][j].setFillColor(sf::Color::Black);
                }
                grid[i][j].setPosition(i*cellSize.x + 5.0f, j*cellSize.y + 5.0f);
                window.draw(grid[i][j]);
            }
        }
        
        text.setString("Generation: "+std::to_string(generation));
        window.draw(text);

        // Display the contents of the window
        window.display();


        sf::Time elapsed = clock.getElapsedTime();
        if(elapsed.asSeconds() > 1){
            clock.restart();
            updateGrid(gen_a, gen_b, generation, columns, rows);

        }

    }

    return 0;
}
