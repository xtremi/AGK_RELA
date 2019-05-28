#include "PhysicsSprite.h"

PhysicsSprite::PhysicsSprite(AgkImage* img, const glm::vec2& pos, const glm::vec2& size, AgkHAlign halign, AgkVAlign valign)
	: Sprite(img, pos, size, halign, valign) {
	setPhysics(AgkPhysicsMode::dynamic);
}

PhysicsSprite::PhysicsSprite(const glm::vec4& color, AgkHAlign halign, AgkVAlign valign)
	: Sprite(color, halign, valign) {
	setPhysics(AgkPhysicsMode::dynamic);
}

PhysicsSprite::PhysicsSprite(const glm::vec4& color, const glm::vec2& pos, float size, AgkHAlign halign, AgkVAlign valign)
	: Sprite(color, pos, size, halign, valign) {
	setPhysics(AgkPhysicsMode::dynamic);
}

PhysicsSprite::PhysicsSprite(const glm::vec4& color, const glm::vec2& pos, const glm::vec2& size, AgkHAlign halign, AgkVAlign valign)
	: Sprite(color, pos, size, halign, valign) {
	setPhysics(AgkPhysicsMode::dynamic);
}