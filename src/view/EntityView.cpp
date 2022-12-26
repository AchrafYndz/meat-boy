#include "EntityView.h"
#include "../controller/Game.h"
#include "../model/World.h"

#include <iostream>

#include <SFML/Graphics.hpp>

EntityView::EntityView(std::string filepath)
{
	texture.loadFromFile(filepath);

	sprite.setTexture(texture);
	sprite.setScale(SCALE, SCALE);
}

Vec2 EntityView::size()
{
	return Vec2(sprite.getLocalBounds().width, sprite.getLocalBounds().height);
}

void EntityView::face(bool left)
{
	if (left) {
		sprite.setScale(-SCALE, SCALE);
		sprite.setOrigin(sprite.getLocalBounds().width, 0.f);
	}
	else {
		sprite.setScale(SCALE, SCALE);
		sprite.setOrigin(0.f, 0.f);
	}
}
