#pragma once
#include <Header1.h>
class Field() {

public:
	enum State{Neinitializata,Initializata};
	Field(bool = false);
	Field(int ox, int oy, int b, bool = false);
	Field(const Field&);
	

	//functii
	void SetMap(sf::Vector2u);//Creez Harta
	void SetMap(unsigned int, unsigned int);//
	void SetNrB(unsigned int);//numarul de bombe
	void create();//initializez bombele, valorile fiecarui element
	void create(uint x, uint y, uint);//
	
	void reset();
	void reset(uint x, uint y, uint);
	void updateVertex(uint, bool endgame = false);
	void updateVertex(uint, uint, bool endgame = false);
	void updateAllVertex(bool endgame = false, bool force = false);
	bool isWon();
	bool isLost();
	void coutField();
	void draw();
	private:{	
	void addBombs();			
	void initNumbers();			
	void initVertex();
	void clear();
	void clear(int x, int y);
	}
	state m_state;
	sf::Vector2u size;
	unsigned int nr_bombs, nr_flags;
	bool is_won, is_lost;
	bool is_debugging;

};