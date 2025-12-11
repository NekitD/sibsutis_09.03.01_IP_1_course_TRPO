#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <cstring>
#include <ctime>
#include "libgame.h"

const int line_x = 1280;
const int line_y = 720;
const int size = 9;
const int count_x = line_x / size;
const int count_y = line_y / size;
bool state[count_x][count_y] = {false};
bool new_state[count_x][count_y] = {false};
bool false_state[count_x][count_y] = {false};
bool paused = false;
int speed = 300;
bool starter;

void rectangle(sf::RenderWindow &window, sf::Text &button)
{
	sf::RectangleShape outline(sf::Vector2f(button.getGlobalBounds().width + 4, button.getGlobalBounds().height + 40));
	outline.setPosition(button.getPosition());
	outline.setOutlineThickness(2);
	outline.setOutlineColor(sf::Color::White);
	outline.setFillColor(sf::Color::Transparent);
	window.draw(outline);
}

void State_replace()
{
	for (int x = 0; x < count_x; x++)
	{
		for (int y = 0; y < count_y; y++)
		{
			int count_neighbours = 0;
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					int nx = Bias(x, i, count_x);
					int ny = Bias(y, j, count_y);
					count_neighbours = NeighborCounting(state[nx][ny], i, j, count_neighbours);
				}
			}
			new_state[x][y] = Condition(state[x][y], count_neighbours);
		}
	}
	std::memcpy(state, new_state, sizeof(state));
}

void FillRand()
{
	int center_x, center_y, rxl, rxr, ryu, ryd, counter = 0;
	center_x = (rand() % count_x) * 3;
	center_y = (rand() % count_y) * 3;
	rxl = rand() % (center_x + 1);
	rxr = rand() % (count_x - center_x);
	ryu = rand() % (center_y + 1);
	ryd = rand() % (count_y - center_y);
	for (int x = rxl; x < rxr; x++)
	{
		for (int y = ryu; y < ryd; y++)
		{
			if (rand() % 2 == 0)
			{
				state[x][y] = true;
				counter++;
			}
			else
			{
				state[x][y] = false;
			}
		}
	}
	if (counter == 0)
	{
		FillRand();
	}
}

void ToZero()
{
	state[count_x][count_y] = false;
	new_state[count_x][count_y] = false;
	false_state[count_x][count_y] = false;
	paused = false;
	starter = true;
	std::memcpy(state, false_state, sizeof(state));
	std::memcpy(new_state, false_state, sizeof(new_state));
}

int PlayingField(int mode)
{
	sf::RenderWindow window(sf::VideoMode(line_x, line_y), "Game of Life");
first:
	ToZero();
	window.clear();
	while (starter && window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
				if (event.key.code == sf::Keyboard::Space)
				{
					starter = false;
				}
			}
			if ((event.type == sf::Event::MouseButtonPressed) and (mode == 2))
			{
				std::memcpy(state, false_state, sizeof(state));
				std::memcpy(new_state, false_state, sizeof(new_state));
				window.clear();
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					FillRand();
				}
			}

			if ((event.type == sf::Event::MouseButtonPressed) and (mode == 1))
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					int mouseX = event.mouseButton.x / size;
					int mouseY = event.mouseButton.y / size;
					if (mouseX >= 0 && mouseX < count_x && mouseY >= 0 && mouseY < count_y)
					{
						state[mouseX][mouseY] = true;
					}
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					int mouseX = event.mouseButton.x / size;
					int mouseY = event.mouseButton.y / size;
					if (mouseX >= 0 && mouseX < count_x && mouseY >= 0 && mouseY < count_y)
					{
						state[mouseX][mouseY] = false;
					}
				}
			}
		}

		window.clear();

		for (int x = 0; x < count_x; x++)
		{
			for (int y = 0; y < count_y; y++)
			{
				if (state[x][y])
				{
					sf::RectangleShape cell(sf::Vector2f(size, size));
					cell.setPosition(x * size, y * size);
					cell.setFillColor(sf::Color::White);
					window.draw(cell);
				}
			}
		}

		window.display();
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (event.mouseWheelScroll.delta < 0)
				{
					speed += 50;
				}

				if (event.mouseWheelScroll.delta > 0)
				{
					speed -= 100;
					if (speed < 0)
					{
						speed = 0;
					}
				}
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					paused = !paused;
				}

				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}

				if (event.key.code == sf::Keyboard::Return)
				{
					goto first;
				}
			}
		}

		if (!paused)
		{
			State_replace();
		}

		window.clear();

		for (int x = 0; x < count_x; x++)
		{
			for (int y = 0; y < count_y; y++)
			{
				if (state[x][y])
				{
					sf::RectangleShape cell(sf::Vector2f(size, size));
					cell.setPosition(x * size, y * size);
					cell.setFillColor(sf::Color::White);
					window.draw(cell);
				}
			}
		}

		window.display();

		sf::sleep(sf::milliseconds(speed));
	}

	return 0;
}

