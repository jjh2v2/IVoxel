#pragma once

#include "WorldGenerator.h"
#include "FlatWorldGenerator.generated.h"

UCLASS(Blueprintable)
class UFlatWorldGenerator : public UWorldGenerator
{
	GENERATED_BODY()

public:
	UFlatWorldGenerator();

	virtual void GetValueAndColor(FIntVector Location, bool &Value, FColor &Color) override;
};