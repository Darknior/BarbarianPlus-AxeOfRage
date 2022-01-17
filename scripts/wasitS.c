#import "data/scripts/library/spawn.h"
#import "data/scripts/library/basic.h"

void LeaderFind()
{//Finds fighter with highest health
    void F1 = getglobalvar("F1");
    void F2 = getglobalvar("F2");
    int HP1; int HP2; int Co1;

    HP1 = getentityproperty(F1, "health");
    HP2 = getentityproperty(F2, "health");

    Co1 = Compare(HP1, HP2);

    if(Co1 == HP1){
      return F1;
    } else {
      return F2;
    }
}

void DifitFind(int Num)
{//Checks if defined fighter is defeated
// Num = Fighter's Number
    void F = getglobalvar("F" + Num);
    int HP = getentityproperty(F, "health");

    if(HP <= 0){
      return 1;
    } else {
      return 0;
    }
}

void Desid()
{//Collects the order of defeated fighters
    int D1 = DifitFind(1);
    int D2 = DifitFind(2);
    int Sign = 0;

    if(D1==1){
      Sign = 1;
    } else if(D2==1){
      Sign = 1;
    }

    return Sign;
}

void FiTung()
{//Counts number of active fighters
    int Count = 0;
    void D1 = getglobalvar("F1");
    void D2 = getglobalvar("F2");

    if(D1){
      Count++;
    }

    if(D2){
      Count++;
    }

    return Count;
}

void Tentuk()
{//Gets number of defeated fighters
//For 1 player only
    int Count = FiTung();
    void F2 = getglobalvar("F2");
    int D2 = 0;
    char Sign = "U";

    if(F2){
      D2 = DifitFind(2);
    }

    if(D2 == Count-1){
      Sign = "E";
    }

    return Sign;
}

void ShowTeks(char Tex, int Index, int f, int Dx, int Dy, int Dz)
{// Shows teks
    void self = getlocalvar("self");
    int x = getentityproperty(self,"x"); 
    int y = getentityproperty(self,"a");
    int z = getentityproperty(self,"z");
    int XPos = openborvariant("xpos");
    int YPos = openborvariant("ypos");

    settextobj(Index, x+Dx-XPos, z-y-Dy-YPos, f, Dz, Tex);
}

void Compare(int A, int B)
{//Compares two values and returns the highest value
    if(A > B){
      return A;
    } else {
      return B;
    }
}