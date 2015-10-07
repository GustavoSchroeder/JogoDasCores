#pragma once

//using namespace std;

class retangulo
{
	bool visivel;
	int red;
	int green;
	int blue;
public:
	void iniciaRetangulo(bool v, int r, int g, int b);
	bool isVisivel();
	float getRed();
	float getGreen();
	float getBlue();
	void setVisivel(bool v);
};

