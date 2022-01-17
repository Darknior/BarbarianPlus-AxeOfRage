#include "data/scripts/library/spawn.h"

void suicide()
{ // Suicide!!
    void self = getlocalvar("self");

    killentity(self); //Suicide!
}

void spawnM(void vName, float fX, float fY, float fZ)
{//Spawns entity next to caller with same remap as spawner's.
	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
	int  iMap = getentityproperty(self, "map");
	
	vSpawn = spawn01(vName, fX, fY, fZ); //Spawn in entity.

	changeentityproperty(vSpawn, "map", iMap);
}

void spawnPM(void vName, float fX, float fY, float fZ)
{//Spawns entity next to caller with same remap as spawner's.
// Also sets spawner's parent as parent of spawned entity
	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
        int Par = getentityproperty(self, "parent");
	int iMap = getentityproperty(self, "map");
	
	vSpawn = spawn01(vName, fX, fY, fZ); //Spawn in entity.

	changeentityproperty(vSpawn, "map", iMap);
	changeentityproperty(vSpawn, "parent", Par);
}
