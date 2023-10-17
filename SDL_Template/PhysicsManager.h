#ifndef __PHYSICSMANAGER_H
#define __PHYSICSMANAGER_H

#include <bitset>
#include "PhysEntity.h"

class PhysicsManager {
public:
	enum class CollisionLayers {
		Player,
		Platform,
		Explosion,
		Bird,
		Spike,
		MaxLayers
	};
	
	enum class CollisionFlags {
		None		= 0x00,
		Player		= 0x01,
		Platform	= 0x02,
		Explosion	= 0x04,
		Bird		= 0x08,
		Spike		= 0x10
	};

private:
	static PhysicsManager * sInstance;

	std::vector<PhysEntity * > mCollisionLayers[static_cast<unsigned int>(CollisionLayers::MaxLayers)];
	std::bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)> mLayerMasks[static_cast<unsigned int>(CollisionLayers::MaxLayers)];

	unsigned long mLastId;

public:
	static PhysicsManager * Instance();
	static void Release();

	void SetLayerCollisionMask(CollisionLayers layer, CollisionFlags flags);

	unsigned long RegisterEntity(PhysEntity * entity, CollisionLayers layer);
	void UnregisterEntity(unsigned long id);

	void Update();

private:
	PhysicsManager();
	~PhysicsManager();
};

inline PhysicsManager::CollisionFlags operator|(PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b) {
	return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
}

inline PhysicsManager::CollisionFlags operator&(PhysicsManager::CollisionFlags a, PhysicsManager::CollisionFlags b) {
	return static_cast<PhysicsManager::CollisionFlags>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
}
#endif