#pragma once

#include<SFML\Graphics.hpp>

using namespace sf;


class jugador {

private:

////////////////VARIABLES
	Clock * tiempo1;
	bool salto_ok;
////////////////GRAFICOS 

	Texture *mariotex;
	Sprite *mario;

public:
	jugador();
	void dibujar(RenderWindow *app);
	void mario_movimiento(int dir);//movimiento del personaje en X e Y
	FloatRect get_bound() { return mario->getGlobalBounds(); };
};