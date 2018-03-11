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
	ATestActor* World;
	FOctree* Childs[8];
	FOctree* Mother;
	bool HasChilds;
	const uint8 Depth;
	const FIntVector Position;

	bool Value;

	//Whatever this octree is not actually block, But used for LOD
	bool IsFake;

	void Destroy();
	void DestroyChilds();
	void Subdivide();
	int Size() const;
	bool IsInOctree(FVector Location);

	FOctree* GetOctree(FVector Location, uint8 MaxDepth = 0);
	FOctree* GetChildOctree(FVector Location);
	void GetChildOctrees(TSet<FOctree*> &RetValue, uint8 MaxDepth = 0);

	void SubdivideToZero();
	void TestRender(UWorld* world);
	void OptimizeOrMakeLod();
};