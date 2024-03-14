//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_m.h"
#include "Camera.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

const float toRadians = 3.14159265f / 180.0f;
//float angulocola = 0.0f;
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

//declaración cuerpo modelo
Model God_B;
//declaración cabeza modelo
Model God_H;
//declaración mandibula modelo
Model God_M;
//declaración cola modelo
Model God_T;
//declaración pata delantera derecha modelo
Model God_FRL;
//declaración pata delantera izquierda modelo
Model God_FLL;
//declaración pata trasera derecha modelo
Model God_BRL;
//declaración pata trasera izquierda modelo
Model God_BLL;


//Humvee
Model H;
// declaración base del auto
Model H_B;
// declaración cofre
Model H_C;
// Llanta 1
Model H_L1;
// Llanta 2
Model H_L2;
// Llanta 3
Model H_L3;
// Llanta 4
Model H_L4;

Skybox skybox;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;


// Vertex Shader
static const char* vShader = "shaders/shader_m.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_m.frag";





void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);


}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.5f, 7.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 1.0f);

	//Modelo de cuerpo
	God_B = Model();
	God_B.LoadModel("Models/god_body.obj");
	//Modelo de cabeza
	God_H = Model();
	God_H.LoadModel("Models/god_Head1.obj");
	//Modelo de mandibula
	God_M = Model();
	God_M.LoadModel("Models/god_Mand.obj");
	//Modelo de cola
	God_T = Model();
	God_T.LoadModel("Models/god_tail.obj");
	//Modelo de pata delantera derecha
	God_FRL = Model();
	God_FRL.LoadModel("Models/god_PDD.obj");
	//Modelo de pata delantera izquierda
	God_FLL = Model();
	God_FLL.LoadModel("Models/god_PDI.obj");
	//Modelo de pata trasera derecha
	God_BRL = Model();
	God_BRL.LoadModel("Models/god_PTD.obj");
	//Modelo de pata trasera izquierda
	God_BLL = Model();
	God_BLL.LoadModel("Models/god_PTI.obj");

	// auto 
	H = Model();
	H.LoadModel("Models/Humvee.obj");
	//Base 
	H_B = Model();
	H_B.LoadModel("Models/Base_H.obj");
	//Cofre 
	H_C = Model();
	H_C.LoadModel("Models/Cofre_H.obj");
	//BAse de la llanta 1
	H_L1 = Model();
	H_L1.LoadModel("Models/H_L1.obj");
	//BAse de la llanta 2
	H_L2 = Model();
	H_L2.LoadModel("Models/H_L2.obj");
	//BAse de la llanta 3 
	H_L3 = Model();
	H_L3.LoadModel("Models/H_L3.obj");
	//BAse de la llanta 4
	H_L4 = Model();
	H_L4.LoadModel("Models/H_L4.obj");


	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	

	glm::mat4 model(1.0);
	glm::mat4 modelaux(1.0);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Se dibuja el Skybox
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformColor = shaderList[0].getColorLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		// INICIA DIBUJO DEL PISO
		color = glm::vec3(0.5f, 0.5f, 0.5f); //piso de color gris
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		meshList[2]->RenderMesh();
/*
	//------------*INICIA DIBUJO DE NUESTROS DEMÁS OBJETOS-------------------*
		//Goddard
		color = glm::vec3(1.0f, 0.0f, 0.624f); //modelo de goddard de color rosa
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, -1.5f));
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		God_B.RenderModel();//modificar por el modelo sin las 4 patas y sin cola
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		//En sesión se separara una parte del modelo de Goddard y se unirá por jeraquía al cuerpo
		
		// Cabeza
		model = modelaux;
		color = glm::vec3(0.0f, 0.992f, 1.0f); // color cabeza
		model = glm::translate(model, glm::vec3(1.2f, 3.5f, 1.2f));
		model = glm::rotate(model, glm::radians(mainWindow.getangulocabeza()), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		God_H.RenderModel();

		// Mandibula
		color = glm::vec3(0.0f, 1.0f, 0.0f); // color 
		model = glm::translate(model, glm::vec3(1.17f, -0.90f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getanguloMand()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		God_M.RenderModel();
		
		//Pata delantera derecha
		model = modelaux;
		color = glm::vec3(1.0f, 0.922f, 0.0f); // color 
		model = glm::translate(model, glm::vec3(1.0f, 2.5f, 0.5f));
		model = glm::rotate(model, glm::radians(mainWindow.getanguloPDD()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		God_FRL.RenderModel();

		//Pata delantera izquierda
		model = modelaux;
		color = glm::vec3(0.643f, 1.0f, 0.0f); // color 
		model = glm::translate(model, glm::vec3(1.0f, 2.5f, 2.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getanguloPDI()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		God_FLL.RenderModel();

		//Pata trasera derecha
		model = modelaux;
		color = glm::vec3(1.0f, 0.471f, 0.0f); // color 
		model = glm::translate(model, glm::vec3(-0.9f, 1.8f, 0.5f));
		model = glm::rotate(model, glm::radians(mainWindow.getanguloPTD()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		God_BRL.RenderModel();

		//Pata trasera izquierda
		model = modelaux;
		color = glm::vec3(0.929f, 0.0f, 0.0f); // color 
		model = glm::translate(model, glm::vec3(-0.9f, 1.8f, 1.8f));
		model = glm::rotate(model, glm::radians(mainWindow.getanguloPTI()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		God_BLL.RenderModel();

		//Cola
		model = modelaux;
		color = glm::vec3(0.839f, 0.0f, 1.0f); // color cola
		model = glm::translate(model, glm::vec3(-1.5f, 2.5f, 1.4f));
		model = glm::rotate(model, glm::radians(mainWindow.getangulocola()), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		God_T.RenderModel();
*/

		//Auto Exportado Humvee
		color = glm::vec3(0.0f, 0.016f, 1.0f); //color verde

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	//	H.RenderModel();
		//base
		color = glm::vec3(0.0f, 0.016f, 1.0f);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, mainWindow.getmuevex()));
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		modelaux = model;
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		H_B.RenderModel();


		//cofre
		model = modelaux;
		color = glm::vec3(0.0f, 0.0f, 0.0f); // color 
		model = glm::translate(model, glm::vec3(-10.0f, 95.0f, 63.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getangulocofre()), glm::vec3(-1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		H_C.RenderModel();

		//llanta 1
		model = modelaux;
		color = glm::vec3(0.294f, 0.302f, 0.294f);
		model = glm::translate(model, glm::vec3(40.0f, 35.0f, 130.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getanguloL()), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		H_L1.RenderModel();

		//llanta 2
		model = modelaux;
		color = glm::vec3(0.294f, 0.302f, 0.294f); 
		model = glm::translate(model, glm::vec3(-60.0f, 35.0f, 130.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getanguloL()), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		H_L2.RenderModel();
		
		//llanta 3
		model = modelaux;
		color = glm::vec3(0.294f, 0.302f, 0.294f);
		model = glm::translate(model, glm::vec3(40.0f, 35.0f, -120.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getanguloL()), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		H_L3.RenderModel();
		
		//lanta 4 
		model = modelaux;
		color = glm::vec3(0.294f, 0.302f, 0.294f);
		model = glm::translate(model, glm::vec3(-60.0f, 35.0f, -120.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getanguloL()), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		H_L4.RenderModel();


		glUseProgram(0); 
		mainWindow.swapBuffers();
	}

	return 0;
}
