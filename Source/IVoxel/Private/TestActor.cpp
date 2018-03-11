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
	Manager = new IVoxelManager(this, 8);
}

void ATestActor::BeginPlay()
{
	Super::BeginPlay();
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
}

void ATestActor::RenderOctree(FVector Location, int RenderDepth, int ChildDepth, bool Debug)
{
	if (Debug)
	{
		Manager->MainOctree->TestRender(GetWorld());
	}
	else
	{
		Manager->PolygonizeOctree(Location, RenderDepth, ChildDepth);
	}
}