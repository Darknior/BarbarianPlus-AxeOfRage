void hoppingStart(int number){
 void e=getlocalvar("self");float base=getentityproperty(e,"base");float a=getentityproperty(e,"a");
 if(a<base-1 || checkhole(getentityproperty(e,"x"),getentityproperty(e,"z"),base-100)){setentityvar(e,"hop_active",0);return;}
 void model=getentityproperty(e,"defaultname");
 if(model=="Dragon" || model=="DragonE"){
  if(number==1){setentityvar(e,"dragon_hop_dir",getentityproperty(e,"direction"));}
  else{changeentityproperty(e,"direction",getentityvar(e,"dragon_hop_dir"));}
 }
 float vx=0.5;if(!getentityproperty(e,"direction")){vx=-vx;}
 setentityvar(e,"hop_active",1);setentityvar(e,"hop_number",number);setentityvar(e,"hop_since",openborvariant("elapsed_time"));setentityvar(e,"hop_air",0);
 changeentityproperty(e,"position",getentityproperty(e,"x"),getentityproperty(e,"z"),base+1);
 changeentityproperty(e,"velocity",vx,0,2.1);changeentityproperty(e,"aiflag","jumping",1);changeentityproperty(e,"aiflag","falling",0);changeentityproperty(e,"takeaction","common_jump");
}
void hoppingContact(){changeentityproperty(getlocalvar("self"),"attackid",0);}
void hoppingWait(int frame){
 void e=getlocalvar("self");if(getentityvar(e,"hop_active")==1){updateframe(e,frame);}
}
void hoppingEnd(){
 void e=getlocalvar("self");float a=getentityproperty(e,"a");float base=getentityproperty(e,"base");setentityvar(e,"hop_active",0);
 if(a>=base && a<=base+1 && !checkhole(getentityproperty(e,"x"),getentityproperty(e,"z"),base-100)){
  changeentityproperty(e,"position",getentityproperty(e,"x"),getentityproperty(e,"z"),base);changeentityproperty(e,"velocity",0,0,0);changeentityproperty(e,"aiflag","jumping",0);changeentityproperty(e,"aiflag","falling",0);
 }else{changeentityproperty(e,"velocity",0,0,getentityproperty(e,"tossv"));}
}
void hoppingUpdate(){
 int i;for(i=0;i<openborvariant("ent_max");i++){
  void e=getentity(i);if(!e){continue;}if(getentityvar(e,"hop_active")!=1){continue;}
  void model=getentityproperty(e,"defaultname");
  if(model=="Dragon" || model=="DragonE"){if(getentityvar(e,"dragon_hop_dir")!=NULL()){changeentityproperty(e,"direction",getentityvar(e,"dragon_hop_dir"));}}
  int ani=getentityproperty(e,"animationid");
  if(getentityproperty(e,"health")<=0 || (ani!=openborconstant("ANI_FREESPECIAL5") && ani!=openborconstant("ANI_FOLLOW22") && ani!=openborconstant("ANI_FOLLOW23") && ani!=openborconstant("ANI_JUMPLAND"))){setentityvar(e,"hop_active",0);continue;}
  float a=getentityproperty(e,"a");float base=getentityproperty(e,"base");
  if(a>base+0.5){changeentityproperty(e,"takeaction","common_jump");changeentityproperty(e,"aiflag","jumping",1);}
  if(a>base+2){setentityvar(e,"hop_air",1);}
  if(a<=base+0.5 && getentityvar(e,"hop_air")){
   if(checkhole(getentityproperty(e,"x"),getentityproperty(e,"z"),base-100)){setentityvar(e,"hop_active",0);continue;}
   int hop=getentityvar(e,"hop_number");setentityvar(e,"hop_air",0);
   changeentityproperty(e,"position",getentityproperty(e,"x"),getentityproperty(e,"z"),base);changeentityproperty(e,"velocity",0,0,0);changeentityproperty(e,"aiflag","jumping",0);changeentityproperty(e,"aiflag","falling",0);
   setentityvar(e,"hop_active",2);
   if(hop==1){performattack(e,openborconstant("ANI_FOLLOW22"));}
   else if(hop==2){performattack(e,openborconstant("ANI_FOLLOW23"));}
   else{setentityvar(e,"hop_active",0);performattack(e,openborconstant("ANI_FOLLOW24"));}
  }
 }
}
