#pragma once

#include "object.h"

namespace ge {
    class SceneSlots : Object {
    public:
        SceneSlots();

        SceneSlots(const SceneSlots &scene_slots);

        SceneSlots(SceneSlots &scene_slots);

        SceneSlots(SceneSlots &&scene_slots) noexcept;

        SceneSlots(unsigned int quantity_of_slots, const std::vector<std::string> &pictures_in_slots);

        ~SceneSlots() override = default;

        SceneSlots &operator=(const SceneSlots &scene_slots);

        SceneSlots &operator=(SceneSlots &&scene_slots) noexcept;

        bool setQuantityOfSlots(unsigned int quantity_of_slots);

        bool setPicturesInSlots(const std::vector<std::string> &pictures_in_slots);

        [[nodiscard]] unsigned int getQuantityOfSlots() const;

        const std::vector<std::string> &getPicturesInSlots();

    private:
        std::vector<sf::Sprite> getSpriteVector(const sf::Vector2u &window_size) override {
            return {}; ///TODO: реализовать
        }

        static constexpr unsigned int DEFAULT_COUNT_SLOTS = 5;
        static constexpr unsigned int UPPER_BOUND_COUNT_SLOTS = 10;
        unsigned int quantity_of_slots_;
        std::vector<std::string> pictures_in_slots_;
    };
}
