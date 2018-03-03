#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"

#include "TestActor.generated.h"

UCLASS()
class ATestActor : public AActor
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* CubeComp;

	UPROPERTY(EditAnywhere)
	USceneComponent* RootComp;

	ATestActor();
};