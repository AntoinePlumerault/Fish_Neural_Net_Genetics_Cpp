#include "Bocal.hpp"

Bocal::Bocal(int width, int height) : sf::RenderWindow(sf::VideoMode(width, height), "Bocal") {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	create(sf::VideoMode(width, height), "Bocal", sf::Style::Default, settings);

	setVerticalSyncEnabled(true);
}