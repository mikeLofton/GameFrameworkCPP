#include "Actor.h"
#include "Transform2D.h"
#include <string.h>
#include "Collider.h"
#include "Component.h"

Actor::Actor()
{
    m_transform = new Transform2D(this);
}

Actor::~Actor()
{
    delete m_transform;
}


Actor::Actor(float x, float y, const char* name = "Actor")
{
    //Initialze default values
    m_transform = new Transform2D(this);
    m_transform->setLocalPosition({ x,y });
    m_name = name;
}

void Actor::start()
{
    m_started = true;
}

void Actor::onCollision(Actor* other)
{
    for (int i = 0; i < m_componentCount; i++)
        m_components[i]->onCollision(other);
}

Component* Actor::addComponent(Component* component)
{
    //Return null if this component has an owner already
    Actor* owner = component->getOwner();
    if (owner)
        return nullptr;

    component->assignOwner(this);

    //Create a new array thats one size larger than the original
    Component** tempArray = new Component * [m_componentCount + 1];

    //Copy all values from the original array into the temp array
    for (int i = 0; i < m_componentCount; i++)
    {
        tempArray[i] = m_components[i];
    }

    //Add the new component to the end of the array
    tempArray[m_componentCount] = component;

    if (m_componentCount > 1)
        delete[] m_components;
    else if (m_componentCount == 1)
        delete m_components;

    //Set the old array to be the new array
    m_components = tempArray;

    //Increment component count
    m_componentCount++;

    return component;
}

bool Actor::removeComponent(Component* component)
{
    //Check to see if the component is null
    if (!component)   
        return false;    

    bool compRemoved = false;
    //Create a new array with a size one less than our old array
    Component** newArray = new Component * [m_componentCount - 1];
    //Create variable to access tempArray index
    int j = 0;
    //Copy values from the old array to the new array
    for (int i = 0; i < m_componentCount; i++)
    {
        if (component != m_components[i])
        {
            newArray[j] = m_components[i];
            j++;
        }
        else
        {
            compRemoved = true;
        }
    }

    //Set the old array to the new array
    if (compRemoved)
    {
        delete[] m_components;
        m_components = newArray;
        m_componentCount--;
        delete component;
    }
    else 
        delete[] newArray;

    //Return whether or not the removal was successful
    return compRemoved;
}

bool Actor::removeComponent(const char* componentName)
{
    //Check to see if the component is null
    if (!componentName)
        return false;

    bool compRemoved = false;
    Component* componentToDelete = nullptr;
    //Create a new array with a size one less than our old array
    Component** newArray = new Component * [m_componentCount - 1];
    //Create variable to access tempArray index
    int j = 0;
    //Copy values from the old array to the new array
    for (int i = 0; i < m_componentCount; i++)
    {
        if (strcmp(m_components[i]->getName(), componentName) == 0)
        {
            newArray[j] = m_components[i];
            j++;
        }
        else
        {
            compRemoved = true;
            componentToDelete = m_components[i];
        }
    }

    //Set the old array to the new array
    if (compRemoved)
    {
        delete[] m_components;
        m_components = newArray;
        m_componentCount--;
        delete componentToDelete;
    }
    else
        delete[] newArray;

    //Return whether or not the removal was successful
    return compRemoved;
}

Component* Actor::getComponent(const char* componentName)
{
    //Iterate through the component array 
    for (int i = 0; i < m_componentCount; i++)
    {
        //Return the component if the name is the same as the current component
        if (strcmp(m_components[i]->getName(), componentName) == 0)
            return m_components[i];            
    }

    //Return nullpter if the component is not the same
	return nullptr;
}

void Actor::update(float deltaTime)
{
    for (int i = 0; i < m_componentCount; i++)
    {
        if (!m_components[i]->getStarted())
            m_components[i]->start();

        m_components[i]->update(deltaTime);
    }
}

void Actor::draw()
{
    for (int i = 0; i < m_componentCount; i++)
    {
        m_components[i]->draw();
    }
}

void Actor::end()
{
    m_started = false;

    for (int i = 0; i < m_componentCount; i++)
    {
        m_components[i]->end();
    }
}

void Actor::onDestroy()
{
    for (int i = 0; i < m_componentCount; i++)
        m_components[i]->onDestroy();

    //Removes this actor from its parent if it has one
    if (getTransform()->getParent())
        getTransform()->getParent()->removeChild(getTransform());
}

bool Actor::checkForCollision(Actor* other)
{
    //Call check collision if there is a collider attached to this actor
    if (m_collider)
        return m_collider->checkCollision(other);

    return false;
}