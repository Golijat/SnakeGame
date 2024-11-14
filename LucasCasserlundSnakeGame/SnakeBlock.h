#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Entity.h"

class SnakeBlock : public Entity {
public:
	SnakeBlock(sf::Vector2f const& position, float width, float height, sf::Color Color, int type)
		: rectShape(sf::Vector2f(width, height)) {
		rectShape.setPosition(position);
		rectShape.setOrigin(width / 2.f, height / 2.f);
		rectShape.setFillColor(Color);
		Width = width;
		Height = height;
		Type = type;

	}

	virtual float getWidth() {
		return Width;
	}

	virtual float getHeight() {
		return Height;
	}

	virtual void setWidth(int newWidth) {
		Width = newWidth;
		rectShape.setSize(sf::Vector2f(Width, Height));
		rectShape.setOrigin(Width / 2.f, Height / 2.f);
	}

	virtual void setHeight(int newHeight) {
		Height = newHeight;
		rectShape.setSize(sf::Vector2f(Width, Height));
		rectShape.setOrigin(Width / 2.f, Height / 2.f);
	}

	virtual void update() {
		rectShape.move(_Movement);
		//rectShape.move(sf::Vector2f(Movement.x, Movement.y + BaseSpeed.y));
	};
	virtual sf::Drawable* getDrawable() {
		return &rectShape;
	};
	virtual sf::FloatRect getBounds() {
		sf::FloatRect ShapeEntityHitbox = rectShape.getGlobalBounds();
		return ShapeEntityHitbox;
	}

	virtual sf::Vector2f getPos() {
		return rectShape.getPosition();
	}
	virtual void setPos(sf::Vector2f newCoords) {
		rectShape.setPosition(newCoords);
	}

	virtual void move(float x, float y) {
		rectShape.move(x, y);
	}

	virtual void setMovement(sf::Vector2f newMovement) {
		_Movement = newMovement;
	}
	virtual sf::Vector2f getMovement() {
		return _Movement;
	}

	virtual int getType() {
		return Type;
	}

private:
	sf::RectangleShape rectShape;
	int colorNum = 0;
	std::string Name;
	float Width;
	float Height;
	sf::Vector2f _Movement;
	sf::Vector2f _BaseSpeed;
	int Type;
};