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
enum { X = 0, Y = 1, Z = 2 };

int axis_numb = 3;
int axisActive = X;

GLfloat Theta[3] = { 0.0, 0.0, 0.0 };
GLfloat velocity = 5.0 * DegreesToRadians;
GLuint modelViewLoc;
GLuint  theta;  // The location of the "theta" shader uniform variable
vec4 at, up, eye;
GLfloat z_eye = 4.0;
GLfloat BoundBox_max, z_near, z_far, aspect;

GLuint ProjectionLoc;
mat4 projection;
GLfloat projection_near, projection_far, aspectRatio;

const int modelsize = 5;
Object model[modelsize] = { Object("cube.obj"), Object("bb8.obj"), Object("megatron.obj"), Object("batman.obj"), Object("ironmanmarkII.obj") };
int activemodel = 0;

// Create a vertex array object
GLuint vao[modelsize];
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------

// OpenGL initialization
void
init()
{
	GLuint program = InitShader("vshader42.glsl", "fshader42.glsl");

	glUseProgram(program);

	glGenVertexArrays(modelsize, vao);

	for (int i = 0; i < modelsize; i++)
	{
		glBindVertexArray(vao[i]);
		model[i].load(program);
	}

	glBindVertexArray(vao[activemodel]);

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

	eye = vec4(0.0, 0.0, z_eye, 1.0);
	at = model[activemodel].bounds.Box_Center();
	up = vec4(0.0, 3.0, 0.0, 0.0);
	modelview = LookAt(eye, at, up);

	modelview *= rotate;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUniformMatrix4fv(modelViewLoc, 1, GL_TRUE, modelview);
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
		activemodel < modelsize - 1 ? activemodel++ : activemodel = 0;
		glBindVertexArray(vao[activemodel]);
		eye.z = 5.0;
		Theta[X] = Theta[Y] = Theta[Z] = 0;
		model[activemodel].draw();
		break;

	case 'a':
	case 'A':
		velocity *= -1;
		break;

	case 'z':
		z_eye *= 0.8;
		break;
	case 'Z':
		z_eye *= 1.2;
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
	projection = Perspective(45.0, aspectRatio, z_near, z_far);
	glUniformMatrix4fv(ProjectionLoc, 1, GL_TRUE, projection);
}

void
reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	aspectRatio = GLfloat(width) / height;
	model[activemodel].bounds.Box_Max();
	z_far = 30;
	z_near = 0.05;
	projection = Perspective(45.0, aspectRatio, z_near, z_far);
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
		case GLUT_LEFT_BUTTON:    axisActive = X;  break;
		case GLUT_MIDDLE_BUTTON:  axisActive = Y;  break;
		case GLUT_RIGHT_BUTTON:   axisActive = Z;  break;
		}
		Theta[axisActive] += velocity;
		if (Theta[axisActive] > 360.0)
		{
			Theta[axisActive] -= 360.0;
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
	glutReshapeFunc(reshape);
	glutMainLoop();
	cout << "END";
	system("pause");
	return 0;
}