#include "Fish.hpp"
#include "Plankton.hpp"
#include "Shark.hpp"
#include "Simulator.hpp"


Bocal mainWindow(WIDTH, HEIGHT);

void simulator(Population<Brain> & fish_population, Population<Brain> & shark_population, Population<Brain> & plankton_population, unsigned int const & simulation_time, bool const & graphic, unsigned int precision) {
	unsigned int n_fishes    = fish_population.size();
	unsigned int n_sharks    = shark_population.size();
	unsigned int n_planktons = plankton_population.size();

	/*================ Graphic ================*/
	sf::Texture background;
	if (!background.loadFromFile("background_2.jpg")) { std::cout << "background not found" << std::endl; }
	background.setSmooth(true);
	sf::Sprite background_sprite;
	background_sprite.setTexture(background);
	/*=========================================*/

	/*=========================================*/
	/*============ Initialisation==============*/
	/*=========================================*/

	std::vector<Life_form*> list_fishes;
	for (unsigned int fish_i = 0; fish_i < n_fishes; fish_i++) {
		Fish fish(&(fish_population[fish_i]));
		list_fishes.push_back(fish.clone());
	}
	std::vector<Life_form*> list_planktons;
	for (unsigned int plankton_i = 0; plankton_i < n_planktons; plankton_i++) {
		Plankton plankton(&(plankton_population[plankton_i]));
		list_planktons.push_back(plankton.clone());
	}
	std::vector<Life_form*> list_sharks;
	for (unsigned int shark_i = 0; shark_i < n_sharks; shark_i++) {
		Shark shark(&(shark_population[shark_i]));
		list_sharks.push_back(shark.clone());
	}
	
	/*=========================================*/
	/*============== Simulation ===============*/
	/*=========================================*/
	for (unsigned int t = 0; t < simulation_time; t++) {
		unsigned int percent = (unsigned int)ceil((t * 100.) / simulation_time);
		std::cout << "\r" << "	- Simulation "; 
		std::cout << "|";
		for (unsigned int i = 0; i < 20; i++) {
			if (percent / 5 > i) { std::cout << "="; }
			else { std::cout << ":"; }
		}
		std::cout << "| [" << percent << " %]" ;
			
		for (unsigned int fish_i = 0; fish_i < n_fishes; fish_i++) {
			Fish* fish_p = (Fish*)(list_fishes[fish_i]);

			Vector input_1  = fish_p->see(list_planktons, precision, 250);
			Vector input_2  = fish_p->see(list_sharks, precision, 250);
			Vector input(2*precision,1); input << input_1, input_2;
			Vector output =	fish_p->think(input);						
			fish_p->act(output);						
			fish_p->move(5);							
			fish_p->eat(list_planktons);
		}
		for (unsigned int shark_i = 0; shark_i < n_sharks; shark_i++) {
			Shark* shark_p = (Shark*)(list_sharks[shark_i]);

			Vector input = shark_p->see(list_fishes, precision, 250);
			Vector output =	shark_p->think(input);
			shark_p->act(output);
			shark_p->move(5);
			shark_p->eat(list_fishes);
		}
		/*================ Graphic ================*/
		if (graphic) {
			sf::Event event;
			while (mainWindow.pollEvent(event)) { if (event.type == sf::Event::Closed) { mainWindow.close(); } }
			
			mainWindow.clear();

			mainWindow.draw(background_sprite);
			sf::String info;
			info += "|";
			for (unsigned int i = 0; i < 20; i++) {
				if (percent / 5 > i) { info += "="; }
				else { info += ":"; }
			}
			info += "| [" + std::to_string(percent) + " %]";

			sf::Font font;
			if (!font.loadFromFile("FUTRFW.TTF")) {
				//error...
			}
			sf::Text info_t(info, font);
			mainWindow.draw(info_t);

			for (Life_form * fish_p : list_fishes) {
				((Fish *)(fish_p))->update_body();
				mainWindow.draw(fish_p->get_body());
			}
			for (Life_form * plankton_p : list_planktons) {
				((Plankton *)(plankton_p))->update_body();
				mainWindow.draw(plankton_p->get_body());
			}
			for (Life_form* shark_p : list_sharks) {
				((Shark *)(shark_p))->update_body();
				mainWindow.draw(shark_p->get_body());
			}
	
			mainWindow.display();
		}
		/*=========================================*/
	}
	std::cout << std::endl;
}

