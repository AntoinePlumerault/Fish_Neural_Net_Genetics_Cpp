#ifndef DEF_SHARK
#define DEF_SHARK

#include "Life_form.hpp"

class Shark : public Life_form {
public:
	Shark(Brain* brain);
	Life_form * clone() const;
};

#endif