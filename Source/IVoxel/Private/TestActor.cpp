#include "TestActor.h"

ATestActor::ATestActor()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Game/Geometry/Meshes/1M_Cube"));

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = RootComp;

	RMC = CreateDefaultSubobject<URuntimeMeshComponent>(TEXT("RMC"));
	RMC->SetupAttachment(RootComp);

	Manager = new IVoxelManager(this, 16);
}

void ATestActor::BeginPlay()
{
	Super::BeginPlay();
}

void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATestActor::SetOctreeValue(FVector Location)
{
}

void ATestActor::RenderOctree(FVector Location, int RenderDepth, int ChildDepth)
{
	
}