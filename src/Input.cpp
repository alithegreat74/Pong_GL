#include "Input.h"


InputManager InputManager::instance;
std::unordered_map<std::string, std::vector<InputCallback>> InputManager::listerners = std::unordered_map<std::string, std::vector<InputCallback>>();

void InputManager::AddListerners(std::string eventName, InputCallback callback)
{
	auto& inputEvent = listerners.find(eventName);
	//If there is an list of callbacks for this event, just add it to the list
	if (inputEvent != listerners.end()) {
		inputEvent->second.push_back(callback);
	}
	else
	{
		std::vector<InputCallback> newSet;
		newSet.push_back(callback);
		listerners.insert({eventName,newSet});
	}
}

void InputManager::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	auto& inputEvent = listerners.find("Keyboard Event");

	if (inputEvent != listerners.end()) {
		for (auto& callback : inputEvent->second) {
			callback(key,action);
		}
	}
}
