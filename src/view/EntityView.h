#ifndef INC_2022_PROJECT_ACHRAFYNDZ_ENITITYVIEW_H
#define INC_2022_PROJECT_ACHRAFYNDZ_ENITITYVIEW_H

#include <memory>

#include <SFML/Graphics.hpp>

class EntityView {
public:
	EntityView();
	virtual ~EntityView() {  }

	void draw(sf::Sprite s);
};

#endif // INC_2022_PROJECT_ACHRAFYNDZ_ENITITYVIEW_H
