#include <iostream>
using namespace std;

#include "vgl.h"
#include "LoadShaders.h"

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs{ vPosition = 0 };

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;
const GLuint VerticesDimension = 2;

void init()
{
	static GLfloat vertices[NumVertices][VerticesDimension] =
	{
		// Triangle 1
		{ -0.90, -0.90 },
		{  0.85, -0.90 },
		{ -0.90, -0.85 },
		// Triangle 2
		{  0.90, -0.85 }, 
		{  0.90,  0.90 }, 
		{ -0.85,  0.90 }
	};

	glCreateBuffers(NumBuffers, Buffers);
	glNamedBufferStorage(Buffers[ArrayBuffer], sizeof(vertices), vertices, 0);

	ShaderInfo shaders[] =
	{
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.flag" },
		{ GL_NONE, NULL }
	};

	GLuint program = LoadShaders(shaders);
	glUseProgram(program);

	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glVertexAttribPointer(vPosition, VerticesDimension, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);
}

void display()
{
	static const float BackgroundColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, BackgroundColor);

	glBindVertexArray(VAOs[Triangles]);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}


void renderLoop(GLFWwindow* window)
{
	while (!glfwWindowShouldClose(window))
	{
		display();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
}


int main(int argc, char** argv)
{
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(640, 480, "Triangles", NULL, NULL);

	glfwMakeContextCurrent(window);
	gl3wInit;

	init();

	renderLoop(window);
}