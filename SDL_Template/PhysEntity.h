#ifndef __PHYSENTITY_H
#define __PHYSENTITY_H

#include <vector>
#include <string>

#include "GameEntity.h"
#include "MathHelper.h"
#include "Collider.h"

class PhysEntity : public GameEntity {
protected:
	unsigned long mId;

	std::string mTag;

	std::vector<Collider *> mColliders;

	Collider * mBroadPhaseCollider;

	void AddCollider(Collider * collider, Vector2 localPos = Vec2_Zero);

	virtual bool IgnoreCollisions();

public:
	PhysEntity();
	virtual ~PhysEntity();

	unsigned long GetId();

	std::string tag();
	void tag(std::string tag);

	bool CheckCollisions(PhysEntity * other);

	virtual void Hit(PhysEntity * other) { }

	virtual void Render() override;
};

#endif