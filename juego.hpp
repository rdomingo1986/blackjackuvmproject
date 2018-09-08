#ifndef JUEGO_HPP
#define JUEGO_HPP
#include"librerias.hpp"
#include"cartas.hpp"
#include"jugador.hpp"
#include"dealer.hpp"
class juego
{
private:
	cartas _mazo[52];
	dealer _cpu;
	jugador _jugador;
	int _apuestas;
	bool _turno;
	int _jugadas[52];
	int _njugada;
	bool _black_jack;
public:
	juego();
	bool jugar();
	void crear_mazo();
	uint dar_carta();
	void iniciar_jugador(string,uint);
	uint black_jack(string);
	bool existe_black_jack();
	void mesa_de_juego();
	void mostrar_jugador(string,uint,bool);
};
juego::juego()
{
	_apuestas=0;
	_njugada=0;
	crear_mazo();
	_turno=true;
	_black_jack=false;
	for(int m=0;m<52;m++)
		_jugadas[m]=-1;
	_jugador.borrar_puntos();
	_cpu.borrar_puntos();
}
void juego::crear_mazo()
{
	const string PALO[4]={"Corazones","Picas","Trebol","Diamantes"};
	const string CARA[13]={"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
	int palo,cara,valor;
	valor=cara=palo=0;
	for(int i=0;i<52;i++)
	{
		if(cara>12)
		{
			palo++;
			cara=0;
		}
		cara>=9 ? valor=10 : valor=cara+1;
		_mazo[i].crear(i,valor,PALO[palo],CARA[cara]);
		cara++;
	}
}
void juego::iniciar_jugador(string name_,uint fichas_)
{
	const string name="DEALER";
	_cpu.dar_fichas(DEALER_FICHAS*fichas_);
	_cpu.nombre=name;
	_jugador.dar_fichas(fichas_);
	_jugador.nombre=name_;
}
uint juego::dar_carta()
{
	int id;
	bool band;
	srand((unsigned)time(0));
	do
	{
		band=false;
		id=rand()%52;
		for(int j=0;j<_njugada;j++)
		{
			if(id==_jugadas[j])
			{
				band=true;
			}
		}
	}while(band==true);
	_jugadas[_njugada]=id;
	_njugada++;
	return id;
}
uint juego::black_jack(string nombre_)
{
	uint puntos_jugador;
	uint puntos_dealer;
	puntos_dealer=puntos_jugador=0;
	for(int k=0;k<2;k++)
	{
		if(_mazo[_jugador.id_carta(k)].valor()==1)
			puntos_jugador+=11;
		else
			puntos_jugador+=_mazo[_jugador.id_carta(k)].valor();
		if(_mazo[_cpu.id_carta(k)].valor()==1)
			puntos_dealer+=11;
		else
			puntos_dealer+=_mazo[_cpu.id_carta(k)].valor();
	}
	if(nombre_==_cpu.nombre)
		return puntos_dealer;
	else
		return puntos_jugador;
}
bool juego::existe_black_jack()
{
	uint puntos_jugador;
	uint puntos_dealer;
	puntos_dealer=puntos_jugador=0;
	puntos_jugador=juego::black_jack(_jugador.nombre);
	puntos_dealer=juego::black_jack(_cpu.nombre);
	if(puntos_jugador==21 && puntos_dealer==21)
	{
		system("cls");
		cout<<"MESA DE JUEGO"<<endl<<endl;
		juego::mostrar_jugador(_jugador.nombre,_jugador.fichas(),true);
		cout<<endl;
		juego::mostrar_jugador(_cpu.nombre,_cpu.fichas(),true);
		cout<<"\t\t\tApuestas: "<<_apuestas;
		cout<<"\n\n\t"<<_jugador.nombre<<" y el "<<_cpu.nombre<<" tienen BLACK JACK. Esta partida es un empate."<<endl;
		_jugador.dar_fichas(_apuestas);
		return true;
	}
	else
	{
		if(puntos_jugador==21)
		{
			system("cls");
			cout<<"MESA DE JUEGO"<<endl<<endl;
			juego::mostrar_jugador(_jugador.nombre,_jugador.fichas(),true);
			cout<<endl;
			juego::mostrar_jugador(_cpu.nombre,_cpu.fichas(),false);
			cout<<"\t\t\tApuestas: "<<_apuestas;
			cout<<"\n\n\t"<<_jugador.nombre<<" tiene black jack y gana la partida"<<endl;
			_cpu.quitar_fichas(_apuestas);
			_jugador.dar_fichas(_apuestas*2);
			return true;
		}
		else
		{
			if(puntos_dealer==21)
			{
				system("cls");
				cout<<"MESA DE JUEGO"<<endl<<endl;
				juego::mostrar_jugador(_jugador.nombre,_jugador.fichas(),false);
				cout<<endl;
				juego::mostrar_jugador(_cpu.nombre,_cpu.fichas(),true);
				cout<<"\t\t\tApuestas: "<<_apuestas;
				cout<<"\n\n\t"<<_cpu.nombre<<" tiene black jack y gana la partida."<<endl;
				_cpu.dar_fichas(_apuestas);
				return true;
			}
			else
				return false;
		}
	}
}
void juego::mesa_de_juego()
{
	int id;
	do
	{
		id=juego::dar_carta();
		if(_turno==true)
		{
			_jugador.recibe_cartas(id);
			_jugador.dar_puntos(_mazo[id].valor());
			_jugador.quitar_fichas(10);
		}
		if(_turno==false)
		{
			_cpu.recibe_cartas(id);
			_cpu.dar_puntos(_mazo[id].valor());
		}
		_apuestas=20;
		_turno==true ? _turno=false : _turno=true;
	}while(_njugada<4);	
	string resp;
	string buscar_as;
	system("cls");
	cout<<"MESA DE JUEGO"<<endl<<endl;
	juego::mostrar_jugador(_jugador.nombre,_jugador.fichas(),false);
	cout<<endl;
	juego::mostrar_jugador(_cpu.nombre,_cpu.fichas(),false);
	cout<<"\t\t\tApuestas: "<<_apuestas;
	_black_jack=juego::existe_black_jack();
	if(_black_jack==false)
	{
		do
		{
			system("cls");
			cout<<"MESA DE JUEGO"<<endl<<endl;
			juego::mostrar_jugador(_jugador.nombre,_jugador.fichas(),false);
			cout<<endl;
			juego::mostrar_jugador(_cpu.nombre,_cpu.fichas(),false);
			cout<<"\t\t\tApuestas: "<<_apuestas;
			cout<<endl<<endl<<_jugador.nombre<<" desea otra carta? s/n:";
			cin>>resp;
			if(resp=="s" || resp=="S")
			{
				id=juego::dar_carta();
				_jugador.recibe_cartas(id);
				_jugador.dar_puntos(_mazo[id].valor());
			}
		}while(resp=="s"|| resp=="S");
		for(int i=0;i<_jugador.ncartas();i++)
		{
			buscar_as=_mazo[_jugador.id_carta(i)].cara();
			if(buscar_as=="A")
			{
				cout<<"Desea cambiar el valor de 1 a 11? s/n:";
				cin>>resp;
				if(resp=="s" || resp=="S")
				{
					_jugador.dar_puntos(10);
				}
			}
		}
		do
		{
			system("cls");
			cout<<"MESA DE JUEGO"<<endl<<endl;
			juego::mostrar_jugador(_jugador.nombre,_jugador.fichas(),false);
			cout<<endl;
			juego::mostrar_jugador(_cpu.nombre,_cpu.fichas(),false);
			cout<<"\t\t\tApuestas: "<<_apuestas;
			resp=_cpu.decidir(_jugador.puntos());
			if(resp=="s" || resp=="S")
			{
				id=juego::dar_carta();
				_cpu.recibe_cartas(id);
				_cpu.dar_puntos(_mazo[id].valor());
			}
		}while(resp=="s" || resp=="S");
		for(i=0;i<_cpu.ncartas();i++)
		{
			buscar_as=_mazo[_cpu.id_carta(i)].cara();
			if(buscar_as=="A")
			{
				resp=_cpu.cambiar_valor_as();
				if(resp=="s" || resp=="S")
				{
					_jugador.dar_puntos(10);
				}
			}
		}
	}
	cout<<endl;
}
void juego::mostrar_jugador(string nombre_,uint fichas_,bool black_jack)
{
	cout<<"Jugador: "<<nombre_<<endl;
	cout<<"Fichas: "<<fichas_<<endl;
	cout<<"Cartas: ";
	if(nombre_=="DEALER")
	{
		for(int i=0;i<_cpu.ncartas();i++)
		{
			_mazo[_cpu.id_carta(i)].mostrar();
			cout<<"- -";
		}
		if(black_jack==true)
			cout<<endl<<"Puntos :"<<_cpu.puntos()+10;
		else
			cout<<endl<<"Puntos :"<<_cpu.puntos();
	}	
	else
	{
		for(int i=0;i<_jugador.ncartas();i++)
		{
			_mazo[_jugador.id_carta(i)].mostrar();
			cout<<"- -";
		}
		if(black_jack==true)
			cout<<endl<<"Puntos :"<<_jugador.puntos()+10;
		else
			cout<<endl<<"Puntos :"<<_jugador.puntos();
	}
	cout<<endl<<endl;
}
bool juego::jugar()
{
	string si_no;
	_apuestas=0;
	_black_jack=false;
	_jugador.borrar_puntos();
	_cpu.borrar_puntos();
	_jugador.borrar_mazo();
	_cpu.borrar_mazo();
	for(int m=0;m<52;m++)
		_jugadas[m]=-1;
	_njugada=0;
	_turno=true;
	mesa_de_juego();
	if(_black_jack==false)
	{
		if(_cpu.puntos()==_jugador.puntos() && (_cpu.puntos()<=21 && _jugador.puntos()<=21))
		{
			cout<<"\n\n\tEl juego es un empate."<<endl;
			_jugador.dar_fichas(_apuestas);
		}
		else
		{
			if(_cpu.puntos()>21 && _jugador.puntos()>21)
			{
				cout<<"\n\n\tNingun Jugador gana porque ambos sobrepasaron los 21 puntos "<<endl;
				_jugador.dar_fichas(_apuestas);
			}
			else
			{
				if(_cpu.puntos()>21)
				{
					cout<<"\n\n\tEl ganador es "<<_jugador.nombre<<" porque "<<_cpu.nombre<<" sobrepaso los 21 puntos"<<endl;
					_cpu.quitar_fichas(_apuestas);
					_jugador.dar_fichas(_apuestas*2);
				}
				else
				{
					if(_jugador.puntos()>21)
					{
						cout<<"\n\n\tEl ganador es "<<_cpu.nombre<<" porque "<<_jugador.nombre<<" sobrepaso los 21 puntos"<<endl;
						_cpu.dar_fichas(_apuestas);
					}
					else
					{
						if(_cpu.puntos()>_jugador.puntos())
						{
							cout<<"\n\n\tEl ganador es "<<_cpu.nombre<<endl;
							_cpu.dar_fichas(_apuestas);
						}
						else
						{
							cout<<"\n\n\tEl ganador es "<<_jugador.nombre<<endl;
							_cpu.quitar_fichas(_apuestas);
							_jugador.dar_fichas(_apuestas*2);
						}
					}
				}
			}
		}
	}
	system("pause");
	if(_cpu.fichas()==0)
	{
		_cpu.fichas_a_cero();
		_jugador.fichas_a_cero();
		system("cls");
		cout<<"\t\t"<<_cpu.nombre<<" se ha quedado sin fichas."<<endl<<endl;
		system("pause");
		return true;
	}
	else
	{
		if(_jugador.fichas()==0)
		{
			_cpu.fichas_a_cero();
			_jugador.fichas_a_cero();
			system("cls");
			cout<<"\t\t"<<_jugador.nombre<<" se ha quedado sin fichas."<<endl<<endl;
			system("pause");
			return true;
		}
		else
		{
			system("cls");
			cout<<_jugador.nombre<<" desea seguir jugando? s/n: ";
			cin>>si_no;
			if(si_no=="s" || si_no=="S")
			{
				return false;
			}
			else
			{
				_cpu.fichas_a_cero();
				cout<<_jugador.nombre<<" se va con "<<_jugador.fichas()<<" fichas."<<endl;
				system("pause");
				_jugador.fichas_a_cero();
				return true;
			}
		}
	}
}
#endif