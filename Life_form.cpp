#include "Life_form.hpp"

Life_form::Life_form(Brain * brain) {
	m_brain = brain;
	Vector position(2, 1);
	position << (float)(rand() % WIDTH), (float)(rand() % HEIGHT);
	m_position = position;

	m_rotation = (float)(std::fmod((rand())/500., 2.*M_PI));
}

void Life_form::move(float distance) {
	m_position(0, 0) += cos(m_rotation)*distance;
	m_position(1, 0) += sin(m_rotation)*distance;

	if (m_position(0) < 0)      { m_position(0) = 0; };
	if (m_position(0) > WIDTH)  { m_position(0) = WIDTH; };
	if (m_position(1) < 0)      { m_position(1) = 0; };
	if (m_position(1) > HEIGHT) { m_position(1) = HEIGHT; };
}

void Life_form::rotate(float rotation) {
	m_rotation = (float)(std::fmod(m_rotation + rotation, 2.*M_PI)); 
}

void Life_form::update_body() {
	m_body.setPosition((float)m_position(0), (float)m_position(1));
	m_body.setRotation((float)(m_rotation*180. / M_PI));
	m_body.setScale((float)(1. + (m_brain->get_fitness()) / 20.), (float)(1. + (m_brain->get_fitness()) / 20.));
}

Vector Life_form::see(std::vector<Life_form*> population, unsigned int precision, unsigned int range) {
	Vector stimulus = Vector::Zero(precision, 1);

	float delta_alpha = (float)(M_PI / precision);

	for (unsigned int i = 0; i < precision; i++) {
		Vector vec_1(2, 1);
		vec_1 << -sin((float)(m_rotation - i*delta_alpha + M_PI / 4)),
			cos((float)(m_rotation - i*delta_alpha + M_PI / 4));
		Vector vec_2(2, 1);
		vec_2 << -sin((float)(m_rotation - (i + 1)*delta_alpha + M_PI / 4)),
			cos((float)(m_rotation - (i + 1)*delta_alpha + M_PI / 4));

		for (Life_form* life_form : population) {
			if (vec_1.dot(life_form->get_position() - m_position) < 0 && vec_2.dot(life_form->get_position() - m_position) > 0) {
				if ((life_form->get_position() - m_position).norm() < range) { stimulus(i, 0) += 1; }
			}
		}
	}
	return stimulus;
}

Vector Life_form::think(Vector input) const {
	return m_brain->activation(input);
}

void Life_form::act(Vector decision) {
	rotate((float)(decision(0, 0) / 3.));
}

void Life_form::eat(std::vector<Life_form*> & list_life_forms) {
	for (Life_form* life_form_p : list_life_forms) {
		if ((m_position - life_form_p->get_position()).norm() < 10) {
			m_brain->get_fitness() += 1;
			life_form_p->m_brain->get_fitness() -= 1;
			Vector new_position(2, 1);
			new_position << (float)(rand() % WIDTH), (float)(rand() % HEIGHT);
			life_form_p->set_position(new_position);
		}
	}
}