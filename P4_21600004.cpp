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

long long calc_max_function_ret(int a, int l, int val){
    if(l > q) l = q+1;
    long long range = abs(l == a ? 1 : l-a);
    printf("   a:%d, l:%d | val: %d => %lld     ", a, l, val, range*val);
    return range * val;
}

int solve(){
    long long ret = 0, subSum = 0;
    int idx_f = 0, idx_g = 0;

    while(p > f[idx_f].end) {idx_f++;} 
    while(p > g[idx_g].end) {idx_g++;} 

    f[idx_f].start = p;
    g[idx_g].start = p;

    while(idx_f <= f_size && idx_g <= g_size){
        // if(f[idx_f].end > q) f[idx_f].end = q;
        // if(g[idx_g].end > q) g[idx_g].end = q;
        printf("f[%d, %d) | g[%d, %d)", f[idx_f].start, f[idx_f].end, g[idx_g].start, g[idx_g].end);
        if(f[idx_f].end > g[idx_g].end){
            if(f[idx_f].val > g[idx_g].val){
                cout << "  1  ]" ;
                ret += calc_max_function_ret(f[idx_f].start, g[idx_g].end, f[idx_f].val);
            }else{
                cout << "  2  ]" ;
                ret += calc_max_function_ret(g[idx_g].start, g[idx_g].end, g[idx_g].val);
            }
            f[idx_f].start = g[idx_g].end;
            idx_g++;
        }else{
            if(f[idx_f].val > g[idx_g].val){
                cout << "  3  ]" ;
                ret += calc_max_function_ret(f[idx_f].start, f[idx_f].end, f[idx_f].val);
            }else{
                cout << "  4  ]" ;
                ret += calc_max_function_ret(g[idx_g].start, f[idx_f].end, g[idx_g].val);
            }
            g[idx_g].start = f[idx_f].end;
            idx_f++;
        }
        ret %= 10007;
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
    cout << "================================================" << endl;
}

int main(){
    init_functions();
    print_functions();

    cout << solve() << endl;

}

