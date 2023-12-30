#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "EntityManager.h"
#include "Entity.h"

#include <iostream>

struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S; };
struct EnemyConfig  { int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX; };
struct BulletConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };

class Game {
public:
    Game(const std::string & config);
    void run();
    void update();

private:
    // Data members (attributes)
    sf::RenderWindow        m_window;
    //EntityManager           m_entities;
    sf::Font                m_font;
    sf::Text                m_text;
    
    PlayerConfig            m_playerConfig;
    EnemyConfig             m_enemyConfig;
    BulletConfig            m_bulletConfig;

    int                     m_score = 0;
    int                     m_currentFrame = 0;
    int                     m_lastEnemySpawnTime = 0;

    bool                    m_paused;
    bool                    m_running = true;
    

    std::shared_ptr<Entity> m_player;

    // Function declarations (member functions)
    void init(const std::string & config);
    void setPaused(bool paused);

    // Systems
    void sMovement();
    void sUserInput();
    void sLifespan();
    void sRender();
    void sEnemySpawner();
    void sCollision();

    void spawnPlayer();
    void spawnEnemy();
    void spawnSmallEnemies(std::shared_ptr<Entity> entity);
    void spawnBullet(std::shared_ptr<Entity> entity, const Vec2 & mousepos);
    void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

};

#endif
