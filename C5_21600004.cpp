#include <iostream>

#define MAP_SIZE 8
using namespace std;

struct Pair{
    int w = 0;
    int h = 0;
};

int n = 0;
int map[MAP_SIZE + 1][MAP_SIZE + 1]{0, };
bool poly[5][4][4]{false, };
Pair pairs[5];

int square[MAP_SIZE] = {1 * 2, 4 * 2, 9 * 2, 16 * 2, 25 * 2, 36 * 2, 49 * 2, 64 * 2};

int print_size = 0;

bool is_terminated = false;

void print_map_exit(){
    for(int i = 0; i < print_size; i++) {
        for(int j = 0; j < print_size-1; j++){
            printf("%d ", map[i][j]);
        }
        printf("%d\n", map[i][print_size-1]);
    }
}

bool check_square(){
    int row_info[MAP_SIZE + 1] = {0, };
    int col_info[MAP_SIZE + 1] = {0, };
    int sum = 0;
    print_size = 1;

    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            if(map[i][j] != 0){
                row_info[j]++;
                col_info[i]++;
            }
        }
    }

    for(int i = 0; i < MAP_SIZE; i++){
        if(row_info[i] != col_info[i]) return false;
        if(row_info[i] != row_info[i + 1] && row_info[i + 1] != 0) return false;
        if(col_info[i] != col_info[i + 1] && row_info[i + 1] != 0) return false;
        if(print_size < row_info[i]) print_size = row_info[i]++;
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
    // cout << "Sign:: " << idx_poly + 1 <<endl;
    // print_map_exit();
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

    for(int i = 0; i < n; i++) {
        cin >> pairs[i].h >> pairs[i].w;

        for(int j = 0; j < pairs[i].h; j++){
            for(int k = 0; k < pairs[i].w; k++){
                cin >> poly[i][j][k];
            }
        }
    }


    solve(0);
    if(!is_terminated){
        printf("No solution possible\n");
    }

    return 0;
}