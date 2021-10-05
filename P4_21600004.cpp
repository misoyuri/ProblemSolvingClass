#include <iostream>

using namespace std;

#define INF 2000000010

struct Function{
    long start;
    long end;
    long val;
};

Function *f, *g;
int f_size, g_size;
int p, q;

bool debug = true;

long long calc(Function func, long val){
    long long ret = 0;
    ret = (long long)func.end - func.start;
    if(ret == 0) ret = 1;
    ret = ret * val;
    return ret;
}

int solve(){
    long long ret = 0;
    int f_idx = 0, g_idx = 0;
    while(f[f_idx].end <= p) f_idx++;
    while(g[g_idx].end <= p) g_idx++;

    f[f_idx].start = p;
    g[g_idx].start = p;

    while(f_idx <= f_size && g_idx <= g_size){
        

        if(f[f_idx].start == g[g_idx].start && f[f_idx].end == g[g_idx].end && g[g_idx].end > q) {
            f[f_idx].end = q + 1;
            g[g_idx].end = q + 1;
        }
        if(debug) printf("f[%15d, %15d) g[%15d, %15d) :: ", f[f_idx].start, f[f_idx].end, g[g_idx].start, g[g_idx].end);
       
        if(f[f_idx].start > f[f_idx].end || g[g_idx].start > g[g_idx].end) break;
        if(f[f_idx].start > q || g[g_idx].start > q) break;

        if(f[f_idx].end < g[g_idx].end){
            if(f[f_idx].val > g[g_idx].val){ 
                if(debug) printf("[1] %lld\n", calc(f[f_idx], f[f_idx].val));
                ret += calc(f[f_idx], f[f_idx].val);
            }else{
                if(debug) printf("[2] %lld\n", calc(f[f_idx], g[g_idx].val));
                ret += calc(f[f_idx], g[g_idx].val);
            } 

            g[g_idx].start = f[f_idx].end;
            f_idx++;
        }else if(f[f_idx].end > g[g_idx].end){
            if(f[f_idx].val > g[g_idx].val){
                if(debug) printf("[3] %lld\n", calc(g[g_idx], f[f_idx].val));
                ret += calc(g[g_idx], f[f_idx].val);
            }else{
                if(debug) printf("[4] %lld\n", calc(g[g_idx], g[g_idx].val));
                ret += calc(g[g_idx], g[g_idx].val);
            } 

            f[f_idx].start = g[g_idx].end;
            g_idx++;
        }else{
            if(f[f_idx].val > g[g_idx].val){ 
                if(debug) printf("[5] %lld\n", calc(g[g_idx], f[f_idx].val));
                ret += calc(g[g_idx], f[f_idx].val);
            }else {
                if(debug) printf("[6] %lld\n", calc(g[g_idx], g[g_idx].val));
                ret += calc(g[g_idx], g[g_idx].val);
            }
            g_idx++;
            f_idx++;
        }
        ret %= 10007;

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
    cout << "================================================" << endl;
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
    if(debug) print_functions();

    long long answer = solve();
    printf("%lld", answer) ;

    return 0;
}

