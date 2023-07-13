#include<SFML/Graphics.hpp>

#include "Snake.h"
#include "Fruit.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

    Snake snake;
    Fruit fruit;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
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
        }

        if (snake.AnyHaveCollisionsWith(fruit) && !snake.is_dead)
        {
            snake.AddPart();
            fruit.SetHasBeenEaten();
        }

        if (snake.HasCollidedWithSelf())
        {
            snake.Die();
        }

        window.clear();
        snake.draw(window);
        fruit.draw(window);
        window.display();
    }
}
