#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <optional>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "lox");

    sf::CircleShape circle(100.f);
    circle.setFillColor(sf::Color::Cyan);
    circle.setPosition({350.f, 250.f});

    while (window.isOpen()) {

        window.clear();
        window.draw(circle);
        window.display();
        circle.setScale({2.f, 2.f});
    }

    return 0;
}
