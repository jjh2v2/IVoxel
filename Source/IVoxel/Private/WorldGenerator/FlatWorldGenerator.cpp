#include "FlatWorldGenerator.h"

UFlatWorldGenerator::UFlatWorldGenerator()
{

}
void UFlatWorldGenerator::GetValueAndColor(FIntVector Location, bool &Value, FColor &Color)
{
	if (Location.Z < 10)
	{
		Value = true;
		Color = FColor(1, 0, 0, 1);
	} 
	else
	{

	}
}