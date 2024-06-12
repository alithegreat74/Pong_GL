#pragma once
#include "stb_image.h"
#include "References.h"
#include <iostream>

struct TextureInfo
{
	int width, height, nChannels;
	unsigned char* data;
};

class TextureLoader {
public:
	static TextureInfo LoadImage(const char* filePath);
	static void UnloadImage(unsigned char* data);
};

class Texture2D:RendererObject {
public:
	Texture2D(TextureInfo info);
	~Texture2D();

	void Bind()const;
	void Unbind()const;
	unsigned int GetIndex() const { return object_id; }
};