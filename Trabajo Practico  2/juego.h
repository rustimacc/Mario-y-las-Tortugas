#pragma once


#include "jugador.h"
#include"enemigo.h"
#include "nodo.h"
#include <SFML\Graphics.hpp>
#include <iostream>


using namespace sf;

class juego {

private:

	///////////VARIABLES
	RenderWindow * app;
	Event evt;


	Clock *regresivo;

	Time *suma_tiempo;

	Clock *tiempo_cola;
	Clock *tiempo_pila1;
	Clock *tiempo_pila2;
	Clock *tiempo_pila3;
	Clock *tiempo_lado;



	int colacontador = 0;

	int k = 0;

	int ultima_enemigo = 0;
	int pilacontador1 = 0,pilacontador3 = 0,pilacontador5 = 0;
	int pilacontador2 = 3, pilacontador4 = 3,pilacontador6=3;

	bool gameover;

	bool pila_ladoizquierdo;

	int lado;

	float segundos;
	float temp;


	///////////GRAFICOS

	Texture *fondotex;
	Sprite  *fondo;

	Texture *puerta_tex;
	Sprite *puerta;

	///////////LISTAS

	nodo *frente_cola1;
	nodo *fin_cola1;
	nodo *frente_cola3;
	nodo *fin_cola3;
	nodo *frente_cola5;
	nodo *fin_cola5;

	nodo *pila1;
	nodo *pila2;
	nodo *pila3;
	nodo *pila4;
	nodo *pila5;
	nodo *pila6;


	//////////JUGADOR

	jugador *mario;

	/////////ENEMIGOS
	enemigo *tortup1[4];
	enemigo *tortup3[4];
	enemigo *tortup5[4];

	enemigo *tortup2[4];
	enemigo *tortup4[4];
	enemigo *tortup6[4];

	/////////TEXTOS

	Font *fuente;
	Text *texto_tiempo;
public:
	juego();
	void loop();//bucle del juego
	void dibujar();//dibujar en pantalla
	void eventos();//detenccion de teclas en le juego
	void cuenta_regresiva();
	void colisiones();
	
	/////////listas 
		
	//cola
	void insertar_cola(nodo *&frente_cola, nodo *&fin_cola, enemigo *tortuguin,int caso);
	void eliminar_cola(nodo *&frente_cola, nodo *&fin_cola, enemigo *tortuguita,int caso);
	bool cola_vacia(nodo *frente,int caso);//si la cola está vacia
	void largar_enemigos(int caso);//da movimiento a la cola
	void cola();//se encarga de eliminar e insertar enemigos en cola
	
	//pila

	void insertar_pila(nodo *&pila2, enemigo *tortuguita,int lado);
	void eliminar_pila(nodo *&pila2, enemigo *tortuguia,int lado);
	void acomodar_pila();//ordenar fila de la pila
	void pila();
};