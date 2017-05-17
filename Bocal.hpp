#ifndef DEF_BOCAL
#define DEF_BOCAL

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Bocal : public sf::RenderWindow {
public:
	Bocal(int width, int height);
};

#endif