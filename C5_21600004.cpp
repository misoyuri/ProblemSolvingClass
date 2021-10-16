#include <iostream>

#define MAX_SIZE 8

using namespace std;

struct Pair{
    int w = 0;
    int h = 0;
};

int n = 0;
int MAP_SIZE = 0;
int **map;
bool poly[5][4][4]{false, };
Pair pairs[5];

int square[MAX_SIZE] = {1, 4, 9, 16, 25, 36, 49, 64};

bool is_terminated = false;

void print_map_exit(){
    for(int i = 0; i < MAP_SIZE; i++) {
        for(int j = 0; j < MAP_SIZE-1; j++){
            printf("%d ", map[i][j]);
        }
        printf("%d\n", map[i][MAP_SIZE-1]);
    }
}

bool check_square(){
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            if(map[i][j] == 0){
                return false;
            }
        }
    }

    return true;
}

void del_poly(int idx_poly, int map_h, int map_w){
    for(int h = 0; h < pairs[idx_poly].h; h++){
        for(int w = 0; w < pairs[idx_poly].w; w++){
            if(poly[idx_poly][h][w]){
                map[h + map_h][w + map_w] =  0;
            }
        }
    }    
}

bool assign_poly(int idx_poly, int map_y, int map_x){
    int height = pairs[idx_poly].h;
    int width = pairs[idx_poly].w;

    for(int h = 0; h < height; h++){
        if(MAP_SIZE <= h + map_y) return false;
        for(int w = 0; w < width; w++){
            if(MAP_SIZE <= w + map_x) return false;
            if(map[h + map_y][w + map_x] != 0 && poly[idx_poly][h][w] == true ) return false;
        }
    }

    for(int h = 0; h < height; h++){
        for(int w = 0; w < width; w++){
            if(poly[idx_poly][h][w]){
                map[h + map_y][w + map_x] =  idx_poly + 1;
            }
        }
    }

    return true;
}

void solve(int idx_poly){
    if(idx_poly >= n) return;
    if(is_terminated) return;

    bool is_signed = false;

    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            is_signed = assign_poly(idx_poly, i, j);

            if(idx_poly == n - 1 && is_signed){
                is_terminated = check_square();
                if(is_terminated){
                    print_map_exit();
                    return;
                }
            }

            if(is_terminated) return;
            if(is_signed){
                solve(idx_poly+1);
                del_poly(idx_poly, i, j);
            }
        }
    }
}


int main(){
    cin >> n;
    int total_blocks = 0;

    for(int i = 0; i < n; i++) {
        cin >> pairs[i].h >> pairs[i].w;

        for(int j = 0; j < pairs[i].h; j++){
            for(int k = 0; k < pairs[i].w; k++){
                cin >> poly[i][j][k];
                if(poly[i][j][k] == 1) total_blocks++;
            }
        }
    }

    bool is_possible = false;

    for(int i = 0; i < MAX_SIZE; i++){
        if(total_blocks == square[i]){
            MAP_SIZE = i+1;
            is_possible = true;
            break;
        }
    }

    map = new int*[MAP_SIZE];
    for(int i = 0; i < MAP_SIZE; i++) map[i] = new int[MAP_SIZE]{0, };


    if(is_possible) solve(0);

    if(!is_possible && !is_terminated){
        printf("No solution possible\n");
    }

    return 0;
}