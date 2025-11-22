// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

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
    instructions.setFillColor(Color::White);
    instructions.setPosition(10, 10);
    instructions.setString("Click at least 3 points to place vertices, press enter when done");

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    Vector2f lastVertex;
    Vector2f randVertex;

    Vector2f lastPoint;
    Vector2f newPoint;

    bool selectingVertices = true;
    bool generatingPoints = true;
    const float pi = 3.14159;
    float optimalRatio = 0.5;

    while (window.isOpen())
    {
        window.setKeyRepeatEnabled(false);

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

            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    cout << "the left button was pressed" << std::endl;
                    cout << "mouse x: " << event.mouseButton.x << std::endl;
                    cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if (selectingVertices)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if (points.size() == 0)
                    {
                        ///fourth click
                        ///push back to points vector
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
            }

            if (event.type == Event::KeyPressed)
            {
                //handle exit with escape
                if (event.key.code == Keyboard::Escape)
                {
                    window.close();
                }

                //finish choosing vertices, calculate optimal ratio
                if (event.key.code == Keyboard::Enter)
                {
                    if (selectingVertices && vertices.size() >= 3)
                    {
                        selectingVertices = false;

                        if (vertices.size() % 4 == 0)
                        {
                            optimalRatio = 1 / (1 + tan(pi / vertices.size()));
                        }

                        else if (vertices.size() % 4 == 1 || vertices.size() % 4 == 3)
                        {
                            optimalRatio = 1 / (1 + (2 * sin(pi / (2 * vertices.size()))));
                        }
                        else if (vertices.size() % 4 == 2) {
                            optimalRatio = 1 / (1 + sin(pi / vertices.size()));
                        }
                        cout << "optimal ratio with " << vertices.size() << " sides: " << optimalRatio << endl;

                        instructions.setString("Click another point to start Chaos Game");
                    }
                }
            }
            if (event.type == Event::KeyReleased)
            {
                //pause generation
                if (event.key.code == Keyboard::Space && points.size() != 0)
                {

                    generatingPoints = !generatingPoints;
                    cout << "generatingPoints now " << generatingPoints << endl;
                    instructions.setString("Paused Generation...");
                }
            }
        }

        /*
        ****************************************
        Update
        ****************************************
        */
        if (points.size() > 0 && generatingPoints)
        {
            ///generate more point(s)
            ///select random vertex
            ///calculate midpoint between random vertex and the last point in the vector
            ///push back the newly generated coord.
            /// 
            instructions.setString("Generating Chaos Game...");

            do    //no same vertex twice in a row when more than 3 vertices
            {
                randVertex = vertices[rand() % vertices.size()];
            } while (randVertex == lastVertex && vertices.size() > 3);

            lastPoint = points[points.size() - 1];

            //new point = fraction of the distance between new and old point
            newPoint = {
                (lastPoint.x - (lastPoint.x - randVertex.x) * optimalRatio),
                (lastPoint.y - (lastPoint.y - randVertex.y) * optimalRatio)
            };

            points.push_back(newPoint);

            lastVertex = randVertex;
        }

        /*
        ****************************************
        Draw
        ****************************************
        */
        window.clear();

        //draw outline
        if (!selectingVertices)
        {

            ConvexShape shape;
            shape.setPointCount(vertices.size());
            shape.setFillColor(Color::Transparent);
            shape.setOutlineThickness(5.0);

            for (unsigned int i = 0; i < vertices.size(); i++)
            {
                shape.setPoint(i, Vector2f(vertices[i].x, vertices[i].y));
            }

            window.draw(shape);

        }

        //draw vertices points
        for (size_t i = 0; i < vertices.size(); i++)
        {

            RectangleShape rect(Vector2f(10.0, 10.0));

            // - 5.0 each coord to account for offset from shape size (which is 10.0)
            rect.setPosition(Vector2f(vertices[i].x - 5.0, vertices[i].y - 5.0));

            rect.setFillColor(Color::Blue);

            window.draw(rect);

        }
        

        //draw points
        for (size_t i = 0; i < points.size(); i++)
        {

            RectangleShape dot(Vector2f(5.0, 5.0));

            // - 2.5 each coord to account for offset from shape size (which is 5.0)
            dot.setPosition(Vector2f(points[i].x - 2.5, points[i].y - 2.5));

            dot.setFillColor(Color::White);

            window.draw(dot);

        }
        window.draw(instructions);

        window.display();

    }

}
