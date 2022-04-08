// Nave

#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
#include<list>

#define up 72
#define left 75
#define right 77
#define down 80


using namespace std;
/*
Posicionar cursor
*/
void gotoxy(int x, int y){
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE); // Obtenemos el control de la consola
	
	COORD dwPos;
	
	dwPos.X = x;
	dwPos.Y = y;
	
	
	SetConsoleCursorPosition(hCon, dwPos);
}

/*
Ocultar cursor
*/
void hideCursor(){

	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE); // Obtenemos el control de la consola
	
	CONSOLE_CURSOR_INFO cci;
	
	cci.dwSize = 1;
	cci.bVisible = false;
	
	SetConsoleCursorInfo(hCon, &cci);
}




/*
Clase nave
*/
class Ship{
	
	int x,y; //Posición de la nave
	int hp; //Corazones
	int lifes; //Vidas
	
	public:
		
		Ship(int x, int y, int hp, int lifes): x(x), y(y), hp(hp), lifes(lifes){}
		void setXY(int _x, int _y){x = _x; y = _y;};
		int getLifes(){return lifes;};
		int X(){return x;};
		int Y(){return y;};
		void decreaseHP(){hp--;};
		
		void printShip();
		void deleteShip();
		void moveShip();
		void printHP();
		void died();
		
};

/*
Matar nave
*/
void Ship::died(){
	if(hp == 0){
		deleteShip();
		gotoxy(x,y);
		printf("   **   ");
		gotoxy(x,y+1);
		printf(" ****  ");
		gotoxy(x,y+2);
		printf("  **   ");
		Sleep(200);
		deleteShip();
		gotoxy(x,y);
		printf(" * ** * ");
		gotoxy(x,y+1);
		printf("  ****  ");
		gotoxy(x,y+2);
		printf(" * ** *  ");
		Sleep(200);
		deleteShip();
		gotoxy(x,y);
		printf(" *     ");
		gotoxy(x,y+1);
		printf(" *   ** ");
		gotoxy(x,y+2);
		printf("      *");
		deleteShip();
		
		lifes--;
		hp = 3;
		
		printHP();
		
		printShip();
	}
}

/*
Pintar límites
*/
void printLimits(){
	for(int i = 2; i < 78 ; i++){
		gotoxy(i,3); printf("%c",205);
		gotoxy(i,33); printf("%c",205);
	}
	
	for(int i = 4; i <33 ; i++){
		gotoxy(2,i); printf("%c",186);
		gotoxy(77,i); printf("%c",186);
	}
	
	
	gotoxy(2,3); printf("%c", 201);
	gotoxy(2,33); printf("%c", 200);
	gotoxy(77,3); printf("%c", 187);
	gotoxy(77,33); printf("%c", 188);
}


/*
Pintar vida de la nave
*/
void Ship::printHP(){
	
	gotoxy(50,2);
	printf("Lives: %d", lifes);
	
	gotoxy(64,2);
	printf("Hp:");
	
	gotoxy(70,2);
	printf("       ");
	
	for(int i = 0; i <hp; i++){
		gotoxy(70+i,2);
		printf("%c",3);
	}
	
}

/*
Pintar nave
*/
void Ship::printShip(){
	
	gotoxy(x,y);  	printf("  %c",30);
	gotoxy(x,y+1);  printf(" %c%c%c",40,207,41);
	gotoxy(x,y+2);  printf("%c%c %c%c",30,190,190,30);
	
}


/*
borrar nave
*/
void Ship::deleteShip(){
	
	gotoxy(x,y);  printf("       ",30);
	gotoxy(x,y+1);  printf("       ",40,207,41);
	gotoxy(x,y+2);  printf("       ",30,190,190,30);
	
}


/*
Mover nave
*/
void Ship::moveShip(){
	
	printHP();
	
	if(kbhit()){
		char key = getch(); //Tecla presionada
		deleteShip();
		//se evaluan los casos
		if(key == left && x>3){
			x--;
		}
		if(key == right && x+6 <77){
			x++;
		}
		
		if(key == up && y>4){
			y--;
		}
		if(key == down && y+3 <33){
			y++;
		}
		
		printShip();
	}
}

