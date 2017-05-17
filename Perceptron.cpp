#include <Eigen\Dense>
#include <vector>
#include <cmath>

#include "Perceptron.hpp"
Perceptron::Perceptron() {

}

Perceptron::Perceptron(std::vector<unsigned int> const & architecture) {
	m_architecture = architecture;

	for (unsigned int layer_index = 1; layer_index < architecture.size(); layer_index++) {
		Mat layer_weights;
		layer_weights = Mat::Random(architecture[layer_index], architecture[layer_index-1]);
		layer_weights *= 4. * sqrt(6. / (architecture[layer_index-1] + architecture[layer_index]));
		m_weights.push_back(layer_weights);
	}

	for (unsigned int layer_index = 0; layer_index < m_weights.size(); layer_index++) {
		for (unsigned int i = 0; i < m_weights[layer_index].cols(); i++) {
			for (unsigned int j = 0; j < m_weights[layer_index].rows(); j++) {
				m_genotype.push_back(m_weights[layer_index](j, i));
			}
		}
	}
}

Perceptron::Perceptron(std::vector<unsigned int> const & architecture, std::vector<double> const & genotype) : Perceptron(architecture) {
	m_genotype = genotype;

	int genotype_index = 0;
	for (unsigned int layer_index = 1; layer_index < m_weights.size(); layer_index++) {
		for (unsigned int i = 0; i < m_weights[layer_index].cols(); i++) {
			for (unsigned int j = 0; j < m_weights[layer_index].rows(); j++) {
				m_weights[layer_index](j, i) = genotype[genotype_index];
				genotype_index += 1;
			}
		}
	}
}

Vec Perceptron::activation(Vec const & inputs) const {
	Vec signal = inputs;
	for (unsigned int layer_index = 0; layer_index < m_weights.size(); layer_index++) {
		signal = m_weights[layer_index] * signal;
		for (unsigned int j = 0; j < signal.size(); j++) {
			signal(j, 0) = 2. * atan(signal(j, 0)) / M_PI;
		}
	}
	return signal;
}

std::vector<Perceptron> cross_over(Perceptron const & perceptron_1, Perceptron const & perceptron_2, std::string method) {
	std::vector<std::vector<double>> new_genotypes = cross_over(perceptron_1.m_genotype, perceptron_2.m_genotype, method); 

	Perceptron new_perceptron_1(perceptron_1.m_architecture, new_genotypes[0]);
	Perceptron new_perceptron_2(perceptron_2.m_architecture, new_genotypes[1]);

	std::vector<Perceptron> new_perceptrons(2);
	new_perceptrons[0] = new_perceptron_1;
	new_perceptrons[1] = new_perceptron_2;

	return new_perceptrons;
}

void Perceptron::mutation(){
	// See theory
}
