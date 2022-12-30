#include "EntityView.h"

EntityView::EntityView(std::string filepath) {
    if (!texture.loadFromFile(filepath)) {
        throw std::invalid_argument("Could not load file for Texture");
    }

    sprite.setTexture(texture);
    sprite.setScale(SCALE, SCALE);
}

Model::Vec2 EntityView::size() { return {sprite.getLocalBounds().width, sprite.getLocalBounds().height}; }

void EntityView::face(bool left) {
    if (left) {
        sprite.setScale(-SCALE, SCALE);
        sprite.setOrigin(sprite.getLocalBounds().width, 0.f);
    } else {
        sprite.setScale(SCALE, SCALE);
        sprite.setOrigin(0.f, 0.f);
    }
}
