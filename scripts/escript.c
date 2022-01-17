//Script for enemies

#include "data/scripts/library/spawn.h"
#include "data/scripts/library/target.h"
#include "data/scripts/library/basic.h"

void faceOpp(int Flag)
{// Faces Opponent
    void self = getlocalvar("self");
    void Opp = getentityproperty(self, "opponent");

    if(Opp){
      int x = getentityproperty(self, "x");
      int Ox = getentityproperty(Opp, "x");

      if(Flag==1){
        if(Ox > x){
          changeentityproperty(self, "direction", 0);
        } else {
          changeentityproperty(self, "direction", 1);
        }
      } else {
        if(Ox > x){
          changeentityproperty(self, "direction", 1);
        } else {
          changeentityproperty(self, "direction", 0);
        }
      }
    }
}

void cancel(int RxMin, int RxMax, int RyMin, int RyMax, int RzMin, int RzMax, void Ani)
{// Attack interruption with range check
	void self 	= getlocalvar("self");
	void target = findtarget(self); //Get nearest player
	float x 	= getentityproperty(self, "x");
	float y 	= getentityproperty(self, "y");
	float z 	= getentityproperty(self, "z");
	int dir 	= getentityproperty(self, "direction");

	if(target!=NULL()){
		float Tx = getentityproperty(target, "x");
		float Ty = getentityproperty(target, "y");
		float Tz = getentityproperty(target, "z");
		float Disx = Tx - x;
		float Disy = Ty - y;
		float Disz = Tz - z;

		if(Disx >= RxMin && Disx <= RxMax && Disy >= RyMin && Disy <= RyMax && Disz >= RzMin && Disz <= RzMax && dir == 1) // Target within range on right facing?
		{
			executeanimation(self, openborconstant(Ani), 1); //Change the animation
		} else if(Disx >= -RxMax && Disx <= -RxMin && Disy >= RyMin && Disy <= RyMax && Disz >= -RzMax && Disz <= -RzMin && dir == 0) // Target within range on left facing?
		{
			executeanimation(self, openborconstant(Ani), 1); //Change the animation
		}
	}
}


void layer(int layer)
{// Set's enemy's layer
    void self = getlocalvar("self");
    changeentityproperty(self, "setlayer", layer);
}

void absentidle()
{// Go to IDLE if there are no players
    void self = getlocalvar("self");
    void P1 = getplayerproperty(0, "entity");
    void P2 = getplayerproperty(1, "entity");

    if(P1==NULL() && P2==NULL()){
      setidle(self, openborconstant("ANI_IDLE"));
    }
}

void dropgun(int Num)
{ // Drop bound gun based on number
    void self = getlocalvar("self");
    void Gun = getentityvar(self, Num);

    if(Gun!=NULL()){
      bindentity(Gun, NULL());
      changeentityproperty(Gun, "antigravity", 0.5);
    }
}

void killgun(int Num, int Flag)
{ // Kill bound gun based on number
    void self = getlocalvar("self");
    void Gun = getentityvar(self, Num);

    if(Gun!=NULL()){
      bindentity(Gun, NULL());
      if(Flag==1){
        damageentity(Gun, self, 1000, 0, openborconstant("ATK_NORMAL2"));
      } else {
        killentity(Gun);
      }
    }
}

void groundchange(void Ani)
{// Check altitude. If enemy is on ground, change animation!

    void self = getlocalvar("self");
    int y = getentityproperty(self,"a"); //Get bomb's altitude

    if( y <= 1 ){ // On ground?
      changeentityproperty(self, "animation", openborconstant(Ani));
    }
}

void mapchange(int Map)
{ // Animation changer
    void self = getlocalvar("self");

    changeentityproperty(self, "map", Map);
}

void spawnM(void Name, float dx, float dy, float dz)
{ // Spawn certain entity and matches its map with own's map
   void self = getlocalvar("self");
   int map = getentityproperty(self,"map");
   void Spawn;

   Spawn = spawn01(Name, dx, dy, 0);
   changeentityproperty(Spawn, "map", map);
}

void spawnGun(void Name, float dx, float dy, float dz, int Num)
{ // Spawn gun, store it and bind it
   void self = getlocalvar("self");
   void Spawn;

   Spawn = spawn01(Name, dx, dy, 0);
   setentityvar(self, Num, Spawn); // Stores spawned gun to be killed later
   bindentity(Spawn, self, dx, dz, dy, 0, 0); // Bind spawned gun
}

void spawnBody(void Name, float dx, float dy, float dz, int Num)
{ // Spawn body part, store it and set it as child
   void self = getlocalvar("self");
   void Spawn;

   Spawn = spawn01(Name, dx, dy, 0);
   setentityvar(self, Num, Spawn); // Stores spawned body to be killed later
   changeentityproperty(Spawn, "parent", self); //Set caller as parent.
}

