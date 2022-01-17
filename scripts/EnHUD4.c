// Custom life icon display script
void main()
{
	void self = getlocalvar("self"); //Get calling entity.
	void vSpawn; //Spawn object.
	int  vAlias = getentityproperty(self, "name");

	clearspawnentry(); //Clear current spawn entry.
	setspawnentry("name", "EnemyHUD4");
	
	vSpawn = spawn(); //Spawn in entity.

	changeentityproperty(vSpawn, "parent", self); //Set caller as parent.
	changeentityproperty(vSpawn, "name", vAlias); //Set name.
	changeentityproperty(vSpawn, "position", 548, 38, 0);
	setglobalvar("F4", self);
}
