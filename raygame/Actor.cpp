#include "Actor.h"
#include "Transform2D.h"
#include <string.h>
#include "Collider.h"

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
}

Component* Actor::addComponent(Component* component)
{
    //Create a new array thats one size larger than the original
    Component** tempArray = new Component * [m_componentCount + 1];

    //Copy all values from the original array into the temp array
    for (int i = 0; i < m_componentCount; i++)
    {
        tempArray[i] = m_comp[i];
    }

    //Add the new component to the end of the array
    tempArray[m_componentCount] = component;

    //Set the old array to be the new array
    m_comp = tempArray;

    //Increment component count
    m_componentCount++;

    return component;
}

bool Actor::removeComponent(Component* component)
{
    //Check to see if the component is null
    if (!component)
    {
        return false;
    }

    bool compRemoved = false;
    //Create a new array with a size one less than our old array
    Component** newArray = new Component * [m_componentCount - 1];
    //Create variable to access tempArray index
    int j = 0;
    //Copy values from the old array to the new array
    for (int i = 0; i < m_componentCount; i++)
    {
        if (component != m_comp[i])
        {
            newArray[j] = m_comp[i];
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
        m_comp = newArray;
        m_componentCount--;
    }
    //Return whether or not the removal was successful
    return compRemoved;
}

void Actor::update(float deltaTime)
{
}

void Actor::draw()
{
}

void Actor::end()
{
    m_started = false;
}

void Actor::onDestroy()
{
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