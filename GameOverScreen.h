#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class GameOverScreen
{
public:
    GameOverScreen(const sf::RectangleShape* frame, const std::string& fontPath)
        : m_frame(frame), m_visible(false), m_finalScore(0)
    {
        m_font.loadFromFile(fontPath);

        m_text.setFont(m_font);
        m_text.setString("GAME OVER");
        m_text.setFillColor(sf::Color::White);

        m_scoreText.setFont(m_font);
        m_scoreText.setFillColor(sf::Color(200, 200, 200));
    }

    void show(int finalScore)
    {
        m_visible    = true;
        m_finalScore = finalScore;
        m_scoreText.setString("SCORE: " + std::to_string(m_finalScore));
    }

    void hide()          { m_visible = false; }
    bool isVisible() const { return m_visible; }

    void draw(sf::RenderWindow& window)
    {
        if (!m_visible) return;

        float frameX = m_frame->getPosition().x;
        float frameY = m_frame->getPosition().y;
        float frameW = m_frame->getSize().x;
        float frameH = m_frame->getSize().y;

        float boxW = frameW * 0.60f;
        float boxH = frameH * 0.30f;        // slightly taller to fit score line
        float boxX = frameX + (frameW - boxW) / 2.f;
        float boxY = frameY + (frameH - boxH) / 2.f;

        float borderThickness = frameW * 0.015f;
        float gap             = borderThickness * 1.5f;

        // --- Outer border ---
        sf::RectangleShape outerBox(sf::Vector2f(boxW, boxH));
        outerBox.setPosition(boxX, boxY);
        outerBox.setFillColor(sf::Color::Transparent);
        outerBox.setOutlineThickness(borderThickness);
        outerBox.setOutlineColor(sf::Color::Red);

        // --- Inner border ---
        sf::RectangleShape innerBox(sf::Vector2f(boxW - gap * 2, boxH - gap * 2));
        innerBox.setPosition(boxX + gap, boxY + gap);
        innerBox.setFillColor(sf::Color(20, 20, 20, 230));
        innerBox.setOutlineThickness(borderThickness);
        innerBox.setOutlineColor(sf::Color::Red);

        // --- Game Over text ---
        float titleSize = frameW * 0.08f;
        m_text.setCharacterSize(static_cast<unsigned int>(titleSize));
        sf::FloatRect titleBounds = m_text.getLocalBounds();
        m_text.setOrigin(titleBounds.left + titleBounds.width  / 2.f,
                         titleBounds.top  + titleBounds.height / 2.f);
        m_text.setPosition(boxX + boxW / 2.f, boxY + boxH * 0.35f); // upper half

        // --- Score text ---
        float scoreSize = frameW * 0.05f;
        m_scoreText.setCharacterSize(static_cast<unsigned int>(scoreSize));
        sf::FloatRect scoreBounds = m_scoreText.getLocalBounds();
        m_scoreText.setOrigin(scoreBounds.left + scoreBounds.width  / 2.f,
                              scoreBounds.top  + scoreBounds.height / 2.f);
        m_scoreText.setPosition(boxX + boxW / 2.f, boxY + boxH * 0.68f); // lower half

        window.draw(outerBox);
        window.draw(innerBox);
        window.draw(m_text);
        window.draw(m_scoreText);
    }

private:
    const sf::RectangleShape*   m_frame;
    sf::Font                    m_font;
    sf::Text                    m_text;
    sf::Text                    m_scoreText;
    bool                        m_visible;
    int                         m_finalScore;
};