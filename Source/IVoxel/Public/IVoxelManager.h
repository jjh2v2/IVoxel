#pragma once

#include "CoreMinimal.h"
#include "Octree.h"
#include "RuntimeMeshComponent.h"
#include "RuntimeMeshShapeGenerator.h"
#include "WorldGenerator.h"
#include "TestActor.h"
#include "FlatWorldGenerator.h"

class ATestActor;
class FOctree;
class UWorldGenerator;

class IVoxelManager
{
private:
	ATestActor * World;

public:
	FOctree * MainOctree;

	TSet<FOctree*> OctreeToOptimize;

	UWorldGenerator* WorldGenerator;

	IVoxelManager(ATestActor* World, UWorldGenerator* WorldGenerator, uint8 OctreeDepth);
	~IVoxelManager();
	void Tick();
	void PolygonizeOctree(FVector OctreeLocation, uint8 RenderSize, uint8 RenderDepth, int RenderSection);
	void GenerateWorld(FVector OctreeLocation, uint8 Depth, uint8 DepthSize);
};