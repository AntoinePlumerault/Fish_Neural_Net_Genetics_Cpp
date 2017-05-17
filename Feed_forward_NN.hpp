#ifndef DEF_FEED_FORWARD_NN
#define DEF_FEED_FORWARD_NN

#include <Eigen\Dense>
#include <vector>

typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> Matrix;
typedef Eigen::Matrix<float, Eigen::Dynamic, 1> Vector;

class Feed_forward_NN {
public:
	void add_layer(unsigned int n_neurons);
	Vector activation(Vector & input) const;
	void print() const;

protected:
	std::vector<Matrix> m_weights;
	std::vector<int> m_architecture;
};

#endif