#pragma once

#include<SFML/Graphics.hpp>

#include<vector>
#include<chrono>

#include "Fruit.h"

using namespace std::chrono_literals;

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
	bool HasCollidedWithSelf();

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	void Die();
	void Move();
	void Update();

	auto difference_between(int a, int b) -> int;
	void SwapSprites(sf::Sprite& A, sf::Sprite& B);

	sf::Texture part_texture;
	sf::Sprite snake_part;

	std::vector<sf::Sprite> sprites{};

	bool is_dead = false;
	int CurrentStateMoving = 0;

	std::chrono::time_point<std::chrono::system_clock> last_time_point = std::chrono::system_clock::now();

	decltype(500ms) current_speed = 500ms;
	sf::Vector2u window_size{};
	int window_size_x = 0;
	int window_size_y = 0;
	// MoveRight = 1
    // MoveLeft = 2
    // MoveUp = 3
    // MoveDown = 4
};