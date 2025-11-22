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
	Vector2f lastPoint;
	Vector2f randPoint;
	Vector2f newPoint;

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
        Update 
        ****************************************
        */
        if(points.size() > 0)
        {
            ///generate more point(s)
			///select random vertex
			///calculate midpoint between random vertex and the last point in the vector
			///push back the newly generated coord.
			/// 
			lastPoint = points[points.size() - 1];

			randPoint = vertices[rand() % 3];

			newPoint = {
				(lastPoint.x + randPoint.x) / 2,
				(lastPoint.y + randPoint.y) / 2
			};

			points.push_back(newPoint);
        }

        /*
        ****************************************
        Draw
        ****************************************
        */
        window.clear();
		 for(int i = 0; i < vertices.size(); i++)
		 {

		 RectangleShape rect(Vector2f(10,10));
	
		 rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
	
		 rect.setFillColor(Color::Blue);
	
		 window.draw(rect);
	
		 }
		
		 ///TODO:  Draw points
		for(int i = 0; i < points.size(); i++)
		 {

		 RectangleShape dot(Vector2f(5,5));
	
		 dot.setPosition(Vector2f(points[i].x, points[i].y));
	
		 dot.setFillColor(Color::White);
	
		 window.draw(dot);
	
		 }
		
		
		 window.display();
		
		 }
		
	}
