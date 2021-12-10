#include "Component.h"

Component::Component()
{
	m_owner = nullptr;
	m_name = "\0";
}

Component::Component(Actor* owner, const char* name)
{
	m_owner = owner;
	m_name = name;
}

Component::~Component()
{

}
