#ifndef DEF_PERCEPTRON
#define DEF_PERCEPTRON

#include <string>
#include <Eigen\Dense>
#include <vector>
#include <iostream>

#include "Individual.hpp"

typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> Mat;
typedef Eigen::Matrix<double, Eigen::Dynamic, 1> Vec;

class Perceptron : public Individual
{
public:
	Perceptron();
	Perceptron(std::vector<unsigned int> const & architecture);
	Perceptron(std::vector<unsigned int> const & architecture, std::vector<double> const & genotype);

	Vec activation(Vec const & inputs) const;
	void mutation();

	friend std::vector<Perceptron> cross_over(Perceptron const & individual_1, Perceptron const & individual_2, std::string method = "uniform");
	Individual* clone() const { return new Perceptron(*this); };

private:
	std::vector<Mat> m_weights;
	std::vector<unsigned int> m_architecture;
	std::vector<double> m_genotype;
};

#endif


