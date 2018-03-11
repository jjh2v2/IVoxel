#pragma once

#include "CoreMinimal.h"
#include "Octree.h"
#include "RuntimeMeshComponent.h"
#include "RuntimeMeshShapeGenerator.h"
#include "TestActor.h"
class ATestActor;
class FOctree;

class IVoxelManager
{
private:
	ATestActor * World;

public:
	FOctree * MainOctree;

	TSet<FOctree*> OctreeToOptimize;

	IVoxelManager(ATestActor* World, uint8 OctreeDepth);
	~IVoxelManager();
	void Tick();
	void PolygonizeOctree(FVector OctreeLocation, uint8 RenderSize, uint8 RenderDepth);
private:
	void MakeCube(int Radius, FVector Location, TArray<FVector>& Vertices, TArray<int32>& Triangles, TArray<FVector>& Normals);
};