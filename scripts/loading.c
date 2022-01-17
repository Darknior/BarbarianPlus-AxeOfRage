void main()
{
	void	sprite;
	int		frame;
	int		time;
	if(!time){
		time=0;
		sprite = loadsprite("data/Bgs/Loading1.gif");
		}
	if(!frame){frame=2;}
	
	if(time%1==0)
	{
		if (frame==1){
		sprite = getglobalvar("Loading1");
		frame++;
		} else	if (frame==2){
		sprite = getglobalvar("Loading1");
		frame++;
		} else	if (frame==3){
		sprite = getglobalvar("Loading1");
		frame++;
		} else	if (frame==4){
		sprite = getglobalvar("Loading1");
		frame++;
		} else	if (frame==5){
		sprite = getglobalvar("Loading2");
		frame++;
		} else	if (frame==6){
		sprite = getglobalvar("Loading2");
		frame++;
		} else	if (frame==7){
		sprite = getglobalvar("Loading2");
		frame++;
		} else	if (frame==8){
		sprite = getglobalvar("Loading2");
		frame=1;
		}
	}

	drawsprite(sprite, 0, 0, 0, 1);
	time++;
}
