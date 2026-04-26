#include "UI.h"
#include "gameglobale.h"
#include <string>

const sf::Color PLAYER_COLORS[2] = {
    sf::Color(80,  160, 255),
    sf::Color(255, 90,  90 )
};

const float BAR_WIDTH  = 200.f;
const float BAR_HEIGHT = 22.f;
const float BAR_Y      = 20.f;

static sf::Font g_font;
static bool     g_fontLoaded = false;

static void loadFont()
{
    if (g_fontLoaded) return;
    if      (g_font.openFromFile("assets/arial.ttf")) g_fontLoaded = true;
    else if (g_font.openFromFile("arial.ttf"))        g_fontLoaded = true;
}

static float getBarX(int index)
{
    return (index == 0) ? 40.f : (1600.f - BAR_WIDTH - 40.f);
}

static void drawSingleHealthBar(sf::RenderWindow& window, int index, int hp, int maxHp)
{
    float xPos = getBarX(index);

    sf::RectangleShape bgBar({BAR_WIDTH, BAR_HEIGHT});
    bgBar.setPosition({xPos, BAR_Y});
    bgBar.setFillColor(sf::Color(30, 30, 30));
    bgBar.setOutlineColor(sf::Color(100, 100, 100));
    bgBar.setOutlineThickness(1.5f);
    window.draw(bgBar);

    float ratio = (maxHp > 0) ? ((float)hp / maxHp) : 0.f;
    if (ratio < 0.f) ratio = 0.f;
    if (ratio > 1.f) ratio = 1.f;

    sf::Color barColor;
    if      (ratio > 0.60f) barColor = sf::Color(50,  200, 50);
    else if (ratio > 0.30f) barColor = sf::Color(230, 160, 20);
    else                    barColor = sf::Color(200, 40,  40);

    if (ratio > 0.f)
    {
        sf::RectangleShape fgBar({BAR_WIDTH * ratio, BAR_HEIGHT});
        fgBar.setPosition({xPos, BAR_Y});
        fgBar.setFillColor(barColor);
        window.draw(fgBar);
    }

    sf::RectangleShape border({BAR_WIDTH, BAR_HEIGHT});
    border.setPosition({xPos, BAR_Y});
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineColor(sf::Color(200, 200, 200));
    border.setOutlineThickness(1.5f);
    window.draw(border);

    loadFont();
    if (g_fontLoaded)
    {
        std::string labels[2] = {"P1", "P2"};

        sf::Text nameText(g_font);
        nameText.setString(labels[index]);
        nameText.setCharacterSize(14);
        nameText.setFillColor(PLAYER_COLORS[index]);
        nameText.setStyle(sf::Text::Bold);
        nameText.setPosition({xPos, BAR_Y - 20.f});
        window.draw(nameText);

        int hpVal = (hp < 0) ? 0 : hp;
        sf::Text hpText(g_font);
        hpText.setString(std::to_string(hpVal));
        hpText.setCharacterSize(12);
        hpText.setFillColor(sf::Color::White);
        auto tb = hpText.getLocalBounds();
        hpText.setOrigin({tb.size.x / 2.f, tb.size.y / 2.f});
        hpText.setPosition({xPos + BAR_WIDTH / 2.f, BAR_Y + BAR_HEIGHT / 2.f - 2.f});
        window.draw(hpText);
    }
}

void drawHealthBars(sf::RenderWindow& window, Player players[])
{
    for (int i = 0; i < MAX_PLAYERS; i++)
    {
        int displayHp = players[i].isAlive ? players[i].health : 0;
        drawSingleHealthBar(window, i, displayHp, players[i].maxHealth);

        if (!players[i].isAlive)
        {
            loadFont();
            if (g_fontLoaded)
            {
                sf::Text deadText(g_font);
                deadText.setString("DEAD");
                deadText.setCharacterSize(12);
                deadText.setFillColor(sf::Color(180, 50, 50));
                deadText.setStyle(sf::Text::Bold);
                auto db = deadText.getLocalBounds();
                deadText.setOrigin({db.size.x / 2.f, db.size.y / 2.f});
                deadText.setPosition({getBarX(i) + BAR_WIDTH / 2.f, BAR_Y + BAR_HEIGHT / 2.f - 2.f});
                window.draw(deadText);
            }
        }
    }
}

void drawWinScreen(sf::RenderWindow& window, int winnerIndex)
{
    sf::RectangleShape overlay({1600.f, 900.f});
    overlay.setFillColor(sf::Color(0, 0, 0, 170));
    window.draw(overlay);

    loadFont();
    if (!g_fontLoaded) return;

    std::string msgs[2] = {"Player 1 Wins!", "Player 2 Wins!"};

    sf::Text winText(g_font);
    winText.setString(msgs[winnerIndex]);
    winText.setCharacterSize(72);
    winText.setFillColor(PLAYER_COLORS[winnerIndex]);
    winText.setStyle(sf::Text::Bold);
    auto wb = winText.getLocalBounds();
    winText.setOrigin({wb.size.x / 2.f, wb.size.y / 2.f});
    winText.setPosition({800.f, 420.f});
    window.draw(winText);

    sf::Text subText(g_font);
    subText.setString("Press R to Restart");
    subText.setCharacterSize(26);
    subText.setFillColor(sf::Color(200, 200, 200));
    auto sb = subText.getLocalBounds();
    subText.setOrigin({sb.size.x / 2.f, sb.size.y / 2.f});
    subText.setPosition({800.f, 520.f});
    window.draw(subText);
}

void drawPauseScreen(sf::RenderWindow& window)
{
    sf::RectangleShape overlay({1600.f, 900.f});
    overlay.setFillColor(sf::Color(0, 0, 0, 130));
    window.draw(overlay);

    loadFont();
    if (!g_fontLoaded) return;

    sf::Text pauseText(g_font);
    pauseText.setString("PAUSED");
    pauseText.setCharacterSize(80);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setStyle(sf::Text::Bold);
    auto pb = pauseText.getLocalBounds();
    pauseText.setOrigin({pb.size.x / 2.f, pb.size.y / 2.f});
    pauseText.setPosition({800.f, 420.f});
    window.draw(pauseText);

    sf::Text resumeText(g_font);
    resumeText.setString("Press ESC to Resume");
    resumeText.setCharacterSize(24);
    resumeText.setFillColor(sf::Color(180, 180, 180));
    auto rb = resumeText.getLocalBounds();
    resumeText.setOrigin({rb.size.x / 2.f, rb.size.y / 2.f});
    resumeText.setPosition({800.f, 520.f});
    window.draw(resumeText);
}

void drawCountdown(sf::RenderWindow& window, int count)
{
    loadFont();
    if (!g_fontLoaded) return;

    std::string txt;
    sf::Color   col;

    if      (count == 3) { txt = "3";      col = sf::Color(255, 80,  80); }
    else if (count == 2) { txt = "2";      col = sf::Color(255, 180, 50); }
    else if (count == 1) { txt = "1";      col = sf::Color(80,  220, 80); }
    else                 { txt = "FIGHT!"; col = sf::Color(255, 255, 80); }

    sf::Text cdText(g_font);
    cdText.setString(txt);
    cdText.setCharacterSize((count == 0) ? 90 : 120);
    cdText.setFillColor(col);
    cdText.setStyle(sf::Text::Bold);
    auto cb = cdText.getLocalBounds();
    cdText.setOrigin({cb.size.x / 2.f, cb.size.y / 2.f});
    cdText.setPosition({800.f, 400.f});
    window.draw(cdText);
}