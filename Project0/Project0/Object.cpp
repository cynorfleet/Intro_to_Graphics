#include "Object.h"

Object::Object()
{

}

Object::Object(const Object& other)
{
	instream = other.instream;
	meshname = other.meshname;
	vertices = other.vertices;
	normals = other.normals;
	vertIndices = other.vertIndices;
	textureIndicies = other.textureIndicies;
	normIndices = other.normIndices;

	buffer = other.buffer;
	Ibuffer = other.Ibuffer;




}

Object::Object(string file_name)
{
	
	objectfile.open(file_name);
	if (!objectfile)
	{
		cerr << "ERROR: WRONG FILE NAME " << file_name;
	}
	else {
		meshname = file_name;
		cout << "LOADING MESH:\t" << meshname;
		int vert, texture, normal;
		int progress = 0;

		while (getline(objectfile, instream)) {
			progress++;
			if(progress%5000 == 0)
			cout << ".";
			if (instream.substr(0, 2) == "v ")
			{
				vertices.push_back(ParseData());
			}
			if (instream.substr(0, 2) == "vn")
			{
				normals.push_back(ParseData());
			}
			if (instream.substr(0, 2) == "f ")
			{
				ParseFace();
			}
		}
	}
	cout << " DONE\n";
}

vec4 Object::ParseData()
{
	stringstream ss;
	vec4 vertdata;
	string junk;

	ss << instream;
	ss >> junk >> vertdata[0] >> vertdata[1] >> vertdata[2];
	vertdata[3] = 1;
	ss.str(""); 
	ss.clear();
	return vertdata;
}

void Object::ParseFace()
{
	stringstream ss;
	int vertex, texture, normal;
	string junk;

	ss << instream;
	ss >> junk;
	char morejunk;

	for (int i = 0; i < 3; i++)
	{
		ss >> vertex >> morejunk;
		if (isdigit(ss.peek()))
		{
			ss >> texture;
			textureIndicies.push_back(texture - 1);
		}
		ss >> morejunk >> normal;
		vertIndices.push_back(vertex-1);
		normIndices.push_back(normal-1);
	}
	ss.str("");
	ss.clear();
}

//----------------------------------------------------------------------------

int Object::load(GLuint program)
{
	int size = vertices.size() * 16;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, size + size, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size, &vertices[0]);
	glBufferSubData(GL_ARRAY_BUFFER, size, size, &vertices[0]);

	glGenBuffers(1, &Ibuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ibuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertIndices.size() * 4, &vertIndices[0], GL_STATIC_DRAW);

	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));

	GLuint vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(size));

	return 0;
}

//----------------------------------------------------------------------------

void Object::draw()
{
	glBindVertexArray(buffer);
	glBindVertexArray(Ibuffer);
	glDrawArrays(GL_LINE_STRIP, 0, vertices.size());
}

//----------------------------------------------------------------------------

Object::~Object()
{
}
