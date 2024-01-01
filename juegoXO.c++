#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

char tablero[3][3];
char letraJugador = 'X';
bool sePuedeSeguirJugando = true;

//prototipo de las funciones
void llenarMatriz();
void mostrarTablero();
void mostrarMenu();
bool verificarSiHayEspacio();
void setearCoordenadaComputadora();
void setearCoordenadaJugador(int &fila, int &columna);
void jugar();
void mostrarMensajeGanador(char letra);
bool verificarSiHayGanador();


int main(int argc, char **argv) {
	setlocale(LC_ALL, "spanish");
	cout<<"*******************************"<<endl;
	cout<<"\tJuego de X - 0"<<endl;
	cout<<"*******************************"<<endl;
	
	llenarMatriz();	
	mostrarMenu();
	
	while(sePuedeSeguirJugando){
		jugar();
		mostrarTablero();
		
		bool hayUnGanador = verificarSiHayGanador();
		sePuedeSeguirJugando = !hayUnGanador;
		
		bool hayEspacio = verificarSiHayEspacio();
		if(!hayEspacio){
			cout<<"\nNo hay ganador, es un empate!\n";
			sePuedeSeguirJugando = false;
		}
	}
}

void llenarMatriz(){
	for(int i = 0 ; i < 3 ; i++){
		for(int j = 0 ; j < 3 ; j++){
			tablero[i][j] = ' ';
		}
	}
}

void mostrarTablero(){
	printf(" %c | %c | %c", tablero[0][0], tablero[0][1], tablero[0][2]);
	printf("\n___|___|___\n");
	printf(" %c | %c | %c", tablero[1][0], tablero[1][1], tablero[1][2]);
	printf("\n___|___|___\n");
	printf(" %c | %c | %c", tablero[2][0], tablero[2][1], tablero[2][2]);
	printf("\n   |   |  \n");
	printf("\n");	
}

void mostrarMenu(){
	int opcion = 0;
	
	cout<<	"\nMenú \n"
	    	"1.- X\n2.- O\n";
	
	do{
		cout<<"\nIngrese una opción: ";
		cin >> opcion;
		
		switch(opcion){
			case 1:
				cout << "JUGADOR: X\nCOMPUTADORA: O\n";
				break;
			case 2:
				cout << "JUGADOR: O\nCOMPUTADORA: X\n";
				break;
			default:
				cout << "Favor ingrese una opción valida del menú\n";
		}
	}while(opcion <=0 || opcion >2);		 
	
	letraJugador = opcion == 1 ? 'X' : 'O';	
}

bool verificarSiHayEspacio(){
	int espaciosLibres = 9;
	
	for(int i = 0 ; i < 3 ; i++){
		for(int j = 0 ; j < 3 ; j++){
			if(tablero[i][j] != ' '){
				espaciosLibres--;
			}
		}
	}
	
	return espaciosLibres > 0;
}

void setearCoordenadaComputadora(){
	srand(time(0));
	int fila = 0;
	int columna = 0;
	
	bool hayEspacio = verificarSiHayEspacio();
	if(hayEspacio){
		do
		{
			fila = rand() % 3;
			columna =  rand() % 3;
		}while(tablero[fila][columna] != ' ');
		
		tablero[fila][columna] = letraJugador == 'X' ? 'O' : 'X';
	}
}

void setearCoordenadaJugador(int &fila, int &columna){
	do{		
		cout << "\nNo. fila que desea jugar (1-3): ";
		cin>>fila;
		
		cout << "No. columna que desea jugar (1-3): ";
		cin>>columna;
		
		if(fila <=0 || fila >3){
			cout<<"Favor ingrese un número del 1 al 3 para el no. de fila"<<endl;
		}
		
		if(columna <=0 || columna >3){
			cout<<"Favor ingrese un número del 1 al 3 para el no. de columna"<<endl;
		}
		
		cout<<endl;
	}while((fila <=0 || fila >3) || (columna <=0 || columna >3));
	
	fila--;
	columna--;
}

void jugar(){
	int fila = 0;
	int columna = 0;

	setearCoordenadaJugador(fila, columna);
	
	while(tablero[fila][columna] != ' '){
		cout<<"Favor ingrese otra posición, la coordenada ya está ocupada"<<endl;
		setearCoordenadaJugador(fila, columna);
	}
	
	tablero[fila][columna] = letraJugador;
	setearCoordenadaComputadora();
}

void mostrarMensajeGanador(char letra){
	string ganador = letraJugador == letra ? "jugador" : "computadora";
	cout<<"\nFelicidades "<<ganador<<": "<<letra<<"!\n¡Ganastes!\n";
}

bool verificarSiHayGanador(){
	//filas
	for(int i = 0 ; i < 3 ; i++){
		if(tablero[i][0] != ' ' && tablero[i][1] != ' ' && tablero[i][2] != ' ' &&
			tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2]){
				mostrarMensajeGanador(tablero[i][0]);
				return true;
		}
	}
	
	//columnas
	for(int i = 0 ; i < 3 ; i++){
		if(tablero[0][i] != ' ' && tablero[1][i] != ' ' && tablero[2][i] != ' ' &&
			tablero[0][i] == tablero[1][i] && tablero[1][i] == tablero[2][i]){
				mostrarMensajeGanador(tablero[0][i]);
				return true;
		}
	}
	
	//diagonales
	if(tablero[0][0] != ' ' && tablero[1][1] != ' ' && tablero[2][2] != ' ' &&
		tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2]){
			mostrarMensajeGanador(tablero[1][1]);
			return true;		
	}
	
	if(tablero[0][2] != ' ' && tablero[1][1] != ' ' && tablero[2][0] != ' ' &&
		tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0]){
			mostrarMensajeGanador(tablero[1][1]);
			return true;
	}

	return false;
}
