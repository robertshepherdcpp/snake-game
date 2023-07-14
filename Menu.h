#pragma once

#include<SFML/Graphics.hpp>

struct Menu
{
	Menu();

	void draw(sf::RenderWindow& window);
	void hide();

	bool is_hidden = false;

	sf::Texture first_texture;
	sf::Sprite first_sprite;

	sf::Texture second_texture;
	sf::Sprite second_sprite;
};