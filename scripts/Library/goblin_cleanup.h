void goblinGate(int last, void headName)
{
    void self = getlocalvar("self");
    int mode = openborvariant("current_set");
    int i;
    void ent;
    float dx;
    float dz;
    if(mode != 3){
        updateframe(self, last);
        return;
    }
    // Replace the loose projectile by the head in the synchronized animation.
    // Enumerate live entities instead of retaining pointers to expired heads.
    if(headName != ""){
        for(i = openborvariant("ent_max") - 1; i >= 0; i--){
            ent = getentity(i);
            if(ent != NULL()){
                if(getentityproperty(ent, "name") == headName){
                    dx = getentityproperty(ent, "x") - getentityproperty(self, "x");
                    dz = getentityproperty(ent, "z") - getentityproperty(self, "z");
                    if(dx > -500 && dx < 500 && dz > -3 && dz < 3){
                        killentity(ent);
                    }
                }
            }
        }
    }
}

// The last invisible frame must release an enemy that still counts for the level.
// Player deaths remain owned by the engine so lives and respawning stay intact.
void goblinFinish(){
 void self=getlocalvar("self");int i;
 if(getentityproperty(self,"type")!=openborconstant("TYPE_ENEMY")){return;}
 for(i=openborvariant("ent_max")-1;i>=0;i--){
  void e=getentity(i);if(e && e!=self && getentityproperty(e,"parent")==self && getentityproperty(e,"type")==openborconstant("TYPE_NONE")){killentity(e);}
 }
 if(getglobalvar("F1")==self){setglobalvar("F1",NULL());}
 if(getglobalvar("F2")==self){setglobalvar("F2",NULL());}
 if(getglobalvar("F3")==self){setglobalvar("F3",NULL());}
 if(getglobalvar("F4")==self){setglobalvar("F4",NULL());}
 setglobalvar("dragon_victory_level", openborvariant("current_level") + 1);
 killentity(self);
}

// OpenBOR 7530's victory gate cannot start ANI_VICTORY for an idle player.
// Enter the victory pose only once every boss and enemy has actually disappeared.
void goblinRoundEnd(){
 if(!openborvariant("in_level") || openborvariant("numbosses")<=0 || openborvariant("bossescount")>0 || openborvariant("count_enemies")>0){return;}
 int i;int level=openborvariant("current_level")+1;
 if(getglobalvar("dragon_victory_level") != level){return;}
 for(i=0;i<4;i++){
  void p=getplayerproperty(i,"entity");
  if(p!=NULL()){if(getentityproperty(p,"health")>0 && getentityproperty(p,"a")<=0 && getentityvar(p,"round_victory_level")!=level){
   setentityvar(p,"round_victory_level",level);
   if(getentityproperty(p,"animvalid",openborconstant("ANI_VICTORY"))){
    changeentityproperty(p,"velocity",0,0,0);changeentityproperty(p,"aiflag","ducking",0);changeentityproperty(p,"aiflag","falling",0);changeentityproperty(p,"aiflag","jumping",0);
    setidle(p,openborconstant("ANI_VICTORY"),1);changeentityproperty(p,"aiflag","idling",0);
   }
  }}
 }
}
