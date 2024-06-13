#pragma once
#include "References.h"
#include <iostream>
#include <stb_image/stb_image.h>

//The Data you need to read a Texture file
struct TextureInfo
{
	int width, height, nChannels;
	unsigned char* data;
};

class TextureLoader {
public:
	//Reads the texture image and loads it's data
	static TextureInfo LoadImage(const char* filePath);
	//Frees the data once we are done adding the shader to opengl
	static void UnloadImage(unsigned char* data);
};

class Texture2D:RendererObject {
public:
	//Configurs the texture data in openngl and unloads it's data
	Texture2D(TextureInfo info);
	~Texture2D();
	//Set it as the current texture
	void Bind()const;
	//Unset it as the current texture
	void Unbind()const;
	unsigned int GetIndex() const { return object_id; }
};