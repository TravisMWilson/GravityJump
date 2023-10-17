#ifndef __SPIKE_H
#define __SPIKE_H

#include "PhysEntity.h"
#include "GLTexture.h"
#include "Spike.h"

using namespace SDLFramework;

class Spike : public PhysEntity {
private:
	GLTexture* mTexture;

	bool IgnoreCollisions() override;

public:
	Spike();
	~Spike();

	void Hit(PhysEntity* other) override;

	void Update() override;
	void Render() override;
};

#endif