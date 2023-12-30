#include "Game.h"
#include <iostream> // Include any other necessary headers

Game::Game(const std::string &config) {
    init(config);
}

void Game::run() {
    while (m_running) {
        sEnemySpawner();
        sMovement();
        sCollision();
        sUserInput();
        sRender();
        m_currentFrame++;
    }
}

void Game::update() {
    // Implementation of the update function
}

void Game::init(const std::string &path) {
    // Initialization logic for the game
    // For instance, window creation, configuration loading, etc.
    m_window.create(sf::VideoMode(1280, 720), "Game Window");
    m_window.setFramerateLimit(60);

    spawnPlayer();
    // Load other resources or perform initialization tasks
}

void Game::setPaused(bool paused) {
    // Implementation of setPaused function
}

void Game::sMovement() {
    // Implementation of sMovement function
}

void Game::sUserInput() {
    // Implementation of sUserInput function
}

void Game::sLifespan() {
    // Implementation of sLifespan function
}

void Game::sRender() {
    // Implementation of sRender function
    // Make sure m_window is valid and properly initialized
}

void Game::sEnemySpawner() {
    // Implementation of sEnemySpawner function
}

void Game::sCollision() {
    // Implementation of sCollision function
}

void Game::spawnPlayer() {
    // Implementation of spawnPlayer function
    // Create and initialize the player entity
}

// Implement other member functions as needed
