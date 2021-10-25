#include<iostream>
#include<SFML/Graphics.hpp>

using namespace std;
using namespace sf;

int main() {
	RenderWindow window(VideoMode(640, 480),"demo");
	window.setFramerateLimit(120);
	int x = 320;
	int y = 280;
	
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.KeyPressed) {
				if (event.key.code == Keyboard::Right) {
					++x;
				}
				if (event.key.code == Keyboard::Left) {
					--x;
				}
				if (event.key.code == Keyboard::Escape) {
					window.close();
				}
			}

		}

		window.clear(Color::White);

		Texture texture;
		texture.loadFromFile("C:\\Users\\Alexandr\\Desktop\\Projects\\sfml-demo\\sfml-demo\\image.png");
		texture.setSmooth(true);
		Sprite sprite(texture, IntRect(0, 0, 640, 20));
		sprite.setPosition(0,300);
		window.draw(sprite);

		RectangleShape shape(Vector2f(20,20));
		shape.setFillColor(Color::Blue);
		shape.setPosition(x, y);
		window.draw(shape);
		window.display();
	}
}