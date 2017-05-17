#ifndef DEF_POPULATION
#define DEF_POPULATION

#include <vector>
#include <iostream>
#include <string>

#include "Individual.hpp"
#include "Fish.hpp"
#include "Plankton.hpp"
#include "Bocal.hpp"

template<class I>
class Population : private std::vector<I*>
{
public:
	void selection	(const std::string & method, const unsigned int & n_survivors);
	void cross		(const std::string & method, const unsigned int & n_children);
	void mutate		(const std::string & method, const float & mutation_probability);

	void push_back(const I & individual) { std::vector<I*>::push_back(new I(individual)); };
	I & operator[](const unsigned int & i) { return *(std::vector<I*>::operator[](i)); }
	I const operator[](const unsigned int & i) const  { return *(std::vector<I*>::operator[](i)); }
	unsigned int size() const { return (unsigned int)(std::vector<I*>::size()); }
	void sort();
};

//==================================================//
//================ Functions Bodies ================//
//==================================================//

template<class I>
bool compare(const I* a, const I* b) {
	return ((*a) > (*b));
}

template<class I>
void Population<I>::selection(const std::string & method, const unsigned int & n_survivors) {
	std::cout << "	- Selection   method : " << method;
	
	Population<I> new_population;
	std::sort(this->begin(), this->end(), compare<I>);
	std::cout << "best = " << (operator[](0)).get_fitness() << std::endl;
	
	//================== Rank based roulette ==================//
	if (method == "rank based roulette") {
		for (unsigned int i = 0; i < n_survivors; i++) {
			unsigned int i_chosen_one = (unsigned int)(size()-1 - (unsigned int)sqrt(rand() % (size()*size())));
			(operator[](i_chosen_one)).reset_fitness();
			new_population.push_back(operator[](i_chosen_one));
		}
	}
	//================ Fitness based roulette ================//
	if (method == "fitness based roulette") {
		for (unsigned int i = 0; i < n_survivors; i++) {
			unsigned int i_chosen_one = (unsigned int)(size() - (unsigned int)sqrt(rand() % (size()*size())));
			(operator[](i_chosen_one)).reset_fitness();
			new_population.push_back(operator[](i_chosen_one));
		}
	}

	std::sort(new_population.begin(), new_population.end(), compare<I>);
	*this = new_population;
}

template<class I>
void Population<I>::cross(const std::string & method, const unsigned int & n_childrens) {
	std::cout << "	- Cross over  method : " << method << std::endl;
	unsigned int n_parents = size();
	for (unsigned int i_child = 0; i_child < n_childrens; i_child++) {
		push_back(cross_over(this->operator[](rand() % n_parents),
			this->operator[](rand() % n_parents),
			method)[rand() % 2]);
	}
}

template<class I>
void Population<I>::mutate(const std::string & method, const float & mutation_probability) {
	std::cout << "	- Mutation    method : " << method << std::endl;
	for (I* individual : *this) {
		individual->mutation(method, mutation_probability);
	}
}

template<class I>
void Population<I>::sort() {
	std::sort(this->begin(), this->end(), compare<I>);
}

#endif

