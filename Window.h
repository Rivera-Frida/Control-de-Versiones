#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	GLfloat getXChange();
	GLfloat getYChange();
	GLfloat getmuevex() { return muevex; }
	GLfloat getangulocola() { return angulocola; }
	GLfloat getangulocabeza() { return angulocabeza; }
	GLfloat getanguloMand() { return anguloMand; }
	GLfloat getanguloPDD() { return anguloPDD; }
	GLfloat getanguloPDI() { return anguloPDI; }
	GLfloat getanguloPTD() { return anguloPTD; }
	GLfloat getanguloPTI() { return anguloPTI; }
	GLfloat getanguloL() { return anguloL; }
	GLfloat getangulocofre() { return angulocofre; }
	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	
	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	GLfloat muevex;
	GLfloat angulocola=0.0f;
	GLfloat angulocabeza = 0.0f;
	GLfloat anguloMand = 0.0f;
	GLfloat anguloPDD = 0.0f;
	GLfloat anguloPDI = 0.0f;
	GLfloat anguloPTI = 0.0f;
	GLfloat anguloPTD = 0.0f;
	GLfloat anguloL = 0.0f;
	GLfloat angulocofre = 0.0f;
	bool mouseFirstMoved;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);

};

