#pragma once

#include <SFML\Graphics.hpp>


using namespace sf;


class enemigo {

private:

	////////////VARIABLES

	int tortuga;//indica que tortuga usar
	//Clock *tiempo;

	bool meterencola;//mueve los enemigos que están el cola




	////////////GRAFICOS 

	Texture *tortu_tex[4];
	Sprite *tortu[4];
	///////////nodos

	enemigo *siguiente;
	enemigo *primerenemigo;
	enemigo *ultimoenemigo;

public:
	enemigo(Vector2f mousepos, int color);

	void dibujar(RenderWindow *app);
	void movimiento(int dir);
	FloatRect get_bound() { return tortu[tortuga]->getGlobalBounds(); };
	int get_X() { return tortu[tortuga]->getPosition().x; };

	//colas
	bool get_fueracola() { return fuera_cola; };
	bool fuera_cola;
	void mover_pos() { tortu[tortuga]->setPosition(tortu[tortuga]->getPosition().x - 32, tortu[tortuga]->getPosition().y); };

	//pilas
	bool izquierda_derecha(enemigo *tor,int lado);
	bool izquierda, derecha;
	bool fuera_pila;
	bool get_fuerapila() { return fuera_pila; };

};
