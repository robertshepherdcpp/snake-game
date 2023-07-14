#include<SFML/Graphics.hpp>

#include "Snake.h"
#include "Fruit.h"
#include "Menu.h"

#include<iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

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
            snake.draw(window);
            fruit.draw(window);
            window.display();
    }
}