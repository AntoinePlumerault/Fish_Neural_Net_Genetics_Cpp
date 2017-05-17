#include "Plankton.hpp"

Plankton::Plankton(Brain* brain) : Life_form(brain) {
	sf::Color color(0, 0, 0, 100);
	m_body.setPointCount(4);
	m_body.setPoint(1, sf::Vector2f(-3, -3));
	m_body.setPoint(0, sf::Vector2f(-3, 3));
	m_body.setPoint(2, sf::Vector2f(3, -3));
	m_body.setPoint(3, sf::Vector2f(3, 3));
	m_body.setFillColor(color);
}

Life_form * Plankton::clone() const {
	return new Plankton(*this); 
}

void Plankton::update_body() {
	m_body.setPosition((float)m_position(0), (float)m_position(1));
	m_body.setRotation((float)m_rotation);
}