#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include "SquareShape.h"

class ObstacleSpawner
{
    private:
        float                       m_obstacleSize;
        int                         m_rightBoundry;
        float                       m_speed;
        sf::RectangleShape*         m_frame;
        std::vector<SquareShape>    m_obstacles;
        float                       m_spawnTimer;
        float                       m_spawnInterval;
        float                       m_gameScore;

    public:

        // getters
        int getGameScore()
        {
            return m_gameScore;
        }

        ObstacleSpawner(float obstacleSize, float speed, sf::RectangleShape* frame)
            : m_obstacleSize(obstacleSize), m_speed(speed), m_frame(frame),
            m_spawnTimer(0.f), m_spawnInterval(1.5f)
        {
            m_rightBoundry = int((0.99 - m_obstacleSize / m_frame->getSize().x) * 100);
            m_gameScore    = 0;
        }

        void updateScale(float scale) {
            m_obstacleSize *= scale;
        }

        void update(float dt, float scale)
        {
            // --- Spawning ---
            m_spawnTimer += dt;
            if (m_spawnTimer >= m_spawnInterval)
            {
                m_spawnTimer = 0.f;

                // Random X within frame, clamped so obstacle stays fully inside
                float blockCount = std::min(6, 1 + int(m_gameScore / 100));
                for (int i = 0; i < blockCount; i++) {
                    float randX = std::rand() % m_rightBoundry;
                    m_obstacles.emplace_back(m_obstacleSize, randX, 0.f, m_frame, sf::Color::Red);
                }
            }

            // --- Move & destroy ---
            for (auto it = m_obstacles.begin(); it != m_obstacles.end(); )
            {
                float speed = m_speed + int(m_gameScore / 50) * 10;
                it->setY(it->getY() + speed * dt);
                it->updatePosition();
                it->setScale(scale);
                if (it->getY() >= 100) {
                    it = m_obstacles.erase(it);
                    m_gameScore += 5;
                }
                else {
                    ++it;
                }
            }
        }

        void draw(sf::RenderWindow& window) const
        {
            for (const auto& obs : m_obstacles)
                obs.draw(window);
        }

        void setSpawnInterval(float interval) { m_spawnInterval = interval; }
        void setSpeed(float speed)            { m_speed = speed; }

        const std::vector<SquareShape>& getObstacles() const { return m_obstacles; }
};