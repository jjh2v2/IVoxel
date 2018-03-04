#include "TestActor.h"

ATestActor::ATestActor()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Game/Geometry/Meshes/1M_Cube"));

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = RootComp;
	MainOctree = new FOctree(FIntVector(GetActorLocation()), 7);

	RMC = CreateDefaultSubobject<URuntimeMeshComponent>(TEXT("RMC"));
	RMC->SetupAttachment(RootComp);
}

ATestActor::~ATestActor()
{
	MainOctree->Destroy();
}

void ATestActor::BeginPlay()
{
	Super::BeginPlay();
}

void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	static int TickCount = 0;
	if (TickCount % 10 == 0)
	{
		MainOctree->TestRender(GetWorld());
	}
	TickCount++;
}

void ATestActor::SetOctreeValue(FVector Location)
{
	MainOctree->GetOctree(Location, 0)->Value = true;
}

void ATestActor::RenderOctree()
{

}