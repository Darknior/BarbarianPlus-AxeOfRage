#import "data/scripts/library/spawn.h"
#import "data/scripts/library/basic.h"

void keyint(void Ani, int Frame, void Key, int Hflag)
{// Change current animation if proper key is pressed or released
// Animation is changed to attack mode

    void self = getlocalvar("self");
    int Dir = getentityproperty(self, "direction");
    int iPIndex = getentityproperty(self,"playerindex"); //Get player index
    void iRKey;

      if (Key=="U"){ //Up Required?
        iRKey = playerkeys(iPIndex, 0, "moveup"); // "Up"
      } else if (Key=="D"){ //Down Required?
        iRKey = playerkeys(iPIndex, 0, "movedown"); // "Down"
      } else if (Key=="L"){ //Left Required?
        iRKey = playerkeys(iPIndex, 0, "moveleft"); // "Left"
      } else if (Key=="R"){ //Right Required?
        iRKey = playerkeys(iPIndex, 0, "moveright"); // "Right"
      } else if (Key=="F"){ //Forward Required?
        if (Dir == 0){ // Facing Left?
          iRKey = playerkeys(iPIndex, 0, "moveleft"); // "Left"
        } else { // Facing Right
          iRKey = playerkeys(iPIndex, 0, "moveright"); // "Right"
        }
      } else if (Key=="B"){ //Backward Required?
        if (Dir == 1){ // Facing Right?
          iRKey = playerkeys(iPIndex, 0, "moveleft"); // "Left"
        } else { // Facing Left
          iRKey = playerkeys(iPIndex, 0, "moveright"); // "Right"
        }
      } else if (Key=="J"){ //Jump Required?
        iRKey = playerkeys(iPIndex, 0, "jump"); // "Jump"
      } else if (Key=="A"){ //Attack Required?
        iRKey = playerkeys(iPIndex, 0, "attack"); // "Attack"
      } else if (Key=="A2"){ //Attack Required?
        iRKey = playerkeys(iPIndex, 0, "attack2"); // "Attack2"
      } else if (Key=="S"){ //Special Required?
        iRKey = playerkeys(iPIndex, 0, "special"); // "Special"
      }

      if (Hflag==1){ //Not holding the button case?
        iRKey = !iRKey; //Take the opposite condition
      }

      if (iRKey){
        if (Ani=="ANI_IDLE"){ // Going idle?
          setidle(self, openborconstant("ANI_IDLE")); //Be idle!
        } else {
          performattack(self, openborconstant(Ani)); //Change the animation
        }
        updateframe(self, Frame); //Change frame
      }
}

void keymove(float Vx)
{// Move hero if direction button is pressed
      void self = getlocalvar("self");
      int iPIndex = getentityproperty(self,"playerindex"); //Get player index
	float xdir = 0;

      if (playerkeys(iPIndex, 0, "moveleft")){// Left is pressed?
	  xdir = -Vx;
	} else if(playerkeys(iPIndex, 0, "moveright")){// Right is pressed?
	  xdir = Vx;
      }

	changeentityproperty(self, "velocity", xdir);
}

void PlayMap()
{// Use map defined on level
    void self = getlocalvar("self");
    int PIndex = getentityproperty(self,"playerindex") + 1; //Get player index + 1
    int Remap = getglobalvar("PMap" + PIndex);

    if(Remap != NULL()){
      changeentityproperty(self, "map", Remap);
    }
}

void spawnM(void Name, float dx, float dy, float dz)
{ // Spawn certain entity and matches its map with own's map
   void self = getlocalvar("self");
   int map = getentityproperty(self,"map");
   void Spawn;

   Spawn = spawn01(Name, dx, dy, dz);
   changeentityproperty(Spawn, "map", map);
}

void bbounce(void Ani){
	// Check altitude. If projectile is on ground, change animation!
    void self = getlocalvar("self"); // Get self
    int x = getentityproperty(self,"x"); // Get self x pos
    int z = getentityproperty(self,"z"); // Get self z pos
    int y = getentityproperty(self,"a"); // Get self altitude
    int H = checkhole(x,z,y-100); // Checkhole

    if( y <= 1 && H != 1)
	{ // On ground but not on hole?
      changeentityproperty(self, "animation", openborconstant(Ani));
	  // Change to desired animation
    }
}

