#include<SFML/Graphics.hpp>

#include "Snake.h"
#include "Fruit.h"
#include "Menu.h"

#include<iostream>
#include<chrono>

using namespace std::chrono_literals;

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "Snake");

    sf::Texture restart_texture;
    restart_texture.loadFromFile("restart.png");
    sf::Sprite restart;
    restart.setTexture(restart_texture);
    restart.setPosition(80.0f, 80.0f);

    Snake snake;
    Fruit fruit;

    Menu menu;

    bool has_pressed_q = true;

    while (window.isOpen())
    {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    std::cout << "Your final score was: " << snake.sprites.size() << "\n";
                    window.close();
                }
                if (event.type == sf::Event::KeyReleased)
                {
                    if (snake.is_dead)
                    {
                        snake.is_dead = false;
                        snake.sprites.clear();
                        snake.sprites = snake.original_sprites;
                        snake.current_speed = 500ms;
                        fruit.should_be_hidden = false;
                        snake.is_dead = false;
                        snake.MoveDown();
                        snake.MoveDown();
                        snake.MoveRight();
                        snake.MoveRight();
                    }
                }
                if (event.type == sf::Event::KeyPressed)
                {
                        if (has_pressed_q)
                        {
                            if (event.key.code == sf::Keyboard::D)
                            {
                                snake.MoveRight();
                            }
                            if (event.key.code == sf::Keyboard::A)
                            {
                                snake.MoveLeft();
                            }
                            if (event.key.code == sf::Keyboard::S)
                            {
                                snake.MoveDown();
                            }
                            if (event.key.code == sf::Keyboard::W)
                            {
                                snake.MoveUp();
                            }
                        }
                        else
                        {
                            if (event.key.code == sf::Keyboard::Q)
                            {
                                has_pressed_q = true;
                            }
                        }
                }
            }

            if (snake.AnyHaveCollisionsWith(fruit) && !snake.is_dead)
            {
                snake.AddPart();
                fruit.SetHasBeenEaten();
            }

            if (snake.HasCollidedWithSelf())
            {
                snake.Die();
                fruit.Hide();
            }

            snake.Update();
            snake.Move();

            window.clear();
            if (!has_pressed_q)
            {
                menu.draw(window);
            }
            if (snake.is_dead)
            {
                window.draw(restart);
            }
            snake.draw(window);
            fruit.draw(window);
            window.display();
    }
}