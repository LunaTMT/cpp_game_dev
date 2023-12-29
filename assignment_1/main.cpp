#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

const float windowWidth = 800;
const float windowHeight = 600;


int main() {
    using circleTuple = tuple<string, sf::CircleShape*, float, float>;
    using rectangleTuple = tuple<string, sf::RectangleShape*, float, float>;
    
    vector<circleTuple> circles;
    vector<rectangleTuple> rectangles;

    ifstream file("shapes.txt");

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << "Reading line: " << line << endl;
            if (line.empty() || line[0] == '/' || line[0] == '\r' || line[0] == '\n') {
                continue; // Skip comments or empty lines
            }

            istringstream iss(line);
            string token;
            vector<string> tokens;

            while (iss >> token) {
                tokens.push_back(token);
            }
            
            string name = tokens[0];
            float posX = stof(tokens[2]);
            float posY = stof(tokens[3]);
            float velX = stof(tokens[4]);
            float velY = stof(tokens[5]);
            int r = stoi(tokens[6]);
            int g = stoi(tokens[7]);
            int b = stoi(tokens[8]);

            if (tokens[0] == "Circle") {
                int radius = stoi(tokens[9]);

                sf::CircleShape* circlePtr = new sf::CircleShape(radius);
                circlePtr->setFillColor(sf::Color(r, g, b));
                circlePtr->setPosition(posX, posY);

                circleTuple circleTuple{name, circlePtr, velX, velY };
                circles.push_back(circleTuple);

            } else if (tokens[0] == "Rectangle") {
                int width = std::stoi(tokens[9]);
                int height = std::stoi(tokens[10]);

                sf::RectangleShape* rectanglePtr = new sf::RectangleShape(sf::Vector2f(width, height));
                rectanglePtr->setFillColor(sf::Color(r, g, b));
                rectanglePtr->setPosition(posX, posY);

                rectangleTuple rectangleTuple{name, rectanglePtr, velX, velY };
                rectangles.push_back(rectangleTuple);

            } else {
                continue;
            }
        }
        file.close();
    } else {
        cout << "Unable to open file";
        return 1; 
    }

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Shapes");

    sf::Font font;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            //Handle events
            if (event.type == sf::Event::Closed)
                window.close();
        }


        for (auto& circleTuple : circles) {
                string name = get<0>(circleTuple);
                auto circle = std::get<1>(circleTuple);  
                float& vel_x = std::get<2>(circleTuple);   
                float& vel_y = std::get<3>(circleTuple);   

                circle->setPosition(circle->getPosition().x + vel_x, circle->getPosition().y + vel_y);

                // Detect collision with window boundaries
                sf::Vector2f circlePosition = circle->getPosition();
                float circleRadius = circle->getRadius();

                if (circlePosition.x + (2*circleRadius) >= windowWidth || circlePosition.x <= 0) {
                    // Reverse velocity in x-direction if hitting left or right boundary
                    vel_x = -vel_x;
                }

                if (circlePosition.y + (2*circleRadius) >= windowHeight || circlePosition.y <= 0) {
                    // Reverse velocity in y-direction if hitting top or bottom boundary
                    vel_y = -vel_y;
                }
            }

        for (auto& rectangleTuple : rectangles) {
            string name = get<0>(rectangleTuple);
            auto rectangle = std::get<1>(rectangleTuple);  // Extracting the rectangle as a pointer
            float& vel_x = std::get<2>(rectangleTuple);   
            float& vel_y = std::get<3>(rectangleTuple);   

            rectangle->setPosition(rectangle->getPosition().x + vel_x, rectangle->getPosition().y + vel_y);

            // Detect collision with window boundaries
            sf::Vector2f rectPosition = rectangle->getPosition();
            sf::FloatRect rectBounds = rectangle->getLocalBounds();

            if (rectPosition.x + rectBounds.width >= windowWidth || rectPosition.x <= 0) {
                // Reverse velocity in x-direction if hitting left or right boundary
                vel_x = -vel_x;
            }

            if (rectPosition.y + rectBounds.height >= windowHeight || rectPosition.y <= 0) {
                // Reverse velocity in y-direction if hitting top or bottom boundary
                vel_y = -vel_y;
            }
        }

        //Draw
        window.clear(sf::Color::White);
    
        // Draw circles with names
        for (const auto& circleTuple : circles) {
            const auto& name = std::get<0>(circleTuple);
            auto& circle = *std::get<1>(circleTuple);  // Extracting the circle as a reference

            float vel_x = std::get<2>(circleTuple);   
            float vel_y = std::get<3>(circleTuple);   
            
            circle.setPosition(circle.getPosition().x + vel_x, circle.getPosition().y + vel_y);

            // Detect collision with window boundaries (same as your existing logic)

            // Drawing name in the center of the circle
            sf::Text text;
            text.setFont(font);
            text.setString(name);
            text.setCharacterSize(20);
            text.setFillColor(sf::Color::Black);

            // Centering the text
            sf::FloatRect textBounds = text.getLocalBounds();
            text.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
            text.setPosition(circle.getPosition().x + circle.getRadius(), circle.getPosition().y + circle.getRadius());

            window.draw(circle);
            window.draw(text);
        }

        // Draw rectangles with names
        for (const auto& rectangleTuple : rectangles) {
            const auto& name = std::get<0>(rectangleTuple);
            auto& rectangle = *std::get<1>(rectangleTuple);  // Extracting the rectangle as a reference

            float vel_x = std::get<2>(rectangleTuple);   
            float vel_y = std::get<3>(rectangleTuple);   

            rectangle.setPosition(rectangle.getPosition().x + vel_x, rectangle.getPosition().y + vel_y);

            // Detect collision with window boundaries (same as your existing logic)

            // Drawing name in the center of the rectangle
            sf::Text text;
            text.setFont(font);
            text.setString(name);
            text.setCharacterSize(20);
            text.setFillColor(sf::Color::Black);

            // Centering the text
            sf::FloatRect textBounds = text.getLocalBounds();
            text.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
            text.setPosition(rectangle.getPosition().x + rectangle.getSize().x / 2.f, rectangle.getPosition().y + rectangle.getSize().y / 2.f);

            window.draw(rectangle);
            window.draw(text);
        }

// ... (rest of your code remains the same) ...

        window.display();
    }


    return 0;
}
