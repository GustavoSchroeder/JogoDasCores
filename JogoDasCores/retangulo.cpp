#pragma once
#include "retangulo.h"

using namespace std;

void retangulo::iniciaRetangulo(bool v, int r, int g, int b)
{
	visivel = v;
	red = r;
	green = g;
	blue = b;
}

bool retangulo::isVisivel(){
	return visivel;
}

float retangulo::getRed(){
	return red;
}

float retangulo::getGreen(){
	return green;
}

float retangulo::getBlue(){
	return blue;
}

void retangulo::setVisivel(bool v){
	visivel = v;
}
