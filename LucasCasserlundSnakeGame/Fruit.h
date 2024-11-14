#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Entity.h"

class Fruit : public Entity {
public:
	Fruit(sf::Vector2f const& position, float width, float height, int type)
		: rectShape(sf::Vector2f(width, height)) {
		rectShape.setPosition(position);
		rectShape.setOrigin(width / 2.f, height / 2.f);
		rectShape.setFillColor(sf::Color::Red);
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
		rectShape.move(sf::Vector2f(Speed.x, Speed.y + BaseSpeed.y));
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

	virtual int getType() {
		return Type;
	}

private:
	sf::RectangleShape rectShape;
	int colorNum = 0;
	std::string Name;
	float Width;
	float Height;
	sf::Vector2f Speed;
	sf::Vector2f BaseSpeed;
	int Type;
};