#include "Octree.h"

FOctree::FOctree(FIntVector Position, uint8 Depth, FOctree* Mother)
	: Depth(Depth), Position(Position), HasChilds(false), Data(FOctreeData()), IsFake(false), Mother(Mother)
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

	Childs[0] = new FOctree(Position + FIntVector(+s, +s, +s), Depth - 1, this);
	Childs[1] = new FOctree(Position + FIntVector(-s, +s, +s), Depth - 1, this);
	Childs[2] = new FOctree(Position + FIntVector(+s, -s, +s), Depth - 1, this);
	Childs[3] = new FOctree(Position + FIntVector(-s, -s, +s), Depth - 1, this);
	Childs[4] = new FOctree(Position + FIntVector(+s, +s, -s), Depth - 1, this);
	Childs[5] = new FOctree(Position + FIntVector(-s, +s, -s), Depth - 1, this);
	Childs[6] = new FOctree(Position + FIntVector(+s, -s, -s), Depth - 1, this);
	Childs[7] = new FOctree(Position + FIntVector(-s, -s, -s), Depth - 1, this);

	if (GetValue())
	{
		for (auto& child : Childs)
		{
			child->SetValue(GetValue());
			child->SetColor(GetColor());
		}
		SetValue(false);
	}
	
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
	return 2 << Depth;
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
	check(HasChilds);
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
	if (Depth < MaxDepth) return;
	RetValue.Add(this);
	if (!HasChilds) return;
	for (auto& child : Childs)
	{
		child->GetChildOctrees(RetValue, MaxDepth);
	}
}

void FOctree::TestRender(UWorld* world)
{
	if (GetValue())
	{
		DrawDebugBox(world, FVector(Position), FVector(Size()), FColor(1, 0, 0), false, 1, 0, 2);
	}
	else
	{
		DrawDebugBox(world, FVector(Position), FVector(Size()), FColor(1, 0, 0), false, 1);
	}
	if (HasChilds)
	{
		for (auto& child : Childs)
		{
			child->TestRender(world);
		}
	}
}

void FOctree::SetValue(bool SetValue)
{
	if (HasChilds)
	{
		DestroyChilds();
	}
	Data.Value = SetValue;

}
void FOctree::SetColor(FColor SetValue)
{
	Data.Color = SetValue;
}
bool FOctree::GetValue()
{
	return Data.Value;
}

FColor FOctree::GetColor()
{
	return Data.Color;
}

void FOctree::OptimizeOrMakeLod()
{
	bool Changed = false;
	//TODO Make Lod
	if (HasChilds)
	{
		//TODO Optimize this calculation
		int Flag = 0;
		int Bit = 1;
		TSet<FColor> Colors;
		FColor FinalColor = FColor(0,0,0,1);
		for (auto& child : Childs)
		{
			if (child->GetValue())
			{
				Flag = Flag | Bit;
				Colors.Add(child->GetColor());
			}
			Bit = Bit << 1;
		}
		if (Colors.Num() != 0)
		{
			int r = 0, g = 0, b = 0, a = 0, count = 0;
			for (auto& color : Colors)
			{
				r += color.R;
				g += color.G;
				b += color.B;
				a += color.A;
				count++;
			}
			FinalColor = FColor(r / count, g / count, b / count, a / count);
		}
		
		switch (Flag)
		{
		case 255: //11111111
			SetValue(true);
			SetColor(FinalColor);
			Changed = true;
			break;
		case 0:   //00000000
			SetValue(false);
			Changed = true;
			break;
		default:
			break;
		}
	}
	if (Mother && Changed)
	{
		Mother->OptimizeOrMakeLod();
	}
}

void FOctree::GenerateWorld(UWorldGenerator* WorldGenerator, uint8 Depth, TSet<FOctree*> &ToOptimize)
{
	if (this->Depth < Depth) return;
	bool Value = false;
	FColor Color;
	WorldGenerator->GetValueAndColor(Position, Value, Color);

	if (this->Depth == Depth)
	{
		SetValue(Value);
		SetColor(Color);
		ToOptimize.Add(this->Mother);
		return;
	}
	Subdivide();
	for (auto& child : Childs)
	{
		child->GenerateWorld(WorldGenerator, Depth, ToOptimize);
	}
	/*
	if (Value)
	{
		if (this->Depth == Depth)
		{
			SetValue(Value);
			SetColor(Color);

			OptimizeOrMakeLod();
			return;
		}

		Subdivide();
		for (auto& child : Childs)
		{
			child->GenerateWorld(WorldGenerator, Depth);
		}
	}
	else
	{
		SetValue(Value);
	}*/
}
