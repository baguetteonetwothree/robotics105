int square_dist = 132;
// north -> 0, east -> 1, south -> 2, west -> 3
int facing = 0;

//creating map within program
//if wall present then val will be 1 else 0
struct mazeMap {
  int north;
  int east;
  int south;
  int west;
};

struct mazeMap cells[4][4];

//can't init any other way
void init(){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j< 4; j++){
			cells[i][j].north = 0;
			cells[i][j].east = 0;
			cells[i][j].south = 0;
			cells[i][j].west = 0;
		}
	}
}
