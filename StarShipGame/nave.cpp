// Nave

#include<stdio.h>
#include<windows.h>
#include<conio.h>

#define up 72
#define left 75
#define right 77
#define down 80

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
	int hp;
	int lifes;
	
	public:
		
		Ship(int x, int y, int hp, int lifes): x(x), y(y), hp(hp), lifes(lifes){}
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
	
	gotoxy(64,2);
	printf("Hp:");
	
	gotoxy(50,2);
	printf("Lifes: %d", lifes);
	
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
			if(key == 'e'){
				hp--;
			}
			if(key == left && x>3){
				x--;
			}
			if(key == right && x+6 < 77){
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
Método main
*/
int main(){
	
	hideCursor();
	printLimits(); //Marco
	Ship ship(38,30,3,3); //Inicialización de la nave
	
	ship.printShip();
	
	bool gameOver = false;
	
	while(!gameOver){
		
		ship.moveShip();
		
		if(ship.hp == 0){
			ship.died();
			ship.lifes--;
		}
		
		Sleep(30);
		
	}
	
	return 0;
}
