#pragma once
#include <SFML/Graphics.hpp>
#include "SquareShape.h"

class PlayerController
{
    private:
        SquareShape         m_square;
        float               m_speed;
        sf::RectangleShape* m_frame;
    public:
        PlayerController(float size, float x, float y, float speed, sf::RectangleShape* frame)
            : m_square(size, x, y, frame, sf::Color::Green), m_speed(speed), m_frame(frame)
        {}

        // getters
        SquareShape getShape()    const { return m_square; }

        void update(float dt)
        {
            float dx = 0.f, dy = 0.f;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)  || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) dx -= 1.f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) dx += 1.f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)    || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) dy -= 1.f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)  || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) dy += 1.f;

            // Normalize diagonal movement so it isn't faster
            if (dx != 0.f && dy != 0.f)
            {
                dx *= 0.7071f; // 1/sqrt(2)
                dy *= 0.7071f;
            }

            float newX = m_square.getX() + dx * m_speed * dt;
            float newY = m_square.getY() + dy * m_speed * dt;

            // Frame bounds
            float left   = 0;
            float top    = 0;
            float right  = (1 - m_square.getSize() / m_frame->getSize().x);
            float bottom = (1 - m_square.getSize() / m_frame->getSize().y);

            // Clamp to frame
            newX = std::max(left, std::min(newX, right * 99));
            newY = std::max(top, std::min(newY, bottom * 99));

            m_square.updatePosition();
            m_square.setPosition(newX, newY);
        }

        void setScale(float scale)
        {
            m_square.setScale(scale);
        }

        void draw(sf::RenderWindow& window) const { m_square.draw(window); }
};