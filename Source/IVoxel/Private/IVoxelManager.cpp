#include "IVoxelManager.h"


IVoxelManager::IVoxelManager(ATestActor* World, UWorldGenerator* WorldGenerator, uint8 OctreeDepth)
	: World(World), MainOctree(new FOctree(FIntVector(0), OctreeDepth, nullptr)), WorldGenerator(WorldGenerator)
{
	
}

IVoxelManager::~IVoxelManager()
{
	MainOctree->Destroy();
	delete MainOctree;
}

void IVoxelManager::Tick()
{

}

void IVoxelManager::PolygonizeOctree(FVector OctreeLocation, uint8 RenderSize, uint8 RenderDepth, int RenderSection)
{
	FOctree* Chunk = MainOctree->GetOctree(OctreeLocation, RenderSize);
	TSet<FOctree*> Octrees;
	Chunk->GetChildOctrees(Octrees, RenderDepth);

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FRuntimeMeshTangent> Tangent;
	TArray<FColor> VertexColor;
	for (auto& Octree : Octrees)
	{
		if (Octree->GetValue() && !Octree->IsFake)
		{
			URuntimeMeshShapeGenerator::CreateBoxMesh(Octree->Size(), FVector(Octree->Position), Octree->GetColor(), Vertices, Triangles, Normals, UVs, Tangent, VertexColor);
		}
	}
	World->RMC->CreateMeshSection(RenderSection, Vertices, Triangles, Normals, UVs, VertexColor, Tangent, true);
}

void IVoxelManager::GenerateWorld(FVector OctreeLocation, uint8 Depth, uint8 GenDepth)
{
	TSet<FOctree*> ToOptimize;
	FOctree* Octree = MainOctree->GetOctree(OctreeLocation, Depth);
	Octree->GenerateWorld(WorldGenerator, GenDepth, ToOptimize);

	for (auto& Octree : ToOptimize)
	{
		if (Octree)
		{
			Octree->OptimizeOrMakeLod();
		}
	}
}
