#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <vector>

using std::vector;

//Compile:
//cmake -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build --config Release

//Build:
//./build/bin/main

/* Rules - https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life#Rules */

void draw_grid(sf::RenderWindow& window, vector<vector<bool>> &gen_a, int c, int r) {
    //set size of cells basd on window size
    sf::Vector2f windowSize = window.getView().getSize();
    sf::Vector2f cellSize(windowSize.x / c, windowSize.y / r);

    //PRINT GEN_A 

    for(int i=0;i<c;i++){
        for(int j=0;j<r;j++){
            sf::RectangleShape cell;
            cell.setSize(cellSize);
            if(gen_a[i][j]){
                cell.setFillColor(sf::Color::White);
            }else{
                cell.setFillColor(sf::Color::Black);
            }
            cell.setPosition(i*cellSize.x + 5.0f, j*cellSize.y + 5.0f);
            window.draw(cell);
        }
    }
}

void setup_squares(sf::RenderWindow& window, vector<vector<bool>> &gen_a, int c, int r, int & population) {
    //depending on where user clicks, set the index of gen_a to true. if double click, set to false
    //if user presses enter, start the game

    //map this backwards. get i & j based off pos

    //grid[i][j].setPosition(i*cellSize.x + 5.0f, j*cellSize.y + 5.0f);
    bool isMousePressed = false;

    while (window.isOpen()) {

        //set size of cells basd on window size
        sf::Vector2f windowSize = window.getView().getSize();
        sf::Vector2f cellSize(windowSize.x / c, windowSize.y / r);

        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                    isMousePressed = true;
                    // Toggle the cell under the mouse
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    int i = static_cast<int>((mousePos.x - 5.0f) / cellSize.x);
                    int j = static_cast<int>((mousePos.y - 5.0f) / cellSize.y);
                    if (i >= 0 && i < c && j >= 0 && j < r) {
                        if(gen_a[i][j]){
                            population--;
                        }else{
                            population++;
                        }
                        gen_a[i][j] = !gen_a[i][j];
                    }
            }
            else if (event.type == sf::Event::MouseButtonReleased) {
                    isMousePressed = false;
            }
            else if (event.type == sf::Event::MouseMoved) {
                if (isMousePressed) {
                    // Continuous toggle as the mouse moves
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    int i = static_cast<int>((mousePos.x - 5.0f) / cellSize.x);
                    int j = static_cast<int>((mousePos.y - 5.0f) / cellSize.y);
                    if (i >= 0 && i < c && j >= 0 && j < r) {
                        if(gen_a[i][j]){
                            population--;
                        }else{
                            population++;
                        }
                        gen_a[i][j] = !gen_a[i][j];
                    }
                }
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    return;
                }
            }
        }

        // Clear the window
        window.clear();

        //PRINT GEN_A 
        draw_grid(window, gen_a, c, r);


        // Display the contents of the window
        window.display();

    }
}

void setup_rows_and_cols(sf::RenderWindow& window, vector<vector<bool>> &gen_a, vector<vector<bool>> &gen_b, int& c, int& r) {
    sf::Font font;
    font.loadFromFile("src/conway/arial.ttf");

    int max_x, max_y;
    //get from window
    max_x = window.getSize().x;
    max_y = window.getSize().y;

    sf::Text dims_text, enter_text;
    dims_text.setFont(font);
    dims_text.setString("Grid r/c size:");
    dims_text.setCharacterSize(16); // Increase character size
    dims_text.setFillColor(sf::Color::Black);
    dims_text.setPosition(std::round(max_x - 250.f), std::round(max_y - 150.f));

    enter_text.setFont(font);
    enter_text.setString("Enter");
    enter_text.setCharacterSize(16); // Increase character size
    enter_text.setFillColor(sf::Color::Black);
    enter_text.setPosition(std::round(max_x - 250.f), std::round(max_y - 110.f));

    sf::RectangleShape dims_box(sf::Vector2f(200.f, 15.f)), 
                       enter_box(sf::Vector2f(100.f, 15.f));
    dims_box.setOutlineColor(sf::Color::Black);
    dims_box.setOutlineThickness(2.f);
    dims_box.setPosition(max_x - 250.f, max_y - 150.f);
    enter_box.setOutlineColor(sf::Color::Black);
    enter_box.setOutlineThickness(2.f);
    enter_box.setPosition(max_x - 250.f, max_y - 110.f);

    std::string dims_input;

    bool dims_focused = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (enter_box.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    if (!dims_input.empty()) {

                       // Convert input to integers
                        r = std::stoi(dims_input);
                        c = std::stoi(dims_input);

                        // Clear and resize gen_a and gen_b
                        gen_a.clear();
                        gen_a.resize(r, std::vector<bool>(c, false));
                        gen_b.clear();
                        gen_b.resize(r, std::vector<bool>(c, false));

                        return;
                    }
                }
            } else if( event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Backspace) {
                    if (!dims_input.empty()) {
                        dims_input.pop_back();
                        dims_text.setString("Grid r/c size: " + dims_input);
                    }
                    
                }
            }else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode >= 48 && event.text.unicode <= 57) {
                    dims_input += static_cast<char>(event.text.unicode);
                    dims_text.setString("Grid r/c size: " + dims_input);
                }
                
            }
        }

        window.clear();
        window.draw(dims_box);
        window.draw(dims_text);
        window.draw(enter_box);
        window.draw(enter_text);
        window.display();
    }

}

void updateGrid(vector<vector<bool>>& gen_a, vector<vector<bool>>& gen_b, int& generation, int& population, int c, int r) {
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
                    population--;
                } else {
                    gen_b[i][j] = true;   // Cell survives
                    //population++;
                }
            } else {
                if (live_neighbours == 3) {
                    gen_b[i][j] = true;   // Cell becomes alive due to reproduction
                    population++;
                } else {
                    gen_b[i][j] = false;  // Cell remains dead
                    //population--;
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

    int columns = 100;
    int rows = 100;
    int generation = 1;
    int population = 0;

    sf::Clock clock;

    sf::Font font;
    font.loadFromFile("src/conway/arial.ttf");

    sf::Text text_generation, text_population;
    text_generation.setFont(font);
    text_generation.setCharacterSize(24);
    text_generation.setFillColor(sf::Color::Blue);
    text_generation.setPosition(10.0f, 10.0f);
    text_population.setFont(font);
    text_population.setCharacterSize(24);
    text_population.setFillColor(sf::Color::Blue);
    text_population.setPosition(10.0f, 40.0f);


    sf::RenderWindow window(sf::VideoMode(800, 800), "Conways Game of Life");
    sf::RectangleShape grid[columns][rows];

  //  vector<vector<bool>> gen_a(columns, vector<bool>(rows, false));
  //  vector<vector<bool>> gen_b(columns, vector<bool>(rows, false));
    vector<vector<bool>> gen_a, gen_b;
    setup_rows_and_cols(window, gen_a, gen_b, columns, rows);
    setup_squares(window, gen_a, columns, rows, population);
    
  
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

        
        draw_grid(window, gen_a, columns, rows);
        
        text_generation.setString("Generation: "+std::to_string(generation));
        text_population.setString("Population: "+std::to_string(population));
        window.draw(text_generation);
        window.draw(text_population);

        // Display the contents of the window
        window.display();


        sf::Time elapsed = clock.getElapsedTime();
        if(elapsed.asSeconds() > 1){
            clock.restart();
            updateGrid(gen_a, gen_b, generation, population, columns, rows);

        }

    }

    return 0;
}
