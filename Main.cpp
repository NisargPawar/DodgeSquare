#include "PlayerController.h"
#include "ObstacleSpawner.h"
#include "HUD.h"
#include "GameOverScreen.h"
#include "Resources.h"

#include <SFML/Graphics.hpp>
#include <windows.h>

const std::string APP_NAME = "DodgeSquare";
const int         WINDOW_DEFAULT_WIDTH = 800;
const int         WINDOW_DEFAULT_HEIGHT = 600;

int main()
{
    

    sf::RenderWindow window(sf::VideoMode(WINDOW_DEFAULT_WIDTH, WINDOW_DEFAULT_HEIGHT), APP_NAME);
    window.setFramerateLimit(120);
    
    sf::Image icon;
    if (icon.loadFromFile("DodgeSquare.png"))
    {
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

    // Filled rectangle
    sf::RectangleShape frame(sf::Vector2f(WINDOW_DEFAULT_WIDTH * 9.f / 16.f, WINDOW_DEFAULT_HEIGHT));

    // seed random once at startup, before the game loop
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    float playerSpeed = 100.f;
    PlayerController player(20.f, 50.f, 99.f, playerSpeed, &frame); // size, x, y, speed (px/sec)
    float obstacleSpeed = 100.f;
    ObstacleSpawner  spawner(20.f, obstacleSpeed, &frame);
    sf::Clock clock;

    bool gameOver = false;
    GameOverScreen gameOverScreen(&frame, "C:/Windows/Fonts/arial.ttf");
    HUD            hud(&frame, "C:/Windows/Fonts/arial.ttf");

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized)
                window.setView(sf::View(sf::FloatRect(0, 0,
                    (float)event.size.width, (float)event.size.height)));
        }

        // --- Compute centered 9:16 rect ---
        float winW = (float)window.getSize().x;
        float winH = (float)window.getSize().y;

        float frameW, frameH;
        if (winH * 9.f / 16.f <= winW)
        {
            // height is the limiting dimension
            frameH = winH;
            frameW = winH * 9.f / 16.f;
        }
        else
        {
            // width is the limiting dimension
            frameW = winW;
            frameH = winW * 16.f / 9.f;
        }

        float frameX = (winW - frameW) / 2.f;
        float frameY = (winH - frameH) / 2.f;

        float frameScaleFactor = frameH / frame.getSize().y;

        frame.setSize(sf::Vector2f(frameW,frameH));
        frame.setPosition(frameX, frameY);
        frame.setFillColor(sf::Color(50, 50, 80));

        // Outline
        frame.setOutlineThickness(2.f);
        frame.setOutlineColor(sf::Color(120, 120, 200));
        player.setScale(frameScaleFactor);
        spawner.updateScale(frameScaleFactor);

        if (!gameOver) {
            player.update(dt);
            spawner.update(dt, frameScaleFactor);

            for (auto it : spawner.getObstacles()) {
                if (it.isColliding(player.getShape())) {
                    gameOver = true;
                    gameOverScreen.show(spawner.getGameScore());
                }
            }
        }
        // draw order
        window.clear(sf::Color(30, 30, 30)); // dark background
        window.draw(frame);
        spawner.draw(window);
        player.draw(window);
        if (!gameOver) hud.draw(window, spawner.getGameScore()); // hide HUD when game over
        gameOverScreen.draw(window);
        window.display();
    }

    return 0;
}