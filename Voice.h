#ifndef VOICE_H
#define VOICE_H

#include <string>
#include <iostream>

#ifdef VOICE
//
#else
//
#endif

class Voice {
public:
	Voice();
	void speak(std::string text);
};

#endif
