#include "Vert_array_object.h"
#include <fstream>
#include <sstream>

using namespace std;

Vert_array_object::Vert_array_object()
{
	//	Open the file
	infile.open("cubeobj.txt");

	//	Traverse file until we get to the data
	Find_Start();
	ReadStream_line();
}

Vert_array_object::Vert_array_object(string obj_filename)
{

	//	Open the file
	infile.open(obj_filename);

	//	Traverse file until we get to the data
	Find_Start();
	ReadStream_line();
}

Vert_array_object::~Vert_array_object()
{
}

void Vert_array_object::ReadStream_line()
{
	string temp = "";
	do {
		//	Read word in file
		infile.getline(buff, BUFFSIZE, ' ');
		//	Turn the line to a string
		temp = buff;

		//	If 2nd char on line is 'n' its a Vector Normal
		if (temp == "vn")
			vertex_normals= Parse_Data();

		//	If 1st char on line is v its a Vertex
		else if (temp == "v")
		{
			vertices=Parse_Data();
		}

		//	If 1st char on line is f its a face
		else if (temp == "f")
		{
			faces=Parse_Data();
		}

		//	If its a new mesh, then do it all over again
		else if (temp == "o")
		{
			//	Read line in file
			infile.getline(buff, BUFFSIZE);
			//	Turn the line to a string
			temp = buff;
			//	Store mesh_name
			mesh_name = buff;
			// ADD CODE TO ADD NEW VERTEX VECTOR HERE
		}
	} while (!infile.eof());
}

vec4 Vert_array_object::Parse_Data()
{
	double num;
	vec4 temp;

	for (int i = 0; i < 3; i++)
	{
		//	Read word in file
		infile.getline(buff, BUFFSIZE, ' ');
		//	Turn the line to a string
		temp[i] = atof(buff);
	}
	temp[4] = 0;
	return temp;
}

void Vert_array_object::Find_Start()
{
	for(int i=0; i <4;i++)
	{
		//	Read line in file
		infile.getline(buff, BUFFSIZE);
		//	Keep traversing file until mesh name found
	}
}

void Vert_array_object::load(GLuint program)
{
	// Create and initialize a buffer object
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(vertex_colors),
		NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(vertex_colors), vertex_colors);
	// set up vertex arrays
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));

	GLuint vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(vertices)));
}

void Vert_array_object::draw()
{
	glDrawArrays(GL_TRIANGLES, 0, 36);
}