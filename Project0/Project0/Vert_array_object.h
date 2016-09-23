#pragma once
#include "Angel.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

//	This class will hold the vertex data necessary to construct a cube
static class Vert_array_object
{
public:
	Vert_array_object();
	~Vert_array_object();

protected:
	// Vertices of a unit cube centered at origin, sides aligned with axes
	point4 vertices[8] = {
		point4(-0.5, -0.5,  0.5, 1.0),
		point4(-0.5,  0.5,  0.5, 1.0),
		point4(0.5,  0.5,  0.5, 1.0),
		point4(0.5, -0.5,  0.5, 1.0),
		point4(-0.5, -0.5, -0.5, 1.0),
		point4(-0.5,  0.5, -0.5, 1.0),
		point4(0.5,  0.5, -0.5, 1.0),
		point4(0.5, -0.5, -0.5, 1.0)
	};

	// RGBA Colors
	color4 vertex_colors[8] = {
		color4(0.0, 0.0, 0.0, 1.0),  // black
		color4(1.0, 0.0, 0.0, 1.0),  // red
		color4(1.0, 1.0, 0.0, 1.0),  // yellow
		color4(0.0, 1.0, 0.0, 1.0),  // green
		color4(0.0, 0.0, 1.0, 1.0),  // blue
		color4(1.0, 0.0, 1.0, 1.0),  // magenta
		color4(1.0, 1.0, 1.0, 1.0),  // white
		color4(0.0, 1.0, 1.0, 1.0)   // cyan
	};
};

