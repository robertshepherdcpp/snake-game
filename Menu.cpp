#include<SFML/Graphics.hpp>

#include"Menu.h"

Menu::Menu()
{
	first_texture.loadFromFile("opening.png");
	first_sprite.setTexture(first_texture);

	second_texture.loadFromFile("press_q.png");
	second_sprite.setTexture(second_texture);
}

void Menu::draw(sf::RenderWindow& window)
{
	if (!is_hidden)
	{
		window.draw(first_sprite);
		window.draw(second_sprite);
	}
}

void Menu::hide()
{
	is_hidden = true;
}