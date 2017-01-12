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
	VA.resize(size.x*size.y);
}
void Field::setNrB(unsigned int b) {
	nr_bombs = b;
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
void Field::reset() {
	clear();
	create();
}
void Field::reset(unsigned int x, unsigned int y, unsigned int b) {
	setMap(x, y);
	setNoBombs(b);
	reset();
}
void Field::updateVertex(unsigned int i, bool endgame) {
	if (i < 0 || i > field.size()) 
		return;
	if (field[i].is_flagged) {
		if (!endgame) {
			VA[4 * i].texCoords = sf::Vector2f((float)(2 * tex_size), 0.f);
			VA[4 * i + 1].texCoords = sf::Vector2f((float)(3 * tex_size), 0.f);
			VA[4 * i + 2].texCoords = sf::Vector2f((float)(3 * tex_size), (float)tex_size);
			VA[4 * i + 3].texCoords = sf::Vector2f((float)(2 * tex_size), (float)tex_size);
		}
		else {
			if (field[i].type == Tile::BOMB) {
				VA[4 * i].texCoords = sf::Vector2f((float)(2 * tex_size), 0.f);
				VA[4 * i + 1].texCoords = sf::Vector2f((float)(3 * tex_size), 0.f);
				VA[4 * i + 2].texCoords = sf::Vector2f((float)(3 * tex_size), (float)tex_size);
				VA[4 * i + 3].texCoords = sf::Vector2f((float)(2 * tex_size), (float)tex_size);
			}
			else {
				VA[4 * i].texCoords = sf::Vector2f((float)(15 * tex_size), 0.f);
				VA[4 * i + 1].texCoords = sf::Vector2f((float)(16 * tex_size), 0.f);
				VA[4 * i + 2].texCoords = sf::Vector2f((float)(16 * tex_size), (float)tex_size);
				VA[4 * i + 3].texCoords = sf::Vector2f((float)(15 * tex_size), (float)tex_size);
			}
		}
		return;
	}
	if (field[i].is_revealed) {
		int type = field[i].type;
		VA[4 * i].texCoords = sf::Vector2f((float)(tex_size*(4 + (int)type)), 0.f);
		VA[4 * i + 1].texCoords = sf::Vector2f((float)(tex_size*(5 + (int)type)), 0.f);
		VA[4 * i + 2].texCoords = sf::Vector2f((float)(tex_size*(5 + (int)type)), (float)tex_size);
		VA[4 * i + 3].texCoords = sf::Vector2f((float)(tex_size*(4 + (int)type)), (float)tex_size);
	}
	else {
		if (field[i].is_pressed) {
			VA[4 * i].texCoords = sf::Vector2f((float)tex_size, 0.f);
			VA[4 * i + 1].texCoords = sf::Vector2f(2 * (float)tex_size, 0.f);
			VA[4 * i + 2].texCoords = sf::Vector2f(2 * (float)tex_size, (float)tex_size);
			VA[4 * i + 3].texCoords = sf::Vector2f((float)tex_size, (float)tex_size);
		}
		else {
			VA[4 * i].texCoords = sf::Vector2f(0.f, 0.f);
			VA[4 * i + 1].texCoords = sf::Vector2f((float)tex_size, 0.f);
			VA[4 * i + 2].texCoords = sf::Vector2f((float)tex_size, (float)tex_size);
			VA[4 * i + 3].texCoords = sf::Vector2f(0.f, (float)tex_size);
		}
	}
}
void Field::updateVertex(unsigned int x, unsigned int y, bool endgame) {
	updateVertex(y*size.y + x, endgame);
}
void Field::updateAllVertex(bool endgame, bool force) {
	bool was_debugging = is_debugging;
	is_debugging = false;
	unsigned int no_updates = 0;
	for (uint i = 0; i < field.size(); ++i) {
		if (field[i].update_vertex || force) {
			updateVertex(i, endgame);
			field[i].update_vertex = false;
			no_updates++;
		}
	}
	is_debugging = was_debugging;
}
bool Field::isWon() {
	if (is_won)
		return true;
	unsigned int nr_revealed = 0;
	for (uint i = 0; i < field.size(); ++i)
		nr_revealed += field[i].is_revealed;
	if (nr_revealed == field.size() - nr_bombs)
		return (is_won = true);
	return false;
}
bool Field::isLost() {
	return is_lost;
} 
void Field::addBombs() {
	if (nr_bombs > size.x*size.y) 
		return;
	unsigned int bombs_on_field = 0;
	for (unsigned int i = 0; i < field.size(); ++i) {
		if (field[i].type == Tile::BOMB) {
			bombs_on_field += 1;
		}
	}
	while (bombs_on_field < nr_bombs) {
		int r = rand() % (size.y*size.x);
		if (field[r].type != Tile::BOMB) {
			field[r].type = Tile::BOMB;
			bombs_on_field += 1;
		}
	}
}