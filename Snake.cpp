#include<SFML/Graphics.hpp>

#include "Snake.h"

#include<iostream>

Snake::Snake()
{
	if (!part_texture.loadFromFile("snake_part.png"))
	{
		// handle the error
	}
	else
	{
		snake_part.setTexture(part_texture);
	}

	snake_part.setPosition(10, 10);
	sprites.push_back(snake_part);
	sf::Sprite CopyOfSprite = snake_part;
	CopyOfSprite.setPosition(10, (10 + (CopyOfSprite.getGlobalBounds().height) / 2));
	sprites.push_back(CopyOfSprite);
}

bool Snake::IsPartInNextToLeftOf(sf::Sprite Last, sf::Sprite IsThisSpriteToTheLeftOfLast)
{
	if ((Last.getPosition().y == IsThisSpriteToTheLeftOfLast.getPosition().y) && (Last.getPosition().x > IsThisSpriteToTheLeftOfLast.getPosition().x))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Snake::IsPartInNextToRightOf(sf::Sprite Last, sf::Sprite IsThisSpriteToTheLeftOfLast)
{
	if ((Last.getPosition().y == IsThisSpriteToTheLeftOfLast.getPosition().y) && (Last.getPosition().x < IsThisSpriteToTheLeftOfLast.getPosition().x))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Snake::IsPartAboveOf(sf::Sprite Last, sf::Sprite IsThisSpriteToTheLeftOfLast)
{
	if ((Last.getPosition().x == IsThisSpriteToTheLeftOfLast.getPosition().x) && (Last.getPosition().y < IsThisSpriteToTheLeftOfLast.getPosition().y))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Snake::IsPartBelowOf(sf::Sprite Last, sf::Sprite IsThisSpriteToTheLeftOfLast)
{
	if ((Last.getPosition().x == IsThisSpriteToTheLeftOfLast.getPosition().x) && (Last.getPosition().y > IsThisSpriteToTheLeftOfLast.getPosition().y))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Snake::AddPart()
{
	std::cout << "AddPart has been called\n";
	if (IsPartInNextToLeftOf(sprites.at(sprites.size() - 1), sprites.at(sprites.size() - 2)))
	{
		// the part is in front of the last one so it looks like this:
		// - -
		// so we need to add the next one here ^
		//     
		std::cout << "IsPartInNextToLeftOf\n";
		auto sizeOfSprite = sprites.at(sprites.size() - 1).getGlobalBounds(); // .width
		auto PositionOfSprite = sprites.at(sprites.size() - 1).getPosition(); // .x && .y
		sf::Sprite CopyOfSprite = snake_part;
		CopyOfSprite.setPosition((PositionOfSprite.x + (sizeOfSprite.width) / 2), (PositionOfSprite.y));
		sprites.push_back(CopyOfSprite);
	}
	else if (IsPartInNextToRightOf(sprites.at(sprites.size() - 1), sprites.at(sprites.size() - 2)))
	{
		std::cout << "IsPartInNextToRightOf\n";
		auto sizeOfSprite = sprites.at(sprites.size() - 1).getGlobalBounds(); // .width
		auto PositionOfSprite = sprites.at(sprites.size() - 1).getPosition(); // .x && .y
		sf::Sprite CopyOfSprite = snake_part;
		CopyOfSprite.setPosition((PositionOfSprite.x - (sizeOfSprite.width) / 2), (PositionOfSprite.y));
		sprites.push_back(CopyOfSprite);
	}

	else if (IsPartAboveOf(sprites.at(sprites.size() - 1), sprites.at(sprites.size() - 2)))
	{
		std::cout << "IsPartAboveOf\n";
		auto sizeOfSprite = sprites.at(sprites.size() - 1).getGlobalBounds(); // .width
		auto PositionOfSprite = sprites.at(sprites.size() - 1).getPosition(); // .x && .y
		sf::Sprite CopyOfSprite = snake_part;
		CopyOfSprite.setPosition((PositionOfSprite.x), (PositionOfSprite.y - (sizeOfSprite.height) / 2));
		sprites.push_back(CopyOfSprite);
	}

	else if (IsPartBelowOf(sprites.at(sprites.size() - 1), sprites.at(sprites.size() - 2)))
	{
		std::cout << "IsPartBelowOf\n";
		auto sizeOfSprite = sprites.at(sprites.size() - 1).getGlobalBounds(); // .width
		auto PositionOfSprite = sprites.at(sprites.size() - 1).getPosition(); // .x && .y
		sf::Sprite CopyOfSprite = snake_part;
		CopyOfSprite.setPosition((PositionOfSprite.x), (PositionOfSprite.y + (sizeOfSprite.height) / 2));
		sprites.push_back(CopyOfSprite);
	}
}

void Snake::draw(sf::RenderWindow& window)
{
	if (!is_dead)
	{
		for (sf::Sprite const& x : sprites)
		{
			window.draw(x);
		}
	}
}

bool Snake::AnyHaveCollisionsWith(Fruit& f)
{
	for (sf::Sprite const& part : sprites)
	{
		if (part.getGlobalBounds().intersects(f.sprite.getGlobalBounds()))
		{
			return true;
		}
	}
	return false;
}

void Snake::SwapSprites(sf::Sprite& A, sf::Sprite& B)
{
	//sf::Sprite CopyOfASprite = A;
	//A = B;
	//B = CopyOfASprite

	// first swap the textures.
	sf::Texture CopyOfATexture = *A.getTexture();
	A.setTexture(*B.getTexture());
	B.setTexture(CopyOfATexture);

	// then swap the positions
	sf::Vector2f CopyOfAPosition = A.getPosition();
	A.setPosition(B.getPosition());
	B.setPosition(CopyOfAPosition);
}

void Snake::MoveDown()
{
	sf::Sprite head = sprites[0];
	sf::Texture texture_;
	if (!texture_.loadFromFile("black_square.png"))
	{
		// handle the error
	}
	sf::Sprite black_square;
	black_square.setTexture(texture_);
	black_square.setPosition((head.getPosition().x), (head.getPosition().y + (head.getGlobalBounds().height / 2)));
	for (int i = 0; i < sprites.size(); i++)
	{
		// so we will have an invisible block and then we just keep swapping that block with the other blocks
		// and it will move all of the other blocks up one position.
		SwapSprites(black_square, sprites[i]);
	}
}

auto Snake::difference_between(int a, int b) -> int
{
	if (a > b)
	{
		return a - b;
	}
	else
	{
		return b - a;
	}
}

void Snake::Die()
{
	is_dead = true;
}

bool Snake::HasCollidedWithSelf()
{
	for (int i = 0; i < sprites.size(); i++)
	{
		for (int j = 0; j < sprites.size(); j++)
		{
			if (i != j)
			{
				sf::Sprite A = sprites[i];
				sf::Sprite B = sprites[j];
				if (A.getGlobalBounds().intersects(B.getGlobalBounds()) && (difference_between(i, j) > 2) && !is_dead)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void Snake::MoveUp()
{
	std::cout << "MoveUp called\n";
	sf::Sprite head = sprites[0];
	sf::Sprite black_square = head;
	black_square.setPosition((head.getPosition().x), (head.getPosition().y - (head.getGlobalBounds().height / 2)));
	sprites.push_back(black_square);
	for (int i = 0; i < sprites.size(); i++)
	{
		// so we will have an invisible block and then we just keep swapping that block with the other blocks
		// and it will move all of the other blocks up one position.
		SwapSprites(black_square, sprites[i]);
	}
	sprites.pop_back();
}


void Snake::MoveRight()
{
	sf::Sprite head = sprites[0];
	sf::Texture texture_;
	if (!texture_.loadFromFile("black_square.png"))
	{
		// handle the error
	}
	sf::Sprite black_square;
	black_square.setTexture(texture_);
	black_square.setPosition((head.getPosition().x + (head.getGlobalBounds().width / 2)), head.getPosition().y);
	for (int i = 0; i < sprites.size(); i++)
	{
		// so we will have an invisible block and then we just keep swapping that block with the other blocks
		// and it will move all of the other blocks up one position.
		SwapSprites(black_square, sprites[i]);
	}
}

void Snake::MoveLeft()
{
	sf::Sprite head = sprites[0];
	sf::Texture texture_;
	if (!texture_.loadFromFile("black_square.png"))
	{
		// handle the error
	}
	sf::Sprite black_square;
	black_square.setTexture(texture_);
	black_square.setPosition((head.getPosition().x - (head.getGlobalBounds().width / 2)), head.getPosition().y);
	for (int i = 0; i < sprites.size(); i++)
	{
		// so we will have an invisible block and then we just keep swapping that block with the other blocks
		// and it will move all of the other blocks up one position.
		SwapSprites(black_square, sprites[i]);
	}
}