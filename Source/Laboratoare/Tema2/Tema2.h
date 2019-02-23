#pragma once
#include <Component/SimpleScene.h>
#include "LabCamera.h"

class Tema2 : public SimpleScene
{
public:
	Tema2();
	~Tema2();

	void Init() override;

private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix) override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;

protected:
	Laborator::Camera *camera;
	glm::mat4 projectionMatrix;
	bool renderCameraTarget;
	int fov = 60;
	int ortho = 10;
	glm::mat4 modelMatrix;
	float translateX, translateY, translateZ;
	float scaleX, scaleY, scaleZ;
	float angularStepOX, angularStepOY, angularStepOZ;
	GLenum polygonMode;
};
