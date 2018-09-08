#include"librerias.hpp"
#include"juego.hpp"
#include"jugador.hpp"
int main()
{
	uint fichas;
	string nom;
	string opc;
	juego game;
	bool game_over;
	bool band;
	band=false;
	do
	{
		system("cls");
		cout<<"\n\t\t\t      MENU PRINCIPAL"<<endl;
		cout<<endl<<"\t\t1. Nuevo Jugador."<<endl;
		cout<<endl<<"\t\t2. Volver a comenzar."<<endl;
		cout<<endl<<"\t\t3. Salir."<<endl;
		cout<<endl<<"\t\t\tSeleccione una Opcion: ";
		cin>>opc;
		if(opc=="1")
		{
			band=true;
			game_over=false;
			system("cls");
			cout<<"BLACK JACK"<<endl<<endl;
			cout<<"Ingrese el nombre del jugador: ";
			cin>>nom;
			do
			{
				system("cls");
				cout<<"BLACK JACK"<<endl<<endl;
				cout<<"Ingrese el nombre del jugador: "<<nom<<endl;
				cout<<"Con cuantas fichas desea jugar?: ";
				cin>>fichas;
				if(fichas<20)
				{
					cout<<endl<<"\t\tLa minima apuesta es de 20 fichas."<<endl;
					system("pause");
				}
			}while(fichas<20);
			game.iniciar_jugador(nom,fichas);
			do
			{
				game_over=game.jugar();
			}while(game_over==false );
		}
		else
		{
			if(opc=="2" && band==true)
			{
				game.iniciar_jugador(nom,fichas);
				do
				{
					game_over=game.jugar();
				}while(game_over==false);
			}
		}
	}while(opc!="3");
	return 0;
}