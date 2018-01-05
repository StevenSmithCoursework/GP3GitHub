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
#include "sound.h"
#include "soundManager.h"
#include "light.h"
#include "font.h"
#include "fontManager.h"
#include "text.h"
#undef main
#define WIDTH 800
#define HEIGHT 600


int main()
{
	//Creates the display
	Display display(WIDTH, HEIGHT, "GPCoursework-Steven Smith");
	
	//Sound Manager
	static soundManager* theSoundManager = soundManager::getInstance();

	//Create Input Manager
	InputManager* mInputMgr = InputManager::Instance();

	//Create Font Manager
	static fontManager* theFontManager = fontManager::getInstance();

	//Create Text(Not working)
	text text(Display::renderer, "..//res//digital-7.ttf", 72, "Score: ", { 255, 0, 0, 255 });
	
	//Creates the meshes
	Mesh mesh("..//res//spaceshipTest.obj");
	Mesh mesh2("..//res//planet.obj");
	Mesh mesh3("..//res//moon.obj");
	Mesh mesh4("..//res//crate.obj");
	Mesh mesh5("..//res//crate.obj");
	Mesh mesh6("..//res//crate.obj");
	Mesh mesh7("..//res//crate.obj");
	Mesh mesh8("..//res//crate.obj");
	//Creates the shader programs
	Shader shader("..//res//basicShader");
	Shader shader2("..//res//basicShader");
	Shader shader3("..//res//basicShader");
	Shader shader4("..//res//basicShader");
	Shader shader5("..//res//basicShader");
	Shader shader6("..//res//basicShader");
	Shader shader7("..//res//basicShader");
	Shader shader8("..//res//basicShader");

	//Creates the textures
	Texture texture("..//res//spaceship.png");
	Texture texture2("..//res//planet.png");
	Texture texture3("..//res//moon.png");
	Texture texture4("..//res//crate.png");
	//Creates the camera
	Transform cameraTransform = glm::vec3(0, -20, 0);
	Camera camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
	//Creates the transforms for the objects
	Transform transform;
	Transform transform2;
	Transform transform3;
	Transform transform4;
	Transform transform5;
	Transform transform6;
	Transform transform7;
	Transform transform8;
	//Create and load fonts
	LPCSTR gameFonts[1] = { "..//res//digital-7.ttf" };
	theFontManager->addFont("SevenSeg", gameFonts[0], 72);
	//Create and load sounds
	LPCSTR gameSounds[3] = { "..//res//ShipEngine.wav", "..//res//GameTheme.wav", "..//res//ItemCollect.wav" };
	theSoundManager->add("Engine", gameSounds[0]);
	theSoundManager->add("Theme", gameSounds[1]);
	theSoundManager->add("Collect", gameSounds[2]);
	
	//Helpers with rotation
	float rotAngleStart = 0.0f;
	float rotAngleNew = 0.0f;

	//Used to manipulate the transforms 
	float counter = 0.0f;
	float deltaTime = 0.0f;
	long last = 0;
	int score = 0;
	//bools for different checks
	bool sound = true;
	bool thirdPerson = true;
	bool muted = false;
	//Cameras position saved
	glm::vec3 camPosition = glm::vec3(0, 0, 0);
	glm::vec3 camRotation = glm::vec3(0, 0, 0);
	glm::vec3 camRotationSave = camera.GetCameraRot();

	//Set crate positions and scale 
	transform4.GetPos() = (glm::vec3(60, -35, 40));
	transform4.SetScale(glm::vec3(0.2, 0.2, 0.2));
	
	transform5.GetPos() = (glm::vec3(40, -35, 90));
	transform5.SetScale(glm::vec3(0.2, 0.2, 0.2));
	
	transform6.GetPos() = (glm::vec3(50, -35, 200));
	transform6.SetScale(glm::vec3(0.2, 0.2, 0.2));
	
	transform7.GetPos() = (glm::vec3(80, -35, 250));
	transform7.SetScale(glm::vec3(0.2, 0.2, 0.2));
	
	transform8.GetPos() = (glm::vec3(15, -35, 300));
	transform8.SetScale(glm::vec3(0.2, 0.2, 0.2));

	//Set light
	light sunLight(GL_LIGHT0, lightColour4(0, 0, 0, 1), lightColour4(1, 1, 1, 1), lightColour4(1, 1, 1, 1), glm::vec4(0, 0, 20, 1),
		glm::vec3(0.0, 0.0, 1.0), 0.0f, 180.0f, 1.0f, 0.0f, 0.0f);
	GLfloat g_Ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, g_Ambient);
	//Show controls
	cout << "Use WASD to move, Q/E to rotate (buggy) and T to change cameras" << endl;
	//Show score
	cout << "Current Score: " << score << endl;

	while (!display.IsClosed())
	{
		//Clears display
		display.Clear(1.0f, 1.0f, 1.0f, 1.0f);
		//Updates inputs
		mInputMgr->Update();
		//Initialises lighting
		sunLight.lightOn();
		//Statrs timer
		long now = SDL_GetTicks();
		deltaTime = ((float)now - last) / 20;
		last = now;
		//Plays start sounds once
		if (sound == true)
		{
			theSoundManager->getSnd("Engine")->playAudio(AL_TRUE);
			theSoundManager->getSnd("Theme")->playAudio(AL_TRUE);
			sound = false;
		}
		//Checks if the user has pressed WASD and moves player accordingly
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
			cameraTransform.GetPos().x -= 0.5f * deltaTime;
		}
		//Rotates the player when pressing Q/E (buggy)
		if (mInputMgr->KeyDown(SDL_SCANCODE_Q))
		{
			transform.GetRot().y += 0.01f * deltaTime;
			camera.cameraUpdate(glm::vec2(0.01f * deltaTime, 0));
			rotAngleNew += 0.01f * deltaTime;
		}
		if (mInputMgr->KeyDown(SDL_SCANCODE_E))
		{
			transform.GetRot().y -= 0.01f * deltaTime;
			camera.cameraUpdate(glm::vec2(-0.01f * deltaTime, 0));
			rotAngleNew -= 0.01f * deltaTime;
		}
		//Sets the camera check to change to third person/static
		if (mInputMgr->KeyDown(SDL_SCANCODE_T))
		{
			thirdPerson = !thirdPerson;
		}
		//Mutes any sounds played (does not toggle on/off)
		if (mInputMgr->KeyDown(SDL_SCANCODE_M))
		{
				theSoundManager->release();
				muted = true;
		}
		//Picks what camera to display
		if (thirdPerson == true)
		{
			camPosition = cameraTransform.GetPos();
			camRotation = camera.GetCameraRot();
		}
		if (thirdPerson == false)
		{
			camPosition = glm::vec3(0, 0, 0);
			camRotation = camRotationSave;
		}
		//Displays camera
		Camera camera(camPosition, camRotation, 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
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

		//Render crates
		shader4.BindShader();
		shader4.Update(transform4, camera);
		texture4.BindTexture(0);
		mesh4.DrawMesh();

		shader5.BindShader();
		shader5.Update(transform5, camera);
		texture4.BindTexture(0);
		mesh5.DrawMesh();

		shader6.BindShader();
		shader6.Update(transform6, camera);
		texture4.BindTexture(0);
		mesh6.DrawMesh();

		shader7.BindShader();
		shader7.Update(transform7, camera);
		texture4.BindTexture(0);
		mesh7.DrawMesh();

		shader8.BindShader();
		shader8.Update(transform8, camera);
		texture4.BindTexture(0);
		mesh8.DrawMesh();
		//Collision detection, if triggered adds score and plays a noise
		if (mesh.SphereCollision(transform.GetPos(), 10.0f, transform4.GetPos(), 20.0f) == true)
		{
			transform4.SetPos(glm::vec3(0, -1000, 0));
			if (muted == false)
			{
				theSoundManager->getSnd("Collect")->playAudio(AL_TRUE);
			}
			score++;
			cout << "Current Score: " << score << endl;
		}
		if (mesh.SphereCollision(transform.GetPos(), 10.0f, transform5.GetPos(), 20.0f) == true)
		{
			transform5.SetPos(glm::vec3(0, -1000, 0));
			if (muted == false)
			{
				theSoundManager->getSnd("Collect")->playAudio(AL_TRUE);
			}
			score++;
			cout << "Current Score: " << score << endl;
		}
		if (mesh.SphereCollision(transform.GetPos(), 10.0f, transform6.GetPos(), 20.0f) == true)
		{
			transform6.SetPos(glm::vec3(0, -1000, 0));
			if (muted == false)
			{
				theSoundManager->getSnd("Collect")->playAudio(AL_TRUE);
			}
			score++;
			cout << "Current Score: " << score << endl;
		}
		if (mesh.SphereCollision(transform.GetPos(), 10.0f, transform7.GetPos(), 20.0f) == true)
		{
			transform7.SetPos(glm::vec3(0, -1000, 0));
			if (muted == false)
			{
				theSoundManager->getSnd("Collect")->playAudio(AL_TRUE);
			}
			score++;
			cout << "Current Score: " << score << endl;
		}
		if (mesh.SphereCollision(transform.GetPos(), 10.0f, transform8.GetPos(), 20.0f) == true)
		{
			transform8.SetPos(glm::vec3(0, -1000, 0));
			if (muted == false)
			{
				theSoundManager->getSnd("Collect")->playAudio(AL_TRUE);
			}
			score++;
			cout << "Current Score: " << score << endl;
		}
		//If win conditions are met, print "You Win!"
		if (score == 5)
		{
			cout << "You Win!" << endl;
			score = 0;
		}
		//Display text (Not working)
		theFontManager->getFont("SevenSeg")->printText("Score: ", FTPoint(10, 10, 0));
		text.display(20, 20, Display::renderer);

		//Swap the display buffers and increase the counter every frame
		display.SwapBuffers();
		counter += 0.01f;
	}

	//Used as main must return an int value
	return 0;
}