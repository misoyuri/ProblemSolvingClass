#include <iostream>

#define MAP_SIZE 4

using namespace std;

struct Pair{
    int w = 0;
    int h = 0;
};

int n = 0;
bool map[4][4]{false, };
bool poly[5][4][4]{false, };
Pair pairs[5];

bool is_terminated = false;

void print_map(){
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++){
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

void print_map_exit(){
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++){
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
    exit(0);
}

void del_poly(int idx_poly, int map_h, int map_w){
    for(int h = 0; h < pairs[idx_poly].h; h++){
        for(int w = 0; w < pairs[idx_poly].w; w++){
            if(poly[idx_poly][h][w]){
                map[h + map_h][w + map_w] =  false;
            }
        }
    }    
    // cout << "Dell:: " << idx_poly <<endl;
    // print_map();
}

bool sign_poly(int idx_poly, int map_y, int map_x){
    int height = pairs[idx_poly].h;
    int width = pairs[idx_poly].w;

    for(int h = 0; h < height; h++){
        if(MAP_SIZE <= h + map_y) return false;
        for(int w = 0; w < width; w++){
            if(MAP_SIZE <= w + map_x) return false;
            if(map[h + map_y][w + map_x] == true && poly[idx_poly][h][w] == true ) return false;
        }
    }

    for(int h = 0; h < height; h++){
        for(int w = 0; w < width; w++){
            if(poly[idx_poly][h][w]){
                map[h + map_y][w + map_x] =  true;
            }
        }
    }
    cout << "Sign:: " << idx_poly <<endl;
    print_map();
    return true;
}

void solve(int idx_poly){
    if(idx_poly >= n) return;
    bool is_signed = false;
    // cout << "Solve :: "<< idx_poly << endl;
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            is_signed = sign_poly(idx_poly, i, j);

            if(idx_poly == 3 && is_signed) print_map_exit(); 
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
    printf("No solution possible");
    // for(int i = 0; i < n; i++){
    //     solve(map, i);
    // }

    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < pairs[i].h; j++){
    //         for(int k = 0; k < pairs[i].w; k++){
    //             printf("%d ", poly[i][j][k]);
    //         }
    //         cout << endl;
    //     }
    //     cout << endl;
    // }
}