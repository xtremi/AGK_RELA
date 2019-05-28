#pragma once
#include "agk.h"

/***********************************************/
class AgkSound
/***********************************************/
{
public:
	AgkSound(char* soundPath, bool isOGG) {		
		if(!isOGG)
			id = agk::LoadSound(soundPath);
		else
			id = agk::LoadSoundOGG(soundPath);
	}	
	UINT getId() {
		return id;
	}

	void play(int vol = 100, int loop = 0) {
		agk::PlaySound(id, vol, loop);
	}
	void stop() {
		agk::StopSound(id);
	}

private:
	UINT id = -1;
};
