#ifndef INC_2022_PROJECT_ACHRAFYNDZ_ENITITYVIEW_H
#define INC_2022_PROJECT_ACHRAFYNDZ_ENITITYVIEW_H

#include <memory>

#include "../controller/Game.h"
#include "../model/Camera.h"
#include "../model/ObserverPattern.h"

#include <iostream>

#include <SFML/Graphics.hpp>

struct Vec2;

class EntityView : public Model::Observer {
private:
    sf::Texture texture;
    sf::Sprite sprite;

public:
    explicit EntityView(const std::string& filename);
    ~EntityView() override = default;

    void update(float x, float y, std::shared_ptr<Model::Camera> camera, bool facingLeft) override {
        if (camera->entityIsVisible(y)) {
            sprite.setPosition(x, y);
            face(facingLeft);
            Controller::Game::getWindow()->draw(sprite);
        }
    }

    Model::Vec2 size();

    void face(bool left);
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_ENITITYVIEW_H
