#ifndef CARTAS_HPP
#define CARTAS_HPP
#include"librerias.hpp"
class cartas
{
private:
	uint _valor;
	int _id;
	string _palo;
	string _cara;
public:
	cartas();
	void crear(int,uint,string,string);
	void mostrar();
	uint valor();
	string cara();
};
cartas::cartas()
{
	_valor=0;
	_id=-1;
	_cara="-1";
	_palo="-1";
}
void cartas::crear(int id_,uint valor_,string palo_,string cara_)
{
	_valor=valor_;
	_id=id_;
	_palo=palo_;
	_cara=cara_;
}
void cartas::mostrar()
{
	cout<<_cara<<" de "<<_palo;
}
uint cartas::valor()
{
	return _valor;
}
string cartas::cara()
{
	return _cara;
}
#endif

