#include <iostream>
#include <GL\glew.h>
#include <ctime>
#include <chrono>
#include "display.h"
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "transform.h"
#include "camera.h"
#include "inputManager.h"

#undef main
#define WIDTH 800
#define HEIGHT 600


int main()
{
	//Creates the display
	Display display(WIDTH, HEIGHT, "GPCoursework-Steven Smith");
	
	//Creates the meshes
	Mesh mesh("..//res//spaceshipTest.obj");
	Mesh mesh2("..//res//planet.obj");
	Mesh mesh3("..//res//moon.obj");
	//Creates the shader programs
	Shader shader("..//res//basicShader");
	Shader shader2("..//res//basicShader");
	Shader shader3("..//res//basicShader");

	//Creates the textures
	Texture texture("..//res//spaceship.png");
	Texture texture2("..//res//planet.png");
	Texture texture3("..//res//moon.png");
	//Creates the camera
	Transform cameraTransform = glm::vec3(0, -20, 0);
	Camera camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
	//Creates the transforms for the objects
	Transform transform = glm::vec3(0, 0, 0);
	Transform transform2;
	Transform transform3;
	//Create Input Manager
	InputManager* mInputMgr;
	mInputMgr = InputManager::Instance();
	float rotAngleStart = 0.0f;
	float rotAngleNew = 0.0f;

	//Used to manipulate the transforms 
	float counter = 0.0f;
	float deltaTime = 0.0f;
	long last = 0;

	while (!display.IsClosed())
	{
		mInputMgr->Update();
		long now = SDL_GetTicks();
		deltaTime = ((float)now - last) / 20;
		last = now;

		if (mInputMgr->KeyDown(SDL_SCANCODE_W))
		{
			glm::vec3 vel;
			vel.x = (float)glm::sin(glm::radians(rotAngleNew * 100));
			vel.z = (float)glm::cos(glm::radians(rotAngleNew * 100));
			cameraTransform.GetPos() += vel * deltaTime;
		}
		if (mInputMgr->KeyDown(SDL_SCANCODE_S))
		{
			glm::vec3 vel;
			vel.x = (float)glm::sin(glm::radians(rotAngleNew * 100));
			vel.z = (float)glm::cos(glm::radians(rotAngleNew * 100));
			cameraTransform.GetPos() -= vel * deltaTime;
		}
		if (mInputMgr->KeyDown(SDL_SCANCODE_A))
		{
			cameraTransform.GetPos().x += 0.5f * deltaTime;
		}
		if (mInputMgr->KeyDown(SDL_SCANCODE_D))
		{
			cameraTransform.GetPos().x -= 0.5f;
		}
		if (mInputMgr->KeyDown(SDL_SCANCODE_Q))
		{
			transform.GetRot().y += 0.01f;
			camera.cameraUpdate(glm::vec2(0.01f, 0));
			rotAngleNew += 0.01f;
		}
		if (mInputMgr->KeyDown(SDL_SCANCODE_E))
		{
			transform.GetRot().y -= 0.01f;
			camera.cameraUpdate(glm::vec2(-0.01f, 0));
			rotAngleNew -= 0.01f;
		}
		//Clears display
		display.Clear(1.0f, 1.0f, 1.0f, 1.0f);

		Camera camera(cameraTransform.GetPos(), camera.GetCameraRot(), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);

		//Saves the counter in different ways to give different effects
		float sinCounter = sinf(counter);
		float cosCounter = cosf(counter);

		//Set transform of first object
		transform.SetScale(glm::vec3(0.5, 0.5, 0.5));
		transform.GetPos() = cameraTransform.GetPos();
		transform.GetPos().y -= 10.0f;

		//Set transform of second object
		transform2.GetPos() = (glm::vec3(-25, -10, 150));
		transform2.SetScale(glm::vec3(0.5, 0.5, 0.5));
		transform2.GetRot().y = counter * 0.03;

		//Set transform of third object
		transform3.GetPos() = (glm::vec3(35, 0, 180));
		transform3.SetScale(glm::vec3(0.2, 0.2, 0.2));
		transform3.GetPos().y = (cosCounter + 30);

		//Render the first object
		shader.BindShader();
		shader.Update(transform, camera);
		texture.BindTexture(0);
		mesh.DrawMesh();

		//Render the second object
		shader2.BindShader();
		shader2.Update(transform2, camera);
		texture2.BindTexture(0);
		mesh2.DrawMesh();

		//Render the third object
		shader3.BindShader();
		shader3.Update(transform3, camera);
		texture3.BindTexture(0);
		mesh3.DrawMesh();

		//Swap the display buffers and increase the counter every frame
		display.SwapBuffers();
		counter += 0.01f;
	}

	//Used as main must return an int value
	return 0;
}