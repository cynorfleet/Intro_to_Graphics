#pragma once
#include "Angel.h"
#include <fstream>
#include <vector>

using namespace std;

typedef Angel::vec4  color4;
typedef Angel::vec4  point4;
typedef Angel::vec4  norm4;

//	This class will hold the vertex data necessary to construct a cube
static class Vert_array_object
{
public:
	Vert_array_object();
	Vert_array_object(string obj_filename);
	void load(GLuint program);
	void draw();
	~Vert_array_object();

protected:
	string mesh_name;

	ifstream infile;

	void ReadStream_line();

	vec4 Parse_Data();

	void Find_Start();



	// Vertices of the object
	point4 vertices;

	// RGBA Colors
	color4 vertex_colors;

	// Normals of the object's vertices
	norm4 vertex_normals;

	// Faces of the object
	norm4 faces;

	// Stream Stuff
	static const int BUFFSIZE = 80;
	char buff[BUFFSIZE];

};
