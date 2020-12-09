#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include<iostream>
#include<fstream>
#include<string>
#include<cstdio>

#include"mesh.h"
#include"Model.h"
#include"Shader.h"
#include"Camera.h"

using namespace std;


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
bool firstMouse = true;
float indexes = 0.5;
float last_x = SCR_WIDTH / 2.0f, last_y = SCR_HEIGHT / 2.0f;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
Camera camera;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void readObj(const char* filename,mesh* &object);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CGHW1", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	string filename = "example2.obj";
	string vShadername = "./shader/shader.vs";
	string fShadername = "./shader/shader.fs";
	/*mesh* object=nullptr;
	readObj(filename.c_str(),object);
	delete object;*/
	Model model(filename.c_str(),0.5);
	Shader s(vShadername.c_str(),fShadername.c_str());
	while (!glfwWindowShouldClose(window))
	{

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		mat4 projection3 = perspective(radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		s.use();
		/*mat4 view3 = camera.GetViewMatrix();
		s.setMat4("projection", projection3);
		s.setMat4("view", view3);

		mat4 model3 = mat4(1.0f);
		model3 = translate(model3, vec3(0.0f, 0.0f, 0.0f));
		model3 = scale(model3, vec3(1.0f, 1.0f, 1.0f));
		s.setMat4("model", model3);*/
		model.Draw(&s);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	//system("pause");
	return 0;
}

void readObj(const char* filename, mesh* &object)
{
	int i = 0;
	if (object != nullptr)
	{
		delete object;
	}
	fstream file;
	file.open(filename);
	if (!file.is_open())
	{
		printf("Can not read file:%s\n", filename);
		return;
	}
	string line;
	unsigned int numbVtx,numTri,numTex,numNor, numbVtx2, numTri2, numTex2, numNor2;
	numbVtx = numTri = numTex = numNor = numbVtx2 = numTri2 = numTex2 = numNor2 = 0;
	while (getline(file, line))
	{
		if (line[0] == 'v')
		{
			if (line[1] == ' ')
			{
				numbVtx++;
			}
			else if (line[1] == 't')
			{
				numTex++;
			}
			else if (line[1] == 'n')
			{
				numNor++;
			}
		}
		else if (line[0] == 'f')
		{
			numTri++;
		}
	}
	file.close();
	file.open(filename);
	tri* nface = new tri[numTri];
	vec3* nvertex = new vec3[numbVtx];
	vec3* nnormal = new vec3[numNor];
	vec2* ntexcord = new vec2[numTex];
	while (getline(file, line))
	{
		if (line[0] == 'v')
		{
			const char* st = line.c_str();
			if (line[1] == ' ')
			{
				double x, y, z;
				sscanf(st+2, "%lf%lf%lf", &x, &y, &z);
				nvertex[numbVtx2++].set(x, y, z);
			}
			else if (line[1] == 't')
			{
				double x, y;
				sscanf(st+2, "%lf%lf", &x, &y);
				ntexcord[numTex2++].set(x, y);
			}
			else if (line[1] == 'n')
			{
				double x, y, z;
				sscanf(st+2, "%lf%lf%lf", &x, &y, &z);
				nnormal[numNor2++].set(x, y, z);
			}
		}
		else if (line[0] == 'f'&& line[1] == ' ')
		{
			const char* st = line.c_str();
			unsigned id1, id2, id3, id4, id5, id6, id7, id8, id9;
			sscanf(st+2, "%u/%u/%u %u/%u/%u %u/%u/%u", &id1, &id2, &id3, &id4, &id5, &id6, &id7, &id8, &id9);
			nface[numTri2].setv(id1, id2, id3);
			nface[numTri2].sett(id4, id5, id6);
			nface[numTri2++].setn(id7, id8, id9);
		}
	}
	object = new mesh(numbVtx2, numTri2,0, nface, nvertex, nnormal, ntexcord,nullptr);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		indexes = (indexes >= 1) ? 1 : indexes + 0.1;

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		indexes = (indexes <= 0) ? 0 : indexes - 0.1;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		last_x = xpos;
		last_y = ypos;
		firstMouse = false;
	}
	float diff_x = xpos - last_x;
	float diff_y = last_y - ypos;
	last_x = xpos;
	last_y = ypos;

	camera.ProcessMouseMovement(diff_x, diff_y);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
