#include "ObjectManager.h"
#include "PhysicsManager.h"
#include "RCEngine.h"

ObjectManager::ObjectManager() {
	this->m_physics = new PhysicsManager();
}

ObjectManager::~ObjectManager() {
	// Destroy all objects here
}

Object2D * ObjectManager::CreateCircle(Vector2 pos, float radius, const short character, const int colour) {
	Object2D* obj = new Circle(pos, radius, character, colour);
	m_objects.push_back(obj);

	return obj;
}

Object2D * ObjectManager::CreateSquare(Vector2 pos, Vector2 size, const short character, const int colour) {
	Object2D* obj = new Square(pos, size, character, colour);
	m_objects.push_back(obj);
	
	return obj;
}

Object2D * ObjectManager::CreateLine(Vector2 start, Vector2 end, const short character, const int colour) {
	Object2D* obj = new Line(start, end, character, colour);
	m_objects.push_back(obj);

	return obj;
}

void ObjectManager::UpdateObjects() {
	m_physics->Update(m_objects);
}

void ObjectManager::DestroyObject(Object2D & object) {
	auto place = std::find(m_objects.begin(), m_objects.end(), &object);
	m_objects.erase(place);
}

void ObjectManager::Render(RCEngine & engine) {
	for (int i = 0; i < m_objects.size(); i++) {
		m_objects[i]->Render(engine);
	}
}
