// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "IVoxelBPLibrary.h"
#include "IVoxel.h"

UIVoxelBPLibrary::UIVoxelBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

float UIVoxelBPLibrary::IVoxelSampleFunction(float Param, UWorld* World, FIntVector Location)
{
	FOctree* MainOctree = new FOctree(Location,	8);
	UE_LOG(LogGarbage, Warning, TEXT("asdf"));
	MainOctree->CreateChilds();
	MainOctree->TestRender(World);
	MainOctree->Destroy();
	return -1;
}

