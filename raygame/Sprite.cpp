#include "Sprite.h"
#include <raylib.h>
#include "Transform2D.h"
#include "Actor.h"
#include <Matrix3.h>

Sprite::Sprite(Texture2D* texture, const char* name) : Component::Component(name)
{
	m_texture = texture;
}

Sprite::Sprite(const char* path, const char* name) : Component::Component(name)
{
	m_texture = new Texture2D(RAYLIB_H::LoadTexture(path));
}

Sprite::~Sprite() 
{
	RAYLIB_H::UnloadTexture(*m_texture);
	delete m_texture;
}

void Sprite::draw()
{
	m_width = getOwner()->getTransform()->getScale().x;
	m_height = getOwner()->getTransform()->getScale().y;

	MathLibrary::Vector2 up = { getOwner()->getTransform()->getGlobalMatrix()->m01,
	getOwner()->getTransform()->getLocalMatrix()->m11 };
	MathLibrary::Vector2 forward = getOwner()->getTransform()->getForward();
	MathLibrary::Vector2 position = getOwner()->getTransform()->getWorldPosition();

	position = position - (forward * getWidth() / 2);
	position = position - (up * getHeight() / 2);

	RAYLIB_H::Vector2 rayPos = { position.x, position.y };
}
