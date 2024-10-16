#pragma once

#include "non_user_objects/visualizable_objects/visualizable.h"
#include "about_authors_sfml_basis.h"
#include "cache_manager.h"

namespace ge {
    class AboutAuthors : public Visualizable {
    public:
        AboutAuthors() = default;

        AboutAuthors(const AboutAuthors &about_authors);

        AboutAuthors(AboutAuthors &about_authors);

        AboutAuthors(AboutAuthors &&about_authors) noexcept;

        explicit AboutAuthors(std::wstring text);

        ~AboutAuthors() override = default;

        AboutAuthors &operator=(const AboutAuthors &about_authors);

        AboutAuthors &operator=(AboutAuthors &&about_authors) noexcept;

        void setText(const std::wstring &text);

        void setBackground(const std::string &background);

        const std::string &getBackground();

        void setTitle(const std::wstring &title);

    private:
        friend class WindowManager;

        bool renderSfmlBasis(const sf::Vector2u &window_size) override;

        void clearSfmlBasis() override;

        std::shared_ptr<SfmlBasis> getSfmlBasis() override;

        bool is_rendered_ = false;
        std::wstring title_ = L"ОБ АВТОРАХ";
        std::wstring text_;
        const std::wstring BACK_BUTTON_TEXT = L"Назад";
        std::string background_;
        std::shared_ptr<AboutAuthorsSfmlBasis> sfml_basis_ = nullptr;
        const sf::Color BACKGROUND_FILL_COLOR = sf::Color(66, 84, 127, 160);
        const sf::Color HIGHLIGHT_COLOR = sf::Color(229,228,226);
    };
}