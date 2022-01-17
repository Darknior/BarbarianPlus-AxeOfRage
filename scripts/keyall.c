void main()
{
    int iPlIndex = getlocalvar("player"); //Get calling player
    void vSelf = getplayerproperty(iPlIndex , "entity"); //Get calling entity
    void vAniID = getentityproperty(vSelf,"animationID"); //Get current animation ID
//    void vAniPos = getentityproperty(vSelf, "animpos"); //Get current animation frame
    int iDir = getentityproperty(vSelf, "direction");  //Get current facing direction

    void iUp = playerkeys(iPlIndex, 1, "moveup"); // New key status of "Up"
    void iDown = playerkeys(iPlIndex, 1, "movedown"); // New key status of "Down"
    void iLeft = playerkeys(iPlIndex, 1, "moveleft"); // New key status of "Left"
    void iRight = playerkeys(iPlIndex, 1, "moveright"); // New key status of "Right"
    void iJump = playerkeys(iPlIndex, 1, "jump"); //New key status of "Jump"
    void iSpecial = playerkeys(iPlIndex, 1, "Special"); //New key status of "Special"
    void iAttack = playerkeys(iPlIndex, 1, "attack"); //New key status of "Attack"
    void iAttack2 = playerkeys(iPlIndex, 1, "attack2"); // New key status of "Attack 2"
    void iAttack3 = playerkeys(iPlIndex, 1, "attack3"); // New key status of "Attack 3"
    void iAttack4 = playerkeys(iPlIndex, 1, "attack4"); // New key status of "Attack 4"

    void iUpR = playerkeys(iPlIndex, 2, "moveup"); // Release status of "Up"
    void iDownR = playerkeys(iPlIndex, 2, "movedown"); // Release status of "Down"
    void iLeftR = playerkeys(iPlIndex, 2, "moveleft"); // Release status of "Left"
    void iRightR = playerkeys(iPlIndex, 2, "moveright"); // Release status of "Right"
    void iAttackR = playerkeys(iPlIndex, 2, "attack");// Release status of "Attack"
    void iAttack2R = playerkeys(iPlIndex, 2, "attack2");// Release status of "Attack2"
    void iAttack3R = playerkeys(iPlIndex, 2, "attack3");// Release status of "Attack3"
    void iAttack4R = playerkeys(iPlIndex, 2, "attack4");// Release status of "Attack4"
    void iJumpR = playerkeys(iPlIndex, 2, "jump");// Release status of "Jump"
    void iStartR = playerkeys(iPlIndex, 2, "start");// Release status of "Start"

    void iDownH = playerkeys(iPlIndex, 0, "movedown");
    void iUpH = playerkeys(iPlIndex, 0, "moveup");
    void iLeftH = playerkeys(iPlIndex, 0, "moveleft");
    void iRightH = playerkeys(iPlIndex, 0, "moveright");

// Movement event capture
    if(iLeft){ //Left is pressed?
      setglobalvar(iPlIndex+"X", -1);
    } else if(iRight){ //Right is pressed?
      setglobalvar(iPlIndex+"X", 1);
    }
    if(iUp){ //Up is pressed?
      setglobalvar(iPlIndex+"Y", 1);
    } else if(iDown){ //Down is pressed?
      setglobalvar(iPlIndex+"Y", -1);
    }

    if(iLeftR || iRightR){ //Left or Right is released?
      setglobalvar(iPlIndex+"X", 0);
    }
    if(iUpR || iDownR){ //Up or Down is released?
      setglobalvar(iPlIndex+"Y", 0);
    }

// Action event capture
    if(iAttack){ //Attack is pressed?
      setglobalvar(iPlIndex+"A", 1);
    }
    if(iAttackR){ //Attack is released?
      setglobalvar(iPlIndex+"A", NULL());
    }

    if(iAttack2){ //Attack2 is pressed?
      setglobalvar(iPlIndex+"A2", 1);
    }
    if(iAttack2R){ //Attack2 is released?
      setglobalvar(iPlIndex+"A2", NULL());
    }

    if(iAttack3){ //Attack3 is pressed?
      setglobalvar(iPlIndex+"A3", 1);
    }
    if(iAttack3R){ //Attack3 is released?
      setglobalvar(iPlIndex+"A3", NULL());
    }

    if(iAttack4){ //Attack4 is pressed?
      setglobalvar(iPlIndex+"A4", 1);
    }
    if(iAttack4R){ //Attack4 is released?
      setglobalvar(iPlIndex+"A4", NULL());
    }

    if(iJump){ //Jump is pressed?
      setglobalvar(iPlIndex+"J", 1);
    }
    if(iJumpR){ //Jump is released?
      setglobalvar(iPlIndex+"J", NULL());
    }

//Move while jumping
    if(vAniID == openborconstant("ANI_JUMP")){ //Jumping?
      if(iLeftR || iRightR){ //Left or Right released?
        if(!iLeftH && !iRightH){ //Left and Right not pressed?
          changeentityproperty(vSelf, "velocity", 0);
        }
      } else if(iLeft){ //Left pressed?
        changeentityproperty(vSelf, "direction", 0);
        changeentityproperty(vSelf, "velocity", -1);
        changeplayerproperty(vSelf, "playkeys", 0);
      } else if(iRight){ //Right pressed?
        changeentityproperty(vSelf, "direction", 1);
        changeentityproperty(vSelf, "velocity", 1);
        changeplayerproperty(vSelf, "playkeys", 0);
      }
    }

//Move while runjumping
    if(vAniID == openborconstant("ANI_RUNJUMP") ){ //Jumping?
      if(iLeftR || iRightR){ //Left or Right released?
        if(!iLeftH && !iRightH){ //Left and Right not pressed?
          changeentityproperty(vSelf, "velocity", 0);
        }
      } else if(iLeft){ //Left pressed?
        changeentityproperty(vSelf, "direction", 0);
        changeentityproperty(vSelf, "velocity", -1.6);
        changeplayerproperty(vSelf, "playkeys", 0);
      } else if(iRight){ //Right pressed?
        changeentityproperty(vSelf, "direction", 1);
        changeentityproperty(vSelf, "velocity", 1.6);
        changeplayerproperty(vSelf, "playkeys", 0);
      }
    }

//Jumping attack
    if(vAniID == openborconstant("ANI_FREESPECIAL6")){ //Static Jumping?
      if(iAttack){ //Attack pressed?
        changeentityproperty(vSelf, "animation", openborconstant("ANI_JUMPATTACK"));
      } else if(iAttack2){ //Attack2 pressed?
        changeentityproperty(vSelf, "animation", openborconstant("ANI_FREESPECIAL3"));
      }
    } else if(vAniID == openborconstant("ANI_FOLLOW6")){ //Forward Jumping?
      if(iAttack){ //Attack pressed?
        changeentityproperty(vSelf, "animation", openborconstant("ANI_JUMPFORWARD"));
      } else if(iAttack2){ //Attack2 pressed?
        changeentityproperty(vSelf, "animation", openborconstant("ANI_FREESPECIAL4"));
      }
    }

//Flip while ducking
    if(vAniID == openborconstant("ANI_DUCK") ){ //Ducking?
      if(iLeft){ //Left pressed?
        changeentityproperty(vSelf, "direction", 0);
      } else if(iRight){ //Right pressed?
        changeentityproperty(vSelf, "direction", 1);
      }
    }
}