#pragma once

#include <iostream>
#include <memory>

//#include "vld.h"
#include "glm\glm.hpp"

#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "Configuration\Configuration.h"
#include "SceneECS\SceneECS.h"

#include "SceneECS\SceneComponentMaker\SceneComponentMaker.h"
#include "SceneECS\SceneResourceManager\SceneResourceManager.h"

#include "TypesList\ComponentTypes.h"
#include "TypesList\EntityState.h"
#include "TypesList\EventTypes.h"
#include "TypesList\InputTypes.h"
#include "TypesList\ResourceTypes.h"


//	
int main(int argc, char** argv);


// Initialize GLEW.
int initializeGLEW();

//	Initialize GLFW.
int initializeGLFW();

//	Initialize the ECS.
void initializeECS();

//	Render the Cycle.
void enterRenderCycle();

//	Terminate the ECS.
void terminateECS();

//	Callbacks.
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursor_enter_callback(GLFWwindow* window, int entered);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
double xpos, ypos;

//	Pointer to the ECS.
std::shared_ptr<SceneECS> ecs;
std::shared_ptr<SceneComponentMaker> sceneComponentMaker;
std::shared_ptr<SceneResourceManager> sceneResourceManager;

//	Current Frame Time.
float deltaFrameTime, currentFrameTime, lastFrameTime;

// Default initialization for monitor
GLFWmonitor * monitor;
const GLFWvidmode * mode;
GLFWwindow	* window;
