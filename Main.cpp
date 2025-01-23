#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.h"
#include "SnakeBlock.h"
#include "Fruit.h"

void newFruitPos(Fruit* Fruit, std::vector<SnakeBlock*> snakeBlocks);

int main() {

	sf::RenderWindow window(sf::VideoMode(800, 600), "The Snake Game!");

	// 800 / 20 = 40
	// 600 / 20 = 30
	// The snake blocks are 20x20, therefore i want a grid that is also 20x20 in the game.
	// When randomly placing the fruit the coordinates will be a random number between 0 - 30, or 0 - 40 times twenty.

	std::vector<sf::Vector2f> snakeBlocksCoords;
	std::vector<SnakeBlock*> snakeBlocks;

	snakeBlocksCoords.push_back(sf::Vector2f(100, 100));
	snakeBlocksCoords.push_back(sf::Vector2f(80, 100));
	snakeBlocksCoords.push_back(sf::Vector2f(60, 100));
	snakeBlocksCoords.push_back(sf::Vector2f(40, 100));
	snakeBlocksCoords.push_back(sf::Vector2f(20, 100));
	snakeBlocksCoords.push_back(sf::Vector2f(0, 100));


	snakeBlocks.push_back(new SnakeBlock(sf::Vector2f(100, 100), 20, 20, sf::Color::Blue, 0));
	snakeBlocks[0]->setMovement(sf::Vector2f(20.0f, 0.0f));
	snakeBlocks.push_back(new SnakeBlock(sf::Vector2f(80, 100), 20, 20, sf::Color::Green, 1));
	snakeBlocks.push_back(new SnakeBlock(sf::Vector2f(60, 100), 20, 20, sf::Color::Green, 1));
	snakeBlocks.push_back(new SnakeBlock(sf::Vector2f(40, 100), 20, 20, sf::Color::Green, 1));
	snakeBlocks.push_back(new SnakeBlock(sf::Vector2f(20, 100), 20, 20, sf::Color::Green, 1));
	snakeBlocks.push_back(new SnakeBlock(sf::Vector2f(0, 100), 20, 20, sf::Color::Green, 1));

	Fruit TheFruit = Fruit(sf::Vector2f(400, 400), 20, 20, 1);

	// Used for handling the coordinates for all the snake blocks.
	// Records the coordinates of a block so that the block after it can copy those coords and so on.
	sf::Vector2f previousCoords;

	// Is used for updating the coordinates for all snake blocks.
	// It is used as the i in snakeBlocksCoords[i], so that the code knows what
	// coordinates in the list to use.
	int count;

	// A clock that i used for handling the movement of the snake. 
	sf::Clock clock;

	// This variable is used togheter with the clock. An if statement checks if the time passed is greater than timeForMovement. Each time a fruit is eaten the timeForMovement will become smaller, making the snake go faster.
	float timeForMovement = 0.49f;

	// Creates the text used for showing the amount of points the player has.
	sf::Text text;
	// A variable to keep track of how many points the player has.
	int amountOfPoints = 0;

	bool isPaused = false;
	bool hasLost = false;

	sf::Font font;
	// Loads the ubunut font.
	if (!font.loadFromFile("assets/fonts/ubuntu-mono.ttf"))
	{
		return EXIT_FAILURE;
	}
	text.setFont(font);
	//Sets the text to show the points of the players.
	text.setString(std::to_string(amountOfPoints));
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	text.setPosition(30.0f, 10.0f);

	// For the point sound
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("assets/sounds/pointSound.mp3")) {
		return -1;
	};
	sf::Sound sound;
	sound.setBuffer(buffer);

	// For the background music
	sf::Music music;
	if (!music.openFromFile("assets/sounds/backgroundMusic.mp3")) {
		return -1;
	}
	music.setVolume(50.0f);
	music.setLoop(true);
	//music.play();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			
			case sf::Event::KeyPressed:

				if (event.key.scancode == sf::Keyboard::Scancode::W) {
					if ((snakeBlocksCoords[0].y - 20) != snakeBlocksCoords[1].y) {
						snakeBlocks[0]->setMovement(sf::Vector2f(0.0f, -20.0f));
					}
				}
				if (event.key.scancode == sf::Keyboard::Scancode::A) {
					if ((snakeBlocksCoords[0].x - 20) != snakeBlocksCoords[1].x) {
						snakeBlocks[0]->setMovement(sf::Vector2f(-20.0f, 0.0f));
					}
				}
				if (event.key.scancode == sf::Keyboard::Scancode::S) {
					if ((snakeBlocksCoords[0].y + 20) != snakeBlocksCoords[1].y) {
						snakeBlocks[0]->setMovement(sf::Vector2f(0.0f, 20.0f));
					}
				}
				if (event.key.scancode == sf::Keyboard::Scancode::D) {
					if ((snakeBlocksCoords[0].x + 20) != snakeBlocksCoords[1].x) {
						snakeBlocks[0]->setMovement(sf::Vector2f(20.0f, 0.0f));
					}
				}
				if (event.key.scancode == sf::Keyboard::Scancode::Escape) {
					if (isPaused == false and hasLost == false) {
						isPaused = true;
						text.setPosition(300.0f, 200.0f);
						text.setString("The Game Is Paused");
					}
					else if (isPaused == true and hasLost == false) {
						isPaused = false;
						text.setPosition(30.0f, 10.0f);
						text.setString(std::to_string(amountOfPoints));
					}
				}


				// Code that can be used to play the game in easy mode. This bunch of code makes it so that you can make the snake move one block at a time instead of it moving on it's own.
				/*
				if (event.key.scancode == sf::Keyboard::Scancode::W) {

					std::cout << "Pressed W" << std::endl;

					if ((snakeBlocksCoords[0].y - 20) == snakeBlocksCoords[1].y) {
					}
					else {
						count = 0;
						previousCoords = snakeBlocksCoords[0];
						snakeBlocksCoords[0].y -= 20;
						for (size_t i = 1; i < snakeBlocksCoords.size(); i++)
						{
							sf::Vector2f tempPreviousCoords = previousCoords;
							previousCoords = snakeBlocksCoords[i];
							snakeBlocksCoords[i] = tempPreviousCoords;
						}

						for (SnakeBlock* block : snakeBlocks) {
							block->setPos(snakeBlocksCoords[count]);
							count += 1;
						}
					}
				}
				if (event.key.scancode == sf::Keyboard::Scancode::A) {

					std::cout << "Pressed A" << std::endl;

					if ((snakeBlocksCoords[0].x - 20) == snakeBlocksCoords[1].x) {
					}
					else {
						count = 0;
						previousCoords = snakeBlocksCoords[0];
						snakeBlocksCoords[0].x -= 20;
						for (size_t i = 1; i < snakeBlocksCoords.size(); i++)
						{
							sf::Vector2f tempPreviousCoords = previousCoords;
							previousCoords = snakeBlocksCoords[i];
							snakeBlocksCoords[i] = tempPreviousCoords;
						}

						for (SnakeBlock* block : snakeBlocks) {
							block->setPos(snakeBlocksCoords[count]);
							count += 1;
						}
					}
				}
				if (event.key.scancode == sf::Keyboard::Scancode::S) {

					std::cout << "Pressed S" << std::endl;

					if ((snakeBlocksCoords[0].y + 20) == snakeBlocksCoords[1].y) {
					}
					else {
						count = 0;
						previousCoords = snakeBlocksCoords[0];
						snakeBlocksCoords[0].y += 20;
						for (size_t i = 1; i < snakeBlocksCoords.size(); i++)
						{
							sf::Vector2f tempPreviousCoords = previousCoords;
							previousCoords = snakeBlocksCoords[i];
							snakeBlocksCoords[i] = tempPreviousCoords;
						}

						for (SnakeBlock* block : snakeBlocks) {
							block->setPos(snakeBlocksCoords[count]);
							count += 1;
						}
					}
				}
				if (event.key.scancode == sf::Keyboard::Scancode::D) {

					std::cout << "Pressed D" << std::endl;

					if ((snakeBlocksCoords[0].x + 20) == snakeBlocksCoords[1].x) {
					}
					else {
						count = 0;
						previousCoords = snakeBlocksCoords[0];
						snakeBlocksCoords[0].x += 20;
						for (size_t i = 1; i < snakeBlocksCoords.size(); i++)
						{
							sf::Vector2f tempPreviousCoords = previousCoords;
							previousCoords = snakeBlocksCoords[i];
							snakeBlocksCoords[i] = tempPreviousCoords;
						}

						for (SnakeBlock* block : snakeBlocks) {
							block->setPos(snakeBlocksCoords[count]);
							count += 1;
						}
					}

				}
								if (event.key.scancode == sf::Keyboard::Scancode::Space) {
					std::cout << snakeBlocks[snakeBlocks.size() - 2]->getPos().x - snakeBlocks[snakeBlocks.size() - 1]->getPos().x << std::endl;
					std::cout << snakeBlocks[snakeBlocks.size() - 2]->getPos().y - snakeBlocks[snakeBlocks.size() - 1]->getPos().y << std::endl;
				}
				*/

				break;
			}
		}

		if (isPaused == false) {


		// Uses the clock to measure when half a second has passed. Once half a second has passed it moves the snake.
		sf::Time elapsed = clock.getElapsedTime();
		if (elapsed.asSeconds() > timeForMovement) {
			clock.restart();
			count = 0;
			previousCoords = snakeBlocksCoords[0];
			snakeBlocksCoords[0].x += snakeBlocks[0]->getMovement().x;
			snakeBlocksCoords[0].y += snakeBlocks[0]->getMovement().y;
			for (size_t i = 1; i < snakeBlocksCoords.size(); i++)
			{
				sf::Vector2f tempPreviousCoords = previousCoords;
				previousCoords = snakeBlocksCoords[i];
				snakeBlocksCoords[i] = tempPreviousCoords;
			}

			for (SnakeBlock* block : snakeBlocks) {
				block->setPos(snakeBlocksCoords[count]);
				count += 1;
			}

			// These if statements checks if the snake head has touched the borders of the screen, if it has it gets put on the opposite side of the screen.

			if (snakeBlocks[0]->getPos().y < 0) {
				snakeBlocks[0]->setPos(sf::Vector2f(snakeBlocks[0]->getPos().x, 600));
				snakeBlocksCoords[0] = snakeBlocks[0]->getPos();
			}
			else if (snakeBlocks[0]->getPos().y > 600) {
				snakeBlocks[0]->setPos(sf::Vector2f(snakeBlocks[0]->getPos().x, 0));
				snakeBlocksCoords[0] = snakeBlocks[0]->getPos();
			}
			else if (snakeBlocks[0]->getPos().x < 0) {
				snakeBlocks[0]->setPos(sf::Vector2f(800, snakeBlocks[0]->getPos().y));
				snakeBlocksCoords[0] = snakeBlocks[0]->getPos();
			}
			else if (snakeBlocks[0]->getPos().x > 800) {
				snakeBlocks[0]->setPos(sf::Vector2f(0, snakeBlocks[0]->getPos().y));
				snakeBlocksCoords[0] = snakeBlocks[0]->getPos();
			}


			
		}
		//----------------------------------------------------- Movement for the snake

		for (SnakeBlock* blockBody : snakeBlocks) {
			if (blockBody->getType() != 0) {
				if (snakeBlocks[0]->getBounds().intersects(blockBody->getBounds())) {
					std::cout << "Game Over" << std::endl;
					text.setPosition(300.0f, 200.0f);
					text.setString("Oh no, you lost!");
					isPaused = true;
					hasLost = true;

				}

			}
		}
		if (snakeBlocks[0]->getBounds().intersects(TheFruit.getBounds())) {

			// Adds a point
			amountOfPoints += 1;
			// Updates the counter
			text.setString(std::to_string(amountOfPoints));

			// Plays the sound for getting a point.
			sound.play();

			// Moves the fruit away to stop continuous collisions.
			TheFruit.setPos(sf::Vector2f(200, 0));


			// Checks the relation of the last and second to last blocks. If the difference in x value between them is 0, that means they have the same x value, which means that the blocks are going up and down.
			if ((snakeBlocks[snakeBlocks.size() - 2]->getPos().x - snakeBlocks[snakeBlocks.size() - 1]->getPos().x) == 0) {
				if (snakeBlocks[snakeBlocks.size() - 2]->getPos().y - snakeBlocks[snakeBlocks.size() - 1]->getPos().y > 0) {
					snakeBlocks.push_back(new SnakeBlock(sf::Vector2f(snakeBlocks[snakeBlocks.size() - 1]->getPos().x, snakeBlocks[snakeBlocks.size() - 1]->getPos().y - 20), 20, 20, sf::Color::Yellow, 1));
					snakeBlocksCoords.push_back(sf::Vector2f(snakeBlocks[snakeBlocks.size() - 1]->getPos().x, snakeBlocks[snakeBlocks.size() - 1]->getPos().y - 20));
				}
				else {
					snakeBlocks.push_back(new SnakeBlock(sf::Vector2f(snakeBlocks[snakeBlocks.size() - 1]->getPos().x, snakeBlocks[snakeBlocks.size() - 1]->getPos().y + 20), 20, 20, sf::Color::Yellow, 1));
					snakeBlocksCoords.push_back(sf::Vector2f(snakeBlocks[snakeBlocks.size() - 1]->getPos().x, snakeBlocks[snakeBlocks.size() - 1]->getPos().y + 20));
				}
			}
			else if (snakeBlocks[snakeBlocks.size() - 2]->getPos().y - snakeBlocks[snakeBlocks.size() - 1]->getPos().y == 0) {
				if (snakeBlocks[snakeBlocks.size() - 2]->getPos().x - snakeBlocks[snakeBlocks.size() - 1]->getPos().x > 0) {
					snakeBlocks.push_back(new SnakeBlock(sf::Vector2f(snakeBlocks[snakeBlocks.size() - 1]->getPos().x - 20, snakeBlocks[snakeBlocks.size() - 1]->getPos().y), 20, 20, sf::Color::Yellow, 1));
					snakeBlocksCoords.push_back(sf::Vector2f(snakeBlocks[snakeBlocks.size() - 1]->getPos().x - 20, snakeBlocks[snakeBlocks.size() - 1]->getPos().y));

				}
				else {
					snakeBlocks.push_back(new SnakeBlock(sf::Vector2f(snakeBlocks[snakeBlocks.size() - 1]->getPos().x + 20, snakeBlocks[snakeBlocks.size() - 1]->getPos().y), 20, 20, sf::Color::Yellow, 1));
					snakeBlocksCoords.push_back(sf::Vector2f(snakeBlocks[snakeBlocks.size() - 1]->getPos().x + 20, snakeBlocks[snakeBlocks.size() - 1]->getPos().y));
				}
			}
			newFruitPos(&TheFruit, snakeBlocks);
			if (timeForMovement > 0.2){
				timeForMovement -= 0.05;
			}

		}
		}


		window.clear(sf::Color::Black);
		
		
		for (SnakeBlock* block : snakeBlocks) {
			window.draw(*block->getDrawable());
		}
		window.draw(*TheFruit.getDrawable());
		window.draw(text);

		window.display();

	}

	return 0;
}

void newFruitPos(Fruit* Fruit, std::vector<SnakeBlock*> snakeBlocks) {
	bool doLoop = true;
	while (doLoop){
		
		Fruit->setPos(sf::Vector2f((rand() % 40) * 20, (rand() % 30) * 20));
		for (SnakeBlock* blockBody : snakeBlocks) {
			if (!blockBody->getBounds().intersects(Fruit->getBounds())) {
				doLoop = false;
			}
		}

	}
}