void tosser3(void Bomb, float dx, float dy, float dz, float Vx, float Vy, float Vz)
{// Tossing bomb with desired speed and base 0 (SIGNAL BOTTLE)
	void self 		= getlocalvar("self");
	int Direction 	= getentityproperty(self, "direction");
	int x 			= getentityproperty(self, "x");
	int y 			= getentityproperty(self, "a");
	int z 			= getentityproperty(self, "z");
	void Shot;

	if(Direction == 0){ //Is entity facing left?                  
		dx = -dx; //Reverse X direction to match facing
	}

	Shot = projectile(Bomb, x+dx, z+dz, y+dy, Direction, 0, 0, 0);
	tossentity(Shot, Vy, Vx, Vz);
	changeentityproperty(Shot, "speed", Vx);
	changeentityproperty(Shot, "projectile", 0); 
	changeentityproperty(Shot, "base", 0);
	changeentityproperty(Shot, "parent", self);
	return Shot;
}

void walk_aa()
{
	 void self = getlocalvar("self");
	 void target = findtarget(self);
	 if(target != NULL() )
	 {
		 int aid = getentityproperty(target, "animationid");
		 if(aid==openborconstant("ANI_RUNJUMPATTACK") || aid==openborconstant("ANI_JUMPATTACK"))
		 {
			 if(getentityproperty(target, "z") > getentityproperty(self, "z") )
			 {changeentityproperty(self, "velocity", getentityproperty(self, "xdir"), -0.1, getentityproperty(self, "tossv"));}
			 else
			 {changeentityproperty(self, "velocity", getentityproperty(self, "xdir"), 0.1, getentityproperty(self, "tossv"));}
		 }
	 }
}


void FindDoor(int Rx, int RyMin, int RyMax, void Ani)
{ // Finds door within specified range then changes animation if door is found
// Rx = Maximum x distance
// RyMin = Minimum y distance; RyMax = Maximum y distance
    void self = getlocalvar("self");
    float x = getentityproperty(self, "x");
    float y = getentityproperty(self, "y");

    void vEntity;                                       //Target entity placeholder.
    int  iEntity;                                       //Entity enumeration holder.
    int  iName;                                         //Entity name.
    int  iMax      = openborvariant("count_entities");  //Entity count.
    float Tx; float Ty;

    //Enumerate and loop through entity collection.
    for(iEntity=0; iEntity<iMax; iEntity++){
      vEntity = getentity(iEntity);                 //Get target entity from current loop.
      iName   = getentityproperty(vEntity, "defaultname"); //Get target name

      if(iName == "Door"){
        Tx = getentityproperty(vEntity, "x");
        Ty = getentityproperty(vEntity, "y");

        if(x >= Tx-Rx && x <= Tx+Rx && y >= Ty+RyMin && y <= Ty+RyMax){
          changeentityproperty(self, "position", Tx);
          changeentityproperty(self, "animation", openborconstant(Ani));
        }
      }
    }
}

void EnterDoor(int Rx, int RyMin, int RyMax)
{ // Finds door within specified range then jumps to defined branch if door is found
// Rx = Maximum x distance
// RyMin = Minimum y distance; RyMax = Maximum y distance
    void self = getlocalvar("self");
    float x = getentityproperty(self, "x");
    float y = getentityproperty(self, "y");

    void vEntity;                                       //Target entity placeholder.
    int  iEntity;                                       //Entity enumeration holder.
    int  iName;                                         //Entity name.
    int  iAlias;                                        //Entity alias.
    int  iMax      = openborvariant("count_entities");  //Entity count.
    float Tx; float Ty;

    //Enumerate and loop through entity collection.
    for(iEntity=0; iEntity<iMax; iEntity++){
      vEntity = getentity(iEntity);                 //Get target entity from current loop.
      iName   = getentityproperty(vEntity, "defaultname"); //Get target name

      if(iName == "Door"){
        Tx = getentityproperty(vEntity, "x");
        Ty = getentityproperty(vEntity, "y");

        if(x >= Tx-Rx && x <= Tx+Rx && y >= Ty+RyMin && y <= Ty+RyMax){
          iAlias = getentityproperty(vEntity, "name");

          jumptobranch(iAlias, 1);
        }
      }
    }
}


void shootname(void Shot, float dx, float dy, float dz) {
// Shooting name with same palette and always faces right
 void self = getlocalvar("self");
 int Direction = getentityproperty(self, "direction");
 int Map = getentityproperty(self, "map");
 int x = getentityproperty(self, "x");
 int y = getentityproperty(self, "y");
 int z = getentityproperty(self, "z");
 void vShot;

 if(Direction == 0){ //Is entity facing left?
   dx = dx; //Keep X direction to the right
 }

 vShot = projectile(Shot, x+dx, z+dz, y+dy, 1, 0, 0, Map);

 return vShot;
}

void DeathCode(int Flag)
{ // Sets death code depending of set flag
    if(Flag == 2){
      setglobalvar("MariDed", "S");
    } else if(Flag == 3){
      setglobalvar("KranDed", "S");
    } else {
      setglobalvar("GortDed", "S");
    }
}
