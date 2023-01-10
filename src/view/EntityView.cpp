#include "EntityView.h"

EntityView::EntityView(const std::string& filepath) {
    if (!texture.loadFromFile(filepath)) {
        throw std::invalid_argument("Could not load file for Texture");
    }

    sprite.setTexture(texture);
    sprite.setScale(SCALE, SCALE);
}

floatVector2 EntityView::getSize() { return {sprite.getLocalBounds().width, sprite.getLocalBounds().height}; }

void EntityView::faceLeft(bool left) {
    if (left) {
        sprite.setScale(-SCALE, SCALE);
        sprite.setOrigin(sprite.getLocalBounds().width, 0.f);
    } else {
        sprite.setScale(SCALE, SCALE);
        sprite.setOrigin(0.f, 0.f);
    }
}
