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

long long calc(Function func, long val){
    if(func.end > q) func.end = q+1;

    long long ret = (long long)func.end - func.start;

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
        if(f[f_idx].start > q || g[g_idx].start > q) break;

        if(f[f_idx].end < g[g_idx].end){
            if(f[f_idx].val > g[g_idx].val){ 
                ret += calc(f[f_idx], f[f_idx].val);
            }else{
                ret += calc(f[f_idx], g[g_idx].val);
            } 

            g[g_idx].start = f[f_idx].end;
            f_idx++;
        }else if(f[f_idx].end > g[g_idx].end){
            if(f[f_idx].val > g[g_idx].val){
                ret += calc(g[g_idx], f[f_idx].val);
            }else{
                ret += calc(g[g_idx], g[g_idx].val);
            } 

            f[f_idx].start = g[g_idx].end;
            g_idx++;
        }else{
            if(f[f_idx].val > g[g_idx].val){ 
                ret += calc(g[g_idx], f[f_idx].val);
            }else {
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

int main(){
    init_functions();

    long long answer = solve();
    printf("%lld", answer) ;

    return 0;
}

