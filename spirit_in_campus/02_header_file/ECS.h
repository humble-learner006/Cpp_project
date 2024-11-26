// Entity Component System
#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentID = std::size_t;
// using as a keyword in C++, it is used to give new name to sth. already exist 
inline ComponentID getComponentTypeID() { //inline <fnc name> get unique ID for components.
	static ComponentID lastID = 0; //static <type(size_t in std)> identifier, init only once
	//here init last(newest) ID as zero. Then add it up.
	return lastID++;
}

/*
about inline keyword
- expand/insert the function inline
This can improve performance by eliminating the overhead of a function call, but it can also increase the size of the binary.
By expanding the function inline, the overhead of a function call (such as stack frame setup and teardown) is eliminated.
This can lead to faster execution, especially for small, frequently called functions.
defnition closer to implementation
*/

template <typename T> inline ComponentID getComponentTypeID() noexcept {
	static ComponentID typeID = getComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
// constexpre keyword is for claiming the variable that can be sure unchange while compiling 
// for better performance and stability of program
// as for static, it is like avoiding initialize again when calling

using ComponentBitSet = std::bitset<maxComponents>;
// a set to show if component exist or not
using ComponentArray = std::array<Component*, maxComponents>;
// a arrary to store the pointer pointing toward components, here maxComponents is the size of the arrary
// arrary is fix size data 
class Component {
public: // public method can be used in other classes.
	Entity* entity;
// every component have following three method. And it will be use in entity classes's method definition
	virtual void init(){}
	virtual void update(){}
	virtual void draw(){}

	virtual ~Component(){}
};


// One entity have lots of component! like position and other stuff.
class Entity {
private:
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitset;

public:
	void update() {
		for (auto& c : components) c->update(); // update all component of this entity
	}

	void draw() {
		for (auto& c : components) c->draw();
	}

	bool isActive() { return active; } // whether a entity is active

	void destory() { active = false; }

// hasComponent
	template <typename T> bool hasComponent() const {
		return componentBitset[getComponentTypeID<T>];
	}

// addComponent
	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs) {
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitset[getComponentTypeID<T>()] = true;
/* example
If T is VelocityComponent, 
then getComponentTypeID<VelocityComponent>() will return
a unique ID for VelocityComponent. 

The component c (which is an instance of VelocityComponent) 
will be stored in componentArray at the index corresponding 
to this unique ID.		
*/

		c->init();
		return *c;

	}

// getComponent
	template<typename T> T& getComponent() const {
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	} 

};

// keep list of entities
class Manager {
private:
	std::vector<std::unique_ptr<Entity>> entities;

public:
	void update()
	{
		for (auto& e : entities) e->update();
	}

	void draw()
	{
		for (auto& e : entities) e->draw();
	}

	void refresh()
	{
		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities));
	}

// manager add entity to entity list
	Entity& addEntity()
	{
		Entity* e = new Entity();
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};