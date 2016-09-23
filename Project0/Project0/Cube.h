#pragma once
#include "Vert_array_object.h"
class Cube :
	 Vert_array_object
{
public:
	Cube();

	// generate 12 triangles: 36 vertices and 36 colors
	void colorcube();
	void quad(int a, int b, int c, int d);
	void load(GLuint program);
	void draw();
	~Cube();

private:
	int Index = 0;
	static const int NumVertices = 36; //(6 faces)(2 triangles/face)(3 vertices/triangle)

	point4 points[NumVertices];
	color4 colors[NumVertices];
};

