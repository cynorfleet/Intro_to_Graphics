#pragma comment(lib, "freeglut")
#pragma comment(lib, "glew32")
#pragma once

#include "Angel.h"
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include <algorithm>

using namespace std;

struct bounding
{
	GLfloat x_min, y_min, z_min, x_max, y_max, z_max;
	GLfloat box_max;
	vec4 box_center;

	//	Default Constructor
	bounding(GLfloat s = 0.0) :
		x_min(s), x_max(s), y_min(s), y_max(s), z_min(s), z_max(s) {}

	//	Parameterized Constructor
	bounding(GLfloat xmin, GLfloat xmax, GLfloat ymin, GLfloat ymax,
		GLfloat zmin, GLfloat zmax) :
		x_min(xmin), x_max(xmax), y_min(ymin), y_max(ymax), z_min(zmin), z_max(zmax) {}

	//	Find vec4 min/max Constructor
	void operator()(const vec4 &vertex_element)
	/*-------------------------------------------- operator ------------
	|  Function 	operator()
	|
	|  Purpose: 	This will overload the parentheses operator, 
	|				read in a vec4, and check if it contains x/y/z
	|				min/max values storing it in bounding data structure.
	|
	|  Parameters:
	|	vertex_element (IN) -- An element of the vertices array (vec4)
	|
	|  Returns:  	N/A
	*-------------------------------------------------------------------*/
	{
		//	Loop the x/y/z values of vec4
		for(int axis = 0; axis < 3; axis++)
		{
			/***********************************************************************
			*	use *(&x_min) as index zero which ref x_min. Add i to traverse (i.e. 
			*	i=1 would traverse to [address space of x_min + 1] == y_min). 
			************************************************************************/
			if (vertex_element[axis] < *(&x_min + axis))
				*(&x_min + axis) = vertex_element[axis];
			/***********************************************************************
			*	use *(&x_max) as index three which ref x_max. Add i to traverse (i.e.
			*	i=0 would traverse to [address space of x_max + 0] == x_max).
			************************************************************************/
			else if (vertex_element[axis] > *(&x_max + axis) )
				*(&x_max + axis) = vertex_element[axis];
		}
	}

	void Reset()
	/*-------------------------------------------- Reset -----
	|  Function 	Reset()
	|
	|  Purpose: 	Resets the bounding data
	|
	|  Parameters:
	|	 (IN) -- ARG DESCRIPTION HERE
	|
	|  Returns:  	N/A
	*-------------------------------------------------------------------*/
	{ x_min = 0, x_max = 0, y_min = 0, y_max = 0, z_min = 0, z_max = 0; }

	vec4 Box_Center()
	/*-------------------------------------------- Box_Center -----
	|  Function 	Box_Center()
	|
	|  Purpose: 	Finds the center point of the bounding box
	|
	|  Returns:  	N/A
	*-------------------------------------------------------------------*/
	{
		box_center[0] = (x_max + x_min) / 2;
		box_center[1] = (y_max + y_min) / 2;
		box_center[2] = (z_max + z_min) / 2;
		box_center[3] = 1;

		return box_center;
	}

	GLfloat Box_Max()
	/*-------------------------------------------- Box_Max -----
	|  Function 	Box_Max()
	|
	|  Purpose: 	Finds the Max value in X/Y/Z
	|
	|  Returns:  	N/A
	*-------------------------------------------------------------------*/
	{
		box_max = 0;
		for (int i = 0; i < 3; i++)
			if ((*(&x_max + i)) > box_max)
				box_max = *(&x_max + i);
		return box_max;
	}

	string ToString()
	/*-------------------------------------------- ToString ------------
	|  Function 	ToString()
	|
	|  Purpose: 	Returns the Min/Max values of X/Y/Z in a vec4
	|
	|  Parameters:
	|	 (IN) -- ARG DESCRIPTION HERE
	|
	|  Returns:  	String
	*-------------------------------------------------------------------*/
	{
		string output = "----------------------------------------\n";

		//	If any of the min/max values leave suggested bounds (-1,1)
		if (any_of((&x_min), (&x_max + 3), [](GLfloat i) {return i < -1.0 || i > 1.0; }))
			output += "WARNING: EXCEEDED SUGGESTED BOUNDS (-1,1)\n\n";

		output +=
			"X_Min = " + to_string(x_min) + "\tX_Max = " + to_string(x_max) + '\n' +
			"Y_Min = " + to_string(y_min) + "\tY_Max = " + to_string(y_max) + '\n' +
			"Z_Min = " + to_string(z_min) + "\tZ_Max = " + to_string(z_max) + '\n' +
			"----------------------------------------\n";
		return output;
	}

	//  --- Indexing Operator ---
	GLfloat& operator [] (int i) { return *(&x_min + i); }
	const GLfloat operator [] (int i) const { return *(&x_min + i); }
};


class Object
{
	ifstream objectfile;
	string instream;
	vector<vec4>vertices;
	vector<vec4> normals;
	vector<GLuint> vertIndices;
	vector<GLuint> textureIndicies;
	vector<GLuint> normIndices;
	vector<vec4>pointarray;
	GLuint buffer, Ibuffer;

public:
	Object();
	Object(const Object & other);
	void _LoadProgress(string filename);
	void _LoadData(string file_name);
	Object(string file_name);
	vec4 ParseData();
	string meshname;
	void ParseFace();
	~Object();
	int load(GLuint);
	void draw();
	bounding bounds;
	int progressscaler;
};