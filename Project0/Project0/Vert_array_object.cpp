#include "Vert_array_object.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

Vert_array_object::Vert_array_object()
{
	//	Open the file
	infile.open("cube.obj");

	//	Traverse file until we get to the data
	Find_Mesh();

	ReadStream_line();
}

Vert_array_object::Vert_array_object(string obj_filename)
{

	//	Open the file
	infile.open(obj_filename);

	//	Traverse file until we get to the data
	Find_Mesh();
	cout << "MESH NAME: " << mesh_name << '\n';
	ReadStream_line();
	cout << "Verticies: " << vertices.size() << '\n';
	cout << "Normals: " << vertex_normals.size() << '\n';
	cout << "Vert Index: " << indexvertex.size() << '\n';
	cout << "Norm Index: " << indexnormal.size() << '\n';


}

Vert_array_object::~Vert_array_object()
{
}

void Vert_array_object::ReadStream_line()
{

	do {
		//	Read word in file
		infile.getline(buff, BUFFSIZE, ' ');
		//	Turn the line to a string
		string temp = buff;

		//	If 1st char on line is v its a Vertex
		if (temp == "v")
		{
			vertices.push_back(Parse_Data());
		}
		//	If 2nd char on line is 'n' its a Vector Normal
		else if (temp == "vn")
		{
			vertex_normals.push_back(Parse_Data());
		}

		//	If 1st char on line is f its a face
		else if (temp == "f")
		{
			/*indexvertex.push_back(0);
			indextexture.push_back(0);
			indexnormal.push_back(0);*/
			Parse_Face();
		}

		//	If its a new mesh, then do it all over again
		else if (temp == "o")
		{
			stringstream ss;
			//	Read line in file
			infile.getline(buff, BUFFSIZE);
			ss.str(buff);
			//	Turn the line to a string
			ss >> temp;
			//	Store mesh_name
			mesh_name = temp;
			// ADD CODE TO ADD NEW VERTEX VECTOR HERE
			cout << "MESH NAME: " << mesh_name << '\n';
		}
		else
			//	Read line in file
			infile.getline(buff, BUFFSIZE);

	} while (!infile.eof());
}

vec4 Vert_array_object::Parse_Data()
{
	stringstream ss;
	vec4 temp;
	infile.getline(buff, BUFFSIZE);
	ss.str(buff);
	for (int i = 0; i < 3; i++)
	{
		ss >> temp[i];
	}
	temp[3] = 1;
	return temp;
}

void Vert_array_object::Parse_Face()
{
	stringstream ss;
	char bs;
	int temp = 0;
	infile.getline(buff, BUFFSIZE);
	ss.str(buff);
	do
	{
		ss >> temp;
			indexvertex.push_back((temp)-1);
		ss >> bs;
		ss >> bs;

		ss >> temp;
		indexnormal.push_back((temp)-1);

	} while (!ss.eof());
}

void Vert_array_object::Find_Mesh()
{
	stringstream ss;
	string ameshname;
	do
	{
		//	Read line in file
		infile.getline(buff, BUFFSIZE);
		//	Keep traversing file until mesh name found
		ss.str(buff);
		ameshname = ss.str();
	} while (ameshname.substr(0,2) != "o ");
	mesh_name = ameshname.substr(2);
}

int Vert_array_object::load(GLuint program)
{
	vertices.shrink_to_fit();
	indexvertex.shrink_to_fit();
	int vao_size = vertices.size() * 16;
	int num_verticies = vertices.size();
	// Create and initialize a buffer object
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, vao_size + vao_size,
		NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0,vao_size, &vertices[0]);
	glBufferSubData(GL_ARRAY_BUFFER, vao_size, vao_size, &vertices[0]);

	//	ElEMENT ARRay STUFF
	glGenBuffers(1, &Ibuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ibuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexvertex.size() * 4, &indexvertex[0], GL_STATIC_DRAW);


	// set up vertex arrays
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));

	GLuint vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(vao_size));

	return 0;
}

void Vert_array_object::draw()
{
//	glDrawElements(GL_TRIANGLES, 0, 36);
glBindVertexArray(buffer);
glBindVertexArray(Ibuffer);
glDrawElements(GL_TRIANGLES, indexvertex.size(), GL_UNSIGNED_INT, 0);
}
