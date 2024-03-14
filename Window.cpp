#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	muevex = 2.0f;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Ejercicio 05: Optimización y carga de modelos", NULL, NULL);
	
	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se está usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}
GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}




void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_Y)
	{
		theWindow-> muevex += 1.0;
	}
	if (key == GLFW_KEY_U)
	{
		theWindow-> muevex -= 1.0;
	}

	if (key == GLFW_KEY_V)
	{
		if (theWindow->angulocola > 40.0)
		{
		}
		else
		{
			theWindow->angulocola += 10.0;
		}
	}

	if (key == GLFW_KEY_B)
	{
		if (theWindow->angulocola < -40.0)
		{
		}
		else
		{
			theWindow->angulocola -= 10.0;
		}
	}
	if (key == GLFW_KEY_F)
	{
		if (theWindow->anguloPDD > 45.0)
		{
		}
		else
		{
			theWindow->anguloPDD += 10.0;
		}
	}

	if (key == GLFW_KEY_G)
	{
		if (theWindow->anguloPDD < -45.0)
		{
		}
		else
		{
			theWindow->anguloPDD -= 10.0;
		}
	}
	if (key == GLFW_KEY_K)
	{
		if (theWindow->anguloPDI > 45.0)
		{
		}
		else
		{
			theWindow->anguloPDI += 10.0;
		}
	}

	if (key == GLFW_KEY_L)
	{
		if (theWindow->anguloPDI < -45.0)
		{
		}
		else
		{
			theWindow->anguloPDI -= 10.0;
		}
	}
	if (key == GLFW_KEY_Z)
	{
		if (theWindow->anguloPTD > 45.0)
		{
		}
		else
		{
			theWindow->anguloPTD += 10.0;
		}
	}

	if (key == GLFW_KEY_X)
	{
		if (theWindow->anguloPTD < -45.0)
		{
		}
		else
		{
			theWindow->anguloPTD -= 10.0;
		}
	}

	if (key == GLFW_KEY_N)
	{
		if (theWindow->anguloPTI > 45.0)
		{
		}
		else
		{
			theWindow->anguloPTI += 10.0;
		}
	}

	if (key == GLFW_KEY_M)
	{
		if (theWindow->anguloPTI < -45.0)
		{
		}
		else
		{
			theWindow->anguloPTI -= 10.0;
		}
	}
	
	if (key == GLFW_KEY_T)
	{
		if (theWindow->angulocabeza > 45.0)
		{
		}
		else
		{
			theWindow->angulocabeza += 10.0;
		}
	}

	if (key == GLFW_KEY_Y)
	{
		if (theWindow->angulocabeza < -45.0)
		{
		}
		else
		{
			theWindow->angulocabeza -= 10.0;
		}
	}
	if (key == GLFW_KEY_O)
	{
		if (theWindow->anguloMand > 45.0)
		{
		}
		else
		{
			theWindow->anguloMand += 10.0;
		}
	}

	if (key == GLFW_KEY_P)
	{
		if (theWindow->anguloMand < -45.0)
		{
		}
		else
		{
			theWindow->anguloMand -= 10.0;
		}
	}


	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("se solto la tecla %d'\n", key);
		}
	}

	if (key == GLFW_KEY_Z)
	{
		theWindow->anguloL += 10.0;
	}

	if (key == GLFW_KEY_X)
	{
		theWindow->anguloL -= 10.0;
	}

	if (key == GLFW_KEY_M)
	{
		if (theWindow->angulocofre > 40.0)
		{
		}
		else
		{
			theWindow->angulocofre += 10.0;
		}
	}

	if (key == GLFW_KEY_N)
	{
		if (theWindow->angulocofre <= 0.0)
		{
		}
		else
		{
			theWindow->angulocofre -= 10.0;
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}
