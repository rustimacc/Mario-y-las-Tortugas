#include"enemigo.h"




enemigo::enemigo(Vector2f mousepos,int color) {

	tortuga = color;

	izquierda = false;

	//tiempo = new Clock;;
	//fuera_cola = true;
	
	////////////////////CARGAR GRAFICOS
	switch (color) {//carga solamente los graficos de la tortuga elegida

	case 0://cargar tortuga amarilla
		tortu_tex[0] = new Texture;
		tortu[0] = new Sprite;

		tortu_tex[0]->loadFromFile("imagenes/amarillo.png");
		tortu[0]->setTexture(*tortu_tex[0]);
		break;
	case 1://cargar tortuga azul
		tortu_tex[1] = new Texture;
		tortu[1] = new Sprite;

		tortu_tex[1]->loadFromFile("imagenes/azul.png");
		tortu[1]->setTexture(*tortu_tex[1]);
		break;
	case 2://cargar tortuga verde
		tortu_tex[2] = new Texture;
		tortu[2] = new Sprite;

		tortu_tex[2]->loadFromFile("imagenes/verde.png");
		tortu[2]->setTexture(*tortu_tex[2]);
		break;
	case 3://cargar tortuga roja
		tortu_tex[3] = new Texture;
		tortu[3] = new Sprite;

		tortu_tex[3]->loadFromFile("imagenes/rojo.png");
		tortu[3]->setTexture(*tortu_tex[3]);
		break;
	}//fin del switch

	tortu[tortuga]->setPosition(mousepos.x,mousepos.y);
	


}

void enemigo::dibujar(RenderWindow *app) {

	app->draw(*tortu[tortuga]);

}

void enemigo::movimiento(int dir) {

	switch (dir) {

	case 1://izquierda

		if (tortu[tortuga]->getPosition().x < 630) {
	
			tortu[tortuga]->setPosition(tortu[tortuga]->getPosition().x - 6, tortu[tortuga]->getPosition().y);
		}
		
		if (tortu[tortuga]->getPosition().x < -20 ) {
		
			tortu[tortuga]->setPosition(740, tortu[tortuga]->getPosition().y);
		
		}
		break;
	case 2://izquierda
			if (tortu[tortuga]->getPosition().x <= 800 && tortu[tortuga]->getPosition().x >= 3) {
				
					tortu[tortuga]->setPosition(tortu[tortuga]->getPosition().x - 6, tortu[tortuga]->getPosition().y);
					
			
		}
		break;
	case 3://derecha
			if (tortu[tortuga]->getPosition().x <= 740 && tortu[tortuga]->getPosition().x >= 3) {

				tortu[tortuga]->setPosition(tortu[tortuga]->getPosition().x + 6, tortu[tortuga]->getPosition().y);

				if (tortu[tortuga]->getPosition().x >= 740) {
					tortu[tortuga]->setPosition(740, tortu[tortuga]->getPosition().y);
				}

			}
		
		break;

	}


}

bool enemigo::izquierda_derecha(enemigo *tor,int lado) {

	
	switch (lado) {
	case 1:
		if (tortu[tortuga]->getGlobalBounds().intersects(tor->get_bound())) {


			tortu[tortuga]->setPosition(tor->get_X() + 38, tortu[tortuga]->getPosition().y);


			return true;
		}
		break;
	case 2:
		if (tortu[tortuga]->getGlobalBounds().intersects(tor->get_bound())) {


			tortu[tortuga]->setPosition(tor->get_X() - 38, tortu[tortuga]->getPosition().y);


			return true;
		}
		break;
	}
}