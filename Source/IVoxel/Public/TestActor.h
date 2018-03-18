#pragma once

#include "Octree.h"
#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "Components/StaticMeshComponent.h"
#include "RuntimeMeshComponent.h"
#include "ConstructorHelpers.h"
#include "IVoxelManager.h"

#include "TestActor.generated.h"

UCLASS()
class ATestActor : public AActor 
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	USceneComponent* RootComp;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UWorldGenerator> WorldGenerator;

	UWorldGenerator* InstancedGenerator = nullptr;

	URuntimeMeshComponent* RMC;
	
	IVoxelManager* Manager;

	ATestActor();

	void Tick(float DeltaTime) override;
	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SetOctreeValue(FVector Location, int Depth, bool Value, FColor Color);

	UFUNCTION(BlueprintCallable)
	void RenderOctree(FVector Location, int RenderDepth, int ChildDepth, bool Debug);

	UFUNCTION(BlueprintCallable)
	void GenerateWorld(FVector Location, int Depth, int GenDepth);
};