// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "IVoxelBPLibrary.h"
#include "IVoxel.h"

UIVoxelBPLibrary::UIVoxelBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

float UIVoxelBPLibrary::IVoxelSampleFunction(int Param, UWorld* World, FIntVector Location)
{
	FOctree* MainOctree = new FOctree(Location, Param, nullptr);
	UE_LOG(LogGarbage, Warning, TEXT("asdf"));
	MainOctree->Subdivide();
	
	MainOctree->TestRender(World);
	MainOctree->Destroy();
	return -1;
}

