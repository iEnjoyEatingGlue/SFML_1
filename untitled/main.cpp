#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    // create some shapes
    sf::CircleShape circle(100.0);
    circle.setPosition(100.0, 300.0);
    circle.setFillColor(sf::Color(100, 250, 50));

    sf::RectangleShape rectangle(sf::Vector2f(120.0, 60.0));
    rectangle.setPosition(500.0, 400.0);
    rectangle.setFillColor(sf::Color(100, 50, 250));

    float rectangle_velocity_x = 50;
    float rectangle_velocity_y = 150;
    float rectangle_angular_velocity = 10;
    float rectangle_bounds_right;
    float rectangle_bounds_bottom;

    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(0.0, 0.0));
    triangle.setPoint(1, sf::Vector2f(0.0, 100.0));
    triangle.setPoint(2, sf::Vector2f(140.0, 40.0));
    triangle.setOutlineColor(sf::Color::Red);
    triangle.setOutlineThickness(5);
    triangle.setPosition(600.0, 100.0);

    // run the program as long as the window is open
    sf::Clock clock;
    float time_passed = 0.0;
    while (window.isOpen())
    {

        sf::Time elapsed = clock.restart();
        time_passed = time_passed + elapsed.asSeconds();
//        std::cout << "time between successive runs in microseconds: " << elapsed.asMicroseconds() << std::endl;
//        std::cout << "frames per second: " << 1.0/elapsed.asSeconds() << std::endl;
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(circle);
        window.draw(rectangle);
        window.draw(triangle);

        window.getSize();
        std::cout << window.getSize().y << std::endl;

        sf::FloatRect rectangle_bounds = rectangle.getGlobalBounds();
//               std::cout << rectangle_bounds.top << " " << rectangle_bounds.left << " " ;
//               std::cout << rectangle_bounds.width << " " << rectangle_bounds.height << std::endl;
        rectangle_bounds_right = rectangle_bounds.left + rectangle_bounds.width;
        rectangle_bounds_bottom = rectangle_bounds.top + rectangle_bounds.height;

        if(rectangle_bounds.left < 0 || rectangle_bounds_right > window.getSize().x)
        {
            rectangle_velocity_x = rectangle_velocity_x * (-1.0);
            srand(time(NULL));
            rectangle.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
        }
        if(rectangle_bounds.top > window.getSize().y || rectangle_bounds_bottom < 0)
        {
            rectangle_velocity_y = rectangle_velocity_y * (-1.0);
            srand(time(NULL));
            rectangle.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
        }



        float x_speed = rectangle_velocity_x * elapsed.asSeconds();
        float y_speed = rectangle_velocity_y * elapsed.asSeconds();
        float rotation = (rectangle_angular_velocity * elapsed.asSeconds());

        rectangle.move(x_speed,y_speed);
        rectangle.rotate(rotation);

        // end the current frame
        window.display();
    }

    return 0;
}
