#include "game.hpp"

float Game::FPS = 0.0f;
std::optional<float> Game::FPS_low = std::nullopt;
std::optional<float> Game::FPS_max = std::nullopt;
int Game::frameCount = 0;
sf::Clock Game::clock;
sf::Clock Game::clockDelta;
float Game::deltaTime = Game::clockDelta.restart().asSeconds();
bool Game::isMainMenu = false;
bool Game::isGameClose = false;
bool Game::inGame = false;