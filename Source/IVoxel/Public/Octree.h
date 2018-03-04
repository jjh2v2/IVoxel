#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "TestActor.h"
#include "DrawDebugHelpers.h"

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

	bool Value;

	void Destroy();
	void DestroyChilds();
	void Subdivide();
	int Size() const;
	bool IsInOctree(FVector Location);

	FOctree* GetOctree(FVector Location, uint8 MaxDepth = 0);
	FOctree* GetChildOctree(FVector Location);

	void SubdivideToZero();
	void TestRender(UWorld* world);
};