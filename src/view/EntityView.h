#ifndef INC_2022_PROJECT_ACHRAFYNDZ_ENITITYVIEW_H
#define INC_2022_PROJECT_ACHRAFYNDZ_ENITITYVIEW_H

#include <memory>

#include "../controller/Game.h"
#include "../model/Camera.h"
#include "../model/ObserverPattern.h"
#include "../util/floatVector2.h"

#include <iostream>

#include <SFML/Graphics.hpp>


class EntityView : public Model::Observer {
private:
    sf::Texture texture;
    sf::Sprite sprite;

public:
    explicit EntityView(const std::string& filepath);
    ~EntityView() override = default;

    void update(float x, float y, std::shared_ptr<Model::Camera> camera, bool facingLeft) override {
        if (camera->entityIsVisible(y)) {
            sprite.setPosition(x, y);
            face(facingLeft);
            Controller::Game::getWindow()->draw(sprite);
        }
    }

    floatVector2 size();

    void face(bool left);
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_ENITITYVIEW_H
