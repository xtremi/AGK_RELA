#include "AgkImage.h"

/****************************************************/
AgkImage::AgkImage(char* imgpath)
/****************************************************/
{
	id = agk::LoadImage(imgpath);
}
/****************************************************/
AgkImage::AgkImage(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
/****************************************************/
{
	id = agk::CreateImageColor(r, g, b, a);
}
AgkImage::AgkImage(float r, float g, float b, float a) 
	: AgkImage((unsigned int)(255.0f*r), (unsigned int)(255.0f*g), (unsigned int)(255.0f*b), (unsigned int)(255.0f*a))
{}
AgkImage::AgkImage(const glm::vec4& color) 
	: AgkImage(color.r, color.g, color.b, color.a)
{}
AgkImage::AgkImage(const glm::vec3& color, float alpha) 
	: AgkImage(color.r, color.g, color.b, alpha)
{}