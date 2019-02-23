#include "Tema2.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>
#include "Transform3DD.h"

using namespace std;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

double translateXMasa = 0;
double translateYMasa = 0;
double translateZMasa = 0.3;
double scaleXMasa = 1.4;
double scaleYMasa = 2.8;
double scaleZMasa = 0.6;
double translateXMargineFata = translateXMasa;
double translateYMargineFata = scaleYMasa / 2 + 0.05;
double translateZMargineFata = translateZMasa + 0.05;
double scaleXMargineFata = scaleXMasa + 0.2;
double scaleYMargineFata = 0.1;
double scaleZMargineFata = scaleZMasa + 0.1;
double translateXMargineDreapta = scaleXMasa / 2 + 0.05;
double translateYMargineDreapta = 0;
double scaleXMargineDreapta = 0.1;
double scaleYMargineDreapta = scaleYMasa + 0.2;
double translateXBuzunarDreaptaJos = scaleXMasa / 2;
double translateYBuzunarDreaptaJos = scaleYMasa / 2;
double translateZBuzunarDreaptaJos = scaleZMasa;
double diametruBuzunar = 0.2;
double diametruBila = 0.1;
double diametruBilaAlba = diametruBila;
double translateXBilaAlba = 0;
double translateYBilaAlba = 0.95;
double translateZBilaAlba = scaleZMasa + diametruBila / 2;
double translateXBilaAlbaInitial = translateXBilaAlba;
double translateYBilaAlbaInitial = translateYBilaAlba;
double translateZBilaAlbaInitial = translateZBilaAlba;
double translateXBilaRosieVarf = 0;
double translateYBilaRosieVarf = -0.5;
double translateXTac = 0;
double translateYTac = 1.9;
double translateZTac = translateZBilaAlba;
double diametruTac = 0.016;
double lungimeTac = 1.6;
double rotatieTac = 0;
double vitezaLovitura = 0;
double coordX = 0;
double unghiBila;
int flagIntoarcereBila = 0;
int flagAtingereFata = 0;
int contorPrimaAtingereSpate = 0;
int contorPrimaAtingereFata = 0;
int flagAtingereDreapta = 0;
int contorPrimaAtingereDreapta = 0;
int flagAtingereStanga = 0;
int contorPrimaAtingereStanga = 0;
float distanceToTarget = 0.55;
bool renderCameraTarget = false;
int flagAlbAtingereBuzunar = 0;
double directieXLansareInitial = -0.0001;
double directieYLansareInitial = -1;
double directieXLansare = -0.0001;
double directieYLansare = -1;
double flagCameraSus = 0;
double translateXBile[16];
double translateYBile[16];
double unghiBile[16];
double flagAtingereBile[16];
double contorAtingereBile[16];
int flagIntoarcereBile[16];
int flagAtingereFataBile[16];
int contorAtingereSpateBile[16];
int contorAtingereFataBile[16];
int flagAtingereDreaptaBile[16];
int contorAtingereDreaptaBile[16];
int flagAtingereStangaBile[16];
int contorAtingereStangaBile[16];
int flagAtingereBuzunarBile[16];
int NicioBilaAtinsa = 1;
double diametruBile[16];
double unghiBilaAux;
int flagInceput = 0;
float neAtenuare = 1;
double vitezaLovituraAux[16];
int flagColiziuneBilaMiscare[16];
double neAtenuareBile[16];
int flagNuMaiIntraAici[16];
int flagEDoarJ[16];
double Coliziune[16][16];

