#ifndef JUGADOR_HPP
#define JUGADOR_HPP
#include"librerias.hpp"
#include"cartas.hpp"
class jugador
{
public:
	string nombre;
protected:
	uint _fichas;
	int _mazo[52];
	int _ncartas;
	uint _puntos;
public:
	jugador();
	void dar_fichas(uint);
	void quitar_fichas(uint);
	void fichas_a_cero();
	void recibe_cartas(int);
	void dar_puntos(uint);
	void borrar_puntos();
	void borrar_mazo();
	uint puntos();
	uint fichas();
	uint ncartas();
	uint id_carta(int);
};
jugador::jugador()
{
	jugador::borrar_mazo();
	_puntos=0;
	_ncartas=0;
	_fichas=0;
	nombre="-1";
}
void jugador::dar_fichas(uint fichas_)
{
	_fichas+=fichas_;
}
void jugador::quitar_fichas(uint fichas_)
{
	_fichas<=fichas_ ? _fichas=0 : _fichas-=fichas_;
}
void jugador::fichas_a_cero()
{
	_fichas=0;
}
void jugador::recibe_cartas(int id)
{
	_mazo[_ncartas]=id;
	_ncartas++;
}
void jugador::dar_puntos(uint puntos_)
{
	_puntos+=puntos_;
}
void jugador::borrar_puntos()
{
	_puntos=0;
}
void jugador::borrar_mazo()
{
	for(int i=0;i<52;i++)
		_mazo[i]=-1;
	_ncartas=0;
}
uint jugador::puntos()
{
	return _puntos;
}
uint jugador::fichas()
{
	return _fichas;
}
uint jugador::ncartas()
{
	return _ncartas;
}
uint jugador::id_carta(int pos_)
{
	return _mazo[pos_];
}
#endif