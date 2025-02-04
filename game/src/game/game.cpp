#include "game.hpp"

float Game::FPS = 0.0f;
int Game::frameCount = 0;
sf::Clock Game::clock;
sf::Clock Game::clockDelta;
float Game::deltaTime = Game::clockDelta.restart().asSeconds();