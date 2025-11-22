// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
    VideoMode vm(1920, 1080);
    // Create and open a window for the game
    RenderWindow window(vm, "Chaos Game!!", Style::Default);

    Font font;
    if (!font.loadFromFile("fonts/Roboto-Italic.ttf"))
    {
        cout << "ERROR: Could not load fonts/Roboto-Italic.ttf" << endl;
        return 1;
    }

    Text instructions;
    instructions.setFont(font);
    instructions.setCharacterSize(24);
    instructions.setFillColor(sf::Color::White);
    instructions.setPosition(10, 10);
    instructions.setString("Click 3 points to place triangle vertices");

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    while (window.isOpen())
    {
        /*
        ****************************************
        Handle the player's input
        ****************************************
        */
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                // Quit the game when the window is closed
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                cout << "the left button was pressed" << std::endl;
                cout << "mouse x: " << event.mouseButton.x << std::endl;
                cout << "mouse y: " << event.mouseButton.y << std::endl;

                if(vertices.size() < 3)
                {
                    vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));

                    if (vertices.size() == 3)
                    {
                        instructions.setString("Click a 4th point to start Chaos Game");
                    }
                }
                else if(points.size() == 0)
                {
                    ///fourth click
                    ///push back to points vector
                    points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    instructions.setString("Generating Chaos Game...");
                }
            }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        /*
        ****************************************
        Update (Chaos Game Algorithm)
        ****************************************
        */
        if(points.size() > 0)
        {
            for (int i = 0; i < 100; i++)
            {
                int r = rand() % 3; 
                Vector2f last = points.back(); 
                Vector2f v = vertices[r]; 
                Vector2f mid(
                    (last.x + v.x) / 2,
                    (last.y + v.y) / 2
                );
                points.push_back(mid);  
            }
        }

        /*
        ****************************************
        Draw
        ****************************************
        */
        window.clear();

        window.draw(instructions);

        // Draws the triangle
        for(size_t i = 0; i < vertices.size(); i++)
        {
            RectangleShape rectangle(Vector2f(10,10));
            rectangle.setPosition(vertices[i]);
            rectangle.setFillColor(Color::White);
            window.draw(rectangle);
        }

        // Draws the chaos points
        for(size_t i = 0; i < points.size(); i++)
        {
            RectangleShape dot(Vector2f(2, 2));
            dot.setPosition(points[i]);
            dot.setFillColor(Color::White);
            window.draw(dot);
        }

        window.display();
    }
}
