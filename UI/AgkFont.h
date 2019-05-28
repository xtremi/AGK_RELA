#pragma once
#include "agk.h"

/***********************************************/
class AgkFont
/***********************************************/
{

public:
	AgkFont(char* fontPath) {
		id = agk::LoadFont(fontPath);
	}

	int getId() {
		return id;
	}

private:
	int id = -1;

};
