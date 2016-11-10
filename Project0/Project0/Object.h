#pragma comment(lib, "freeglut")
#pragma comment(lib, "glew32")
#pragma once

#include "Angel.h"
#include<vector>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;

struct bounding
{
	float x_min, y_min, z_min, x_max, y_max, z_max;

	//	Default Constructor
	bounding(GLfloat s = 0.0) :
		x_min(s), x_max(s), y_min(s), y_max(s), z_min(s), z_max(s) {}

	//	Parameterized Constructor
	bounding(GLfloat xmin, GLfloat xmax, GLfloat ymin, GLfloat ymax,
		GLfloat zmin, GLfloat zmax) :
		x_min(xmin), x_max(xmax), y_min(ymin), y_max(ymax), z_min(zmin), z_max(zmax) {}

	//	Find vec4 min/max Constructor
	void operator()(const vec4 &other)
	/*-------------------------------------------- bounding -----
	|  Function 	bounding()
	|
	|  Purpose: 	This function will take in a vec4 and check if it 
	|				contains x/y/z min/max values and store it in bounding.
	|
	|  Parameters:
	|	other (IN) -- ARG DESCRIPTION HERE
	|
	|  Returns:  	N/A
	*-------------------------------------------------------------------*/
	{
		//	Loop the x/y/z values of vec4
		for(int i = 0; i < 3; i++)
		{
			/***********************************************************************
			*	use *(&x_min) as index zero which ref x_min. Add i to traverse (i.e. 
			*	i=1 would traverse to [address space of x_min + 1] == y_min). 
			************************************************************************/
			if (other[i] < *(&x_min + i))
				*(&x_min + i) = other[i];
			/***********************************************************************
			*	use *(&x_max) as index three which ref x_max. Add i to traverse (i.e.
			*	i=0 would traverse to [address space of x_max + 0] == x_max).
			************************************************************************/
			else if (other[i] > *(&x_max + i) )
				*(&x_max + i) = other[i];
		}
	}

	string ToString()
	{
		return	"\n***********************************************************\n"
				"X_Min = " + to_string(x_min) + "\tX_Max = " + to_string(x_max) + '\n' +
				"Y_Min = " + to_string(y_min) + "\tY_Max = " + to_string(y_max) + '\n' +
				"Z_Min = " + to_string(z_min) + "\tZ_Max = " + to_string(z_max) + '\n' +
				"***********************************************************\n";
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
	bounding bounds;
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
	void MakeArray();
	~Object();
	int load(GLuint);
	void draw();
	int progressscaler;
};