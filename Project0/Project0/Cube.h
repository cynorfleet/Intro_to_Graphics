#pragma once
#include "Vert_array_object.h"

using namespace std;

class Cube :
	Vert_array_object
{
public:
	Cube(string obj);

	// generate 12 triangles: 36 vertices and 36 colors
	void colorcube();
	void quad(int a, int b, int c, int d);
	void load(GLuint program);
	void draw();
	~Cube();

private:
	int Index = 0;
	point4 points;
	color4 colors;
	mat4 matrix;
};
