#include "UIButtonTypes.h"


//SPRITE BUTTON:
UISpriteButton::UISpriteButton(AgkImage* img, const glm::vec2& size, const glm::vec2& pos, UIButtonType _type)
	: Sprite(img, pos, size) , UIButton(_type)
{}
UISpriteButton::UISpriteButton(const glm::vec3& color, const glm::vec2& size, const glm::vec2& pos, UIButtonType _type) 
	: Sprite(color, pos, size)
{}
UISpriteButton::UISpriteButton(const glm::vec4& color, const glm::vec2& size, const glm::vec2& pos, UIButtonType _type)
	: Sprite(color, pos, size) 
{}

//TEXT SPRITE BUTTON:
UITextButton::UITextButton(char* txt, const glm::vec3& col, float size, const glm::vec2& pos, UIButtonType _type)
	: TextSprite(txt, col, pos, size), UIButton(_type) 
{}

//SPRITE AND TEXT BUTTON:
UISpriteAndTextButton::UISpriteAndTextButton(
	AgkImage* img, char* txt, const glm::vec3& textCol,
	const glm::vec2& size, float textSize, const glm::vec2& pos,
	AgkHAlign halign, AgkVAlign valign, UIButtonType _type)
	: SpriteAndText(img, txt, textCol, size, textSize, pos, halign, valign), UIButton(_type) 
{}

UISpriteAndTextButton::UISpriteAndTextButton(
	const glm::vec3& col, char* txt, const glm::vec3& textCol,
	const glm::vec2& size, float textSize, const glm::vec2& pos,
	AgkHAlign halign, AgkVAlign valign,	UIButtonType _type)
	: SpriteAndText(col, txt, textCol, size, textSize, pos, halign, valign), UIButton(_type)
{}
