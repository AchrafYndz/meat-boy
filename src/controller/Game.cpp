#include "Game.h"
#include "../model/Player.h"
#include "StateManager.h"

#include <sstream>

sf::RenderWindow Controller::Game::window;

Controller::Game::Game() {
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Meat Boy");

    if (!gameFont.loadFromFile("resources/fonts/meat-boy-font.ttf")) {
        throw std::invalid_argument("Could not load game font");
    }
    text.setFont(gameFont);

    if (!backgroundTexture.loadFromFile("resources/textures/background.png")) {
        throw std::invalid_argument("Could not load background texture");
    }
    backgroundSprite.setTexture(backgroundTexture);

    const float scaleFactor = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(backgroundTexture.getSize().x);
    backgroundSprite.setScale(scaleFactor, scaleFactor);

    if (!menuBackgroundTexture.loadFromFile("resources/textures/menu_background.png")) {
        throw std::invalid_argument("Could not load background texture");
    }
    menuBackgroundSprite.setTexture(menuBackgroundTexture);

    const float menuScaleFactor = static_cast<float>(WINDOW_HEIGHT) / static_cast<float>(menuBackgroundTexture.getSize().y);
    menuBackgroundSprite.setScale(menuScaleFactor, menuScaleFactor);

    stateManager = std::make_shared<StateManager>();

    camera = std::make_shared<Model::Camera>();

    world = std::make_shared<Model::World>();
}

void Controller::Game::run() {
    std::shared_ptr<Utility::Stopwatch> stopwatch = Utility::Stopwatch::getInstance();
    while (window.isOpen()) {
        if (stopwatch->timeSinceLastUpdate() > TIME_PER_FRAME) {
            stopwatch->reset();
            window.clear();
            process();
            render();
            window.display();
        }
    }
}

void Controller::Game::process() {
    if (stateManager->isInMenuState()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                handleMenuInput(event.key.code);
                break;
            default:
                break;
            }
        }
    } else {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                stateManager->goToMenu();
            else if (event.type == sf::Event::Closed)
                window.close();
        }

        std::shared_ptr<Model::Player> player = world->getPlayer();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player->buttonAction(player->KeyEnum::left, true);
        else
            player->buttonAction(player->KeyEnum::left, false);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player->buttonAction(player->KeyEnum::right, true);
        else
            player->buttonAction(player->KeyEnum::right, false);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            player->buttonAction(player->KeyEnum::space, true);
        else
            player->buttonAction(player->KeyEnum::space, false);

        // WIN STATE -> go to next Level or Main Menu if it's the last Level
        if (player->hasReachedGoal()) {
            if (selectedLevel == 3)
                stateManager->goToMenu();
            else {
                selectedLevel++;
                world->loadLevel(selectedLevel, stateManager, camera);
            }
        }
        // DIE -> reload Level
        else if (!camera->entityIsVisible(camera->toPixels(player->getPosition()).y)) {
            world->loadLevel(selectedLevel, stateManager, camera);
        }
    }
}

void Controller::Game::render() {
    if (stateManager->isInMenuState()) {
        window.draw(menuBackgroundSprite);

        const float windowWidth = static_cast<float>(window.getSize().x);
        // draw the game title
        text.setCharacterSize(static_cast<int>(400 * SCALE));
        text.setString("Meat Boy");
        text.setFillColor(sf::Color(96, 05, 00));
        const float textWidth = text.getLocalBounds().width;
        text.setPosition(sf::Vector2f(windowWidth / 2.0f - textWidth / 2.0f, 10));

        // reposition View (for when we went from Level to Main Menu)
        sf::View view = window.getView();
        view.setCenter(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);
        window.setView(view);

        window.draw(text);

        // draw level selection
        for (int i = 1; i <= totalLevels; i++) {
            text.setString("Level " + std::to_string(i));
            text.setFillColor(i == selectedLevel ? sf::Color(210, 70, 70) : sf::Color(41, 27, 23));
            const float textWidth = text.getLocalBounds().width;
            text.setPosition(sf::Vector2f(windowWidth / 2.0f - textWidth / 2.0f, 120.0f + (static_cast<float>(i) * 80.0f)));
            window.draw(text);
        }
    } else {
        window.draw(Game::backgroundSprite);
        world->update(camera);
        camera->update(world->getPlayer(), stateManager);

        float cameraCenter = camera->getCameraHeight();
        sf::View v = window.getView();
        v.setCenter(WINDOW_WIDTH / 2.f, cameraCenter);
        window.setView(v);
    }
}

void Controller::Game::handleMenuInput(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::W || key == sf::Keyboard::Up) {
        if (selectedLevel > 1) {
            selectedLevel--;
        } else {
            selectedLevel = 1;
        }
    } else if (key == sf::Keyboard::S || key == sf::Keyboard::Down) {
        if (selectedLevel < totalLevels)
            selectedLevel++;
    } else if (key == sf::Keyboard::Enter) {
        world->loadLevel(selectedLevel, stateManager, camera);
    }
}