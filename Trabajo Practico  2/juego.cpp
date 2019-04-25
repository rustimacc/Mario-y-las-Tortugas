#include"juego.h"


juego::juego() {

	app = new RenderWindow(VideoMode(800, 600), "Trabajo Practico pilas y colas");
	app->setFramerateLimit(60);



	regresivo = new Clock;
	temp = 30;

	tiempo_cola = new Clock;
	
	tiempo_pila1 = new Clock; 
	tiempo_pila2 = new Clock;
	tiempo_pila3 = new Clock;

	tiempo_lado = new Clock;

	gameover = false;

	pila_ladoizquierdo = false;
	lado = 1;
	/////////GRAFICOS

	fondotex = new Texture;
	fondo = new Sprite;

	puerta_tex = new Texture;
	puerta = new Sprite;

	puerta_tex->loadFromFile("imagenes/puerta.png");
	puerta->setTexture(*puerta_tex);
	puerta->setPosition(385, 22);
	puerta->setScale(1.1, 1.1);

	fondotex->loadFromFile("imagenes/fondo.png");
	fondo->setTexture(*fondotex);
	fondo->setScale((float)app->getSize().x / fondotex->getSize().x, (float)app->getSize().y / fondotex->getSize().y);


	///////textos

	fuente = new Font;
	texto_tiempo = new Text;
	
	fuente->loadFromFile("fuente.ttf");

	texto_tiempo->setFont(*fuente);
	texto_tiempo->setFillColor(Color::White);
	texto_tiempo->setCharacterSize(30);
	texto_tiempo->setPosition(700, 15);

	//////////JUGADOR

	mario = new jugador;

	/////////ENEMIGOS


	///////pisos con colas 
	tortup1[0] = new enemigo({ 650,420 }, 0);
	tortup1[1] = new enemigo({ 680,420 }, 1);
	tortup1[2] = new enemigo({ 710,420 }, 2);
	tortup1[3] = new enemigo({ 740,420 }, 3);

	tortup3[0] = new enemigo({ 650,270 }, 0);
	tortup3[1] = new enemigo({ 680,270 }, 1);
	tortup3[2] = new enemigo({ 710,270 }, 2);
	tortup3[3] = new enemigo({ 740,270 }, 3);


	tortup5[0] = new enemigo({ 650,120 }, 0);
	tortup5[1] = new enemigo({ 680,120 }, 1);
	tortup5[2] = new enemigo({ 710,120 }, 2);
	tortup5[3] = new enemigo({ 740,120 }, 3);

	tortup2[0] = new enemigo({ 650,345 }, 0);
	tortup2[1] = new enemigo({ 680,345 }, 1);
	tortup2[2] = new enemigo({ 710,345 }, 2);
	tortup2[3] = new enemigo({ 740,345 }, 3);

	tortup4[0] = new enemigo({ 650,195 }, 0);
	tortup4[1] = new enemigo({ 680,195 }, 1);
	tortup4[2] = new enemigo({ 710,195 }, 2);
	tortup4[3] = new enemigo({ 740,195 }, 3);

	tortup6[0] = new enemigo({ 650,45 }, 0);
	tortup6[1] = new enemigo({ 680,45 }, 1);
	tortup6[2] = new enemigo({ 710,45 }, 2);
	tortup6[3] = new enemigo({ 740,45 }, 3);

	////////LISTAS

	frente_cola1 = NULL;
	fin_cola1 = NULL;
	frente_cola3 = NULL;
	fin_cola3 = NULL;
	frente_cola5 = NULL;
	fin_cola5 = NULL;

	pila1 = NULL;
	pila2 = NULL;
	pila3 = NULL;
	pila4 = NULL;
	pila5 = NULL;
	pila6 = NULL;


	for(int i = 0; i < 4; i++) {//insertar enemigos en listas

		insertar_cola(frente_cola1,fin_cola1,tortup1[i],1);
		insertar_cola(frente_cola3, fin_cola3, tortup3[i],3);
		insertar_cola(frente_cola5, fin_cola5, tortup5[i],5);
		insertar_pila(pila2, tortup2[i],2);
		insertar_pila(pila4, tortup4[i],2);
		insertar_pila(pila6, tortup6[i],2);
		
	}
	
	/////////FUNCIONES

	loop();
}

