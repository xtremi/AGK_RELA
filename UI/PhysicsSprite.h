#pragma once
#include "Sprite.h"

enum class AgkPhysicsMode {
	off			= 0,
	static_		= 1,
	dynamic		= 2,
	kinematic	= 3
};

class PhysicsSprite : public Sprite {

public:
	PhysicsSprite(AgkImage* img, const glm::vec2& pos, const glm::vec2& size, AgkHAlign halign = AgkHAlign::center, AgkVAlign valign = AgkVAlign::center);
	PhysicsSprite(const glm::vec4& color, AgkHAlign halign = AgkHAlign::center, AgkVAlign valign = AgkVAlign::center);
	PhysicsSprite(const glm::vec4& color, const glm::vec2& pos, float size = 1.0f, AgkHAlign halign = AgkHAlign::center, AgkVAlign valign = AgkVAlign::center);
	PhysicsSprite(const glm::vec4& color, const glm::vec2& pos, const glm::vec2& size, AgkHAlign halign = AgkHAlign::center, AgkVAlign valign = AgkVAlign::center);

	void disablePhysics() {
		agk::SetSpritePhysicsOff(id);
	}

	void setPhysics(AgkPhysicsMode physicsMode) {
		if (physicsMode == AgkPhysicsMode::off)
			disablePhysics();
		else
			agk::SetSpritePhysicsOn(id, (int)physicsMode);
	}
	void setVelocity(const glm::vec2& v) {
		agk::SetSpritePhysicsVelocity(id, v.x, v.y);
	}
	void setAngularVelocity(float va) {
		agk::SetSpritePhysicsAngularVelocity(id, va);
	}
	glm::vec2 getVelocity() {
		return glm::vec2(agk::GetSpritePhysicsVelocityX(id), agk::GetSpritePhysicsVelocityY(id));
	}
	void setImpulse(const glm::vec2& from, const glm::vec2& imp) {
		agk::SetSpritePhysicsImpulse(id, from.x, from.y, imp.x, imp.y);
	}
	void setImpulse(const glm::vec2& imp) {
		setImpulse(this->getPos(), imp);
	}

private:

};