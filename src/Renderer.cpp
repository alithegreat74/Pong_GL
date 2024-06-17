#include "Renderer.h"

bool Effects::shake = false;
float Effects::shakeTime = 0;

Time Time::instance;

void Effects::StartShake()
{
	//Set the shake components
	shake = true;
	shakeTime = UI::shakeTime;
}

//right now we only have the screen shake effect
void Effects::RenderEffects()
{
	//if the shake time is over stop the shake
	if (shakeTime <= 0) {
		shake = false;
		return;
	}
	//decrement shake time as it gets further
	shakeTime -= Time::Get().DeltaTime()*10;
}
