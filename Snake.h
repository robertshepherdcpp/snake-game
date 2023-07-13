#pragma once

#include<SFML/Graphics.hpp>

#include<vector>

#include "Fruit.h"

struct Snake
{
	Snake();

	void AddPart();
	void draw(sf::RenderWindow& window);

	bool IsPartInNextToLeftOf(sf::Sprite, sf::Sprite);
	bool IsPartInNextToRightOf(sf::Sprite, sf::Sprite);
	bool IsPartAboveOf(sf::Sprite, sf::Sprite);
	bool IsPartBelowOf(sf::Sprite, sf::Sprite);

	bool AnyHaveCollisionsWith(Fruit& f);

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	void SwapSprites(sf::Sprite& A, sf::Sprite& B);

	sf::Texture part_texture;
	sf::Sprite snake_part;

	std::vector<sf::Sprite> sprites{};
};