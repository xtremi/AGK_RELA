#include "NumberTextSprite.h"

NumberTextSprite::NumberTextSprite(
	float v, const glm::vec3& color,
	const glm::vec2& pos, float textSize,
	AgkHAlign halign, AgkVAlign valign)
	: TextSprite("", color, pos, textSize, halign, valign)
{
	setValue(v);
}

void NumberTextSprite::setValue(float v, int p) {
	value = v;
	setText(agk::Str(v, p));
}

float NumberTextSprite::getValue() {
	return value;
}