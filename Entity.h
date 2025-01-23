#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Entity {
public:
	virtual void update() = 0;
	virtual sf::Drawable* getDrawable() = 0;

	virtual sf::FloatRect getBounds() {
		sf::FloatRect tempHitBox;
		return tempHitBox;
	}
	virtual float getWidth() {
		return 0.0f;
	}
	virtual float getHeight() {
		return 0.0f;
	}

	virtual void setWidth(int newWidth) {

	}
	virtual void setHeight(int newHeight) {

	}
	virtual void move(float x, float y) {

	}
	virtual sf::Vector2f getPos() {
		return sf::Vector2f(0.0f, 0.0f);
	}
	virtual void setPos(sf::Vector2f newCoords) {

	}

	virtual void setMovement(sf::Vector2f newMovement) {

	}
	virtual sf::Vector2f getMovement() {
		return sf::Vector2f(0.0f, 0.0f);
	}

	virtual int getType() {
		return 0;
	}
	// I will use Type to know what type of block that is being handled. For example the head of the snake is 0, the other parts of the snake is 1 and the fruit is 2.
	// When collisions are checked it checks if the head has collided with a type 1 or type 2, if it is a type 2 you get a point and a bigger snake, if it is a type 1 you
	// loose, because you hit youself.
};