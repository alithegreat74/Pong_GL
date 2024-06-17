#include "Input.h"

//Static variables
InputManager InputManager::instance;
std::unordered_map<int, std::vector<InputCallback>> InputManager::listerners = std::unordered_map<int, std::vector<InputCallback>>();

void InputManager::AddListerners(int key, InputCallback callback)
{
	auto& inputEvent = listerners.find(key);
	//If there is an list of callbacks for this event, just add it to the list
	if (inputEvent != listerners.end()) {
		inputEvent->second.push_back(callback);
	}
	else
	{
		std::vector<InputCallback> newSet;
		newSet.push_back(callback);
		listerners.insert({key,newSet});
	}
}
//This is the callback function that glfw runs when a keyboard state change has occured
void InputManager::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//Searches for the pressed key's functions and runs those functoins
	auto& inputEvent = listerners.find(key);
	if (inputEvent != listerners.end()) {
		for (auto& callback : inputEvent->second) {
			callback(action);
		}
	}
}


/// <summary>
/// This part manages the game state
/// for now we only have paused and not paused
/// </summary>

bool GameManager::pause = false;

void GameManager::OnPause(int action)
{
	if (action == GLFW_PRESS) {
		pause = !pause;
	}
}
