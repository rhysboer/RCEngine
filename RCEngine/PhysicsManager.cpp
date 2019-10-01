#include "PhysicsManager.h"
#include "RCEngine.h"

static fn CollisionFunctionArray[] =
{
	PhysicsManager::Plane2Plane,	PhysicsManager::Plane2Sphere,	PhysicsManager::Plane2AABB,
	PhysicsManager::Sphere2Plane,	PhysicsManager::Sphere2Sphere,	PhysicsManager::Sphere2AABB,
	PhysicsManager::AABB2AABB,		PhysicsManager::AABB2AABB,		PhysicsManager::AABB2AABB,
};

PhysicsManager::PhysicsManager() {
	this->m_timestep = 0.01f;
	this->m_gravity = Vector2(0.0f, 30.81f); //40.0f
	this->m_isOn = true;
}

PhysicsManager::~PhysicsManager() {
}

void PhysicsManager::Update(std::vector<Object2D*>& objects) {
	for (int i = 0; i < objects.size(); i++) {
		if (objects[i]->IsUsingPhysics()) {
			// Apply gravity

			//objects[i]->SetVelocity(this->m_gravity * RCEngine::DeltaTime());
			//objects[i]->Translate(objects[i]->GetVelocity());
			objects[i]->FixedUpdate(this->m_gravity);
		}
	}

	CheckCollision(objects);
}

void PhysicsManager::CheckCollision(std::vector<Object2D*>& objects) {
	for (int i = 0; i < objects.size(); i++) {
		if (!objects[i]->IsCollidable()) continue;

		for (int j = i + 1; j < objects.size(); j++) {
			if (i == j && !objects[j]->IsCollidable()) continue;

			Object2D* obj1 = objects[i];
			Object2D* obj2 = objects[j];

			int index = (obj1->GetCollisionType() * CollisionType::COUNT) + obj2->GetCollisionType();

			fn collision = CollisionFunctionArray[index];

			if (collision != nullptr) {
				collision(obj1, obj2);
			}
		}
	}
}

void PhysicsManager::SetGravity(const Vector2 gravity) {
	this->m_gravity = gravity;
}

void PhysicsManager::EnablePhysics(const bool usePhysics) {
	m_isOn = usePhysics;
}

bool PhysicsManager::Sphere2Plane(Object2D * obj1, Object2D * obj2) {
	Circle* circle = dynamic_cast<Circle*>(obj1->GetType());
	Line* line = dynamic_cast<Line*>(obj2->GetType());

	if (circle != nullptr || line != nullptr) {
		
		Vector2 vec1 = line->GetDrawPoints()[0];
		Vector2 vec2 = line->GetDrawPoints()[1];
		Vector2 circ = circle->GetPosition();

		float distX = vec1.X - vec2.X;
		float distY = vec1.Y - vec2.Y;
		float len = sqrt((distX * distX) + (distY*distY));


		float dot = (
			(((circ.X - vec1.X) * (vec2.X - vec1.X)) +
			((circ.Y - vec1.Y) * (vec2.Y - vec1.Y))) /
			pow(len, 2) 
		);

		Vector2 closest = Vector2(
			vec1.X + (dot * (vec2.X - vec1.X)),
			vec1.Y + (dot * (vec2.Y - vec1.Y))
		);

		distX = closest.X - circ.X;
		distY = closest.Y - circ.Y;
		float distance = sqrt((distX * distX) + (distY*distY));

		if (distance <= circle->GetRadius()) {
			circle->Translate(Vector2(0,-(circle->GetRadius() - distance)));

			Vector2 normalVec = Vector2::Normalised(line->GetNormal());
			Vector2 force = 2.0f * Vector2::Dot(circle->GetVelocity(), normalVec) * normalVec;
			force.Y *= -1;
			force.X *= -1;

			circle->AddForce(force);


			//Vector2 newVelocity = circle->GetVelocity();
			//newVelocity.Y /= 2;
			//newVelocity.Y *= -1;
			//circle->SetVelocity(newVelocity);

			return true;
		}

	}

	return false;
}

bool PhysicsManager::Sphere2Sphere(Object2D * obj1, Object2D * obj2) {
	Circle* circle1 = dynamic_cast<Circle*>(obj1->GetType());
	Circle* circle2 = dynamic_cast<Circle*>(obj2->GetType());

	if (circle1 && circle2) {
		Vector2 delta = circle1->GetPosition() - circle2->GetPosition();
		float distance = Vector2::Magnitude(delta);
		float intersection = circle1->GetRadius() + circle2->GetRadius() - distance;

		
		//if (intersection > 0) {

		//	/* Vector perpendicular to the point of collision */
		//	Vector2 collisionNormal = Vector2::Normalised(delta);
		//												 /* The relative velocity of the two object colliding */
		//	Vector2 relativeVelocity = circle1->GetVelocity() - circle2->GetVelocity();
		//	/* Collsion normal scaled by the dot product of the collision normal */
		//	Vector2 collisionVector = collisionNormal * (Vector2::Dot(relativeVelocity, collisionNormal));
		//	/* How much force get applied to the object */
		//	Vector2 forceVector = collisionVector * 1.0f / (1.0f / 5.0f + 1.0f / 5.0f);

		//	/* Combined both sphere elasticities */
		//	float combinedElasticity = (0.7f + 0.7f) / 2.0f;
		//	circle2->AddForce(forceVector + (forceVector*combinedElasticity));
		//	//circle1->ApplyForceToActor(circle2, forceVector + (forceVector*combinedElasticity));


		//	/* The vector along which will move the two objects so they are no longer colliding */
		//	Vector2 separationVector = collisionNormal * intersection * 0.5f;

		//	circle1->SetPosition(circle1->GetPosition() - separationVector);
		//	circle2->SetPosition(circle2->GetPosition() + separationVector);

		//	return true;
		//}
		
	}

	return false;
}

/*

Vector2 lineNormal = line->GetNormal();
float dot = Vector2::Dot(circle->GetPosition(), line->GetNormal()) - line->GetSize();

if (dot < 0) {
lineNormal *= -1;
dot *= -1;
}

float intersection = circle->GetRadius() - dot;
if (intersection > 0) {

Vector2 planeNormal = line->GetNormal();
if (dot < 0) {
planeNormal *= -1;
}

// 5 = mass
Vector2 force = Vector2(0, 0);//-1 * 5.0f * planeNormal * (Vector2::Dot(planeNormal, circle->GetVelocity()));

circle->AddForce(force + (force * 1.5f));
circle->SetPosition(circle->GetPosition() + lineNormal * intersection * 0.5f);

return true;
}

*/
