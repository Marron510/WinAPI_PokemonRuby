#pragma once
#include <EngineCore/Actor.h>

class AtitleMap : public AActor
{
public:
	// constrcuter destructer
	AtitleMap();
	~AtitleMap();

	// delete Function
	AtitleMap(const AtitleMap& _Other) = delete;
	AtitleMap(AtitleMap&& _Other) noexcept = delete;
	AtitleMap& operator=(const AtitleMap& _Other) = delete;
	AtitleMap& operator=(AtitleMap&& _Other) noexcept = delete;

protected:

private:

};

