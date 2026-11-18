// A2 airborne spin: raised start, active descent, then a grounded finisher.
void aerialSpinStart(int forward){
 void e=getlocalvar("self");float base=getentityproperty(e,"base");float a=getentityproperty(e,"a");float x=getentityproperty(e,"x");float z=getentityproperty(e,"z");float vx=0;
 if(a<base){return;}
 a+=8;if(a<base+28){a=base+28;}
 if(forward){vx=1.25;if(getentityproperty(e,"direction")==0){vx=-vx;}}
 changeentityproperty(e,"position",x,z,a);changeentityproperty(e,"velocity",vx,0,1.8);
 changeentityproperty(e,"aiflag","jumping",1);changeentityproperty(e,"aiflag","falling",0);changeentityproperty(e,"takeaction","common_jump");
 setentityvar(e,"spin_active",1);setentityvar(e,"spin_descending",0);setentityvar(e,"spin_since",openborvariant("elapsed_time"));
}
void aerialSpinDescend(){
 void e=getlocalvar("self");
 if(!getentityvar(e,"spin_descending")){setentityvar(e,"spin_descending",1);changeentityproperty(e,"velocity",getentityproperty(e,"xdir"),0,-1.2);}
}
void aerialSpinWait(){
 void e=getlocalvar("self");if(getentityproperty(e,"a")>getentityproperty(e,"base")+0.5){updateframe(e,2);}
}
void aerialSpinEnd(){setentityvar(getlocalvar("self"),"spin_active",0);}
void aerialSpinUpdate(){
 int i;for(i=0;i<openborvariant("ent_max");i++){
  void e=getentity(i);if(e==NULL()){continue;}
  if(getentityvar(e,"spin_active")!=1){continue;}
  if(getentityproperty(e,"health")<=0){setentityvar(e,"spin_active",0);continue;}
  int ani=getentityproperty(e,"animationid");
  if(ani!=openborconstant("ANI_FREESPECIAL3") && ani!=openborconstant("ANI_FREESPECIAL4") && ani!=openborconstant("ANI_JUMPLAND")){
   setentityvar(e,"spin_active",0);continue;
  }
  float a=getentityproperty(e,"a");float base=getentityproperty(e,"base");
  if(a>base+0.5 && getentityproperty(e,"tossv") < -1.2){changeentityproperty(e,"velocity",getentityproperty(e,"xdir"),0,-1.2);}
  if(a<=base+0.5 && openborvariant("elapsed_time")>getentityvar(e,"spin_since")+8){
   if(checkhole(getentityproperty(e,"x"),getentityproperty(e,"z"),base-100)){setentityvar(e,"spin_active",0);continue;}
   setentityvar(e,"spin_active",2);changeentityproperty(e,"position",getentityproperty(e,"x"),getentityproperty(e,"z"),base);changeentityproperty(e,"velocity",0,0,0);
   changeentityproperty(e,"aiflag","jumping",0);changeentityproperty(e,"aiflag","falling",0);changeentityproperty(e,"attackid",0);performattack(e,openborconstant("ANI_FOLLOW21"));
  }
 }
}
