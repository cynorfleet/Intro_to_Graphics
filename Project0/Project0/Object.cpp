//	Christian Norfleet
//	Program 4

#include "Object.h"
# include <cmath>
# include <string>
# include <fstream>
# include <iomanip>
#include <thread>

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
	pointarray = other.pointarray;

	buffer = other.buffer;
	Ibuffer = other.Ibuffer;
}

void Object::_LoadProgress(string file_name)
{
	ifstream scalerfile;
	int length;
	scalerfile.open(file_name);
	if (scalerfile) {
		// get length of file:
		scalerfile.seekg(0, scalerfile.end);
		length = scalerfile.tellg();
		scalerfile.seekg(0, scalerfile.beg);
		progressscaler = (length*.1);
	}
	scalerfile.close();
}

void Object::_LoadMTL(string file)
{
	string ext_replacethis = ".obj";
	string ext_withthis = ".mtl";
	string line, junk;

	stringstream ss;

	size_t found = file.rfind(ext_replacethis);
	if (found != std::string::npos)
		file.replace(found, ext_replacethis.length(), ext_withthis);

	ifstream material;
	material.open(file);
	cout << "\nOPENING FILE: " << file << "\n";
	if (!material)
	{
		cout << "ERROR:cannot open " << file;
		exit(1);
	}

	while (getline(material, line))
	{
		if (line.substr(0, 3) == "Ns ")
		{
			ss << line;
			ss >> junk >> shininess;
			ss.str("");
			ss.clear();
		}

		if (line.substr(0, 3) == "Ka ")
		{
			ss << line;
			ss >> junk >> Kar >> Kag >> Kab;
			matlA = vec3(Kar, Kag, Kab);
			ss.str("");
			ss.clear();
		}

		if (line.substr(0, 3) == "Kd ")
		{
			ss << line;
			ss >> junk >> Kdr >> Kdg >> Kdb;
			matlD = vec3(Kdr, Kdg, Kdb);
			ss.str("");
			ss.clear();
		}

		if (line.substr(0, 3) == "Ks ")
		{
			ss << line;
			ss >> junk >> Ksr >> Ksg >> Ksb;
			matlS = vec3(Ksr, Ksg, Ksb);
			ss.str("");
			ss.clear();
		}
	}
	material.close();
}

void Object::_LoadData(string file_name)
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
			if (objectfile.tellg() % progressscaler <= 100)
				cout << ".";
			if (instream.substr(0, 2) == "v ")
			{
				vertices.push_back(ParseData());

				//	Find Min/Max
				bounds(vertices.back());
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

	objectfile.close();
	for (int i = 0; i < vertIndices.size(); i++)
	{
		pointarray.push_back(vertices[vertIndices[i]]);
		normalarray.push_back(normals[normIndices[i]]);
	}
	cout << " DONE\n";
}

Object::Object(string file_name)
{
	_LoadProgress(file_name);
	_LoadData(file_name);
	_LoadMTL(file_name);
	cout << bounds.ToString();
	cout << "BOX_MAX: " << bounds.Box_Max() << '\n';
	cout << "Center: " << bounds.Box_Center() << "\n\n";
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
		vertIndices.push_back(vertex - 1);
		normIndices.push_back(normal - 1);
	}
	ss.str("");
	ss.clear();
}

//----------------------------------------------------------------------------

int Object::load(GLuint program)
{
	int size = (pointarray.size()) * 16;
	glGenBuffers(1, &buffer);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, size + size, NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, size, &pointarray[0]);
	glBufferSubData(GL_ARRAY_BUFFER, size, size, &normalarray[0]);

	//glGenBuffers(1, &Ibuffer);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ibuffer);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertIndices.size() * 4, &vertIndices[0], GL_STATIC_DRAW);

	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));

	GLuint vNormal = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(size));

	matlDLoc = glGetUniformLocation(program, "matlD");
	matlSLoc = glGetUniformLocation(program, "matlS");
	matlALoc = glGetUniformLocation(program, "matlA");
	shinyLoc = glGetUniformLocation(program, "shininess");

	return 0;
}

//----------------------------------------------------------------------------

void Object::draw()
{
	glUniform3fv(matlDLoc, 1, matlD);
	glUniform3fv(matlSLoc, 1, matlS);
	glUniform3fv(matlALoc, 1, matlA);
	glUniform1f(shinyLoc, shininess);
	glDrawArrays(GL_TRIANGLES, 0, pointarray.size());
}

//----------------------------------------------------------------------------

Object::~Object()
{
}