#ifndef DEF_SIMULATOR
#define DEF_SIMULATOR

#include "Brain.hpp"
#include "Population.hpp"

void simulator(Population<Brain> & fish_population, 
		       Population<Brain> & shark_population,
	           Population<Brain> & plankton_population,
	           unsigned int const & simulation_time, 
	           bool const & graphic,
			   unsigned int precision);

#endif