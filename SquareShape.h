#pragma once
#include <SFML/Graphics.hpp>

class SquareShape
{
    private:
        float                m_x, m_y, relative_x, relative_y;
        sf::RectangleShape   m_shape;
        sf::RectangleShape*  m_frame;
    public:
        SquareShape(float size, float x, float y, sf::RectangleShape* frame, sf::Color color)
            : m_x(x), m_y(y), m_frame(frame)
        {
            m_shape.setSize(sf::Vector2f(size, size));
            m_shape.setFillColor(color);
            m_shape.setPosition(m_x, m_y);
        }

        // Getters
        float           getX()     const { return m_x; }
        float           getY()     const { return m_y; }
        sf::Color       getColor() const { return m_shape.getFillColor(); }
        float           getSize()  const { return m_shape.getSize().x; }

        float           getAbsX()     const { return m_shape.getPosition().x; }
        float           getAbsY()     const { return m_shape.getPosition().y; }

        // Setters
        void setX(float x)
        {
            m_x = x;
            relative_x = m_frame->getPosition().x + m_frame->getSize().x * x/100;
            m_shape.setPosition(relative_x, relative_y);
        }

        void setY(float y)
        {
            m_y = y;
            relative_y = m_frame->getPosition().y + m_frame->getSize().y * y/100;
            m_shape.setPosition(relative_x, relative_y);
        }

        void setPosition(float x, float y)
        {
            m_x = x;
            m_y = y;
            relative_x = m_frame->getPosition().x + m_frame->getSize().x * x / 100;
            relative_y = m_frame->getPosition().y + m_frame->getSize().y * y / 100;
            m_shape.setPosition(relative_x, relative_y);
        }

        void setColor(sf::Color color)
        {
            m_shape.setFillColor(color);
        }

        void setScale(float scale)
        {
            float currW = m_shape.getSize().x;
            float currH = m_shape.getSize().y;
            sf::Vector2f newSize(currW * scale, currH * scale);
            m_shape.setSize(newSize);
        }

        void updatePosition()
        {
            setPosition(m_x, m_y);
        }

        // Draw to any render target
        void draw(sf::RenderWindow& window) const
        {
            window.draw(m_shape);
        }

        inline bool isColliding(SquareShape shape)
        {
            bool x1 = getAbsX() < shape.getAbsX() + shape.getSize();
            bool x2 = getAbsX() + getSize() > shape.getAbsX();
            bool y1 = getAbsY() < shape.getAbsY() + shape.getSize();
            bool y2 = getAbsY() + getSize() > shape.getAbsY();

            return x1 && x2 && y1 && y2;
        }
};