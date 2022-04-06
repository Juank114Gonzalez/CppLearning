// Nave

#include<stdio.h>
#include<windows.h>
#include<conio.h>

#define up 72
#define left 75
#define right 77
#define down 80

void gotoxy(int x, int y){
	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE); // Obtenemos el control de la consola
	
	COORD dwPos;
	
	dwPos.X = x;
	dwPos.Y = y;
	
	
	SetConsoleCursorPosition(hCon, dwPos);
}

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
	
	public:
		
		Ship(int x, int y): x(x), y(y){}
		void printShip();
		void deleteShip();
		void moveShip();
};

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

void Ship::printShip(){
	
	gotoxy(x,y);  	printf("  %c",30);
	gotoxy(x,y+1);  printf(" %c%c%c",40,207,41);
	gotoxy(x,y+2);  printf("%c%c %c%c",30,190,190,30);
	
}

void Ship::deleteShip(){
	
	gotoxy(x,y);  printf("      ",30);
	gotoxy(x,y+1);  printf("      ",40,207,41);
	gotoxy(x,y+2);  printf("      ",30,190,190,30);
	
}

void Ship::moveShip(){
	if(kbhit()){
			char key = getch(); //Tecla presionada
			deleteShip();
			//se evaluan los casos
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
	printLimits();
	Ship ship(38,30);
	
	ship.printShip();
	
	bool gameOver = false;
	
	while(!gameOver){
		
		ship.moveShip();
		
		Sleep(30);
		
	}
	
	
	return 0;
}
