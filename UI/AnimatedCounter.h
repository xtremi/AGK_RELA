#pragma once
#include "AnimatedTextSprite.h"

class AnimatedCounter : public AnimatedTextSprite {

public:
	AnimatedCounter(const glm::vec3& color, float txtsize);

	void processCustomAnimation() {
		currentValue += stepValue;
		setText((char*)std::to_string(currentValue).c_str());

		if (currentValue > endValue)
			stopAnimation();
	}

	void setData(int _endValue, int _stepValue) {
		endValue = _endValue;
		stepValue = _stepValue;
	}

private:
	int endValue = 0;
	int stepValue = 0;
	int currentValue = 0;
};
