#include<SFML/Graphics.hpp>

#include "Snake.h"

#include<chrono>
#include<iostream>
#include<ranges>
#include<algorithm>

using namespace std::chrono_literals;

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
	original_sprites.push_back(snake_part);
	sf::Sprite CopyOfSprite = snake_part;
	CopyOfSprite.setPosition(10, (1 + (CopyOfSprite.getGlobalBounds().height) / 2));
	sprites.push_back(CopyOfSprite);
	original_sprites.push_back(CopyOfSprite);
}

bool Snake::IsPartInNextToLeftOf(sf::Sprite& Last, sf::Sprite& IsThisSpriteToTheLeftOfLast) const noexcept
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

bool Snake::IsPartInNextToRightOf(sf::Sprite& Last, sf::Sprite& IsThisSpriteToTheLeftOfLast) const noexcept
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

bool Snake::IsPartAboveOf(sf::Sprite& Last, sf::Sprite& IsThisSpriteToTheLeftOfLast) const noexcept
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

bool Snake::IsPartBelowOf(sf::Sprite& Last, sf::Sprite& IsThisSpriteToTheLeftOfLast) const noexcept
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
	if (!is_dead)
	{
		if (IsPartInNextToLeftOf(sprites.at(sprites.size() - 1), sprites.at(sprites.size() - 2)))
		{
			// the part is in front of the last one so it looks like this:
			// - -
			// so we need to add the next one here ^
			auto sizeOfSprite = sprites.at(sprites.size() - 1).getGlobalBounds(); // .width
			auto PositionOfSprite = sprites.at(sprites.size() - 1).getPosition(); // .x && .y
			sf::Sprite CopyOfSprite = snake_part;
			CopyOfSprite.setPosition((PositionOfSprite.x + (sizeOfSprite.width) / 2), (PositionOfSprite.y));
			sprites.push_back(CopyOfSprite);
		}
		else if (IsPartInNextToRightOf(sprites.at(sprites.size() - 1), sprites.at(sprites.size() - 2)))
		{
			auto sizeOfSprite = sprites.at(sprites.size() - 1).getGlobalBounds(); // .width
			auto PositionOfSprite = sprites.at(sprites.size() - 1).getPosition(); // .x && .y
			sf::Sprite CopyOfSprite = snake_part;
			CopyOfSprite.setPosition((PositionOfSprite.x - (sizeOfSprite.width) / 2), (PositionOfSprite.y));
			sprites.push_back(CopyOfSprite);
		}

		else if (IsPartAboveOf(sprites.at(sprites.size() - 1), sprites.at(sprites.size() - 2)))
		{
			auto sizeOfSprite = sprites.at(sprites.size() - 1).getGlobalBounds(); // .width
			auto PositionOfSprite = sprites.at(sprites.size() - 1).getPosition(); // .x && .y
			sf::Sprite CopyOfSprite = snake_part;
			CopyOfSprite.setPosition((PositionOfSprite.x), (PositionOfSprite.y - (sizeOfSprite.height) / 2));
			sprites.push_back(CopyOfSprite);
		}

		else if (IsPartBelowOf(sprites.at(sprites.size() - 1), sprites.at(sprites.size() - 2)))
		{
			auto sizeOfSprite = sprites.at(sprites.size() - 1).getGlobalBounds(); // .width
			auto PositionOfSprite = sprites.at(sprites.size() - 1).getPosition(); // .x && .y
			sf::Sprite CopyOfSprite = snake_part;
			CopyOfSprite.setPosition((PositionOfSprite.x), (PositionOfSprite.y + (sizeOfSprite.height) / 2));
			sprites.push_back(CopyOfSprite);
		}
	}
}

void Snake::draw(sf::RenderWindow& window)
{
	if (!is_dead)
	{
		window_size = window.getSize();
		window_size_x = static_cast<float>(window_size.x);
		window_size_y = static_cast<float>(window_size.y);
		if ((sprites[0].getPosition().x > window_size_x) ||
			(sprites[0].getPosition().x < 0) ||
			(sprites[0].getPosition().y > window_size_y) ||
			(sprites[0].getPosition().y < 0))
		{
			std::cout << "You died becuase you went out of bounds\n";
			std::cout << "Your final score was " << sprites.size() << "\n";
			is_dead = true;
		}
		else
		{
			sf::Texture snake_texture;
			if (!snake_texture.loadFromFile("snake_part.png"))
			{
				// handle error
			}

			sf::Texture red_square;
			if (!red_square.loadFromFile("red_square.png"))
			{
				// handle the error.
			}

			// make the head look different to the rest
			sprites[0].setTexture(red_square);

			// 1 and not zero because the head will be red.
			for (int i = 1; i < sprites.size(); i++)
			{
				sprites[i].setTexture(snake_texture);
			}

			for (sf::Sprite const& x : sprites)
			{
				window.draw(x);
			}
		}
	}
	else
	{
		if (!HasDoneIsDead)
		{
			sf::Texture head_texture;
			if (!head_texture.loadFromFile("red_square.png"))
			{
				// handle error
			}
			for (int i = 1; i < sprites.size(); i++)
			{
				sprites[i].setTexture(head_texture);
			}

			std::ranges::for_each(sprites, [&](const sf::Sprite& sprite) {window.draw(sprite); });
		}
		else
		{
			// do nothing
		}
	}
}

