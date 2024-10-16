#pragma once

#include "non_user_objects/visualizable_objects/sfml_basis.h"

namespace ge {
    class SettingsSfmlBasis : public ge::SfmlBasis {
    public:
        SettingsSfmlBasis() = default;

        ~SettingsSfmlBasis() override = default;

        void draw(sf::RenderWindow &window) override;

        sf::Sprite background_sprite;
        sf::Font font;
        sf::Text title;
        sf::RectangleShape parameters_background;
        std::vector<sf::Text> parameters;
        std::vector<std::vector<sf::Text> > arrow_switches;
        sf::Text back_button;
        sf::RectangleShape back_button_background;
    };
}