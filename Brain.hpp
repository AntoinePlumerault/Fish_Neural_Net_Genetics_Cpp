#ifndef DEF_BRAIN
#define DEF_BRAIN

#include <iostream>

#include "Individual.hpp"
#include "Feed_forward_NN.hpp"

class Brain : public Individual, public Feed_forward_NN {
public:
	Brain();
	Brain(std::vector<float> const & genotype);
	void add_layer(unsigned int n_neurons);
	Individual* clone() const;
	friend std::vector<Brain> cross_over(Brain const & parent_1, Brain const & parent_2, std::string method);
	void mutation(std::string method, float mutation_probability);

private :
	std::vector<float> m_weights_genotype;
	std::vector<unsigned int> m_architecture_genotype;
};

#endif