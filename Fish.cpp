#include "Fish.hpp"

Fish::Fish(Brain* brain) : Life_form(brain) {
	sf::Color color(250, 50, 50, 250);
	m_body.setPointCount(3);
	m_body.setPointCount(3);
	m_body.setPoint(0, sf::Vector2f(10, 0));
	m_body.setPoint(1, sf::Vector2f(-10, -5));
	m_body.setPoint(2, sf::Vector2f(-10, 5));
	m_body.setFillColor(color);
	m_body.setOrigin(0, 0);
	m_body.setPosition(0, 0);
	m_body.setRotation(0);
}

Life_form * Fish::clone() const { 
	return new Fish(*this); 
}