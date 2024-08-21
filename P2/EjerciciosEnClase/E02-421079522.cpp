//Pr�ctica 2: �ndices, mesh, proyecciones, transformaciones geom�tricas
#include <stdio.h>
#include <string.h>
#include<cmath>

#include<vector>
#include <glew.h>
#include <glfw3.h>

//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al c�digo
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f / 180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;

//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crear�an ac�

float angulo = 0.0f;

//color caf� en RGB : 0.478, 0.255, 0.067

//Pir�mide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = {
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3

	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//V�rtices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// back
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
	//GLfloat vertices_letras[] = {
		//AQUI VA LISTA DE LETRAS YA HECHAS, COLUMNAS R,G,B ES PARA DEFINIR COLOR
		//X			Y			Z			R		G		B
		/*-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		1.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		1.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		-1.0f,  1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,*/

	//};
	//MeshColor* letras = new MeshColor();
	//letras->CreateMeshColor(vertices_letras, 18);
	//meshColorList.push_back(letras);


	GLfloat vertices_trianguloazul[] = {
		//X			Y			Z			R		G		B
		0.0f,	1.0f,		0.0f,			0.0f,	0.0f,	1.0f,
		0.6f,	0.1f,		0.0f,			0.0f,	0.0f,	1.0f,
		-0.6f,	0.1f,		0.0f,			0.0f,	0.0f,	1.0f,

	};

	MeshColor* trianguloazul = new MeshColor();
	trianguloazul->CreateMeshColor(vertices_trianguloazul, 18);
	meshColorList.push_back(trianguloazul);

	GLfloat vertices_cuadradocafe1[] = {
		//X			Y			Z			R		G		B
		-0.9f,	-1.0f,		0.5f,			0.478, 0.255, 0.067,
		-0.9f,	-0.8f,		0.5f,			0.478, 0.255, 0.067,
		-0.7f,	-0.8f,		0.5f,			0.478, 0.255, 0.067,
		-0.7f,	-0.8f,		0.5f,			0.478, 0.255, 0.067,
		-0.9f,	-1.0f,		0.5f,			0.478, 0.255, 0.067,
		-0.7f,	-1.0f,		0.5f,			0.478, 0.255, 0.067,

	};

	MeshColor* cuadradocafe1 = new MeshColor();
	cuadradocafe1->CreateMeshColor(vertices_cuadradocafe1, 54);
	meshColorList.push_back(cuadradocafe1);

	GLfloat vertices_cuadradocafe2[] = {
		//X			Y			Z			R		G		B
		0.9f,	-1.0f,		0.5f,			0.478, 0.255, 0.067,
		0.9f,	-0.8f,		0.5f,			0.478, 0.255, 0.067,
		0.7f,	-0.8f,		0.5f,			0.478, 0.255, 0.067,
		0.7f,	-0.8f,		0.5f,			0.478, 0.255, 0.067,
		0.9f,	-1.0f,		0.5f,			0.478, 0.255, 0.067,
		0.7f,	-1.0f,		0.5f,			0.478, 0.255, 0.067,
	};

	MeshColor* cuadradocafe2 = new MeshColor();
	cuadradocafe2->CreateMeshColor(vertices_cuadradocafe2, 90);
	meshColorList.push_back(cuadradocafe2);

	GLfloat vertices_cuadradoverde[] = {
		//X			Y			Z			R		G		B
		-0.15f,	-1.0f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.15f,	-1.0f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.15f,	-0.7f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.15f,	-1.0f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.15f,	-0.7f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.15f,	-0.7f,		0.5f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* cuadradoverde = new MeshColor();
	cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 126);
	meshColorList.push_back(cuadradoverde);

	GLfloat vertices_cuadradoverde2[] = {
		//X			Y			Z			R		G		B
		-0.1f,	0.0f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.4f,	0.0f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.4f,	-0.3f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.1f,	0.0f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.4f,	-0.3f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.1f,	-0.3f,		0.5f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* cuadradoverde2 = new MeshColor();
	cuadradoverde2->CreateMeshColor(vertices_cuadradoverde2, 162);
	meshColorList.push_back(cuadradoverde2);

	GLfloat vertices_cuadradoverde3[] = {
		//X			Y			Z			R		G		B
		0.1f,	0.0f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.4f,	0.0f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.4f,	-0.3f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.1f,	0.0f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.4f,	-0.3f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.1f,	-0.3f,		0.5f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* cuadradoverde3 = new MeshColor();
	cuadradoverde3->CreateMeshColor(vertices_cuadradoverde3, 198);
	meshColorList.push_back(cuadradoverde3);


	GLfloat vertices_cuadradorojo[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-1.0f,		0.0f,			1.0f,	0.0f,	0.0f,
		0.5f,	-1.0f,		0.0f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.1f,		0.0f,			1.0f,	0.0f,	0.0f,
		-0.5f,	-1.0f,		0.0f,			1.0f,	0.0f,	0.0f,
		0.5f,	0.1f,		0.0f,			1.0f,	0.0f,	0.0f,
		-0.5f,	0.1f,		0.0f,			1.0f,	0.0f,	0.0f,

	};

	MeshColor* cuadradorojo = new MeshColor();
	cuadradorojo->CreateMeshColor(vertices_cuadradorojo, 234);
	meshColorList.push_back(cuadradorojo);


	GLfloat vertices_trianguloverde[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-0.8f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.6f,	-0.8f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.8f,	-0.1f,		0.5f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* trianguloverde = new MeshColor();
	trianguloverde->CreateMeshColor(vertices_trianguloverde, 252);
	meshColorList.push_back(trianguloverde);

	GLfloat vertices_trianguloverde2[] = {
		//X			Y			Z			R		G		B
		1.0f,	-0.8f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.6f,	-0.8f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.8f,	-0.1f,		0.5f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* trianguloverde2 = new MeshColor();
	trianguloverde2->CreateMeshColor(vertices_trianguloverde2, 270);
	meshColorList.push_back(trianguloverde2);

}


void CreateShaders()
{
	Shader* shader1 = new Shader(); //shader para usar �ndices: objetos: cubo y  pir�mide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader* shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);
}


int main()
{
	mainWindow = Window(720, 720);
	mainWindow.Initialise();

	CrearLetrasyFiguras(); //usa MeshColor, �ndices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensi�n 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	//glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	//Model: Matriz de Dimensi�n 4x4 en la cual se almacena la multiplicaci�n de las transformaciones geom�tricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad

		// Usar el shader para colores
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();

		// Inicializar la matriz de modelo
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));

		// Enviar las matrices al shader
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

		// Renderizar letras y figuras
		
		meshColorList[0]->RenderMeshColor(); 
		meshColorList[1]->RenderMeshColor();  
		meshColorList[2]->RenderMeshColor();
		meshColorList[3]->RenderMeshColor();
		meshColorList[4]->RenderMeshColor();
		meshColorList[5]->RenderMeshColor();
		meshColorList[6]->RenderMeshColor();
		meshColorList[7]->RenderMeshColor();
		meshColorList[8]->RenderMeshColor();

		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslaci�n
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACI�N //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/
