#include <functii.h>
#include <Header1.h>
#pragma once
Field::Field(bool bug) : is_debugging(bug) {
	setFieldSize(10, 10);
	setNoBombs(20);
	clear(10, 10);
}
Field::Field(int w, int h, int b, bool bug) : is_debugging(bug) {
	setFieldSize(w, h);
	setNoBombs(b);
	clear(w, h);
}
Field::Field(const Field &copy) {
	this->size.x = copy.size.x;
	this->size.y = copy.size.y;
	this->tex_size = copy.tex_size;
	this->draw_size = copy.draw_size;

	for (unsigned int i = 0; i < field.size(); ++i) {
		this->field[i] = copy.field[i];
	}
}
void Field::setMap(sf::Vector2u s) {
	setFieldSize(s.x, s.y);
}
void Field::setMap(unsigned int x, unsigned int y) {
	size.x = x;
	size.y = y;
	field.resize(size.x*size.y);
	//
}
void Field::setNrB(unsigned int b) {
	no_bombs = b;
}
void Field::create(unsigned int x, unsigned int y, unsigned int b) {
	setMap(x, y);
	setNrB(b);
	create();
}
void Field::create() {
	addBombs();
	initNumbers();
	VA = sf::VertexArray(sf::Quads, 4 * size.x*size.y);
	initVertex();
	makeRandomSpecial();
	m_state = INITIALIZED;
}