bool Snake::AnyHaveCollisionsWith(const Fruit& f) const
{
	for (const sf::Sprite& part : sprites)
	{
		if (part.getGlobalBounds().intersects(f.sprite.getGlobalBounds()))
		{
			return true;
		}
	}
	return false;

	/*
	if(my::ranges::any_of(sprites, [&](sf::Sprite& part){return part.getGlobalBounds().intersects(f.sprite.getGlobalBounds());}))
	{
	    return true;
	}
	else
	{
	    return false;
	}
	*/
}

void Snake::SwapSprites(sf::Sprite& A, sf::Sprite& B)
{
	// swap the positions
	sf::Vector2f CopyOfAPosition = A.getPosition();
	A.setPosition(B.getPosition());
	B.setPosition(CopyOfAPosition);
}

void Snake::MoveDown()
{
	if (!is_dead)
	{
		CurrentStateMoving = 4;
		sf::Sprite head = sprites[0];
		sf::Texture texture_;
		if (!texture_.loadFromFile("black_square.png"))
		{
			// handle the error
		}
		sf::Sprite black_square;
		black_square.setTexture(texture_);
		black_square.setPosition((head.getPosition().x), (head.getPosition().y + (head.getGlobalBounds().height / 2)));
		std::ranges::for_each(sprites, [&](sf::Sprite& sprite)
		{
				SwapSprites(black_square, sprite);
		});
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
	std::cout << "Final score was " << sprites.size() << "\n";
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
					return false; // allow the snake to crash into itself
					// Could turn this back to returning true just for testing purposes
				}
			}
		}
	}
	return false;
}

void Snake::Update()
{
	if (sprites.size() >= 5)
	{
		current_speed = 400ms;
	}
	if (sprites.size() >= 10)
	{
		current_speed = 300ms;
	}
	if (sprites.size() >= 15)
	{
		current_speed = 200ms;
	}
	if (sprites.size() >= 20)
	{
		current_speed = 100ms;
	}
	if (sprites.size() >= 25)
	{
		current_speed = 50ms;
	}
	if (sprites.size() >= 30)
	{
		current_speed = 35ms;
	}
	if (sprites.size() >= 40)
	{
		current_speed = 20ms;
	}
	if (sprites.size() >= 60)
	{
		current_speed = 10ms;
	}
	if (sprites.size() >= 100)
	{
		current_speed = 2ms;
	}

}

void Snake::MoveUp()
{
	if (!is_dead)
	{
		CurrentStateMoving = 3;
		sf::Sprite head = sprites[0];
		sf::Sprite black_square = head;
		black_square.setPosition((head.getPosition().x), (head.getPosition().y - (head.getGlobalBounds().height / 2)));
		sprites.push_back(black_square);

		std::ranges::for_each(sprites, [&](sf::Sprite& sprite) {SwapSprites(black_square, sprite); });

		sprites.pop_back();
	}
}

// MoveRight = 1
// MoveLeft = 2
// MoveUp = 3
// MoveDown = 4

void Snake::Move()
{
	if (((std::chrono::system_clock::now() - last_time_point) >= current_speed) && (!is_dead))
	{
		last_time_point = std::chrono::system_clock::now();
		if (CurrentStateMoving == 0)
		{
			// not moving atall
		}
		else if (CurrentStateMoving == 1)
		{
			// Moving Right
			MoveRight();
		}
		else if (CurrentStateMoving == 2)
		{
			// Moving Left
			MoveLeft();
		}
		else if (CurrentStateMoving == 3)
		{
			// Moving Up
			MoveUp();
		}
		else if (CurrentStateMoving == 4)
		{
			// Moving down
			MoveDown();
		}
	}
}

void Snake::MoveRight()
{
	if (!is_dead)
	{
		CurrentStateMoving = 1;
		sf::Sprite head = sprites[0];
		sf::Texture texture_;
		if (!texture_.loadFromFile("black_square.png"))
		{
			// handle the error
		}
		sf::Sprite black_square;
		black_square.setTexture(texture_);
		black_square.setPosition((head.getPosition().x + (head.getGlobalBounds().width / 2)), head.getPosition().y);
		std::ranges::for_each(sprites, [&](sf::Sprite& sprite)
		{
				SwapSprites(black_square, sprite);
		});
	}
}

void Snake::MoveLeft()
{
	if (!is_dead)
	{
		CurrentStateMoving = 2;
		sf::Sprite head = sprites[0];
		sf::Texture texture_;
		if (!texture_.loadFromFile("black_square.png"))
		{
			// handle the error
		}
		sf::Sprite black_square;
		black_square.setTexture(texture_);
		black_square.setPosition((head.getPosition().x - (head.getGlobalBounds().width / 2)), head.getPosition().y);
		std::ranges::for_each(sprites, [&](sf::Sprite& sprite)
		{
				SwapSprites(black_square, sprite);
		});
	}
}