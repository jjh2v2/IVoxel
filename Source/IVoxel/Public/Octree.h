#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "TestActor.h"

class FOctree
{
public:
	FOctree(FIntVector Position, uint8 Depth);
	~FOctree();

	/*
	* Childs Location
	* 01 Below 45 
	* 23 Below 67
	*/
	FOctree* Childs[8];
	bool HasChilds;
	const uint8 Depth;
	const FIntVector Position;

	void Destroy();
	void DestroyChilds();
	void CreateChilds();
	int Size() const;

	void TestRender(UWorld* world);
};