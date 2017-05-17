#ifndef DEF_LIFE_FORM
#define DEF_LIFE_FORM

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Eigen\Dense>
#include <cmath>

#include "Brain.hpp"

#define WIDTH (900)
#define HEIGHT (900)

typedef Eigen::Matrix<float, Eigen::Dynamic, 1> Vector;

class Life_form {
public:
	Life_form(Brain * brain);
	virtual Life_form * clone() const = 0;
	void set_position(Vector position) { m_position = position; }
	void set_rotation(float rotation) { m_rotation = rotation; }
	Vector get_position() const { return m_position; }
	float get_rotation() const { return m_rotation; }
	sf::ConvexShape get_body() { return m_body; }
	void move(float distance);
	void rotate(float rotation);
	void update_body();
	
	//==================== Life ====================
	Vector see(std::vector<Life_form*> population, unsigned int precision, unsigned int range);
	Vector think(Vector input) const;
	void act(Vector decision);
	void eat(std::vector<Life_form*> & list_life_forms);
	//==============================================

protected:
	Vector m_position;
	Brain * m_brain;
	float m_rotation; //radiants [0,2*pi]
	sf::ConvexShape m_body;
};

#endif