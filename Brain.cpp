#include "Brain.hpp"

Brain::Brain() : Feed_forward_NN(), Individual() {
	m_architecture_genotype.push_back(0);
	m_genotype.push_back(0);
}

Brain::Brain(std::vector<float> const & genotype) : Brain() {
	m_genotype = genotype;

	for (unsigned int layer_i = 1; layer_i < (unsigned int)(genotype[0] + 1); layer_i++) {
		add_layer((unsigned int)(genotype[layer_i]));
	}

	int genotype_i = (unsigned int)(genotype[0] + 1);
	for (unsigned int weights_i = 0; weights_i < m_weights.size(); weights_i++) {
		for (unsigned int i = 0; i < m_weights[weights_i].cols(); i++) {
			for (unsigned int j = 0; j < m_weights[weights_i].rows(); j++) {
				m_weights[weights_i](j, i) = genotype[genotype_i];
				m_weights_genotype.push_back(genotype[genotype_i]);
				genotype_i += 1;
			}
		}
	}
}

void Brain::add_layer(unsigned int n_neurons) {
	Feed_forward_NN::add_layer(n_neurons);

	// ================ Genotype building ================
	m_architecture_genotype[0] += 1;
	m_architecture_genotype.push_back(n_neurons);

	if (m_architecture_genotype[0] > 1) {
		for (unsigned int i = 0; i < m_weights[m_weights.size() - 1].cols(); i++) {
			for (unsigned int j = 0; j < m_weights[m_weights.size() - 1].rows(); j++) {
				m_weights_genotype.push_back(m_weights[m_weights.size() - 1](j, i));
			}
		}
	}
	std::vector<float> genotype(m_architecture.begin(), m_architecture.end());
	m_genotype = genotype;
	m_genotype.insert(m_genotype.end(), m_weights_genotype.begin(), m_weights_genotype.end());
	// ===================================================

}

Individual* Brain::clone() const {
	return new Brain(*this); 
}

std::vector<Brain> cross_over(Brain const & parent_1, Brain const & parent_2, std::string method) {
	// ================ Genotype building ================ 
	std::vector<float> child_1_genotype((parent_1.m_architecture_genotype).begin(), (parent_1.m_architecture_genotype).end());
	std::vector<float> child_2_genotype((parent_1.m_architecture_genotype).begin(), (parent_1.m_architecture_genotype).end());
	
	std::vector<std::vector<float>> children_weights_genotypes = cross_over_g(parent_1.m_weights_genotype, parent_2.m_weights_genotype, method);
	
	child_1_genotype.insert(child_1_genotype.end(), (children_weights_genotypes[0]).begin(), (children_weights_genotypes[0].end()));
	child_2_genotype.insert(child_2_genotype.end(), (children_weights_genotypes[1]).begin(), (children_weights_genotypes[1].end()));
	// ===================================================

	Brain child_1(child_1_genotype), child_2(child_2_genotype);

	std::vector<Brain> children;
	children.push_back(child_1);
	children.push_back(child_2);

	return children;
}

void Brain::mutation(std::string method, float mutation_probability) {
	// ================ Genotype building ================ 
	std::vector<float> new_genotype(m_architecture_genotype.begin(), m_architecture_genotype.end());
	mutation_g(m_weights_genotype, method, mutation_probability);
	new_genotype.insert(new_genotype.end(), m_weights_genotype.begin(), m_weights_genotype.end());
	// ===================================================

	Brain new_brain(new_genotype);

	*this = new_brain;
}