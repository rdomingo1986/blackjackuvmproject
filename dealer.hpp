#ifndef DEALER_HPP
#define DEALER_HPP
#include"librerias.hpp"
#include"jugador.hpp"
class dealer:public jugador
{
private:
	int resp;
public:
	dealer();
	string decidir(uint);
	string cambiar_valor_as();
};
dealer::dealer()
{
}
string dealer::decidir(uint puntos_jugador)
{
	if(puntos_jugador==_puntos)
	{
		return "n";
	}
	else
	{
		if(puntos_jugador>21)
		{
			return "n";
		}
		else
		{
			if(puntos_jugador<_puntos)
			{
				return "n";
			}
			else
			{
				if(_puntos<=12) 
					return "s";
				else
				{
					if(_puntos>12 && _puntos<18)
					{
						srand((unsigned)time(0));
						resp=rand()%2;
						if(resp==0)
							return "s";
						else
							return "n";
					}
					else
						return "n";
				}
			}
		}
	}
}
string dealer::cambiar_valor_as()
{
	if((_puntos+10)<21)
		return "s";
	else
		return "n"; 
}
#endif