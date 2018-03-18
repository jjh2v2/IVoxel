#include "TestActor.h"

ATestActor::ATestActor()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UMaterialInterface> CubeMaterial(TEXT("/IVoxel/IVoxelMaterial"));

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = RootComp;

	RMC = CreateDefaultSubobject<URuntimeMeshComponent>(TEXT("RMC"));
	RMC->SetupAttachment(RootComp);
	RMC->SetMaterial(0, CubeMaterial.Object);

	
}

void ATestActor::BeginPlay()
{
	Super::BeginPlay();

	if (WorldGenerator)
	{
		InstancedGenerator = NewObject<UWorldGenerator>((UObject*)GetTransientPackage(), WorldGenerator);
	}
	Manager = new IVoxelManager(this, InstancedGenerator, 14);
}

void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATestActor::SetOctreeValue(FVector Location, int Depth, bool Value, FColor Color)
{
	FOctree* Octree = Manager->MainOctree->GetOctree(Location, Depth);
	Octree->SetValue(Value);
	Octree->SetColor(Color);
	Octree->Mother->OptimizeOrMakeLod();
}

void ATestActor::RenderOctree(FVector Location, int RenderDepth, int ChildDepth, bool Debug)
{
	if (Debug)
	{
		Manager->MainOctree->TestRender(GetWorld());
	}
	else
	{
		Manager->PolygonizeOctree(Location, RenderDepth, ChildDepth, 0);
	}
}

void ATestActor::GenerateWorld(FVector Location, int Depth, int GenDepth)
{
	if (!WorldGenerator)
	{
		UE_LOG(LogGarbage, Warning, TEXT("World generator is null"));
		return;
	}
	Manager->GenerateWorld(Location, Depth, GenDepth);
}