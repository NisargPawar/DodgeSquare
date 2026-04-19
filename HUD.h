#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class HUD
{
    private:
        const sf::RectangleShape*   m_frame;
        sf::Font                    m_font;
        sf::Text                    m_scoreText;

    public:
        HUD(const sf::RectangleShape* frame, const std::string& fontPath)
            : m_frame(frame)
        {
            m_font.loadFromFile(fontPath);
            m_scoreText.setFont(m_font);
            m_scoreText.setFillColor(sf::Color::White);
        }

        void draw(sf::RenderWindow& window, int score)
        {
            float frameX = m_frame->getPosition().x;
            float frameY = m_frame->getPosition().y;
            float frameW = m_frame->getSize().x;

            float fontSize = frameW * 0.06f;
            m_scoreText.setCharacterSize(static_cast<unsigned int>(fontSize));
            m_scoreText.setString("SCORE: " + std::to_string(score));

            // Center horizontally at top of frame with small padding
            sf::FloatRect bounds = m_scoreText.getLocalBounds();
            m_scoreText.setOrigin(bounds.left + bounds.width / 2.f, bounds.top);
            m_scoreText.setPosition(frameX + frameW / 2.f, frameY + frameW * 0.03f);

            window.draw(m_scoreText);
        }
};