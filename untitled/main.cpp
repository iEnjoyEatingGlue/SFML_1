#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class CustomRectangleShape: public sf::RectangleShape
{
public:
    CustomRectangleShape(sf::Vector2f size,sf::Vector2f position): sf::RectangleShape(size)
    {
        setPosition(position);
    }
    void setSpeed(const int &x,const int &y,const int &rot)
    {
        m_speed_x = x;
        m_speed_y = y;
        rot_speed = rot;
    }
    void animate(const sf::Time &elapsed)
    {
        bounce();
        float time = elapsed.asSeconds();
        move(m_speed_x*time,m_speed_y*time);
        rotate(rot_speed*time);
    }
    void setBounds(const float &top,const float &bot,const float &left,const float &right)
    {
        bound_top = top;
        bound_bottom = bot;
        bound_left = left;
        bound_right = right;
    }
    void moveInDirection(const sf::Time &elapsed/*, const sf::Keyboard::Key &key*/)
    {
        float time = elapsed.asSeconds();
        sf::FloatRect rectangle_bounds_2 = getGlobalBounds();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if(rectangle_bounds_2.top >= bound_top)
            {
                move(0,m_speed_y*time * -1.0);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if(rectangle_bounds_2.top + rectangle_bounds_2.height <= bound_bottom)
            {
                move(0,m_speed_y*time);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if(rectangle_bounds_2.left >= bound_left )
            {
                move(m_speed_x*time * -1.0,0);
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if(rectangle_bounds_2.left + rectangle_bounds_2.width <= bound_right)
            {
                move(m_speed_x*time,0);
            }
        }
    }
    bool isClicked(sf::Vector2i &mouse_position) const
    {
        bool a = false;
        sf::FloatRect rectangle_bounds_2 = getGlobalBounds();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if(rectangle_bounds_2.top < mouse_position.y && mouse_position.y < rectangle_bounds_2.top + rectangle_bounds_2.height
                    && rectangle_bounds_2.left < mouse_position.x && mouse_position.x < rectangle_bounds_2.left + rectangle_bounds_2.width)
            {
                a = true;
            }
        }

        return (a);

    }

private:
    int m_speed_x = 0;
    int m_speed_y = 0;
    int rot_speed = 0;

    float bound_top = 0;
    float bound_bottom = 0;
    float bound_left = 0;
    float bound_right = 0;

    void bounce()
    {
        sf::FloatRect rectangle_bounds_2 = getGlobalBounds();

        if(rectangle_bounds_2.top <= bound_top){
            m_speed_y = abs(m_speed_y);
            setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }

        if(rectangle_bounds_2.top + rectangle_bounds_2.height >= bound_bottom){
            m_speed_y = abs(m_speed_y) * -1;
            setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }

        if(rectangle_bounds_2.left <= bound_left ){
           m_speed_x = abs(m_speed_x);
           setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }

        if(rectangle_bounds_2.left + rectangle_bounds_2.width >= bound_right){
            m_speed_x = abs(m_speed_x) * -1;
            setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        }
    }
};



int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    sf::Vector2f size(120.0, 60.0);
    sf::Vector2f position(120.0, 60.0);
    CustomRectangleShape rectangle_2(size, position);
    rectangle_2.setFillColor(sf::Color(4, 50, 250));
    rectangle_2.setSpeed(100, 200, 50);
    rectangle_2.setBounds(0, 600, 0,800);


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

        float x_speed = rectangle_velocity_x * elapsed.asSeconds();
        float y_speed = rectangle_velocity_y * elapsed.asSeconds();
        float rotation = (rectangle_angular_velocity * elapsed.asSeconds());

        rectangle.move(x_speed,y_speed);
        rectangle.rotate(rotation);
//        rectangle_2.animate(elapsed);

        window.getSize();

        sf::FloatRect rectangle_bounds = rectangle.getGlobalBounds();

        rectangle_bounds_right = rectangle_bounds.left + rectangle_bounds.width;
        rectangle_bounds_bottom = rectangle_bounds.top + rectangle_bounds.height;

        if(rectangle_bounds.left < 0 || rectangle_bounds_right > window.getSize().x)
        {
            rectangle_velocity_x = rectangle_velocity_x * (-1.0);
//            srand(time(NULL));
            rectangle.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
        }
        if(rectangle_bounds_bottom > window.getSize().y || rectangle_bounds.top < 0)
        {

            rectangle_velocity_y = rectangle_velocity_y * (-1.0);
//            srand(time(NULL));
            rectangle.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
        }


        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        rectangle_2.moveInDirection(elapsed);

        sf::Vector2i position = sf::Mouse::getPosition(window);
//        std::cout << position.x << std::endl;
        std::cout << position.y << std::endl;

        if(rectangle_2.isClicked(position) == true)
        {
            rectangle_2.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
        }
//        if(event.type == sf::Event::KeyReleased)
//                    {
//                        if(event.key.code == sf::Keyboard::Space)
//                        {
//                            rectangle_2.animate(elapsed);

//                            std::cout << "Space released" << std::endl;
//                        }
//                    }
//                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//                {
//                    rectangle_2.animate(elapsed);
//                }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        window.draw(circle);
        window.draw(rectangle);
        window.draw(triangle);
        window.draw(rectangle_2);

        // end the current frame
        window.display();
    }

    return 0;
}















//class Vehicle {

//public:
//    std::string name() { return name_; }
//    int number_of_wheels() { return number_of_wheels_; }
//    std::string propulsion_type() { return propulsion_type_; }
//    double max_speed() { return max_speed_; }

//protected:
//    Vehicle(const std::string &name, int number_of_wheels,
//            const std::string &propulsion_type, double max_speed)
//      : name_(name), number_of_wheels_(number_of_wheels),
//        propulsion_type_(propulsion_type), max_speed_(max_speed) {}

//    std::string name_;
//    int number_of_wheels_;
//    std::string propulsion_type_;
//    double max_speed_;
//};


//class Car : public Vehicle {

//public:
//    Car(const std::string &name, const std::string &propulsion_type,
//        double max_speed, bool has_abs)
//        : Vehicle(name, 4, propulsion_type, max_speed),
//          has_abs_(has_abs) {}

//    bool has_abs() { return has_abs_; }

//private:
//    bool has_abs_;
//};

//int main()
//{
//    Car passat("Volkswagen Passat", "Diesel", 200, true);
//}


