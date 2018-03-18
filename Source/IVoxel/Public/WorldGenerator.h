#pragma once

#include "Octree.h"
#include "WorldGenerator.generated.h"

UCLASS(Blueprintable, abstract, HideCategories = ("Tick", "Replication", "Input", "Actor", "Rendering"))
class UWorldGenerator : public UObject
{
	GENERATED_BODY()
public:
	virtual void GetValueAndColor(FIntVector Location, bool &Value, FColor &Color)
	{

	}
};