int Rules()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Rules");

	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		return 1;
	}

	sf::Text title("Rules", font, 40);
	title.setPosition(620 - title.getGlobalBounds().width / 2, 40);
	title.setFillColor(sf::Color::White);

	sf::Text text(" * Press ESC to return Menu\n\n * Press ENTER to restart the game\n\n * Press SPACE to pause/start the game\n\n * Scroll mouse wheel to change speed\n\n * Press left mouse button to color a cell", font, 30);
	text.setPosition(100 - title.getGlobalBounds().width / 2, 140);
	text.setFillColor(sf::Color::White);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
			}
		}

		window.clear();
		window.draw(title);
		window.draw(text);
		window.display();
	}

	return 0;
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Menu");

	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		return 1;
	}

	sf::Text title("LIFE-GAME", font, 40);
	title.setPosition(620 - title.getGlobalBounds().width / 2, 80);
	title.setFillColor(sf::Color::White);

	sf::Text button_1("Normal game", font, 30);
	button_1.setPosition(620 - button_1.getGlobalBounds().width / 2, 200);
	button_1.setFillColor(sf::Color::White);

	sf::Text button_2("Automatic game", font, 30);
	button_2.setPosition(620 - button_2.getGlobalBounds().width / 2, 300);
	button_2.setFillColor(sf::Color::White);

	sf::Text button_3("Rules", font, 30);
	button_3.setPosition(620 - button_3.getGlobalBounds().width / 2, 400);
	button_3.setFillColor(sf::Color::White);

	sf::Text button_4("Exit", font, 30);
	button_4.setPosition(620 - button_4.getGlobalBounds().width / 2, 500);
	button_4.setFillColor(sf::Color::White);

	bool button_1_stop = false;
	bool button_2_stop = false;
	bool button_3_stop = false;
	bool button_4_stop = false;

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::MouseMoved)
			{
				sf::Vector2i pos = sf::Mouse::getPosition(window);

				button_1_stop = button_1.getGlobalBounds().contains(pos.x, pos.y);
				button_2_stop = button_2.getGlobalBounds().contains(pos.x, pos.y);
				button_3_stop = button_3.getGlobalBounds().contains(pos.x, pos.y);
				button_4_stop = button_4.getGlobalBounds().contains(pos.x, pos.y);
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (button_1_stop)
				{
					window.display();
					PlayingField(1);
				}

				else if (button_2_stop)
				{
					window.display();
					PlayingField(2);
				}

				else if (button_3_stop)
				{
					Rules();
				}

				else if (button_4_stop)
				{
					window.close();
				}
			}
		}

		window.clear();
		window.draw(title);

		if (button_1_stop)
		{
			rectangle(window, button_1);
		}

		if (button_2_stop)
		{
			rectangle(window, button_2);
		}

		if (button_3_stop)
		{
			rectangle(window, button_3);
		}

		if (button_4_stop)
		{
			rectangle(window, button_4);
		}

		window.draw(button_1);
		window.draw(button_2);
		window.draw(button_3);
		window.draw(button_4);
		window.display();
	}

	return 0;
}
