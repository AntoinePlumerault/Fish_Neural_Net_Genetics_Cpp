#include <SFML/Graphics.hpp>
#include <iostream>

#include "Simulator.hpp"
#include "Population.hpp"

int main(){
srand((unsigned int)time(NULL));
unsigned int precision = 10;

//================================================//
//================ Initialisation ================//
//================================================//

unsigned int n_fishes    = 30;
unsigned int n_sharks    = 30;
unsigned int n_planktons = 60;

Population<Brain> fish_population;
for (unsigned int fish_brain_i = 0; fish_brain_i < n_fishes; fish_brain_i++){
	Brain brain;
	brain.add_layer(2*precision);
	brain.add_layer(3);
	brain.add_layer(1);

	fish_population.push_back(brain);
}
Population<Brain> shark_population;
for (unsigned int shark_brain_i = 0; shark_brain_i < n_sharks; shark_brain_i++) {
	Brain brain;
	brain.add_layer(precision);
	brain.add_layer(3);
	brain.add_layer(1);

	shark_population.push_back(brain);
}
Population<Brain> plankton_population;
for (unsigned int plankton_brain_i = 0; plankton_brain_i < n_planktons; plankton_brain_i++) {
	Brain brain;

	plankton_population.push_back(brain);
}

//================================================//
//============== Genetic Algorithm ===============//
//================================================//

unsigned int n_generation = 1000;
std::cout << "===================== Genetic Algorithm =====================" << std::endl;
for (unsigned int generation_i = 1; generation_i < n_generation; generation_i++) {
	if (generation_i % 10 == 0) {
		std::cout << "   Results :" << std::endl;
		fish_population.sort();
		shark_population.sort();
		Population<Brain> fish_population_test;
		Population<Brain> shark_population_test;
		for (unsigned int fish_i = 0; fish_i < 10; fish_i++) {
			fish_population_test.push_back(fish_population[fish_i]);
		}
		for (unsigned int shark_i = 0; shark_i < 10; shark_i++) {
			shark_population_test.push_back(shark_population[shark_i]);
		}
		simulator(fish_population_test,
				  shark_population_test,
				  plankton_population,
				  1000, true, precision);
	}

std::cout << std::endl << "Generation " << generation_i << " :"  << std::endl;																						
	simulator(	fish_population, 
				shark_population, 
				plankton_population,
				300, false, precision);														
	std::cout << "   Fishes :" << std::endl;
	fish_population.selection("rank based roulette", 20);                                            
	fish_population.cross("one point", 10);															
	fish_population.mutate("uniform", (float)0.001);													
	
	std::cout << "   Sharks :" << std::endl;
	shark_population.selection("rank based roulette", 20);
	shark_population.cross("one point", 10);
	shark_population.mutate("uniform", (float)0.001);
}

return 0;
}