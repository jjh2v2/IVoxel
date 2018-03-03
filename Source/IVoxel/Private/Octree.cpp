#include "Octree.h"

FOctree::FOctree(FIntVector Position, uint8 Depth)
	: Depth(Depth), Position(Position), HasChilds(false)
{

}

/*
 * Use Destroy() instead, or it will breakpoint
 */
FOctree::~FOctree()
{
	check(!HasChilds);
}

void FOctree::CreateChilds()
{
	int s = Size();

	/*
	* Childs Location
	* 0 1    4 5
	* 2 3    6 7
	*/

	Childs[0] = new FOctree(Position + FIntVector(+s, +s, +s), Depth - 1);
	Childs[1] = new FOctree(Position + FIntVector(-s, +s, +s), Depth - 1);
	Childs[2] = new FOctree(Position + FIntVector(+s, -s, +s), Depth - 1);
	Childs[3] = new FOctree(Position + FIntVector(-s, -s, +s), Depth - 1);
	Childs[4] = new FOctree(Position + FIntVector(+s, +s, -s), Depth - 1);
	Childs[5] = new FOctree(Position + FIntVector(-s, +s, -s), Depth - 1);
	Childs[6] = new FOctree(Position + FIntVector(+s, -s, -s), Depth - 1);
	Childs[7] = new FOctree(Position + FIntVector(-s, -s, -s), Depth - 1);

	HasChilds = true;
}

int FOctree::Size() const
{
	return 4 << Depth;
}

void FOctree::Destroy()
{
	if (HasChilds)
	{
		DestroyChilds();
	}
	delete this;
}

void FOctree::DestroyChilds()
{
	for (auto& child : Childs)
	{
		child->Destroy();
	}
	HasChilds = false;
}

void FOctree::TestRender(UWorld* world)
{
	FActorSpawnParameters SpawnParm;
	SpawnParm.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	world->SpawnActor<ATestActor>(FVector(Position), FRotator(0), SpawnParm)->SetActorScale3D(FVector(Size() / 24));

	if (HasChilds)
	{
		for (auto& child : Childs)
		{
			child->TestRender(world);
		}
	}
}