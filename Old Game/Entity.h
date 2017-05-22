#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>

class Entity
{
public:
	Entity();
	~Entity();

	sf::RectangleShape body;
	sf::Sprite sprite;
	sf::Text text;
};

#endif