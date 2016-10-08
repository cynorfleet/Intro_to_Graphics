#pragma once

#include "Angel.h"

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;

static class Vert_pt_ary
{
public:
	Vert_pt_ary(int vert_amount);
	~Vert_pt_ary();
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
};

