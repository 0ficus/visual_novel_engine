#pragma once

#include "non_user_objects/visualizable_objects/sfml_basis.h"

namespace ge {
    class AboutAuthorsSfmlBasis : public ge::SfmlBasis {
    public:
        AboutAuthorsSfmlBasis() = default;

        ~AboutAuthorsSfmlBasis() override = default;

        void draw(sf::RenderWindow &window) override;

        sf::Sprite background_sprite;
        sf::Font font;
        sf::Text title;
        sf::Text text;
        sf::RectangleShape text_background;
        sf::Text back_button;
        sf::RectangleShape back_button_background;
    };
}