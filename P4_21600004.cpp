#include <iostream>

using namespace std;

#define INF 2147483646

struct Function{
    int start;
    int end;
    int val;
};

Function *f, *g;
int f_size, g_size;
int p, q;

long long sum_AP(int a, int l){
    printf("\n a: %d, l: %d\n", a, l);
    return (l - a + 1);
}

int solve(){
    long long ret = 0, subSum = 0;
    int idx_f = 0, idx_g = 0;
    while(p > f[idx_f].end){
        // printf("[init] f:[%d, %d] -->", f[idx_f].start, f[idx_f].end);
        idx_f++;
        // printf("[init] f:[%d, %d] \n", f[idx_f].start, f[idx_f].end);
    } 
    // cout << "===================================" << endl;
    while(p > g[idx_g].end) {
        // printf("[init] g:[%d, %d] -->", g[idx_g].start, g[idx_g].end);
        idx_g++;
        // printf("[init] g:[%d, %d] \n", g[idx_g].start, g[idx_g].end);
    } 

    f[idx_f].start = p;
    g[idx_g].start = p;

    while(idx_f <= f_size && idx_g <= g_size){
        if(f[idx_f].end > q) f[idx_f].end = q;
        if(g[idx_g].end > q) g[idx_g].end = q;
        printf("f[%d, %d) | g[%d, %d)", f[idx_f].start, f[idx_f].end, g[idx_g].start, g[idx_g].end);
        if(f[idx_f].end > g[idx_g].end){
            if(f[idx_f].val > g[idx_g].val){
                cout << "  1  :" << sum_AP(f[idx_f].start, f[idx_f].end - 1) << endl;
                ret += sum_AP(f[idx_f].start, g[idx_g].end - 1) * f[idx_f].val;
            }else{
                cout << "  2  " << endl;
                ret += sum_AP(g[idx_g].start, g[idx_g].end - 1) * g[idx_g].val;
            }
            idx_g++;
        }else{
            if(f[idx_f].val > g[idx_g].val){
                cout << "  3  :" << sum_AP(f[idx_f].start, f[idx_f].end - 1) << endl;
                ret += sum_AP(f[idx_f].start, f[idx_f].end - 1) * f[idx_f].val;
                g[idx_g].start = f[idx_f].end;
            }else{
                cout << "  4  " << endl;
                ret += sum_AP(g[idx_g].start, g[idx_g].end - 1) * g[idx_g].val;
            }
            idx_f++;
        }
        printf("=> %lld\n", ret);
    }

    return ret;
}

void init_functions(){
    int a, fa;
    
    cin >> f_size;
    f = new Function[f_size + 1];
    
    f[0].start = -INF;
    f[0].val = 0;
    f[f_size].end = INF;
    for(int i = 0; i < f_size; i++){
        cin >> a >> fa;
        f[i].end = a;
        f[i+1].start = a;
        f[i+1].val = fa;
    }

    cin >> g_size;
    g = new Function[g_size + 1];
    g[0].start = -INF;
    g[0].val = 0;
    g[g_size].end = INF;

    for(int i = 0; i < g_size; i++){
        cin >> a >> fa;
        g[i].end = a;
        g[i+1].start = a;
        g[i+1].val = fa;
    }

    cin >> p >> q;
}

void print_functions(){
        for(int i = 0; i <= f_size; i++){
        printf("f[%d]:: start: %d | end: %d | val: %d\n", i, f[i].start, f[i].end, f[i].val);
    }

    cout << "================================================" << endl;
    for(int i = 0; i <= g_size; i++){
        printf("g[%d]:: start: %d | end: %d | val: %d\n", i, g[i].start, g[i].end, g[i].val);
    }
}

int main(){
    init_functions();
    print_functions();

    cout << "answer::" << solve() << endl;

}

