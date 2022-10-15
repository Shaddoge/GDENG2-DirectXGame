#include "EngineTime.h"

EngineTime* EngineTime::sharedInstance = NULL;

void EngineTime::Initialize()
{
	sharedInstance = new EngineTime();
}

double EngineTime::GetDeltaTime()
{
	return sharedInstance->deltaTime;
}

EngineTime::EngineTime()
{
}

EngineTime::~EngineTime()
{
}

void EngineTime::LogFrameStart()
{
	sharedInstance->start = std::chrono::system_clock::now();
}

void EngineTime::LogFrameEnd()
{
	sharedInstance->end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = sharedInstance->end - sharedInstance->start;

	sharedInstance->deltaTime = elapsed_seconds.count();
}
