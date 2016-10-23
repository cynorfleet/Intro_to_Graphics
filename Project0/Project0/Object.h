#pragma comment(lib, "freeglut")
#pragma comment(lib, "glew32")
#pragma once

#include "Angel.h"
#include<vector>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;

class Object
{
	ifstream objectfile;
	string instream;
	vector<vec4>vertices;
	vector<vec4> normals;
	vector<GLuint> vertIndices;
	vector<GLuint> textureIndicies;
	vector<GLuint> normIndices;

	GLuint buffer, Ibuffer;

public:
	Object();
	Object(const Object & other);
	Object(string file_name);
	vec4 ParseData();
	string meshname;
	void ParseFace();
	~Object();
	int load(GLuint);
	void draw();
};