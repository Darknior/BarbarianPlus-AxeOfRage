void main()
{//
    if(openborvariant("in_menuscreen")==1 || openborvariant("in_titlescreen")){
      setglobalvar("F1", NULL());
      setglobalvar("F2", NULL());
      setglobalvar("F3", NULL());
      setglobalvar("F4", NULL());
      setglobalvar("Kalah1", NULL());
      setglobalvar("Kalah2", NULL());
      setglobalvar("Kalah3", NULL());
      setglobalvar("Noma", NULL());

      setglobalvar("WDrop1", NULL());
      setglobalvar("C1", 0);
      setglobalvar("Pilihs", 0);
      setglobalvar("Ack", 0);

      setglobalvar("Destine", NULL());
      setglobalvar("MariDed", NULL());
      setglobalvar("KranDed", NULL());
      setglobalvar("GortDed", NULL());

// Random starting seed from msMalik681
      int seed; //initialize seed.
      if(seed==NULL()){
        seed=1;
      } //start it off.
      seed++; //increment seed.
      srand(seed); //apply seed to random function.
    } else if(openborvariant("in_level")){ //  currently for testing
//      drawstring(150,60,2, getglobalvar("GortDed"));
//      drawstring(150,80,2, getglobalvar("MariDed"));
//      drawstring(150,100,2, getglobalvar("KranDed"));
//      void PName = getplayerproperty(0, "name");

//      drawstring(150,60,2, PName);
    }
}

void oncreate()
{
//    setindexedvar(1, 0);

    void Loading1; void Loading2; void Loading3; void Loading4; void Loading5; 
    
    Loading1 = loadsprite("data/bgs/loading/Loading1.png");
    Loading2 = loadsprite("data/bgs/loading/Loading2.png");

    setglobalvar("Loading1", Loading1);
    setglobalvar("Loading2", Loading2);
}

void ondestroy(){
    void Loading1 = getglobalvar("Loading1");
    void Loading2 = getglobalvar("Loading2");

    free(Loading1); free(Loading2);

    setglobalvar("Loading1", NULL());
    setglobalvar("Loading2", NULL());
}