void juego::loop() {

	while (app->isOpen()) {

		dibujar();
		eventos();



		///////////FUNCIONES DEL JUGADOR

		colisiones();

		//////////FUNCIONES DE ENEMIGOS

		cola();
		
		if (!gameover) {
			for (int j = 0; j < 4; j++) {
				if (tortup1[j]->get_fueracola()) {
					tortup1[j]->movimiento(1);
				}
				if (tortup3[j]->get_fueracola()) {
					tortup3[j]->movimiento(1);
				}
				if (tortup5[j]->get_fueracola()) {
					tortup5[j]->movimiento(1);
				}
				//////pilas
				if (lado == 1) {
					if (tortup2[j]->get_fueracola()) {
						tortup2[j]->movimiento(2);
					}
					if (tortup4[j]->get_fueracola()) {
						tortup4[j]->movimiento(2);
					}
					if (tortup6[j]->get_fueracola()) {
						tortup6[j]->movimiento(2);
					}
				}
				if (lado == 2) {
					if (tortup2[j]->get_fueracola()) {
						tortup2[j]->movimiento(3);
					}
					if (tortup4[j]->get_fueracola()) {
						tortup4[j]->movimiento(3);
					}
					if (tortup6[j]->get_fueracola()) {
						tortup6[j]->movimiento(3);
					}
				}



				

			}
		}
		pila();

		acomodar_pila();		
		
		///////////TEXTOS
		//cuenta_regresiva();
	}
}

void juego::dibujar() {

	app->clear();


	app->draw(*fondo);//dibujar fondo

	app->draw(*puerta);

	mario->dibujar(app);


	for (int l = 0; l < 4; l++) {
		tortup1[l]->dibujar(app);
		tortup3[l]->dibujar(app);
		tortup5[l]->dibujar(app);
		tortup2[l]->dibujar(app);
		tortup4[l]->dibujar(app);
		tortup6[l]->dibujar(app);
	}
	app->draw(*texto_tiempo);//dibujar cuenta regresiva

	

	app->display();

}

void juego::eventos() {

	if (app->pollEvent(evt)) {

		switch (evt.type) {

		case Event::Closed:
			exit(1);

		case Event::KeyPressed:
			if (evt.key.code == Keyboard::Escape) { exit(1); };//al presionar Escape se cierra la aplicacion
			if (evt.key.code == Keyboard::R) { app->close(); new juego; };//reiniciar juego

			if (!gameover) {//si no se perdió o ganó se puede jugar
			if (evt.key.code == Keyboard::A) {mario->mario_movimiento(2); };//izquierda
			if (evt.key.code == Keyboard::D) {mario->mario_movimiento(1); };//derecha
			if (evt.key.code == Keyboard::W) {mario->mario_movimiento(3); };//salto

			if (evt.key.code == Keyboard::Left) { mario->mario_movimiento(2); };//izquierda
			if (evt.key.code == Keyboard::Right) { mario->mario_movimiento(1); };//derecha
			if (evt.key.code == Keyboard::Up) { mario->mario_movimiento(3); };//salto

			if (evt.key.code == Keyboard::Space) {
				if (lado == 1) {
					lado = 2;
				}
				else {
					lado = 1;
				}
				//cout << lado << endl;
			};
			}//bucle game over
			
			}//movimiento personaje
			}
		}


void juego::cuenta_regresiva() {

	char letras[10];
	if (!gameover) {//si el juego no terminó, el tiempo corre
		segundos = temp - regresivo->getElapsedTime().asSeconds();//cuenta regresiva de 30 segundos
		_itoa_s(segundos, letras, 10);
		texto_tiempo->setString(letras);//escribir tiempo que queda en pantalla
	}
	

	if (segundos <= 0) {//si el timepo llega a 0, se termina la partida
		
		gameover = true;
		texto_tiempo->setPosition(270, 90);
		texto_tiempo->setCharacterSize(100);
		texto_tiempo->setString("¡Perdiste¡");
	}
	

	

}

void juego::colisiones() {

	if (puerta->getGlobalBounds().intersects(mario->get_bound())) {//si jugador colisiona con puerta, gana

		gameover = true;//se termina el juego

		texto_tiempo->setPosition(60,90);
		texto_tiempo->setCharacterSize(100);
		texto_tiempo->setString("¡Ganaste prodigix del vicio¡");

	}
	
	for (int i = 0; i < 4; i++) {
		if (mario->get_bound().intersects(tortup1[i]->get_bound())|| mario->get_bound().intersects(tortup3[i]->get_bound())|| mario->get_bound().intersects(tortup5[i]->get_bound())) {
			gameover = true;//se termina el juego

			texto_tiempo->setPosition(270, 90);
			texto_tiempo->setCharacterSize(100);
			texto_tiempo->setString("¡PERDISTE¡");
		}
		if (mario->get_bound().intersects(tortup2[i]->get_bound()) || mario->get_bound().intersects(tortup4[i]->get_bound()) || mario->get_bound().intersects(tortup6[i]->get_bound())) {
			gameover = true;//se termina el juego

			texto_tiempo->setPosition(270, 90);
			texto_tiempo->setCharacterSize(100);
			texto_tiempo->setString("¡PERDISTE¡");
		}


	}



}

