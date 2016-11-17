//	Christian Norfleet
//	Program 4
//	Display a preloaded object
//
//	Colors are assigned to each vertex and then the rasterizer interpolates
//   those colors across the triangles.  We us an orthographic projection
//   as the default projection.

#include "Angel.h"
#include "Object.h"

#pragma comment(lib, "freeglut")
#pragma comment(lib, "glew32")

// Array of rotation angles (in degrees) for each coordinate axis
enum axisType { X = 0, Y = 1, Z = 2 };
axisType axis = X;
int axisActive = axis;

GLfloat Theta[3] = { 0.0, 0.0, 0.0 };
GLfloat velocity = DegreesToRadians * 10;
GLuint modelViewLoc;
GLuint program;
GLuint  theta;  // The location of the "theta" shader uniform variable
vec4 at, up;
vec4 camera(0.0, 0.0, 5.0, 1);
vec2 projbox(0.5, 50);

GLuint ProjectionLoc;
mat4 projection;
GLfloat projection_near, projection_far, aspectRatio;

vector<string> modelname = { "cube.obj", "bb8.obj", "megatron.obj", "batman.obj", "ironmanmarkII.obj" };
vector <Object> model;
int activemodel = 0;

// Create a vertex array object
GLuint** vao = new GLuint*[model.size()];
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------

void
_LoadModels()
/*-------------------------------------------- _LoadModels -----
|  Function 	_LoadModels()
|
|  Purpose: 	Will populate vector with model objects generated from
|				the names provided in model names.
|
|  Returns:  	N/A
*-------------------------------------------------------------------*/
{
	if (model.size() == 0)
		for (int i = 0; i < modelname.size(); i++)
			model.push_back(Object(modelname[i]));
}

// OpenGL initialization
void
init()
{
	program = InitShader("vshader_a4.glsl", "fshader_a4.glsl");

	glUseProgram(program);

	glGenVertexArrays(model.size(), *vao);

	_LoadModels();
	for (int i = 0; i < model.size(); i++)
	{
		glBindVertexArray(*vao[i]);
		model[i].load(program);
	}

	glBindVertexArray(*vao[activemodel]);

	ProjectionLoc = glGetUniformLocation(program, "projection");
	modelViewLoc = glGetUniformLocation(program, "modelViewLoc");

	glEnable(GL_DEPTH_TEST);
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

mat4 _RotateFunc(GLfloat angle, int which_axis)
{
	switch (which_axis)
	{
	case 0:
		return mat4(1.0, 0.0, 0.0, 0.0,
			0.0, cos(theta), sin(theta), 0.0,
			0.0, -sin(theta), cos(theta), 0.0,
			0.0, 0.0, 0.0, 1.0);
		break;
	case 1:
		return mat4(cos(theta), 0.0, sin(theta), 0.0,
			0.0, 1.0, 0.0, 0.0,
			-sin(theta), 0.0, cos(theta), 0.0,
			0.0, 0.0, 0.0, 1.0);
		break;
	case 2:
		return mat4(cos(theta), -sin(theta), 0.0, 0.0,
			sin(theta), cos(theta), 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0);
		break;
	}
}

//----------------------------------------------------------------------------
int frame, fps, time, timebase = 0;
void
display(void)
{
	mat4 modelview;
	mat4 rotate = _RotateFunc(Theta[X], X) * _RotateFunc(Theta[Y], Y)
		*_RotateFunc(Theta[Z], Z);

	at = model[activemodel].bounds.Box_Center();
	up = vec4(0.0, 10.0, 0.0, 0.0);
	modelview = LookAt(camera, at, up);

	modelview *= rotate;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniform3fv(theta, 1, Theta);
	model[activemodel].draw();

	string winowname = model[activemodel].meshname + ": FPS:%d ";
	// Timing etc
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	char display_string[100];
	if (time - timebase > 1000) {
		fps = frame*1000.0 / (time - timebase);
		sprintf_s(display_string, "PreLoded Models | FPS:%d ", fps);
		glutSetWindowTitle(display_string);
		timebase = time;
		frame = 0;
	}

	glutSwapBuffers();
}

//----------------------------------------------------------------------------

bool wirestate = true;
void
keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 's': case 'S':
		activemodel < model.size() - 1 ? activemodel++ : activemodel = 0;
		glBindVertexArray(*vao[activemodel]);
		camera.z = 5.0;
		Theta[X] = Theta[Y] = Theta[Z] = 0;
		model[activemodel].draw();
		break;

	case 'a': case 'A':
		velocity *= -1;
		break;

	case 'z': case 'Z':
		camera.z *= 2;
		break;

	case 'w':
		glPolygonMode(GL_FRONT_AND_BACK, (wirestate) ? GL_LINE : GL_FILL);
		wirestate = !wirestate;
		break;

	case 033: // Escape Key
	case 'q': case 'Q':
		exit(EXIT_SUCCESS);
		break;
	}

	model[activemodel].bounds.Box_Max();
	projection = Perspective(45, aspectRatio, projbox[0], projbox[1]);
}

void
reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	aspectRatio = GLfloat(width) / height;
	model[activemodel].bounds.Box_Max();
	projection = Perspective(45, aspectRatio, model[activemodel].bounds.z_min + 3, model[activemodel].bounds.z_max -10);
	glUniformMatrix4fv(ProjectionLoc, 1, GL_TRUE, projection);
}

//----------------------------------------------------------------------------

void
mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) 
	{
		switch (button) 
		{
			case GLUT_LEFT_BUTTON:    axis = X;  break;
			case GLUT_MIDDLE_BUTTON:  axis = Y;  break;
			case GLUT_RIGHT_BUTTON:   axis = Z;  break;
		}

		Theta[axis] += velocity;
		if (Theta[axis] > 360.0)
		{
			Theta[axis] -= 360.0;
		}
	}
}

//----------------------------------------------------------------------------

void
idle(void)
{
	glutPostRedisplay();
}

//----------------------------------------------------------------------------



int
main(int argc, char **argv)
{
	//_LoadModels();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(512, 512);
	glutInitContextVersion(3, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutCreateWindow("PreLoded Models");

	glewExperimental = GL_TRUE;

	glewInit();

	init();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutIdleFunc(idle);

	glutMainLoop();
	cout << "END";
	system("pause");
	return 0;
}