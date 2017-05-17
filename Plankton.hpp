#ifndef DEF_PLANKTON
#define DEF_PLANKTON

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Life_form.hpp"

class Plankton : Life_form {
public:
	Plankton(Brain * brain);
	Life_form * clone() const;
	void update_body();
};

#endif