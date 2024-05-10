#include "window_manager.h"

#include <iostream>
#include <chrono>

std::unordered_map<ge::GameMode, WindowManagerPtr> ge::WindowManager::getMap() {
    std::unordered_map<ge::GameMode, WindowManagerPtr> result;

    result[GameMode::MainMenu] = &ge::WindowManager::mainMenuManager;
    result[GameMode::MainSettings] = &ge::WindowManager::mainSettingsManager;
    result[GameMode::AboutAuthors] = &ge::WindowManager::aboutAuthorsManager;
    result[GameMode::InGame] = &ge::WindowManager::inGameManager;
    result[GameMode::RecentScript] = &ge::WindowManager::recentScriptManager;
    result[GameMode::Info] = &ge::WindowManager::infoManager;
    result[GameMode::IngameMenu] = &ge::WindowManager::ingameMenuManager;
    result[GameMode::IngameSettings] = &ge::WindowManager::ingameSettingsManager;

    return result;
}

ge::GameMode mainMenuEventHandler(sf::RenderWindow &window, ge::MainMenu &main_menu, sf::Event event) {
    switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::LostFocus:
            window.setMouseCursorVisible(true);
        case sf::Event::GainedFocus:
            window.setMouseCursorVisible(false);
        case sf::Event::KeyPressed: {
            if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
                main_menu.moveUp();
                break;
            }
            if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
                main_menu.moveDown();
                break;
            }
            if (event.key.code != sf::Keyboard::Enter) {
                break;
            }
            const unsigned int selected_button = main_menu.getSelectedButton();
            if (selected_button == 0) {
                return ge::GameMode::InGame;
            }
            if (selected_button == 2) {
                return ge::GameMode::MainSettings;
            }
            if (selected_button == 3) {
                return ge::GameMode::AboutAuthors;
            }
            if (selected_button == 4) {
                window.close();
                break;
            }
            break;
        }
        default:
            break;
    }
    return ge::GameMode::MainMenu;
}

bool ge::WindowManager::mainMenuManager(ge::VisualNovel &visual_novel, sf::RenderWindow &window,
                                        ge::DrawableElements &drawable_elements) {
    std::shared_ptr<MainMenu> main_menu = drawable_elements.getMainMenuPtr();
    if (!main_menu) {
        return false;
    }
    if (main_menu->is_rendered_) {
        sf::Event event{};
        window.waitEvent(event);
        switch (mainMenuEventHandler(window, drawable_elements.putMainMenu(), event)) {
            case GameMode::MainMenu: {
                break;
            }
            case GameMode::InGame: {
                Frame &initial_frame = visual_novel.script_.chapters_[visual_novel.getNameStartChapter()].frames_[0];
                std::shared_ptr<Scene> scene(
                        new Scene(std::make_shared<Frame>(initial_frame),
                                  visual_novel.getNameStartChapter(),
                                  0));

                drawable_elements.setScene(scene);
                visual_novel.current_game_mode_ = GameMode::InGame;
                return true;
            }
            case GameMode::MainSettings: {
                if (!drawable_elements.getSettingsPtr()) {
                    std::shared_ptr<Settings> settings(new Settings);
                    drawable_elements.setSettings(settings);
                }
                visual_novel.current_game_mode_ = GameMode::MainSettings;
                return true;
            }
            case GameMode::AboutAuthors: {
                if (!drawable_elements.getAboutAuthorsPtr()) {
                    std::shared_ptr<AboutAuthors> about_authors(new AboutAuthors);
                    about_authors->setText(visual_novel.about_authors_);
                    drawable_elements.setAboutAuthors(about_authors);
                }
                visual_novel.current_game_mode_ = GameMode::AboutAuthors;
                return true;
            }
            default:
                return false;
        }
    }
    window.clear();
    if (!main_menu->renderSfmlBasis(window.getSize())) {
        return false;
    }
    main_menu->getSfmlBasis()->draw(window);
    return true;
}

ge::GameMode inGameEventHandler(sf::RenderWindow &window, ge::Scene &scene, sf::Event event) {
    switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::LostFocus:
            window.setMouseCursorVisible(true);
        case sf::Event::GainedFocus:
            window.setMouseCursorVisible(false);
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
                scene.moveUp();
                break;
            }
            if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
                scene.moveDown();
                break;
            }
            if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
                scene.moveLeft();
                break;
            }
            if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
                scene.moveRight();
                break;
            }
            if (event.key.code == sf::Keyboard::Escape) {
                return ge::GameMode::MainMenu;
            }
            if (event.key.code != sf::Keyboard::Enter) {
                break;
            }
            if (scene.getSelectedRow() == scene.ROW_ACTION_OR_DIALOGUE && scene.getChoiceOfActions()) {
                //TODO: переход по действию
                break;
            }
            if (scene.getSelectedRow() == scene.ROW_ACTION_OR_DIALOGUE) {
                //TODO: далее
                break;
            }
            if (scene.getSelectedColumn() == scene.COLUMN_MENU) {
                //return ge::GameMode::IngameMenu;
                return ge::GameMode::MainMenu;
            }
            if (scene.getSelectedColumn() == scene.COLUMN_SETTINGS) {
                //return ge::GameMode::IngameSettings;
                break;
            }
            if (scene.getSelectedColumn() == scene.COLUMN_INFO) {
                //return ge::GameMode::Info;
                break;
            }
            break;
        default:
            break;
    }
    return ge::GameMode::InGame;
}