void spawnMover(void Name, float dx, float dy, float dz, int Num)
{ // Spawn mover, store it and bind it
   void self = getlocalvar("self");
   int Aggro = getentityproperty(self,"aggression");
   void Spawn;

   Spawn = spawn01(Name, dx, dy, 0);
   changeentityproperty(Spawn, "aggression", Aggro);
   setentityvar(self, Num, Spawn); // Stores spawned gun to be killed later
   bindentity(self, Spawn, dx, dz, dy, 0, 0); // Bind self to spawned gun
}

void dasherP( float Vx, float Vy, float Vz , int Flip)
{// Dash with desired speed!
// Won't apply if enemy is in midair
    void self = getlocalvar("self");
    int dir = getentityproperty(self,"direction");
    int y = getentityproperty(self, "a");
    int b = getentityproperty(self, "base");

    if(dir==0 && Flip==1){ // Facing left?
      Vx = -Vx ;
    }

    if(y <= b){
      changeentityproperty(self, "velocity", Vx, Vz, Vy); //Move!
    }
}

void attack0(void Ani)
{// Attack interruption
    void self = getlocalvar("self");

    performattack(self, openborconstant(Ani)); //Attack!
}

void attack1(int RxMin, int RxMax, int RyMin, int RyMax, void Ani)
{// Attack interruption with range check
// Straight targetting
    void self = getlocalvar("self");
    void target = findtarget(self); //Get nearest player
    float x = getentityproperty(self, "x");
    float y = getentityproperty(self, "a");
    int dir = getentityproperty(self, "direction");

    if(target!=NULL()){
      float Tx = getentityproperty(target, "x");
      float Ty = getentityproperty(target, "a");
      float Disx = Tx - x;
      float Disy = Ty - y;

      if( Disx >= RxMin && Disx <= RxMax && Disy >= RyMin && Disy <= RyMax && dir == 1) // Target within range on right facing?
      {
        performattack(self, openborconstant(Ani)); //Change the animation
      } else if( Disx >= -RxMax && Disx <= -RxMin && Disy >= RyMin && Disy <= RyMax && dir == 0) // Target within range on left facing?
      {
        performattack(self, openborconstant(Ani)); //Change the animation
      }
    }
}

void attack2(int RMin, int RMax, void Ani, int Flip)
{// Attack interruption with range check
// Diagonal targetting
    void self = getlocalvar("self");
    void target = findtarget(self); //Get nearest player
    float x = getentityproperty(self, "x");
    float y = getentityproperty(self, "a");
    int dir = getentityproperty(self, "direction");

    if(target!=NULL()){
      float Tx = getentityproperty(target, "x");
      float Ty = getentityproperty(target, "a");
      float Disx = Tx - x;
      float Disy = Ty - y;

      if(Flip==1){
        Disy = -Disy;
      }

      if( Disx >= Disy + RMin && Disx <= Disy + RMax && dir == 1) 
      {
        performattack(self, openborconstant(Ani)); //Change the animation
      } else if( Disx >= -Disy - RMax && Disx <= -Disy - RMin && dir == 0)
      {
        performattack(self, openborconstant(Ani)); //Change the animation
      }
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

void attackF(void Ani)
{// Attack interruption if any player falls
    void self = getlocalvar("self");
    void target = findtarget(self); //Get nearest player

    if(target){
      int Fall = getentityproperty(target, "aiflag", "drop");

      if(Fall == 1){
        dasher(0, 0, 0);
        performattack(self, openborconstant(Ani)); //Change the animation
      }
    }
}

void HealAct(int HP, int Cost, void Ani)
{// Attack interruption if health falls below limit but have enough MP
// HP = Min health ratio
// Cost = Min MP
// Ani = animation to change to
    void self = getlocalvar("self");
    int MHealth = getentityproperty(self, "maxhealth");
    int Health = getentityproperty(self, "health");
    int MP = getentityproperty(self, "mp");

    if(Health*100 <= HP*MHealth && MP>=Cost){
      dasher(0, 0, 0);
      performattack(self, openborconstant(Ani)); //Change the animation
    }
}

void React(void Ani, int Ratio)
{// Changes animation if nearby opponent attacks
    void self = getlocalvar("self");
    void target = findtarget(self); //Get nearest player

    if(target && Ratio >= 50 - rand()%50){
      void PAni = getentityproperty(target, "animationID");

      if(PAni == openborconstant("ANI_ATTACK1") || PAni == openborconstant("ANI_ATTACK2") || PAni == openborconstant("ANI_ATTACK3") || PAni == openborconstant("ANI_JUMPATTACK") || PAni == openborconstant("ANI_RUNATTACK") || PAni == openborconstant("ANI_DUCKATTACK") || PAni == openborconstant("ANI_FREESPECIAL")){
        dasher(0, 0, 0);
        performattack(self, openborconstant(Ani));
      }
    }
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
