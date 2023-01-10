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
    /**
     * The EntityView class is an observer that handles the visual representation of the entities.
     */
private:
    sf::Texture texture;
    sf::Sprite sprite;

public:
    /**
     *  Constructor for the EntityView class
     *
     *  @param filepath path to the image file to use for the sprite
     */
    explicit EntityView(const std::string& filepath);

    /**
     * Default Destructor of the EntityView class
     */
    ~EntityView() override = default;

    /**
     * updates the position and orientation of the EntityView
     *
     * @param x x-coordinate of the Entity position
     * @param y y-coordinate of the entities position
     * @param camera
     * @param facingLeft true if facing left, false otherwise
     *
     */
    void update(float x, float y, std::shared_ptr<Model::Camera> camera, bool facingLeft) override {
        if (camera->entityIsVisible(y)) {
            sprite.setPosition(x, y);
            faceLeft(facingLeft);
            Controller::Game::getWindow()->draw(sprite);
        }
    }

    /**
     * returns the size of the sprite
     *
     * @return floatVector2 object representing the width and height of the sprite
     *
     */
    floatVector2 getSize();

    /**
     * sets the EntitiesView's orientation based on the provided parameter
     *
     * @param left whether or not the sprite should faceLeft left
     */
    void faceLeft(bool left);
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_ENITITYVIEW_H