bool ge::WindowManager::inGameManager(ge::VisualNovel &visual_novel, sf::RenderWindow &window,
                                      ge::DrawableElements &drawable_elements) {
    std::shared_ptr<Scene> scene = drawable_elements.getScenePtr();
    if (!scene) {
        return false;
    }
    if (scene->is_rendered_) {
        sf::Event event{};
        window.waitEvent(event);
        switch (inGameEventHandler(window, drawable_elements.putScene(), event)) {
            case GameMode::InGame: {
                break;
            }
            case GameMode::MainMenu: {
                drawable_elements.resetScene();
                visual_novel.current_game_mode_ = GameMode::MainMenu;
                return true;
            }
            case GameMode::IngameMenu:
                // TODO : реализовать
                return true;
            case GameMode::IngameSettings:
                // TODO : реализовать
                return true;
            case GameMode::Info:
                // TODO : реализовать
                return true;
            default:
                return false;
        }
    }
    window.clear();
    if (scene->is_waiting_new_frame_) {
        scene->setNewFrame(std::make_shared<Frame>(
                visual_novel.script_.chapters_[scene->current_chapter_name_].frames_[scene->current_frame_number_]));
    }
    scene->renderSfmlBasis(window.getSize());
    scene->getSfmlBasis()->draw(window);
    return true;
}

ge::GameMode aboutAuthorsHandler(sf::RenderWindow &window, ge::AboutAuthors &about_authors, sf::Event event) {
    switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::LostFocus:
            window.setMouseCursorVisible(true);
        case sf::Event::GainedFocus:
            window.setMouseCursorVisible(false);
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Escape) {
                return ge::GameMode::MainMenu;
            }
            break;
        default:
            break;
    }
    return ge::GameMode::AboutAuthors;
}

bool ge::WindowManager::aboutAuthorsManager(ge::VisualNovel &visual_novel, sf::RenderWindow &window,
                                            ge::DrawableElements &drawable_elements) {
    std::shared_ptr<AboutAuthors> about_authors = drawable_elements.getAboutAuthorsPtr();
    if (!about_authors) {
        return false;
    }
    if (about_authors->is_rendered_) {
        sf::Event event{};
        window.waitEvent(event);
        switch (aboutAuthorsHandler(window, drawable_elements.putAboutAuthors(), event)) {
            case GameMode::MainMenu: {
                visual_novel.current_game_mode_ = GameMode::MainMenu;
                break;
            }
            case GameMode::AboutAuthors:
                break;
            default:
                break;
        }
    }
    window.clear();
    if (!about_authors->renderSfmlBasis(window.getSize())) {
        return false;
    }
    about_authors->getSfmlBasis()->draw(window);
    return true;
}


ge::GameMode settingsHandler(sf::RenderWindow &window, ge::Settings &settings, sf::Event event) {
    switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::LostFocus:
            window.setMouseCursorVisible(true);
        case sf::Event::GainedFocus:
            window.setMouseCursorVisible(false);
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Escape) {
                return ge::GameMode::MainMenu;
            }
            if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
                settings.moveUp();
                break;
            }
            if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
                settings.moveDown();
                break;
            }
            if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
                settings.moveLeft();
                break;
            }
            if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
                settings.moveRight();
                break;
            }
        default:
            break;
    }
    return ge::GameMode::MainSettings;
}

bool ge::WindowManager::mainSettingsManager(ge::VisualNovel &visual_novel, sf::RenderWindow &window,
                                            ge::DrawableElements &drawable_elements) {
    std::shared_ptr<Settings> settings = drawable_elements.getSettingsPtr();
    if (!settings) {
        return false;
    }
    if (settings->is_rendered_) {
        sf::Event event{};
        window.waitEvent(event);
        switch (settingsHandler(window, drawable_elements.putSettings(), event)) {
            case GameMode::MainSettings:
                break;
            case GameMode::MainMenu: {
                visual_novel.current_game_mode_ = GameMode::MainMenu;
                return true;
            }
            default:
                return false;
        }
    }
    window.clear();
    if (!settings->renderSfmlBasis(window.getSize())) {
        return false;
    }
    settings->getSfmlBasis()->draw(window);
    return true;
}