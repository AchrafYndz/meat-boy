#include "EntityView.h"
#include "../controller/Game.h"

#include <iostream>

#include <SFML/Graphics.hpp>

EntityView::EntityView()
{

}

void EntityView::draw(sf::Sprite s)
{
	Game::getWindow()->draw(s);
}