#pragma once
#include "Actor.h"

class Component
{
public:
	Component();
	Component(Actor* owner, const char* name);
	~Component();

	const char* getName() { return m_name; }
	Actor* getOwner() { return m_owner; }
	virtual void start();
	virtual void update(float deltaTime);
	virtual void draw();
	virtual void end();
	virtual void OnCollision(Actor* actor);

private:
	Actor* m_owner;
	const char* m_name;
};

