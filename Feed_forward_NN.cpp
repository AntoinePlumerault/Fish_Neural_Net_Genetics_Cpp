#include <Eigen\Dense>
#include <vector>
#include <cmath>
#include <iostream>

#include "Feed_forward_NN.hpp"

void Feed_forward_NN::add_layer(unsigned int n_neurons) {
	if (m_architecture.size() != 0) {
		Matrix layer_weights;
		layer_weights = Matrix::Random(n_neurons, m_architecture[m_architecture.size() - 1] + 1);
		layer_weights *= (float)(4. * sqrt(6. / (m_architecture[m_architecture.size() - 1] + n_neurons + 1)));
		m_weights.push_back(layer_weights);
	}
	m_architecture.push_back(n_neurons);
}

Vector Feed_forward_NN::activation(Vector & input) const {
	Vector signal = input;
	signal.conservativeResize(signal.rows() + 1, 1); signal(signal.rows() - 1, 0) = 1; // add bias
	for (unsigned int layer_i = 0; layer_i < m_weights.size(); layer_i++) {
		signal = m_weights[layer_i] * signal;
		for (unsigned int j = 0; j < signal.rows(); j++) {
			signal(j, 0) = (float)(2. * atan(signal(j, 0)) / M_PI); 
		}
		signal.conservativeResize(signal.rows() + 1, 1); signal(signal.rows() - 1, 0) = 1; // add bias
	}
	return signal;
}

void Feed_forward_NN::print() const {
	std::cout << "Brain :" << std::endl;
	for (unsigned int weights_i = 0; weights_i < m_weights.size(); weights_i++) {
		std::cout << "Layer " << weights_i + 1 << std::endl;
		std::cout << m_weights[weights_i] << std::endl;
	}
	std::cout << "Layer " << m_weights.size() + 1 << std::endl;
}