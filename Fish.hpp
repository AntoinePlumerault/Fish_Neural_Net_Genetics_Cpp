#ifndef DEF_FISH
#define DEF_FISH

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Life_form.hpp"

class Fish : public Life_form {
public:
	Fish(Brain* brain);
	Life_form * clone() const;
};

#endif