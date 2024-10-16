#pragma once

#include "non_user_objects/visualizable_objects/sfml_basis.h"

namespace ge {
    class RecentScriptSfmlBasis : public ge::SfmlBasis {
    public:
        RecentScriptSfmlBasis() = default;

        ~RecentScriptSfmlBasis() override = default;

        void draw(sf::RenderWindow &window) override;

        sf::Sprite background_sprite;
        sf::Font font;
        sf::Text title;
        std::vector<std::pair<sf::Text, sf::Text>> script_step;
        sf::RectangleShape text_background;
        sf::Text back_button;
        sf::RectangleShape back_button_background;
    };
}