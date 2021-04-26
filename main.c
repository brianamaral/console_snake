#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>

//SNAKE GAME
struct player{
	int position_x;
	int position_y;
	int x_dir;
	int y_dir;
};

struct food{
	int position_x;
	int position_y;
	bool spawned;	
};

void print_grind(char grind[15][30],struct player *player,struct food food,int size){
	int i;
	int j;
	int k;
	system("cls");
	printf("-------------------------Score: %d--------------------------",size);
	for(i = 0; i < 15;i++){
		
		printf("\n");
		for(j = 0; j < 30; j++){
			
			if(i == food.position_x && j == food.position_y && food.spawned){
				grind[i][j] = 'F';
			}
			
			for(k = 0; k < size; k++){
				if(i == player[k].position_x && j == player[k].position_y){
					grind[i][j] = 'o'; 			
				}	
			}
			printf(" %c",grind[i][j]);
			grind[i][j] = ' '; 	
				
		}
	}
}

bool facing_up(struct player* player){
	if(player->x_dir == -1){return true;}
}

bool facing_down(struct player *player){
	if(player->x_dir == 1){return true;}
}

bool facing_left(struct player *player){
	if(player->y_dir == -1){return true;}
}

bool facing_right(struct player *player){
	if(player->y_dir == 1){return true;}
}



void control_player(struct player *player){
		if(kbhit()){
			int key = getch();
			if(facing_up(player) || facing_down(player)){
				if(key == 97){
					player->y_dir = -1;
					player->x_dir = 0;
				}else if(key == 100){
					player->y_dir = 1;
					player->x_dir = 0;
				} 
				
			}else if(facing_left(player) || facing_right(player)){
				if(key == 119){
					player->x_dir = -1;
					player->y_dir = 0;	
				}else if(key == 115){
					player->x_dir = 1;
					player->y_dir = 0;
				} 	
			}
			
		}		
	}
void move_player(struct player *player,int size){
	
	int i;
	int past_x_pos = player[0].position_x;
	int past_y_pos = player[0].position_y;
	int temp_x,temp_y;
	for(i = 1; i < size; i++){
		
		temp_x = player[i].position_x;
		temp_y = player[i].position_y;  
		 	
		player[i].position_x = past_x_pos;
		player[i].position_y = past_y_pos;
		
		past_x_pos = temp_x;
		past_y_pos = temp_y;			
	}
	player[0].position_x += player[0].x_dir;
	player[0].position_y += player[0].y_dir;
	
}
void wait(int miliseconds ){
	unsigned int wait_time = clock() + miliseconds;
	while(clock() < wait_time);
}

int rand_num(int max,int min){
	return (rand() % (max + 1 - min) + min);
}

void food_position(struct food *food){
	if(food->spawned == false){
		food->position_x = rand_num(14,0);
		food->position_y = rand_num(29,0);
		food->spawned = true;
	}
}

int increase_player_size(int size){
	size +=1;
	return size;
}

int verify_colisions(struct player *player,struct food *food,int size){
	bool same_x = player[0].position_x == food->position_x;
	bool same_y = player[0].position_y == food->position_y;
	
	if( same_x && same_y ){
		size += 1;
		food->spawned = false;	
	} return size;
}

bool game_over(struct player * player,int size){
	int i;
	
	for(i = 1; i < size; i++){
		if(player[i].position_x == player[0].position_x && player[i].position_y == player[0].position_y){
			return true;
			
		}
	}
	
	if(player[0].position_x > 14 || player[0].position_y > 29 || player[0].position_x < 0 || player[0].position_y < 0){
		return true;
		
	}else{
		return false;
	}
}



int main(int argc, char *argv[]) {
	
	srand(time(0));
	int height = 15;
	int width = 30;
	char grind[15][30];
	int size = 1;
	int *sizeP = &size;
	struct player player[70];
	struct player p1;
	p1.position_x = 10;
	p1.position_y = 0;
	p1.x_dir = 0;
	p1.y_dir = 1;
	player[0] = p1;
	//player[1] = p1;
		
	struct food food,*foodP;
	foodP = &food;
	int test = 1;
	while(true){
		if(game_over(player,size)){
			size = 1;
			player[0].position_x = 5;
			player[0].position_y = 0;
			player[0].x_dir = 0;
			player[0].y_dir = 1;
			int i,j;
			system("cls");
			printf("-------------------------GAME OVER--------------------------\n");
			for(i = 0; i < 15; i++){
				printf("\n");
				for(j = 0; j < 30;j++){
					wait(5);
					printf(" #");
				}
			}
			wait(1000);
		}
		size = verify_colisions(player,foodP,size);
		food_position(foodP);		
		control_player(player);
		move_player(player,size);
		
		print_grind(grind,player,food,size);			
		wait(1000/15);			
	}
}