//////////////////listas

///////COLAS
void juego::insertar_cola(nodo *&frente_cola, nodo *&fin_cola, enemigo *tortuguin,int caso) {
	
	    
		nodo *nuevonodo = new nodo;

		nuevonodo->tortu = tortuguin;
		
		nuevonodo->siguiente = NULL;

		if (cola_vacia(frente_cola,caso)) {
			frente_cola = nuevonodo;
		}
		else {

			fin_cola->siguiente = nuevonodo;
		}
		fin_cola = nuevonodo;

		//cout << "el elemento se inserto correctamente" << endl;

	
}

bool juego::cola_vacia(nodo *frente, int caso) {
	switch (caso) {

	case 1:
		if (frente_cola1 == NULL) { return true; }
		else { return false; };
		break;
	case 3:
		if (frente_cola3 == NULL) { return true; }
		else { return false; };
		break;
	case 5:
		if (frente_cola5 == NULL) { return true; }
		else { return false; };
		break;

	}
}

void juego::eliminar_cola(nodo *&frente_cola, nodo *&fin_cola, enemigo *tortuguita,int caso) {
	
	
	tortuguita=frente_cola->tortu;

	nodo *temp = frente_cola;
	
	

	if (frente_cola == fin_cola) {
		frente_cola = NULL;
		fin_cola = NULL;
	}
	else {
		frente_cola = frente_cola->siguiente;
	}
	
	largar_enemigos(caso);
	tortuguita->fuera_cola = true;
	
	delete temp;
	
}
void juego::largar_enemigos(int caso) {//esta funcion va moviendo una posicion los enemigos en cola

	switch (caso) {
	case 1:
		for (int k = 0; k < 4; k++) {

			tortup1[k]->mover_pos();
		}
		break;
	case 3:
		for (int k = 0; k < 4; k++) {

			tortup3[k]->mover_pos();
		}
		break;
	case 5:
		for (int k = 0; k < 4; k++) {

			tortup5[k]->mover_pos();
		}
		break;
	}
	
}
void juego::cola() {


	if (colacontador == 3) {//volver a insertar enemigo en cola
		colacontador = 0;
	}

	if (tiempo_cola->getElapsedTime().asSeconds() > 2.5f) {
		eliminar_cola(frente_cola1, fin_cola1, tortup1[colacontador],1);
		eliminar_cola(frente_cola3, fin_cola3, tortup3[colacontador],3);
		eliminar_cola(frente_cola5, fin_cola5, tortup5[colacontador],5);

		insertar_cola(frente_cola1, fin_cola1, tortup1[colacontador],1);
		insertar_cola(frente_cola3, fin_cola3, tortup3[colacontador],3);
		insertar_cola(frente_cola5, fin_cola5, tortup5[colacontador],5);

		colacontador++;
		tiempo_cola->restart();
	}
	
	
 }

///////PILAS

void juego::insertar_pila(nodo *&pila2, enemigo *tortuguita,int lado) {

	nodo *nuevo_nodo = new nodo;
	nuevo_nodo->tortu = tortuguita;
	nuevo_nodo->siguiente = pila2;
	tortuguita->fuera_cola = false;
	pila2 = nuevo_nodo;

	//cout << "\n se agrego joya papa!!!" << endl;
}

void juego::eliminar_pila(nodo *&pila2, enemigo *tortuguita,int lado) {

	nodo *aux = pila2;
	aux->tortu = tortuguita;
	pila2 = aux->siguiente;
	tortuguita->fuera_cola = true;
	k++;
	//cout << "bye bye" << endl;
	delete aux;
}

