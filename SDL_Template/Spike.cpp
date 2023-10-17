#include "Spike.h"
#include "BoxCollider.h"
#include "PhysicsManager.h"

bool Spike::IgnoreCollisions() {
	return !Active();
}

Spike::Spike() {
	mTag = "Spike";

	mTexture = new GLTexture("GravityJump.png", 971, 1, 162, 81);
	mTexture->Parent(this);
	mTexture->Position(Vec2_Zero);

	AddCollider(new BoxCollider(Vector2(128.0f, 70.0f)));

	mId = PhysicsManager::Instance()->RegisterEntity(this, PhysicsManager::CollisionLayers::Spike);
}

Spike::~Spike() {
	delete mTexture;
	mTexture = nullptr;

	PhysicsManager::Instance()->UnregisterEntity(mId);
}

void Spike::Hit(PhysEntity* other) {

}

void Spike::Update() {

}

void Spike::Render() {
	mTexture->Render();
	PhysEntity::Render();
}