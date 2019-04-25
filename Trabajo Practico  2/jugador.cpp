#include "jugador.h"



jugador::jugador() {

///////////VARIABLES

	salto_ok = false;
	tiempo1 = new Clock;


///////////CARGAR GRAFICOS MARIO

	mariotex = new Texture;
	mario = new Sprite;

	mariotex->loadFromFile("imagenes/mario.png");
	mario->setTexture(*mariotex);
	mario->setOrigin(mariotex->getSize().x / 2, mariotex->getSize().y / 2);
	mario->setScale(0.9, 0.9);
	mario->setPosition(50, 495);



}

void jugador::dibujar(RenderWindow *app) {

	app->draw(*mario);

}


void jugador::mario_movimiento(int dir) {

	switch (dir) {

	case 1:
		if (mario->getPosition().x <= 785) {
			mario->setScale(-0.9, 0.9);
			mario->setPosition(mario->getPosition().x + 25, mario->getPosition().y);
		}
		break;

	case 2:
		if (mario->getPosition().x >= 20) {
			mario->setScale(0.9, 0.9);
			mario->setPosition(mario->getPosition().x - 25, mario->getPosition().y);

		}
		break;

	case 3:
		if (mario->getPosition().y > 100) {

			mario->setPosition(mario->getPosition().x, mario->getPosition().y - 75);

		}
		break;


	}
}