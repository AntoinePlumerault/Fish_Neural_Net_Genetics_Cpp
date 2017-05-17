#ifndef DEF_INDIVIDUAL
#define DEF_INDIVIDUAL

#include <string>
#include <vector>
#include <cstdlib> //rand()
#include <algorithm>

class Individual
{
public:
	virtual Individual * clone() const = 0;
	friend std::vector<Individual> cross_over(Individual const & parent_1, Individual const & parent_2, std::string method);
	virtual void mutation(std::string method, float mutation_probability) = 0;
	float & get_fitness();
	void reset_fitness();
	friend bool operator>(Individual const & individual_1, Individual const & individual_2);
	
protected:
	float  m_fitness;
	std::vector<float> m_genotype;
};

//================ Genotype ================
std::vector<std::vector<float>> cross_over_g(std::vector<float> const & parent_1_genotype, std::vector<float> const & parent_2_genotype, std::string method);
void mutation_g(std::vector<float> genotype, std::string method, float mutation_probability);
//==========================================

#endif