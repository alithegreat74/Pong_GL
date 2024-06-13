#pragma once
#include "Renderer.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <functional>

/// <summary>
/// We're gonna use a singlton for our input handler so there's only one instance of it and we can access it from all over the game
/// We're also gonna use observer pattern. it is so each input listener is an observer and the input manager is the subject
/// </summary>

using InputCallback = std::function<void(int, int)>;
class InputManager {
public:
	static InputManager& Get() {
		if (&instance == nullptr)
			instance = InputManager();
		return instance;
	}
	InputManager(const InputManager&) = delete;
	void AddListerners(std::string eventName, InputCallback callback);

	static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
	static std::unordered_map<std::string, std::vector<InputCallback>> listerners;
	static InputManager instance;
	InputManager() = default;
};

class InputListerner {
public:
	virtual void Callback(int key, int action) {}
	virtual void Listen(){}
};