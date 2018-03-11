#include "Octree.h"

FOctree::FOctree(FIntVector Position, uint8 Depth)
	: Depth(Depth), Position(Position), HasChilds(false), Value(false)
{

}

/*
 * Use Destroy() instead.
 */
FOctree::~FOctree()
{
	check(!HasChilds);
}

void FOctree::Subdivide()
{
	if (HasChilds) return;
	check(Depth >= 0);
	int s = Size() / 2;

	/*
	* Childs Location
	* Up     Below
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

bool FOctree::IsInOctree(FVector Location)
{
	FVector P1 = FVector(Position + FIntVector(Size()/2));
	FVector P2 = FVector(Position - FIntVector(Size()/2));
	return Location.X < P1.X && Location.X > P2.X  //X
		&& Location.Y < P1.Y && Location.Y > P2.Y  //Y
		&& Location.Z < P1.Z && Location.Z > P2.Z; //Z
}

int FOctree::Size() const
{
	return 8 << Depth;
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

void FOctree::SubdivideToZero()
{
	if (Depth <= 0) return;
	if (!HasChilds)
	{
		Subdivide();
	}
	for (auto& child : Childs)
	{
		child->SubdivideToZero();
	}

}

FOctree* FOctree::GetOctree(FVector Location, uint8 MaxDepth)
{
	//check(IsInOctree(Location));

	if (Depth > MaxDepth)
	{
		Subdivide();
		return GetChildOctree(Location)->GetOctree(Location, MaxDepth);
	}
	else
	{
		return this;
	}
}

/*
* Childs Location
* Up     Below
* 0 1    4 5
* 2 3    6 7
*/
FOctree* FOctree::GetChildOctree(FVector Location)
{
	check(HasChilds);
	//check(IsInOctree(Location));

	int Result = 0;
	FVector Center = FVector(Position);
	Result = Result | (Center.X > Location.X ? 1 : 0); //X
	Result = Result | (Center.Y > Location.Y ? 2 : 0); //Y
	Result = Result | (Center.Z > Location.Z ? 4 : 0); //Z
	return Childs[Result];
}

void FOctree::GetChildOctrees(TSet<FOctree*>& RetValue, uint8 MaxDepth)
{
	RetValue.Add(this);
	for (auto& child : Childs)
	{
		GetChildOctrees(RetValue, MaxDepth);
	}
}

void FOctree::TestRender(UWorld* world)
{
	DrawDebugBox(world, FVector(Position), FVector(Size()), FColor(1, 0, 0), false, 10);
	if (Value)
	{
		DrawDebugBox(world, FVector(Position), FVector(Size()), FColor(1, 0, 0), false, 10, 0, 2);
	}
	if (HasChilds)
	{
		for (auto& child : Childs)
		{
			child->TestRender(world);
		}
	}
}

void FOctree::OptimizeOrMakeLod()
{

}