void juego::pila() {
	
	if (pila2 == NULL) {

		if (tiempo_lado->getElapsedTime().asSeconds() > 10) {
			lado = 2;
			tiempo_lado->restart();
		}

	}
	if (pila1 == NULL) {

		if (tiempo_lado->getElapsedTime().asSeconds() > 10) {
			lado = 1;
			tiempo_lado->restart();
		}

	}




	if (lado==1) {
		pilacontador2 = 3;
		pilacontador4 = 3;
		pilacontador6 = 3;
		if (tiempo_pila1->getElapsedTime().asSeconds() > 2) {
			if (pila2 != NULL) {
				eliminar_pila(pila2, tortup2[pilacontador1], 1);

				pilacontador1++;
				//ultima_enemigo++;
				
				tiempo_pila1->restart();
				

			}
		
	}
		if (tiempo_pila2->getElapsedTime().asSeconds() > 2) {
			if (pila4 != NULL) {
				eliminar_pila(pila4, tortup4[pilacontador3], 1);

				pilacontador3++;
				//ultima_enemigo++;

				tiempo_pila2->restart();


			}

		}
		if (tiempo_pila3->getElapsedTime().asSeconds() > 2) {
			if (pila6 != NULL) {
				eliminar_pila(pila6, tortup6[pilacontador5], 1);

				pilacontador5++;
				//ultima_enemigo++;

				tiempo_pila3->restart();


			}

		}
		
	}
	
	if (lado==2) {
		
		pilacontador1 = 0;
		pilacontador3 = 0;
		pilacontador5 = 0;
		if (pila1 != NULL) {
		if (tiempo_pila1->getElapsedTime().asSeconds() > 2) {
			
				eliminar_pila(pila1, tortup2[pilacontador2], 1);

				pilacontador2--;
				//ultima_enemigo++;
				tiempo_pila1->restart();

			}
			
		}
		if (pila3 != NULL) {
			if (tiempo_pila2->getElapsedTime().asSeconds() > 2) {

				eliminar_pila(pila3, tortup4[pilacontador4], 1);

				pilacontador4--;
				//ultima_enemigo++;
				tiempo_pila2->restart();

			}

		}
		if (pila5 != NULL) {
			if (tiempo_pila3->getElapsedTime().asSeconds() > 2) {

				eliminar_pila(pila5, tortup6[pilacontador6], 1);

				pilacontador6--;
				//ultima_enemigo++;
				tiempo_pila3->restart();

			}

		}

	}
	
}

void juego::acomodar_pila() {
	//cout << "\t\t" << tortup2[0]->get_X();

	//cout <<endl<< tortup6[3]->get_X();
	for (int j = 0; j < 4; j++) {
		if (lado == 1) {

			if (tortup2[0]->get_X() <= 8 && pila1 == NULL) {//si tortu está en la pos 8 y la pila es null agregar a la pila
				insertar_pila(pila1, tortup2[0], 1);
			}

			if (tortup2[j]->get_X() < 400) {

				if (tortup2[j]->izquierda_derecha(tortup2[j - 1], 1)) {//si tortu colisiona con tortu anterior, agregar a la pila
					insertar_pila(pila1, tortup2[j], 1);
				}
			}
			///////
			if (tortup4[0]->get_X() <= 8 && pila3 == NULL) {//si tortu está en la pos 8 y la pila es null agregar a la pila
				insertar_pila(pila3, tortup4[0], 1);
			}

			if (tortup4[j]->get_X() < 400) {

				if (tortup4[j]->izquierda_derecha(tortup4[j - 1], 1)) {//si tortu colisiona con tortu anterior, agregar a la pila
					insertar_pila(pila3, tortup4[j], 1);
				}
			}

			////////
			if (tortup6[0]->get_X() <= 8 && pila5 == NULL) {//si tortu está en la pos 8 y la pila es null agregar a la pila
				insertar_pila(pila5, tortup6[0], 1);
			}

			if (tortup6[j]->get_X() <= 400) {

				if (tortup6[j]->izquierda_derecha(tortup6[j - 1], 1)) {//si tortu colisiona con tortu anterior, agregar a la pila
					insertar_pila(pila5, tortup6[j], 1);
				}
			}


		}
		if (lado == 2) {
			if (tortup2[3]->get_X() >= 740 && pila2 == NULL) {
				insertar_pila(pila2, tortup2[3], 2);
			}

			if (tortup2[j]->get_X() > 400) {

				if (tortup2[j]->izquierda_derecha(tortup2[j + 1], 2)) {
					insertar_pila(pila2, tortup2[j], 2);

				}
			}
			
			//////////

			if (tortup4[3]->get_X() >= 740 && pila4 == NULL) {
				insertar_pila(pila4, tortup4[3], 2);
			}

			if (tortup4[j]->get_X() > 400) {

				if (tortup4[j]->izquierda_derecha(tortup4[j + 1], 2)) {
					insertar_pila(pila4, tortup4[j], 2);

				}
			}
			
			/////////
			
			if (tortup6[3]->get_X() >= 740 && pila6 == NULL) {
				insertar_pila(pila6, tortup6[3], 2);
			}

			if (tortup6[j]->get_X() > 600) {
				if (j != 3) {
					if (tortup6[j]->izquierda_derecha(tortup6[j + 1], 2)) {
						insertar_pila(pila6, tortup6[j], 2);
					}
				}
				
			}
			
		}

	}
	}
	



