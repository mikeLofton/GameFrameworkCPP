#pragma once
#include "Component.h"
class Texture2D;

class Sprite :
	public Component
{
public:
	/// <param name="texture">Sets the sprites image to be this texture</param>
	/// <param name="name">The name of the component instance</param>
	Sprite(Texture2D* texture, const char* name = "SpriteComponent");

	/// <param name="path">The path of the texture to load</param>
	/// <param name="name"></param>
	Sprite(const char* path, const char* name = "SpriteComponent");

	~Sprite() override;

	int getHeight() { return m_height; }
	int getWidth() { return m_width; }

	void draw() override;

private:
	Texture2D* m_texture;
	int m_width;
	int m_height;
};

