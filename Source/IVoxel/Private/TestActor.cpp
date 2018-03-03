#include "TestActor.h"

ATestActor::ATestActor()
{
	ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Game/Geometry/Meshes/1M_Cube"));

	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent = RootComp;

	CubeComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CubeComp"));
	CubeComp->SetupAttachment(RootComponent);
	CubeComp->SetStaticMesh(CubeMesh.Object);
}