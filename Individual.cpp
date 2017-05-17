#include "individual.hpp"

std::vector<Individual> cross_over(Individual const & parent_1, Individual const & parent_2, std::string method) {
	std::vector<Individual> childs;
	return childs;
}

std::vector<std::vector<float>> cross_over_g(std::vector<float> const & parent_1_genotype, std::vector<float> const & parent_2_genotype, std::string method) {
	unsigned int genom_1_size = (unsigned int)parent_1_genotype.size();
	unsigned int genom_2_size = (unsigned int)parent_2_genotype.size();

	std::vector<float> child_1_genotype, child_2_genotype;
	
	/*==================== One point cross-over ====================*/
	if (method == "one point") {
		unsigned int cut_i= std::rand() % std::min(genom_1_size, genom_2_size);
		
		for (unsigned int i = 0; i < cut_i; i++) {
			child_1_genotype.push_back(parent_1_genotype[i]);
			child_2_genotype.push_back(parent_2_genotype[i]);
		}
		for (unsigned int i = cut_i; i < genom_1_size ; i++) {
			child_2_genotype.push_back(parent_1_genotype[i]);
		}
		for (unsigned int i = cut_i; i < genom_2_size; i++) {
			child_1_genotype.push_back(parent_2_genotype[i]);
		}
	}
	/*==================== Two point cross-over ====================*/
	if (method == "two points") {
		unsigned int cut_i_1 = std::rand() % std::min(genom_1_size, genom_2_size);
		unsigned int cut_i_2 = std::rand() % std::min(genom_1_size, genom_2_size);
		
		for (unsigned int i = 0; i < cut_i_1; i++) {
			child_1_genotype.push_back(parent_1_genotype[i]);
			child_2_genotype.push_back(parent_2_genotype[i]);
		}
		for (unsigned int i = cut_i_1; i < cut_i_2; i++) {
			child_1_genotype.push_back(parent_2_genotype[i]);
			child_2_genotype.push_back(parent_1_genotype[i]);
		}
		for (unsigned int i = cut_i_2; i < genom_1_size; i++) {
			child_1_genotype.push_back(parent_1_genotype[i]);
		}
		for (unsigned int i = cut_i_2; i < genom_2_size; i++) {
			child_2_genotype.push_back(parent_2_genotype[i]);
		}
	}
	/*================== Uniform point cross-over ==================*/
	if (method == "uniform") {
		for (unsigned int i = 0; i < std::min(genom_1_size, genom_2_size); i++) {
			if (std::rand() % 2) {
				child_1_genotype.push_back(parent_1_genotype[i]);
				child_2_genotype.push_back(parent_2_genotype[i]);
			}
			else {
				child_1_genotype.push_back(parent_2_genotype[i]);
				child_2_genotype.push_back(parent_1_genotype[i]);
			}
		}
		if (genom_1_size > genom_2_size) {
			for (unsigned int i = genom_1_size; i < genom_2_size; i++) {
				child_1_genotype.push_back(parent_1_genotype[i]);
			}
		}
		else {
			for (unsigned int i = genom_2_size; i < genom_1_size; i++) {
				child_2_genotype.push_back(parent_2_genotype[i]);
			}
		}
	}

	std::vector<std::vector<float>> child_genotypes(2);
	child_genotypes[0] = child_1_genotype;
	child_genotypes[1] = child_2_genotype;

	return child_genotypes;
}

void mutation_g(std::vector<float> genotype, std::string method, float mutation_probability) {
	if (method == "uniform") {
		for (float gene : genotype) {
			if ((rand() % 100000) / 100000. < mutation_probability) { gene += (float)(2*((rand() % 100000) / 100000. - 0.5)*0.5); }
		}		
	}
}

float & Individual::get_fitness() { 
	return m_fitness; 
}

void Individual::reset_fitness() { 
	m_fitness = 0; 
}

bool operator>(Individual const & individual_1, Individual const & individual_2) { 
	return (individual_1.m_fitness > individual_2.m_fitness); 
}