/*
Clase asteroide
*/
class Asteroid{
	
	int x,y;
	
	public:
		
		Asteroid(int x, int y): x(x), y(y){}
		int X(){return x;};
		int Y(){return y;};
		void printAsteroid();
		void moveAsteroid();
		void colition(class Ship &S);

};

/*
Colición del asteroide
*/
void Asteroid::colition(class Ship &S){
	
	if(x >= S.X() && x < S.X() + 6 && y >= S.Y() && y<= S.Y()+2){
		
		S.decreaseHP();
		
		S.deleteShip();
		
		S.printShip();
		
		S.printHP();
		
		x = (rand()%71) + 4;
		y = 4;
			
	}
}


/*
Pintar el asteroide
*/
void Asteroid::printAsteroid(){
	
	gotoxy(x,y);
	printf("%c",184);
	
}


/*
Mover el asteroide
*/
void Asteroid::moveAsteroid(){
	
	gotoxy(x,y);
	printf(" ");
	y++;
	
	if(y>32){
		x = (rand()%71) + 4;
		y = 4;
	}
	
	printAsteroid();
	
}

/*
Clase bala
*/
class Bullet{
	int x,y;
	
	public:
		int X() {return x;};
		int Y() {return y;};
		Bullet(int x, int y): x(x), y(y){};
		void moveBullet();
		bool out();
};


/*
Mover la bala
*/
void Bullet::moveBullet(){
	gotoxy(x,y); printf(" ");
	
	if(y > 4){
		y--;	
	}
	
	gotoxy(x,y); printf("%c", 219);
}


/*
Comprobar si la bala llega al borde de la pantalla
*/
bool Bullet::out(){
	if(y == 4) {
		return true;
	}
	else{
		return false;	
	}
}


/*
Método main
*/
int main(){
	
	hideCursor();
	printLimits(); //Marco
	Ship ship(38,30,3,3); //Inicialización de la nave
	
	list<Asteroid* > asteroid;
	list<Asteroid*>:: iterator ita;
	
	
	for(int i = 0; i<5 ; i++){
		asteroid.push_back(new Asteroid(rand()%75 + 4, 4));
	}
	
	list<Bullet*> bullet;
	
	list<Bullet*>:: iterator itb;
	
	ship.printShip();
	
	int score = 0;
	
	bool gameOver = false;
	
	while(!gameOver){
		
		gotoxy(5,2);
		printf("Score: ", score);
		
		if(kbhit()){
			char key = getch();
			
			if(key == 'a'){
				bullet.push_back(new Bullet(ship.X()+ 2, ship.Y()-1));
			}
		}
		for(itb = bullet.begin(); itb != bullet.end(); itb++){
					
			(*itb)->moveBullet();
			
			if((*itb)->out()){
				gotoxy((*itb)->X(), (*itb)->Y());
				printf(" ");
				delete(*itb);
				itb = bullet.erase(itb);
			}
		}
		
		for(ita = asteroid.begin(); ita != asteroid.end(); ita++){
			(*ita)->moveAsteroid();
			(*ita)->colition(ship);
		}
		
		for(ita = asteroid.begin();ita != asteroid.end(); ita++){
			for(itb = bullet.begin(); itb != bullet.end();itb++){
				if(((*ita)->X() == (*itb)->X() && ((*ita)->Y()+1 == (*itb)->Y()) || (*ita)->Y() == (*itb)->Y())){
					gotoxy((*itb)->X(), (*itb)->Y());
					printf(" ");
					delete(*itb);
					itb = bullet.erase(itb);
					
					asteroid.push_back(new Asteroid(rand()%75 + 4, 4));
					gotoxy((*ita)->X(), (*ita)->Y());
					printf(" ");
					delete(*ita);
					ita = asteroid.erase(ita);
					
					score+=5;
				}
			}
		}
		
		gotoxy(5,2);
		printf("Score: ", score);
		
		ship.died();
		ship.moveShip();
		Sleep(30);
		
		if(ship.getLifes() == 0){
			gameOver = true;
		}
	}
	
	return 999;
	
}