void Tema2::Init()
{
	renderCameraTarget = false;

	camera = new Laborator::Camera();
	camera->Set(glm::vec3(0, 1, 3.5f), glm::vec3(0, 0.7f, 0), glm::vec3(0, 1, 0));

	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	{
		Mesh* mesh = new Mesh("tac");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "tac.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	for (int i = 0; i < 15; i++)
		diametruBile[i] = diametruBila;

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	// Create a shader program for drawing face polygon with the color of the normal
	{
		Shader *shader = new Shader("Verde");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader *shader = new Shader("Maro");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader2.glsl", GL_FRAGMENT_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader *shader = new Shader("Alb");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader3.glsl", GL_FRAGMENT_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader *shader = new Shader("Negru");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader4.glsl", GL_FRAGMENT_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader *shader = new Shader("Rosu");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader5.glsl", GL_FRAGMENT_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader *shader = new Shader("Galben");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader6.glsl", GL_FRAGMENT_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

	{
		Shader *shader = new Shader("Olive");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader7.glsl", GL_FRAGMENT_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}

void Tema2::FrameStart()
{
	// clears the VertexColor buffer (using the previously set VertexColor) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the Normals area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::Update(float deltaTimeSeconds)
{
	//Baza mesei
	{
		glm::mat4 modelMatrix = glm::mat4(1);// x     z      y
		modelMatrix *= Transform3DD::Translate(translateXMasa, translateZMasa, translateYMasa);
		modelMatrix *= Transform3DD::Scale(scaleXMasa, scaleZMasa, scaleYMasa);
		RenderMesh(meshes["box"], shaders["Verde"], modelMatrix);
	}

	//Marginea din fata
	{
		glm::mat4 modelMatrix = glm::mat4(1);// x     z      y
		modelMatrix *= Transform3DD::Translate(translateXMargineFata, translateZMargineFata, translateYMargineFata);
		modelMatrix *= Transform3DD::Scale(scaleXMargineFata, scaleZMargineFata, scaleYMargineFata);
		RenderMesh(meshes["box"], shaders["Maro"], modelMatrix);
	}

	//Marginea din spate
	{
		glm::mat4 modelMatrix = glm::mat4(1);// x     z      y
		modelMatrix *= Transform3DD::Translate(translateXMargineFata, translateZMargineFata, -translateYMargineFata);
		modelMatrix *= Transform3DD::Scale(scaleXMargineFata, scaleZMargineFata, scaleYMargineFata);
		RenderMesh(meshes["box"], shaders["Maro"], modelMatrix);
	}

	//Marginea din dreapta
	{
		glm::mat4 modelMatrix = glm::mat4(1);// x     z      y
		modelMatrix *= Transform3DD::Translate(translateXMargineDreapta, translateZMargineFata, translateYMargineDreapta);
		modelMatrix *= Transform3DD::Scale(scaleXMargineDreapta, scaleZMargineFata, scaleYMargineDreapta);
		RenderMesh(meshes["box"], shaders["Maro"], modelMatrix);
	}

	//Marginea din stanga
	{
		glm::mat4 modelMatrix = glm::mat4(1);// x     z      y
		modelMatrix *= Transform3DD::Translate(-translateXMargineDreapta, translateZMargineFata, translateYMargineDreapta);
		modelMatrix *= Transform3DD::Scale(scaleXMargineDreapta, scaleZMargineFata, scaleYMargineDreapta);
		RenderMesh(meshes["box"], shaders["Maro"], modelMatrix);
	}

	//Buzunarele
	//dreapta jos
	{
		glm::mat4 modelMatrix = glm::mat4(1);// x     z      y
		modelMatrix *= Transform3DD::Translate(translateXBuzunarDreaptaJos, translateZBuzunarDreaptaJos, translateYBuzunarDreaptaJos);
		modelMatrix *= Transform3DD::Scale(diametruBuzunar, diametruBuzunar, diametruBuzunar);
		RenderMesh(meshes["sphere"], shaders["Negru"], modelMatrix);
	}

	//stanga jos
	{
		glm::mat4 modelMatrix = glm::mat4(1);// x     z      y
		modelMatrix *= Transform3DD::Translate(-translateXBuzunarDreaptaJos, translateZBuzunarDreaptaJos, translateYBuzunarDreaptaJos);
		modelMatrix *= Transform3DD::Scale(diametruBuzunar, diametruBuzunar, diametruBuzunar);
		RenderMesh(meshes["sphere"], shaders["Negru"], modelMatrix);
	}

	//dreapta sus
	{
		glm::mat4 modelMatrix = glm::mat4(1);// x     z      y
		modelMatrix *= Transform3DD::Translate(translateXBuzunarDreaptaJos, translateZBuzunarDreaptaJos, -translateYBuzunarDreaptaJos);
		modelMatrix *= Transform3DD::Scale(diametruBuzunar, diametruBuzunar, diametruBuzunar);
		RenderMesh(meshes["sphere"], shaders["Negru"], modelMatrix);
	}

	//stanga sus
	{
		glm::mat4 modelMatrix = glm::mat4(1);// x     z      y
		modelMatrix *= Transform3DD::Translate(-translateXBuzunarDreaptaJos, translateZBuzunarDreaptaJos, -translateYBuzunarDreaptaJos);
		modelMatrix *= Transform3DD::Scale(diametruBuzunar, diametruBuzunar, diametruBuzunar);
		RenderMesh(meshes["sphere"], shaders["Negru"], modelMatrix);
	}

	//dreapta centru
	{
		glm::mat4 modelMatrix = glm::mat4(1);// x     z      y
		modelMatrix *= Transform3DD::Translate(translateXBuzunarDreaptaJos, translateZBuzunarDreaptaJos, 0.0f);
		modelMatrix *= Transform3DD::Scale(diametruBuzunar / 2, diametruBuzunar, diametruBuzunar);
		RenderMesh(meshes["sphere"], shaders["Negru"], modelMatrix);
	}

	//stanga centru
	{
		glm::mat4 modelMatrix = glm::mat4(1);// x     z      y
		modelMatrix *= Transform3DD::Translate(-translateXBuzunarDreaptaJos, translateZBuzunarDreaptaJos, 0.0f);
		modelMatrix *= Transform3DD::Scale(diametruBuzunar / 2, diametruBuzunar, diametruBuzunar);
		RenderMesh(meshes["sphere"], shaders["Negru"], modelMatrix);
	}

	//Tacul
	{
		if (flagCameraSus == 0 || vitezaLovitura == 0)
		{
			glm::mat4 modelMatrix = glm::mat4(1);// x     z      y
			modelMatrix *= Transform3DD::Translate(translateXBilaAlba, translateZBilaAlba, translateYBilaAlba);
			modelMatrix *= Transform3DD::Scale(0.03, 0.03, 0.03);
			modelMatrix *= Transform3DD::RotateOY(RADIANS(-unghiBila));
			modelMatrix *= Transform3DD::RotateOZ(RADIANS(9.0f));
			RenderMesh(meshes["tac"], shaders["Olive"], modelMatrix);
		}
	}

	//Bila alba initial
	{
		glm::mat4 modelMatrix = glm::mat4(1);// x     z      y
		modelMatrix *= Transform3DD::Translate(translateXBilaAlba, translateZBilaAlba, translateYBilaAlba);
		modelMatrix *= Transform3DD::Scale(diametruBilaAlba, diametruBilaAlba, diametruBilaAlba);
		RenderMesh(meshes["sphere"], shaders["Alb"], modelMatrix);

		if (!window->MouseHold(GLFW_MOUSE_BUTTON_LEFT))
		{
			if (vitezaLovitura == 0)
			{
				flagIntoarcereBila = 0;
				flagAtingereFata = 0;
				flagAtingereDreapta = 0;
				flagAtingereStanga = 0;

				contorPrimaAtingereSpate = 0;
				contorPrimaAtingereFata = 0;
				contorPrimaAtingereDreapta = 0;
				contorPrimaAtingereStanga = 0;

				for (int i = 0; i < 15; i++)
				{
					flagAtingereBile[i] = 0;
					contorAtingereBile[i] = 0;
					flagIntoarcereBile[i] = 0;
					flagAtingereFataBile[i] = 0;
					contorAtingereSpateBile[i] = 0;
					contorAtingereFataBile[i] = 0;
					flagAtingereDreaptaBile[i] = 0;
					contorAtingereDreaptaBile[i] = 0;
					flagAtingereStangaBile[i] = 0;
					contorAtingereStangaBile[i] = 0;
				}
			}

			//Plecare bila
			if (flagIntoarcereBila == 0 && flagAtingereFata == 0 && flagAtingereDreapta == 0 && flagAtingereStanga == 0)
			{
				NicioBilaAtinsa = 1;
				for (int i = 0; i < 15; i++)
				{
					if (flagAtingereBile[i] == 1 || flagColiziuneBilaMiscare[i] == 1)
						NicioBilaAtinsa = 0;
				}

				if (NicioBilaAtinsa == 1)
				{
					unghiBila = atan(directieYLansare / directieXLansare);
					unghiBila = unghiBila * 180 / M_PI;

					if (directieXLansare > 0 && directieYLansare < 0)
						unghiBila = 180 + unghiBila;

					if (directieXLansare > 0 && directieYLansare > 0)
						unghiBila = -180 + unghiBila;

					if (unghiBila < 0)
					{
						unghiBila = 360 + unghiBila;
					}
				}

				translateXBilaAlba = translateXBilaAlba - deltaTimeSeconds * neAtenuare * vitezaLovitura * cos(unghiBila* M_PI / 180);
				translateYBilaAlba = translateYBilaAlba - deltaTimeSeconds * neAtenuare * vitezaLovitura * sin(unghiBila* M_PI / 180);
			}

			//Reflexia cu manta din spate
			if (translateYBilaAlba <= (-translateYMargineFata + diametruBila) || flagIntoarcereBila == 1)
			{
				flagAtingereFata = 0;
				contorPrimaAtingereFata = 0;
				flagAtingereDreapta = 0;
				contorPrimaAtingereDreapta = 0;
				flagAtingereStanga = 0;
				contorPrimaAtingereStanga = 0;
				contorPrimaAtingereSpate++;
				if (contorPrimaAtingereSpate == 1)
					unghiBila = -unghiBila;
				flagIntoarcereBila = 1;

				translateXBilaAlba = translateXBilaAlba - deltaTimeSeconds * neAtenuare * vitezaLovitura * cos(unghiBila* M_PI / 180);
				translateYBilaAlba = translateYBilaAlba - deltaTimeSeconds * neAtenuare * vitezaLovitura * sin(unghiBila* M_PI / 180);
			}

			//Reflexia cu manta din fata
			if (translateYBilaAlba >= (translateYMargineFata - diametruBila) || flagAtingereFata == 1)
			{
				flagIntoarcereBila = 0;
				contorPrimaAtingereSpate = 0;
				flagAtingereDreapta = 0;
				contorPrimaAtingereDreapta = 0;
				flagAtingereStanga = 0;
				contorPrimaAtingereStanga = 0;
				contorPrimaAtingereFata++;
				if (contorPrimaAtingereFata == 1)
					unghiBila = -unghiBila;
				flagAtingereFata = 1;

				translateXBilaAlba = translateXBilaAlba - deltaTimeSeconds * neAtenuare * vitezaLovitura * cos(unghiBila* M_PI / 180);
				translateYBilaAlba = translateYBilaAlba - deltaTimeSeconds * neAtenuare * vitezaLovitura * sin(unghiBila* M_PI / 180);
			}

			//Reflexia cu manta din dreapta
			if (translateXBilaAlba >= (translateXMargineDreapta - diametruBila) || flagAtingereDreapta == 1)
			{
				flagIntoarcereBila = 0;
				contorPrimaAtingereSpate = 0;
				flagAtingereFata = 0;
				contorPrimaAtingereFata = 0;
				flagAtingereStanga = 0;
				contorPrimaAtingereStanga = 0;
				contorPrimaAtingereDreapta++;
				if (contorPrimaAtingereDreapta == 1)
					unghiBila = 180 - unghiBila;
				flagAtingereDreapta = 1;

				translateXBilaAlba = translateXBilaAlba - deltaTimeSeconds * neAtenuare * vitezaLovitura * cos(unghiBila* M_PI / 180);
				translateYBilaAlba = translateYBilaAlba - deltaTimeSeconds * neAtenuare * vitezaLovitura * sin(unghiBila* M_PI / 180);
			}

			//Reflexia cu manta din stanga
			if (translateXBilaAlba <= (-translateXMargineDreapta + diametruBila) || flagAtingereStanga == 1)
			{
				flagIntoarcereBila = 0;
				contorPrimaAtingereSpate = 0;
				flagAtingereFata = 0;
				contorPrimaAtingereFata = 0;
				flagAtingereDreapta = 0;
				contorPrimaAtingereDreapta = 0;
				contorPrimaAtingereStanga++;
				if (contorPrimaAtingereStanga == 1)
					unghiBila = 180 - unghiBila;
				flagAtingereStanga = 1;

				translateXBilaAlba = translateXBilaAlba - deltaTimeSeconds * neAtenuare * vitezaLovitura * cos(unghiBila* M_PI / 180);
				translateYBilaAlba = translateYBilaAlba - deltaTimeSeconds * neAtenuare * vitezaLovitura * sin(unghiBila* M_PI / 180);
			}

			//Scaderea vitezei bilei albe
			if (vitezaLovitura != 0)
			{
				if ((vitezaLovitura - deltaTimeSeconds) >= 0)
					vitezaLovitura = vitezaLovitura - deltaTimeSeconds;
				else
				{
					vitezaLovitura = 0;

					for (int i = 0; i < 15; i++)
					{
						flagColiziuneBilaMiscare[i] = 0;

						flagAtingereBile[i] = 0;
						contorAtingereBile[i] = 0;
						flagIntoarcereBile[i] = 0;
						flagAtingereFataBile[i] = 0;
						contorAtingereSpateBile[i] = 0;
						contorAtingereFataBile[i] = 0;
						flagAtingereDreaptaBile[i] = 0;
						contorAtingereDreaptaBile[i] = 0;
						flagAtingereStangaBile[i] = 0;
						contorAtingereStangaBile[i] = 0;
					}
				}
			}
		}

		//Ordine buzunare -> dreapta: jos, centru, sus + stanga: jos, centru, sus
		if ((pow(translateXBilaAlba - translateXBuzunarDreaptaJos, 2) + pow(translateYBilaAlba - translateYBuzunarDreaptaJos, 2) <= pow(diametruBila / 2 + diametruBuzunar / 2, 2)) ||
			(pow(translateXBilaAlba - translateXBuzunarDreaptaJos, 2) + pow(translateYBilaAlba, 2) <= pow(diametruBila / 2 + diametruBuzunar / 4, 2)) ||
			(pow(translateXBilaAlba - translateXBuzunarDreaptaJos, 2) + pow(translateYBilaAlba - (-translateYBuzunarDreaptaJos), 2) <= pow(diametruBila / 2 + diametruBuzunar / 2, 2)) ||
			(pow(translateXBilaAlba - (-translateXBuzunarDreaptaJos), 2) + pow(translateYBilaAlba - translateYBuzunarDreaptaJos, 2) <= pow(diametruBila / 2 + diametruBuzunar / 2, 2)) ||
			(pow(translateXBilaAlba - (-translateXBuzunarDreaptaJos), 2) + pow(translateYBilaAlba, 2) <= pow(diametruBila / 2 + diametruBuzunar / 4, 2)) ||
			(pow(translateXBilaAlba - (-translateXBuzunarDreaptaJos), 2) + pow(translateYBilaAlba - (-translateYBuzunarDreaptaJos), 2) <= pow(diametruBila / 2 + diametruBuzunar / 2, 2)))
		{
			diametruBilaAlba = 0;
			flagAlbAtingereBuzunar = 1;
			cout << "Fault! Bila Alba a intrat in buzunar si va fi repozitionata pe pozitia initiala!" << endl;
		}

		//Setare flag-uri dupa ce bila alba a intrat in buzunar sau s-a comis fault prin neatingerea niciunei bile
		if (diametruBilaAlba == 0)
		{
			for (int i = 0; i < 15; i++)
			{
				flagAtingereBile[i] = 0;
				vitezaLovituraAux[i] = 0;
				flagNuMaiIntraAici[i] = 0;
				for (int j = 0; j < 15; j++)
				{
					Coliziune[i][j] = 0;
				}
			}

			vitezaLovitura = 0;
			translateXBilaAlba = translateXBilaAlbaInitial;
			translateYBilaAlba = translateYBilaAlbaInitial;
			translateZBilaAlba = translateZBilaAlbaInitial;
			directieXLansare = directieXLansareInitial;
			directieYLansare = directieYLansareInitial;
			diametruBilaAlba = diametruBila;
		}

		if (vitezaLovitura > 0)
			flagAlbAtingereBuzunar = 0;
	}

	//Bila rosie varful triunghiului
	for (int i = 0; i < 15; i++)
	{
		glm::mat4 modelMatrix = glm::mat4(1);// x     z      y

		//Triunghiul de bile
		if (flagInceput == 0)
		{
			translateXBile[0] = translateXBilaRosieVarf;
			translateYBile[0] = translateYBilaRosieVarf;

			double contorRand = 1.05;
			//Primul rand
			float dist = translateYBilaRosieVarf - contorRand * sqrt(3 * pow(diametruBila * 100, 2.0) / 4) / 100;
			modelMatrix = glm::mat4(1);// x     z      y
			translateXBile[1] = contorRand * 0.05f;
			translateYBile[1] = dist;

			dist = translateYBilaRosieVarf - contorRand * sqrt(3 * pow(diametruBila * 100, 2.0) / 4) / 100;
			modelMatrix = glm::mat4(1);// x     z      y
			translateXBile[2] = contorRand * (-0.05f);
			translateYBile[2] = dist;

			contorRand += 1.05;
			//Al doilea rand
			dist = translateYBilaRosieVarf - contorRand * sqrt(3 * pow(diametruBila * 100, 2.0) / 4) / 100;
			modelMatrix = glm::mat4(1);// x     z      y
			translateXBile[3] = 0.0f;
			translateYBile[3] = dist;

			dist = translateYBilaRosieVarf - contorRand * sqrt(3 * pow(diametruBila * 100, 2.0) / 4) / 100;
			modelMatrix = glm::mat4(1);// x     z      y
			translateXBile[4] = contorRand * 0.05f;
			translateYBile[4] = dist;

			dist = translateYBilaRosieVarf - contorRand * sqrt(3 * pow(diametruBila * 100, 2.0) / 4) / 100;
			modelMatrix = glm::mat4(1);// x     z      y
			translateXBile[5] = contorRand * (-0.05f);
			translateYBile[5] = dist;

			contorRand += 1.05;
			//Al treilea rand
			dist = translateYBilaRosieVarf - contorRand * sqrt(3 * pow(diametruBila * 100, 2.0) / 4) / 100;
			modelMatrix = glm::mat4(1);// x     z      y
			translateXBile[6] = (contorRand - 2.1) * 0.05f;
			translateYBile[6] = dist;

			dist = translateYBilaRosieVarf - contorRand * sqrt(3 * pow(diametruBila * 100, 2.0) / 4) / 100;
			modelMatrix = glm::mat4(1);// x     z      y
			translateXBile[7] = (contorRand - 2.1) * (-0.05f);
			translateYBile[7] = dist;

			dist = translateYBilaRosieVarf - contorRand * sqrt(3 * pow(diametruBila * 100, 2.0) / 4) / 100;
			modelMatrix = glm::mat4(1);// x     z      y
			translateXBile[8] = contorRand * 0.05f;
			translateYBile[8] = dist;

			dist = translateYBilaRosieVarf - contorRand * sqrt(3 * pow(diametruBila * 100, 2.0) / 4) / 100;
			modelMatrix = glm::mat4(1);// x     z      y
			translateXBile[9] = contorRand * (-0.05f);
			translateYBile[9] = dist;

			contorRand += 1.05;
			//Al patrulea rand
			dist = translateYBilaRosieVarf - contorRand * sqrt(3 * pow(diametruBila * 100, 2.0) / 4) / 100;
			modelMatrix = glm::mat4(1);// x     z      y
			translateXBile[10] = 0.0f;
			translateYBile[10] = dist;

			dist = translateYBilaRosieVarf - contorRand * sqrt(3 * pow(diametruBila * 100, 2.0) / 4) / 100;
			modelMatrix = glm::mat4(1);// x     z      y
			translateXBile[11] = (contorRand - 2.1) * 0.05f;
			translateYBile[11] = dist;

			dist = translateYBilaRosieVarf - contorRand * sqrt(3 * pow(diametruBila * 100, 2.0) / 4) / 100;
			modelMatrix = glm::mat4(1);// x     z      y
			translateXBile[12] = (contorRand - 2.1) * (-0.05f);
			translateYBile[12] = dist;

			dist = translateYBilaRosieVarf - contorRand * sqrt(3 * pow(diametruBila * 100, 2.0) / 4) / 100;
			modelMatrix = glm::mat4(1);// x     z      y
			translateXBile[13] = contorRand * 0.05f;
			translateYBile[13] = dist;

			dist = translateYBilaRosieVarf - contorRand * sqrt(3 * pow(diametruBila * 100, 2.0) / 4) / 100;
			modelMatrix = glm::mat4(1);// x     z      y
			translateXBile[14] = contorRand * (-0.05f);
			translateYBile[14] = dist;

			flagInceput = 1;
		}

		if (diametruBile[i] != diametruBila)
		{
			translateXBile[i] = 2000;
			translateYBile[i] = 2000;
		}

		if (diametruBile[i] == diametruBila)
		{
			modelMatrix *= Transform3DD::Translate(translateXBile[i], translateZBilaAlba, translateYBile[i]);
			modelMatrix *= Transform3DD::Scale(diametruBile[i], diametruBile[i], diametruBile[i]);
			if (i == 0 || i == 1 || i == 5 || i == 6 | i == 7 || i == 13 || i == 14)
				RenderMesh(meshes["sphere"], shaders["Rosu"], modelMatrix);
			if (i == 2 || i == 4 || i == 8 || i == 9 || i == 10 || i == 11 || i == 12)
				RenderMesh(meshes["sphere"], shaders["Galben"], modelMatrix);
			if (i == 3)
				RenderMesh(meshes["sphere"], shaders["Negru"], modelMatrix);
		}


		for (int j = 0; j < 15; j++)
		{
			if (j != i)
			{
				int flagColiziune4 = 0;
				for (int k = 0; k < 15; k++)
				{
					if (k != j)
					{
						if (Coliziune[j][k] == 1)
						{
							flagColiziune4 = 1;
						}
					}
				}

				//Miscarea bilei j chiar daca bila i s-a oprit
				if (flagColiziune4 == 0 && vitezaLovituraAux[j] > 0 && (vitezaLovituraAux[i] * neAtenuareBile[i]) == 0 && Coliziune[i][j] == 1)
				{
					if (!window->MouseHold(GLFW_MOUSE_BUTTON_LEFT))
					{
						translateXBile[j] = translateXBile[j] - deltaTimeSeconds * vitezaLovituraAux[j] * cos(unghiBile[j] * M_PI / 180);
						translateYBile[j] = translateYBile[j] - deltaTimeSeconds * vitezaLovituraAux[j] * sin(unghiBile[j] * M_PI / 180);
					}

					//Reflexia cu manta din spate
					if (translateYBile[j] <= (-translateYMargineFata + diametruBile[j]) || flagIntoarcereBile[j] == 1)
					{
						flagAtingereFataBile[j] = 0;
						contorAtingereFataBile[j] = 0;
						flagAtingereDreaptaBile[j] = 0;
						contorAtingereDreaptaBile[j] = 0;
						flagAtingereStangaBile[j] = 0;
						contorAtingereStangaBile[j] = 0;
						contorAtingereSpateBile[j]++;
						if (contorAtingereSpateBile[j] == 1)
							unghiBile[j] = -unghiBile[j];
						flagIntoarcereBile[j] = 1;

						translateXBile[j] = translateXBile[j] - deltaTimeSeconds * vitezaLovituraAux[j] * cos(unghiBile[j] * M_PI / 180);
						translateYBile[j] = translateYBile[j] - deltaTimeSeconds * vitezaLovituraAux[j] * sin(unghiBile[j] * M_PI / 180);
					}

					//Reflexia cu manta din fata
					if (translateYBile[j] >= (translateYMargineFata - diametruBile[j]) || flagAtingereFataBile[j] == 1)
					{
						flagIntoarcereBile[j] = 0;
						contorAtingereSpateBile[j] = 0;
						flagAtingereDreaptaBile[j] = 0;
						contorAtingereDreaptaBile[j] = 0;
						flagAtingereStangaBile[j] = 0;
						contorAtingereStangaBile[j] = 0;
						contorAtingereFataBile[j]++;
						if (contorAtingereFataBile[j] == 1)
							unghiBile[j] = -unghiBile[j];
						flagAtingereFataBile[j] = 1;

						translateXBile[j] = translateXBile[j] - deltaTimeSeconds * vitezaLovituraAux[j] * cos(unghiBile[j] * M_PI / 180);
						translateYBile[j] = translateYBile[j] - deltaTimeSeconds * vitezaLovituraAux[j] * sin(unghiBile[j] * M_PI / 180);
					}

					//Reflexia cu manta din dreapta
					if (translateXBile[j] >= (translateXMargineDreapta - diametruBile[j]) || flagAtingereDreaptaBile[j] == 1)
					{
						flagIntoarcereBile[j] = 0;
						contorAtingereSpateBile[j] = 0;
						flagAtingereFataBile[j] = 0;
						contorAtingereFataBile[j] = 0;
						flagAtingereStangaBile[j] = 0;
						contorAtingereStangaBile[j] = 0;
						contorAtingereDreaptaBile[j]++;
						if (contorAtingereDreaptaBile[j] == 1)
							unghiBile[j] = 180 - unghiBile[j];
						flagAtingereDreaptaBile[j] = 1;

						translateXBile[j] = translateXBile[j] - deltaTimeSeconds * vitezaLovituraAux[j] * cos(unghiBile[j] * M_PI / 180);
						translateYBile[j] = translateYBile[j] - deltaTimeSeconds * vitezaLovituraAux[j] * sin(unghiBile[j] * M_PI / 180);
					}

					//Reflexia cu manta din stanga
					if (translateXBile[j] <= (-translateXMargineDreapta + diametruBile[j]) || flagAtingereStangaBile[j] == 1)
					{
						flagIntoarcereBile[j] = 0;
						contorAtingereSpateBile[j] = 0;
						flagAtingereFataBile[j] = 0;
						contorAtingereFataBile[j] = 0;
						flagAtingereDreaptaBile[j] = 0;
						contorAtingereDreaptaBile[j] = 0;
						contorAtingereStangaBile[j]++;
						if (contorAtingereStangaBile[j] == 1)
							unghiBile[j] = 180 - unghiBile[j];
						flagAtingereStangaBile[j] = 1;

						translateXBile[j] = translateXBile[j] - deltaTimeSeconds * vitezaLovituraAux[j] * cos(unghiBile[j] * M_PI / 180);
						translateYBile[j] = translateYBile[j] - deltaTimeSeconds * vitezaLovituraAux[j] * sin(unghiBile[j] * M_PI / 180);
					}

					//Intrarea bilei j in buzunar
					if ((pow(translateXBile[j] - translateXBuzunarDreaptaJos, 2) + pow(translateYBile[j] - translateYBuzunarDreaptaJos, 2) <= pow(diametruBila / 2 + diametruBuzunar / 2, 2)) ||
						(pow(translateXBile[j] - translateXBuzunarDreaptaJos, 2) + pow(translateYBile[j], 2) <= pow(diametruBile[j] / 2 + diametruBuzunar / 4, 2)) ||
						(pow(translateXBile[j] - translateXBuzunarDreaptaJos, 2) + pow(translateYBile[j] - (-translateYBuzunarDreaptaJos), 2) <= pow(diametruBila / 2 + diametruBuzunar / 2, 2)) ||
						(pow(translateXBile[j] - (-translateXBuzunarDreaptaJos), 2) + pow(translateYBile[j] - translateYBuzunarDreaptaJos, 2) <= pow(diametruBila / 2 + diametruBuzunar / 2, 2)) ||
						(pow(translateXBile[j] - (-translateXBuzunarDreaptaJos), 2) + pow(translateYBile[j], 2) <= pow(diametruBile[j] / 2 + diametruBuzunar / 4, 2)) ||
						(pow(translateXBile[j] - (-translateXBuzunarDreaptaJos), 2) + pow(translateYBile[j] - (-translateYBuzunarDreaptaJos), 2) <= pow(diametruBila / 2 + diametruBuzunar / 2, 2)))
					{
						diametruBile[j] = 0;
						flagAtingereBuzunarBile[j] = 1;

						for (int i = 0; i < 15; i++)
							Coliziune[i][j] = 0;

						int ultimaBilaBagata = 1;
						for (int k = 0; k < 15; k++)
						{
							if (k != j)
							{
								if (flagAtingereBuzunarBile[k] == 0)
									ultimaBilaBagata = 0;
							}
						}

						if (j == 3 && ultimaBilaBagata == 1)
							cout << "Felicitari! Ai bagat bila neagra la final si ai castigat jocul!" << endl;

						if (j == 3 && ultimaBilaBagata == 0)
							cout << "Ai pierdut! Ai bagat bila neagra inainte de a baga celelalte bile colorate!" << endl;

						translateXBile[j] = 2000;
						translateYBile[j] = 2000;
					}

					//Scaderea vitezei bilei j
					if (vitezaLovituraAux[j] != 0)
					{
						if ((vitezaLovituraAux[j] - deltaTimeSeconds) >= 0)
							vitezaLovituraAux[j] = vitezaLovituraAux[j] - deltaTimeSeconds;
						else
						{
							vitezaLovituraAux[j] = 0;

							Coliziune[i][j] = 0;

							flagAtingereBile[j] = 0;
							contorAtingereBile[j] = 0;
							flagIntoarcereBile[j] = 0;
							flagAtingereFataBile[j] = 0;
							contorAtingereSpateBile[j] = 0;
							contorAtingereFataBile[j] = 0;
							flagAtingereDreaptaBile[j] = 0;
							contorAtingereDreaptaBile[j] = 0;
							flagAtingereStangaBile[j] = 0;
							contorAtingereStangaBile[j] = 0;
						}
					}
				}

				if (diametruBile[j] == diametruBila)
				{
					if (vitezaLovituraAux[i] == 0 && vitezaLovituraAux[j] == 0 && (translateXBile[j] - translateXBile[i]) * (translateXBile[j] - translateXBile[i]) + (translateYBile[j] - translateYBile[i]) * (translateYBile[j] - translateYBile[i]) <= (diametruBile[j] * diametruBile[j]))
					{
						translateXBile[j] = translateXBile[i] + diametruBila + 0.01;
						translateYBile[j] = translateYBile[i] + diametruBila + 0.01;
					}

					//Reflexie coliziune bila i - bila j
					if (((translateXBile[j] - translateXBile[i]) * (translateXBile[j] - translateXBile[i]) + (translateYBile[j] - translateYBile[i]) * (translateYBile[j] - translateYBile[i])) <= (diametruBile[j] * diametruBile[j]) || (flagAtingereBile[j] == 1 && Coliziune[i][j] == 1))
					{
						Coliziune[i][j] = 1;

						flagIntoarcereBile[i] = 0;
						flagAtingereFataBile[i] = 0;
						flagAtingereDreaptaBile[i] = 0;
						flagAtingereStangaBile[i] = 0;

						contorAtingereSpateBile[i] = 0;
						contorAtingereFataBile[i] = 0;
						contorAtingereDreaptaBile[i] = 0;
						contorAtingereStangaBile[i] = 0;

						if ((flagIntoarcereBile[j] == 0 && flagAtingereFataBile[j] == 0 && flagAtingereDreaptaBile[j] == 0 && flagAtingereStangaBile[j] == 0))
						{
							contorAtingereBile[j]++;
							if (contorAtingereBile[j] == 1 && flagColiziuneBilaMiscare[j] == 0)
							{
								vitezaLovituraAux[j] = vitezaLovituraAux[i] * neAtenuareBile[i];

								unghiBile[j] = atan((translateYBile[j] - translateYBile[i]) / (translateXBile[j] - translateXBile[i]));
								unghiBile[j] = unghiBile[j] * 180 / M_PI;
								if ((translateXBile[j] - translateXBile[i]) > 0 && (translateYBile[j] - translateYBile[i]) < 0)
									unghiBile[j] = 180 + unghiBile[j];
								if ((translateXBile[j] - translateXBile[i]) > 0 && (translateYBile[j] - translateYBile[i]) > 0)
									unghiBile[j] = -180 + unghiBile[j];

								if (unghiBile[j] < 0)
									unghiBile[j] = 360 + unghiBile[j];

								if (unghiBile[i] < 0)
									unghiBile[i] = 360 + unghiBile[i];

								if (abs(unghiBile[i] - unghiBile[j]) > 180)
								{
									if (unghiBile[i] < unghiBile[j])
										unghiBile[i] = unghiBile[i] + 360;
									if (unghiBile[j] < unghiBile[i])
										unghiBile[j] = unghiBile[j] + 360;
								}

								neAtenuareBile[i] = abs(unghiBile[i] - unghiBile[j]) / 180;

								if (unghiBile[i] > unghiBile[j])
									unghiBile[i] = unghiBile[j] + 90;

								if (unghiBile[i] < unghiBile[j])
									unghiBile[i] = unghiBile[j] - 90;

								flagAtingereBile[j] = 1;
							}
							flagAtingereBile[j] = 1;

							if (!window->MouseHold(GLFW_MOUSE_BUTTON_LEFT))
							{
								translateXBile[j] = translateXBile[j] - deltaTimeSeconds * vitezaLovituraAux[j] * cos(unghiBile[j] * M_PI / 180);
								translateYBile[j] = translateYBile[j] - deltaTimeSeconds * vitezaLovituraAux[j] * sin(unghiBile[j] * M_PI / 180);
							}
						}

						//Reflexia cu manta din spate
						if (translateYBile[j] <= (-translateYMargineFata + diametruBile[j]) || flagIntoarcereBile[j] == 1)
						{
							flagAtingereFataBile[j] = 0;
							contorAtingereFataBile[j] = 0;
							flagAtingereDreaptaBile[j] = 0;
							contorAtingereDreaptaBile[j] = 0;
							flagAtingereStangaBile[j] = 0;
							contorAtingereStangaBile[j] = 0;
							contorAtingereSpateBile[j]++;
							if (contorAtingereSpateBile[j] == 1)
								unghiBile[j] = -unghiBile[j];
							flagIntoarcereBile[j] = 1;

							translateXBile[j] = translateXBile[j] - deltaTimeSeconds * vitezaLovituraAux[j] * cos(unghiBile[j] * M_PI / 180);
							translateYBile[j] = translateYBile[j] - deltaTimeSeconds * vitezaLovituraAux[j] * sin(unghiBile[j] * M_PI / 180);
						}

						//Reflexia cu manta din fata
						if (translateYBile[j] >= (translateYMargineFata - diametruBile[j]) || flagAtingereFataBile[j] == 1)
						{
							flagIntoarcereBile[j] = 0;
							contorAtingereSpateBile[j] = 0;
							flagAtingereDreaptaBile[j] = 0;
							contorAtingereDreaptaBile[j] = 0;
							flagAtingereStangaBile[j] = 0;
							contorAtingereStangaBile[j] = 0;
							contorAtingereFataBile[j]++;
							if (contorAtingereFataBile[j] == 1)
								unghiBile[j] = -unghiBile[j];
							flagAtingereFataBile[j] = 1;

							translateXBile[j] = translateXBile[j] - deltaTimeSeconds * vitezaLovituraAux[j] * cos(unghiBile[j] * M_PI / 180);
							translateYBile[j] = translateYBile[j] - deltaTimeSeconds * vitezaLovituraAux[j] * sin(unghiBile[j] * M_PI / 180);
						}

						//Reflexia cu manta din dreapta
						if (translateXBile[j] >= (translateXMargineDreapta - diametruBile[j]) || flagAtingereDreaptaBile[j] == 1)
						{
							flagIntoarcereBile[j] = 0;
							contorAtingereSpateBile[j] = 0;
							flagAtingereFataBile[j] = 0;
							contorAtingereFataBile[j] = 0;
							flagAtingereStangaBile[j] = 0;
							contorAtingereStangaBile[j] = 0;
							contorAtingereDreaptaBile[j]++;
							if (contorAtingereDreaptaBile[j] == 1)
								unghiBile[j] = 180 - unghiBile[j];
							flagAtingereDreaptaBile[j] = 1;

							translateXBile[j] = translateXBile[j] - deltaTimeSeconds * vitezaLovituraAux[j] * cos(unghiBile[j] * M_PI / 180);
							translateYBile[j] = translateYBile[j] - deltaTimeSeconds * vitezaLovituraAux[j] * sin(unghiBile[j] * M_PI / 180);
						}

						//Reflexia cu manta din stanga
						if (translateXBile[j] <= (-translateXMargineDreapta + diametruBile[j]) || flagAtingereStangaBile[j] == 1)
						{
							flagIntoarcereBile[j] = 0;
							contorAtingereSpateBile[j] = 0;
							flagAtingereFataBile[j] = 0;
							contorAtingereFataBile[j] = 0;
							flagAtingereDreaptaBile[j] = 0;
							contorAtingereDreaptaBile[j] = 0;
							contorAtingereStangaBile[j]++;
							if (contorAtingereStangaBile[j] == 1)
								unghiBile[j] = 180 - unghiBile[j];
							flagAtingereStangaBile[j] = 1;

							translateXBile[j] = translateXBile[j] - deltaTimeSeconds * vitezaLovituraAux[j] * cos(unghiBile[j] * M_PI / 180);
							translateYBile[j] = translateYBile[j] - deltaTimeSeconds * vitezaLovituraAux[j] * sin(unghiBile[j] * M_PI / 180);
						}

						//Intrarea bilei j in buzunar
						if ((pow(translateXBile[j] - translateXBuzunarDreaptaJos, 2) + pow(translateYBile[j] - translateYBuzunarDreaptaJos, 2) <= pow(diametruBila / 2 + diametruBuzunar / 2, 2)) ||
							(pow(translateXBile[j] - translateXBuzunarDreaptaJos, 2) + pow(translateYBile[j], 2) <= pow(diametruBile[j] / 2 + diametruBuzunar / 4, 2)) ||
							(pow(translateXBile[j] - translateXBuzunarDreaptaJos, 2) + pow(translateYBile[j] - (-translateYBuzunarDreaptaJos), 2) <= pow(diametruBila / 2 + diametruBuzunar / 2, 2)) ||
							(pow(translateXBile[j] - (-translateXBuzunarDreaptaJos), 2) + pow(translateYBile[j] - translateYBuzunarDreaptaJos, 2) <= pow(diametruBila / 2 + diametruBuzunar / 2, 2)) ||
							(pow(translateXBile[j] - (-translateXBuzunarDreaptaJos), 2) + pow(translateYBile[j], 2) <= pow(diametruBile[j] / 2 + diametruBuzunar / 4, 2)) ||
							(pow(translateXBile[j] - (-translateXBuzunarDreaptaJos), 2) + pow(translateYBile[j] - (-translateYBuzunarDreaptaJos), 2) <= pow(diametruBila / 2 + diametruBuzunar / 2, 2)))
						{
							diametruBile[j] = 0;
							flagAtingereBuzunarBile[j] = 1;

							for (int i = 0; i < 15; i++)
								Coliziune[i][j] = 0;

							int ultimaBilaBagata = 1;
							for (int k = 0; k < 15; k++)
							{
								if (k != j)
								{
									if (flagAtingereBuzunarBile[k] == 0)
										ultimaBilaBagata = 0;
								}
							}

							if (j == 3 && ultimaBilaBagata == 1)
								cout << "Felicitari! Ai bagat bila neagra la final si ai castigat jocul!"<<endl;

							if (j == 3 && ultimaBilaBagata == 0)
								cout << "Ai pierdut! Ai bagat bila neagra inainte de a baga celelalte bile colorate!" << endl;

							translateXBile[j] = 2000;
							translateYBile[j] = 2000;
						}

						//Scaderea vitezei bilei j
						if (vitezaLovituraAux[j] != 0)
						{
							if ((vitezaLovituraAux[j] - deltaTimeSeconds) >= 0)
								vitezaLovituraAux[j] = vitezaLovituraAux[j] - deltaTimeSeconds;
							else
							{
								vitezaLovituraAux[j] = 0;

								flagNuMaiIntraAici[j] = 0;

								Coliziune[i][j] = 0;

								flagAtingereBile[j] = 0;
								contorAtingereBile[j] = 0;
								flagIntoarcereBile[j] = 0;
								flagAtingereFataBile[j] = 0;
								contorAtingereSpateBile[j] = 0;
								contorAtingereFataBile[j] = 0;
								flagAtingereDreaptaBile[j] = 0;
								contorAtingereDreaptaBile[j] = 0;
								flagAtingereStangaBile[j] = 0;
								contorAtingereStangaBile[j] = 0;
							}
						}
					}
				}

			}
		}

		if (diametruBile[i] == diametruBila)
		{
			if (vitezaLovituraAux[i] == 0 && vitezaLovitura * neAtenuare == 0 && (translateXBile[i] - translateXBilaAlba) * (translateXBile[i] - translateXBilaAlba) + (translateYBile[i] - translateYBilaAlba) * (translateYBile[i] - translateYBilaAlba) <= (diametruBile[i] * diametruBile[i]))
			{
				translateXBile[i] = translateXBilaAlba + diametruBila + 0.01;
				translateYBile[i] = translateYBilaAlba + diametruBila + 0.01;
			}

			int flagColiziune = 0;
			for (int j = 0; j < 15; j++)
			{
				if (i != j)
				{
					if (Coliziune[i][j] == 1)
					{
						flagColiziune = 1;
					}
				}
			}

			//Misca bila Rosie si daca bila Alba este oprita
			if (vitezaLovituraAux[i] > 0 && (vitezaLovitura * neAtenuare) == 0 && flagColiziune == 0)
			{
				if (!window->MouseHold(GLFW_MOUSE_BUTTON_LEFT))
				{
					translateXBile[i] = translateXBile[i] - deltaTimeSeconds * vitezaLovituraAux[i] * cos(unghiBile[i] * M_PI / 180);
					translateYBile[i] = translateYBile[i] - deltaTimeSeconds * vitezaLovituraAux[i] * sin(unghiBile[i] * M_PI / 180);

					//Reflexia cu manta din spate
					if (translateYBile[i] <= (-translateYMargineFata + diametruBile[i]) || flagIntoarcereBile[i] == 1)
					{
						flagAtingereFataBile[i] = 0;
						contorAtingereFataBile[i] = 0;
						flagAtingereDreaptaBile[i] = 0;
						contorAtingereDreaptaBile[i] = 0;
						flagAtingereStangaBile[i] = 0;
						contorAtingereStangaBile[i] = 0;
						contorAtingereSpateBile[i]++;
						if (contorAtingereSpateBile[i] == 1)
							unghiBile[i] = -unghiBile[i];
						flagIntoarcereBile[i] = 1;

						translateXBile[i] = translateXBile[i] - deltaTimeSeconds * vitezaLovituraAux[i] * cos(unghiBile[i] * M_PI / 180);
						translateYBile[i] = translateYBile[i] - deltaTimeSeconds * vitezaLovituraAux[i] * sin(unghiBile[i] * M_PI / 180);
					}

					//Reflexia cu manta din fata
					if (translateYBile[i] >= (translateYMargineFata - diametruBile[i]) || flagAtingereFataBile[i] == 1)
					{
						flagIntoarcereBile[i] = 0;
						contorAtingereSpateBile[i] = 0;
						flagAtingereDreaptaBile[i] = 0;
						contorAtingereDreaptaBile[i] = 0;
						flagAtingereStangaBile[i] = 0;
						contorAtingereStangaBile[i] = 0;
						contorAtingereFataBile[i]++;
						if (contorAtingereFataBile[i] == 1)
							unghiBile[i] = -unghiBile[i];
						flagAtingereFataBile[i] = 1;

						translateXBile[i] = translateXBile[i] - deltaTimeSeconds * vitezaLovituraAux[i] * cos(unghiBile[i] * M_PI / 180);
						translateYBile[i] = translateYBile[i] - deltaTimeSeconds * vitezaLovituraAux[i] * sin(unghiBile[i] * M_PI / 180);
					}

					//Reflexia cu manta din dreapta
					if (translateXBile[i] >= (translateXMargineDreapta - diametruBile[i]) || flagAtingereDreaptaBile[i] == 1)
					{
						flagIntoarcereBile[i] = 0;
						contorAtingereSpateBile[i] = 0;
						flagAtingereFataBile[i] = 0;
						contorAtingereFataBile[i] = 0;
						flagAtingereStangaBile[i] = 0;
						contorAtingereStangaBile[i] = 0;
						contorAtingereDreaptaBile[i]++;
						if (contorAtingereDreaptaBile[i] == 1)
							unghiBile[i] = 180 - unghiBile[i];
						flagAtingereDreaptaBile[i] = 1;

						translateXBile[i] = translateXBile[i] - deltaTimeSeconds * vitezaLovituraAux[i] * cos(unghiBile[i] * M_PI / 180);
						translateYBile[i] = translateYBile[i] - deltaTimeSeconds * vitezaLovituraAux[i] * sin(unghiBile[i] * M_PI / 180);
					}

					//Reflexia cu manta din stanga
					if (translateXBile[i] <= (-translateXMargineDreapta + diametruBile[i]) || flagAtingereStangaBile[i] == 1)
					{
						flagIntoarcereBile[i] = 0;
						contorAtingereSpateBile[i] = 0;
						flagAtingereFataBile[i] = 0;
						contorAtingereFataBile[i] = 0;
						flagAtingereDreaptaBile[i] = 0;
						contorAtingereDreaptaBile[i] = 0;
						contorAtingereStangaBile[i]++;
						if (contorAtingereStangaBile[i] == 1)
							unghiBile[i] = 180 - unghiBile[i];
						flagAtingereStangaBile[i] = 1;

						translateXBile[i] = translateXBile[i] - deltaTimeSeconds * vitezaLovituraAux[i] * cos(unghiBile[i] * M_PI / 180);
						translateYBile[i] = translateYBile[i] - deltaTimeSeconds * vitezaLovituraAux[i] * sin(unghiBile[i] * M_PI / 180);
					}

					//Intrarea bilei rosii in buzunar dupa ce bila Alba a lovit bila Rosie
				//Ordine buzunare -> dreapta: jos, centru, sus + stanga: jos, centru, sus
					if ((pow(translateXBile[i] - translateXBuzunarDreaptaJos, 2) + pow(translateYBile[i] - translateYBuzunarDreaptaJos, 2) <= pow(diametruBila / 2 + diametruBuzunar / 2, 2)) ||
						(pow(translateXBile[i] - translateXBuzunarDreaptaJos, 2) + pow(translateYBile[i], 2) <= pow(diametruBile[i] / 2 + diametruBuzunar / 4, 2)) ||
						(pow(translateXBile[i] - translateXBuzunarDreaptaJos, 2) + pow(translateYBile[i] - (-translateYBuzunarDreaptaJos), 2) <= pow(diametruBila / 2 + diametruBuzunar / 2, 2)) ||
						(pow(translateXBile[i] - (-translateXBuzunarDreaptaJos), 2) + pow(translateYBile[i] - translateYBuzunarDreaptaJos, 2) <= pow(diametruBila / 2 + diametruBuzunar / 2, 2)) ||
						(pow(translateXBile[i] - (-translateXBuzunarDreaptaJos), 2) + pow(translateYBile[i], 2) <= pow(diametruBile[i] / 2 + diametruBuzunar / 4, 2)) ||
						(pow(translateXBile[i] - (-translateXBuzunarDreaptaJos), 2) + pow(translateYBile[i] - (-translateYBuzunarDreaptaJos), 2) <= pow(diametruBila / 2 + diametruBuzunar / 2, 2)))
					{
						diametruBile[i] = 0;
						flagAtingereBuzunarBile[i] = 1;

						translateXBile[i] = 2000;
						translateYBile[i] = 2000;

						for (int j = 0; j < 15; j++)
							Coliziune[i][j] = 0;

						int ultimaBilaBagata2 = 1;
						for (int k = 0; k < 15; k++)
						{
							if (k != i)
							{
								if (flagAtingereBuzunarBile[k] == 0)
									ultimaBilaBagata2 = 0;
							}
						}

						if (i == 3 && ultimaBilaBagata2 == 1)
							cout << "Felicitari! Ai bagat bila neagra la final si ai castigat jocul!" << endl;

						if (i == 3 && ultimaBilaBagata2 == 0)
							cout << "Ai pierdut! Ai bagat bila neagra inainte de a baga celelalte bile colorate!" << endl;
					}

					//Scade viteza sau seteaza flag-uri 0
					if (vitezaLovituraAux[i] != 0)
					{
						if ((vitezaLovituraAux[i] - deltaTimeSeconds) >= 0)
							vitezaLovituraAux[i] = vitezaLovituraAux[i] - deltaTimeSeconds;
						else
						{
							vitezaLovituraAux[i] = 0;

							for (int j = 0; j < 15; j++)
								Coliziune[i][j] = 0;

							flagAtingereBile[i] = 0;
							contorAtingereBile[i] = 0;
							flagIntoarcereBile[i] = 0;
							flagAtingereFataBile[i] = 0;
							contorAtingereSpateBile[i] = 0;
							contorAtingereFataBile[i] = 0;
							flagAtingereDreaptaBile[i] = 0;
							contorAtingereDreaptaBile[i] = 0;
							flagAtingereStangaBile[i] = 0;
							contorAtingereStangaBile[i] = 0;
						}
					}
				}
			}
		}

		int flagColiziune2 = 0;
		for (int j = 0; j < 15; j++)
		{
			if (i != j)
			{
				if (Coliziune[i][j] == 1)
				{
					flagColiziune2 = 1;
				}
			}
		}

		//Bila Alba loveste bila Rosie
		if (diametruBile[i] == diametruBila)
		{
			if (((translateXBile[i] - translateXBilaAlba) * (translateXBile[i] - translateXBilaAlba) + (translateYBile[i] - translateYBilaAlba) * (translateYBile[i] - translateYBilaAlba)) <= (diametruBile[i] * diametruBile[i]) || (flagAtingereBile[i] == 1 && flagColiziune2 == 0))
			{
				flagIntoarcereBila = 0;
				flagAtingereFata = 0;
				flagAtingereDreapta = 0;
				flagAtingereStanga = 0;

				contorPrimaAtingereSpate = 0;
				contorPrimaAtingereFata = 0;
				contorPrimaAtingereDreapta = 0;
				contorPrimaAtingereStanga = 0;

				if ((flagIntoarcereBile[i] == 0 && flagAtingereFataBile[i] == 0 && flagAtingereDreaptaBile[i] == 0 && flagAtingereStangaBile[i] == 0))
				{
					contorAtingereBile[i]++;
					if (contorAtingereBile[i] == 1 && flagColiziuneBilaMiscare[i] == 0)
					{
						vitezaLovituraAux[i] = vitezaLovitura * neAtenuare;

						unghiBile[i] = atan((translateYBile[i] - translateYBilaAlba) / (translateXBile[i] - translateXBilaAlba));
						unghiBile[i] = unghiBile[i] * 180 / M_PI;
						if ((translateXBile[i] - translateXBilaAlba) > 0 && (translateYBile[i] - translateYBilaAlba) < 0)
							unghiBile[i] = 180 + unghiBile[i];
						if ((translateXBile[i] - translateXBilaAlba) > 0 && (translateYBile[i] - translateYBilaAlba) > 0)
							unghiBile[i] = -180 + unghiBile[i];

						if (unghiBile[i] < 0)
							unghiBile[i] = 360 + unghiBile[i];

						if (unghiBila < 0)
							unghiBila = 360 + unghiBila;

						if (abs(unghiBila - unghiBile[i]) > 180)
						{
							if (unghiBila < unghiBile[i])
								unghiBila = unghiBila + 360;
							if (unghiBile[i] < unghiBila)
								unghiBile[i] = unghiBile[i] + 360;
						}

						neAtenuare = abs(unghiBila - unghiBile[i]) / 180;

						if (unghiBila > unghiBile[i])
							unghiBila = unghiBile[i] + 90;

						if (unghiBila < unghiBile[i])
							unghiBila = unghiBile[i] - 90;

						flagAtingereBile[i] = 1;
					}
					flagAtingereBile[i] = 1;

					if (!window->MouseHold(GLFW_MOUSE_BUTTON_LEFT))
					{
						translateXBile[i] = translateXBile[i] - deltaTimeSeconds * vitezaLovituraAux[i] * cos(unghiBile[i] * M_PI / 180);
						translateYBile[i] = translateYBile[i] - deltaTimeSeconds * vitezaLovituraAux[i] * sin(unghiBile[i] * M_PI / 180);
					}
				}

				//Reflexia cu manta din spate dupa ce bila Alba a lovit bila Rosie
				if (translateYBile[i] <= (-translateYMargineFata + diametruBile[i]) || flagIntoarcereBile[i] == 1)
				{
					flagAtingereFataBile[i] = 0;
					contorAtingereFataBile[i] = 0;
					flagAtingereDreaptaBile[i] = 0;
					contorAtingereDreaptaBile[i] = 0;
					flagAtingereStangaBile[i] = 0;
					contorAtingereStangaBile[i] = 0;
					contorAtingereSpateBile[i]++;
					if (contorAtingereSpateBile[i] == 1)
						unghiBile[i] = -unghiBile[i];
					flagIntoarcereBile[i] = 1;

					translateXBile[i] = translateXBile[i] - deltaTimeSeconds * vitezaLovituraAux[i] * cos(unghiBile[i] * M_PI / 180);
					translateYBile[i] = translateYBile[i] - deltaTimeSeconds * vitezaLovituraAux[i] * sin(unghiBile[i] * M_PI / 180);
				}

				//Reflexia cu manta din fata dupa ce bila Alba a lovit bila Rosie
				if (translateYBile[i] >= (translateYMargineFata - diametruBile[i]) || flagAtingereFataBile[i] == 1)
				{
					flagIntoarcereBile[i] = 0;
					contorAtingereSpateBile[i] = 0;
					flagAtingereDreaptaBile[i] = 0;
					contorAtingereDreaptaBile[i] = 0;
					flagAtingereStangaBile[i] = 0;
					contorAtingereStangaBile[i] = 0;
					contorAtingereFataBile[i]++;
					if (contorAtingereFataBile[i] == 1)
						unghiBile[i] = -unghiBile[i];
					flagAtingereFataBile[i] = 1;

					translateXBile[i] = translateXBile[i] - deltaTimeSeconds * vitezaLovituraAux[i] * cos(unghiBile[i] * M_PI / 180);
					translateYBile[i] = translateYBile[i] - deltaTimeSeconds * vitezaLovituraAux[i] * sin(unghiBile[i] * M_PI / 180);
				}

				//Reflexia cu manta din dreapta dupa ce bila Alba a lovit bila Rosie
				if (translateXBile[i] >= (translateXMargineDreapta - diametruBile[i]) || flagAtingereDreaptaBile[i] == 1)
				{
					flagIntoarcereBile[i] = 0;
					contorAtingereSpateBile[i] = 0;
					flagAtingereFataBile[i] = 0;
					contorAtingereFataBile[i] = 0;
					flagAtingereStangaBile[i] = 0;
					contorAtingereStangaBile[i] = 0;
					contorAtingereDreaptaBile[i]++;
					if (contorAtingereDreaptaBile[i] == 1)
						unghiBile[i] = 180 - unghiBile[i];
					flagAtingereDreaptaBile[i] = 1;

					translateXBile[i] = translateXBile[i] - deltaTimeSeconds * vitezaLovituraAux[i] * cos(unghiBile[i] * M_PI / 180);
					translateYBile[i] = translateYBile[i] - deltaTimeSeconds * vitezaLovituraAux[i] * sin(unghiBile[i] * M_PI / 180);
				}

				//Reflexia cu manta din stanga dupa ce bila Alba a lovit bila Rosie
				if (translateXBile[i] <= (-translateXMargineDreapta + diametruBile[i]) || flagAtingereStangaBile[i] == 1)
				{
					flagIntoarcereBile[i] = 0;
					contorAtingereSpateBile[i] = 0;
					flagAtingereFataBile[i] = 0;
					contorAtingereFataBile[i] = 0;
					flagAtingereDreaptaBile[i] = 0;
					contorAtingereDreaptaBile[i] = 0;
					contorAtingereStangaBile[i]++;
					if (contorAtingereStangaBile[i] == 1)
						unghiBile[i] = 180 - unghiBile[i];
					flagAtingereStangaBile[i] = 1;

					translateXBile[i] = translateXBile[i] - deltaTimeSeconds * vitezaLovituraAux[i] * cos(unghiBile[i] * M_PI / 180);
					translateYBile[i] = translateYBile[i] - deltaTimeSeconds * vitezaLovituraAux[i] * sin(unghiBile[i] * M_PI / 180);
				}

				//Intrarea bilei rosii in buzunar dupa ce bila Alba a lovit bila Rosie
				//Ordine buzunare -> dreapta: jos, centru, sus + stanga: jos, centru, sus
				if ((pow(translateXBile[i] - translateXBuzunarDreaptaJos, 2) + pow(translateYBile[i] - translateYBuzunarDreaptaJos, 2) <= pow(diametruBila / 2 + diametruBuzunar / 2, 2)) ||
					(pow(translateXBile[i] - translateXBuzunarDreaptaJos, 2) + pow(translateYBile[i], 2) <= pow(diametruBile[i] / 2 + diametruBuzunar / 4, 2)) ||
					(pow(translateXBile[i] - translateXBuzunarDreaptaJos, 2) + pow(translateYBile[i] - (-translateYBuzunarDreaptaJos), 2) <= pow(diametruBila / 2 + diametruBuzunar / 2, 2)) ||
					(pow(translateXBile[i] - (-translateXBuzunarDreaptaJos), 2) + pow(translateYBile[i] - translateYBuzunarDreaptaJos, 2) <= pow(diametruBila / 2 + diametruBuzunar / 2, 2)) ||
					(pow(translateXBile[i] - (-translateXBuzunarDreaptaJos), 2) + pow(translateYBile[i], 2) <= pow(diametruBile[i] / 2 + diametruBuzunar / 4, 2)) ||
					(pow(translateXBile[i] - (-translateXBuzunarDreaptaJos), 2) + pow(translateYBile[i] - (-translateYBuzunarDreaptaJos), 2) <= pow(diametruBila / 2 + diametruBuzunar / 2, 2)))
				{
					diametruBile[i] = 0;
					flagAtingereBuzunarBile[i] = 1;

					translateXBile[i] = 2000;
					translateYBile[i] = 2000;

					for (int j = 0; j < 15; j++)
						Coliziune[i][j] = 0;

					int ultimaBilaBagata2 = 1;
					for (int k = 0; k < 15; k++)
					{
						if (k != i)
						{
							if (flagAtingereBuzunarBile[k] == 0)
								ultimaBilaBagata2 = 0;
						}
					}

					if (i == 3 && ultimaBilaBagata2 == 1)
						cout << "Felicitari! Ai bagat bila neagra la final si ai castigat jocul!" << endl;

					if (i == 3 && ultimaBilaBagata2 == 0)
						cout << "Ai pierdut! Ai bagat bila neagra inainte de a baga celelalte bile colorate!" << endl;
				}

				//Scade viteza bilei dupa ce bila Alba loveste bila Rosie si setarea flag-uri 0
				if (vitezaLovituraAux[i] != 0)
				{
					if ((vitezaLovituraAux[i] - deltaTimeSeconds) >= 0)
						vitezaLovituraAux[i] = vitezaLovituraAux[i] - deltaTimeSeconds;
					else
					{
						vitezaLovituraAux[i] = 0;

						for (int j = 0; j < 15; j++)
							Coliziune[i][j] = 0;

						flagAtingereBile[i] = 0;
						contorAtingereBile[i] = 0;
						flagIntoarcereBile[i] = 0;
						flagAtingereFataBile[i] = 0;
						contorAtingereSpateBile[i] = 0;
						contorAtingereFataBile[i] = 0;
						flagAtingereDreaptaBile[i] = 0;
						contorAtingereDreaptaBile[i] = 0;
						flagAtingereStangaBile[i] = 0;
						contorAtingereStangaBile[i] = 0;
					}
				}
			}
		}
	}
}

void Tema2::FrameEnd()
{
	DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Tema2::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	//Mareste viteza bilei Albe atat timp cat tii apasat pe mouse stanga
	if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT))
	{
		vitezaLovitura = vitezaLovitura + 2 * deltaTime; // 2 - Se mareste vitezaLovitura de 2 ori
		neAtenuare = 1;
		for (int i = 0; i < 15; i++)
		{
			flagNuMaiIntraAici[i] = 0;
			neAtenuareBile[i] = 1;

			for (int j = 0; j < 15; j++)
			{
				Coliziune[i][j] = 0;
			}
		}
	}

	// move the camera only if MOUSE_RIGHT button is pressed
	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float cameraSpeed = 2.0f;

		if (renderCameraTarget == false)
		{
			if (window->KeyHold(GLFW_KEY_W)) {
				// TODO : translate the camera forward
				camera->TranslateForward(deltaTime);
			}

			if (window->KeyHold(GLFW_KEY_A)) {
				// TODO : translate the camera to the left
				camera->TranslateRight(-deltaTime);
			}

			if (window->KeyHold(GLFW_KEY_S)) {
				// TODO : translate the camera backwards
				camera->TranslateForward(-deltaTime);
			}

			if (window->KeyHold(GLFW_KEY_D)) {
				// TODO : translate the camera to the right
				camera->TranslateRight(deltaTime);
			}
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			// TODO : translate the camera down
			camera->TranslateUpword(-deltaTime);

		}

		if (window->KeyHold(GLFW_KEY_E)) {
			// TODO : translate the camera up
			camera->TranslateUpword(deltaTime);
		}
	}

	//Miscarea bilei Albe pe masa cu tastele WASD
	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		if (window->KeyHold(GLFW_KEY_W)) {
			if (flagAlbAtingereBuzunar == 0 && ((translateYBilaAlba - 0.3*deltaTime) > ((translateYMargineFata - diametruBila) / 3 + diametruBila)))
				translateYBilaAlba = translateYBilaAlba - 0.3*deltaTime;

			if (flagAlbAtingereBuzunar == 1 && ((translateYBilaAlba - 0.3*deltaTime) > (-translateYMargineFata + diametruBila)))
				translateYBilaAlba = translateYBilaAlba - 0.3*deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			if ((translateXBilaAlba - 0.3*deltaTime) > (-translateXMargineDreapta + diametruBila))
				translateXBilaAlba = translateXBilaAlba - 0.3*deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			if ((translateYBilaAlba + 0.3*deltaTime) < (translateYMargineFata - diametruBila))
				translateYBilaAlba = translateYBilaAlba + 0.3*deltaTime;
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			if ((translateXBilaAlba + 0.3*deltaTime) < (translateXMargineDreapta - diametruBila))
				translateXBilaAlba = translateXBilaAlba + 0.3*deltaTime;
		}

	}
}

void Tema2::OnKeyPress(int key, int mods)
{
	// add key press event
	//Camera third person la apasarea tastei space
	if (key == GLFW_KEY_SPACE)
	{
		renderCameraTarget = true;
		camera->Set(glm::vec3(translateXBilaAlba, 0.75f, translateYBilaAlba + distanceToTarget), glm::vec3(translateXBilaAlba, 0.75f, translateYBilaAlba), glm::vec3(0, 1, 0));
		flagCameraSus = 0;
	}
}

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
	//Rotirea camerei third-person cu target-ul bila alba
	if (renderCameraTarget == true)
	{
		if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
		{
			float sensivityOX = 0.001f;
			float sensivityOY = 0.001f;
			float angleXAnterior = 0;

			camera->RotateThirdPerson_OY(-sensivityOX * deltaX);

			directieXLansare = camera->Directie().x;
			directieYLansare = camera->Directie().z;
		}
	}
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
	//Vedere top-down dupa plecarea bilei Albe
	if (renderCameraTarget == true)
	{
		if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT))
		{
			camera->Set(glm::vec3(0, 3.5f, 0.01f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
			renderCameraTarget = false;
			flagCameraSus = 1;
		}
	}
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}
