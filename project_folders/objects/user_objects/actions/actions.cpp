#include "actions.h"

#include <utility>

void checkingCorrectness(const sf::Vector2u &coors, const sf::Vector2u &low_limits, const sf::Vector2u &high_limits) {
    if (coors.x < low_limits.x || coors.y < low_limits.y || coors.x > high_limits.x || coors.y > high_limits.y) {
        throw std::invalid_argument("the transmitted coordinates are off-screen\n");
    }
    //TODO: добавить проверку на корректность длин текстов
}

ge::Action::Action() {
    checkingCorrectness(coords_, COORS_LOW_LIMIT, COORS_HIGH_LIMIT);
}

ge::Action::Action(const Action &action)
        : coords_(action.coords_), text_(action.text_), chapter_name_to_go_(action.chapter_name_to_go_) {
    checkingCorrectness(coords_, COORS_LOW_LIMIT, COORS_HIGH_LIMIT);
}

ge::Action::Action(const sf::Vector2i &coors, std::string text, std::string chapter_name_to_go)
        : coords_(coors), text_(std::move(text)), chapter_name_to_go_(std::move(chapter_name_to_go)) {
    checkingCorrectness(coords_, COORS_LOW_LIMIT, COORS_HIGH_LIMIT);
}

ge::Action::Action(Action &action)
        : coords_(action.coords_), text_(action.text_), chapter_name_to_go_(action.chapter_name_to_go_) {
}

ge::Action::Action(Action &&action) noexcept
        : coords_(action.coords_), text_(std::move(action.text_)),
          chapter_name_to_go_(std::move(action.chapter_name_to_go_)) {
}

ge::Action &ge::Action::operator=(const Action &action) {
    coords_ = action.coords_;
    text_ = action.text_;
    chapter_name_to_go_ = action.chapter_name_to_go_;
    return *this;
}

ge::Action &ge::Action::operator=(Action &&action) noexcept {
    std::swap(coords_, action.coords_);
    text_ = std::move(action.text_);
    chapter_name_to_go_ = std::move(action.chapter_name_to_go_);
    return *this;
}


const sf::Vector2u &ge::Action::getCoords() {
    return coords_;
}

const std::string &ge::Action::getText() {
    return text_;
}

const std::string &ge::Action::getChapterNameToGo() {
    return chapter_name_to_go_;
}

bool ge::Action::setCoords(const sf::Vector2u &coords) {
    try {
        checkingCorrectness(coords, COORS_LOW_LIMIT, COORS_HIGH_LIMIT);
        coords_ = coords;
    } catch (...) {
        return false;
    }
    return true;
}

bool ge::Action::setText(const std::string &text) {
    try {
        /// TODO: проверка текста
        text_ = text;
    } catch (...) {
        return false;
    }
    return true;
}

bool ge::Action::setChapterNameToGo(const std::string &chapter_name_to_go) {
    try {
        /// TODO: проверка текста
        chapter_name_to_go_ = chapter_name_to_go;
    } catch (...) {
        return false;
    }
    return true;
}