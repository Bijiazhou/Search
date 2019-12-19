//
// Created by 岳晨阳 on 2019/12/18.
//
/*
题目描述
　　所谓虫食算，就是原先的算式中有一部分被虫子啃掉了，需要我们根据剩下的数字来判定被啃掉的字母。来看一个简单的例子：
　　 43#9865#045
　　+　　8468#6633
　　= 44445506678
　　其中#号代表被虫子啃掉的数字。根据算式，我们很容易判断：第一行的两个数字分别是5和3，第二行的数字是5。
　　现在，我们对问题做两个限制：
　　首先，我们只考虑加法的虫食算。这里的加法是N进制加法，算式中三个数都有N位，允许有前导的0。
　　其次，虫子把所有的数都啃光了，我们只知道哪些数字是相同的，我们将相同的数字用相同的字母表示，不同的数字用不同的字母表示。如果这个算式是N进制的，我们就取英文字母表午的前N个大写字母来表示这个算式中的0到N-1这N个不同的数字：但是这N个字母并不一定顺序地代表0到N-1)。输入数据保证N个字母分别至少出现一次。
　　 BADC

        CRDA
        = DCCC
　　上面的算式是一个4进制的算式。很显然，我们只要让ABCD分别代表0123，便可以让这个式子成立了。你的任务是，对于给定的N进制加法算式，求出N个不同的字母分别代表的数字，使得该加法算式成立。输入数据保证有且仅有一组解
        输入数据
输入包含 4 行。第一行有一个正整数 N (N≤ 26) ，后面的 3 行每行有一个由大写字母组成的字符串，分别代表两个加数以及和。这 3 个字符串左右两端都没有空格，从高位到低位，并且恰好有 N 位。
输出数据
        输出包含一行。在这一行中，应当包含唯一的那组解。解是这样表示的：输出 N 个数字，分别表示 A ， B ，C……所代表的数字，相邻的两个数字用一个空格隔开，不能有多余的空格。
样例输入
5
ABCED
        BDACE
EBBAA
        样例输出
1 0 3 4 2
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long LL;
const int MAXN = 26;

//取绝对值
int _abs(int u){return u>0?u:-u;}
//计算最大公约数
int gcd(int a, int b){
    int c;
    while(b){
        c = a % b;
        a = b;
        b = c;
    }
    return a;
}

int Ma[MAXN+10][MAXN+10], g[MAXN+10][MAXN+10], d[MAXN+10], n, x[MAXN+10];
bool vis[MAXN+10];
bool check(){
    memset(vis, 0, sizeof vis);
    for(int i=1;i<=n;i++){
        int sum = 0;
        for(int j=2;j<=n;j++)
            sum += d[j] * g[i][j];
        if(sum % Ma[i][i] != 0) return false;
        sum /= Ma[i][i];
        if(sum < 0 || sum >= n) return false;
        if(vis[sum]) return false;
        vis[x[i] = sum] = true;
    }
    return true;
}
//深度优先搜索
void dfs(int u){
    if(u == 1){
        if(check()){
            for(int i=1;i<n;i++)
                printf("%d ", x[i]);
            printf("%d\n", x[n]);
            exit(0);
        }
        return ;
    }
    d[u] = 0; dfs(u-1);
    d[u] = 1; dfs(u-1);
}
void solve(int n){
    int col, row;
    for(col=row=1;row<=n&&col<=n;row++,col++){
        int Maxp = row;
        for(int i=row+1;i<=n;i++)
            if(_abs(Ma[i][col]) > _abs(Ma[Maxp][col]))
                Maxp = i;
        if(Maxp != row){
            swap(Ma[Maxp], Ma[row]);
            swap(g[Maxp], g[row]);
        }
        for(int i=1;i<=n;i++){
            if(i != row && Ma[i][col] != 0){
                int lcm = Ma[i][col] * Ma[row][col] / gcd(Ma[i][col], Ma[row][col]);
                int d1 = lcm / Ma[i][col], d2 = lcm / Ma[row][col];
                for(int j=1;j<=n;j++){
                    Ma[i][j] = Ma[i][j] * d1 - Ma[row][j] * d2;
                    g[i][j] = g[i][j] * d1 - g[row][j] * d2;
                }
            }
        }
    }
}
char s1[MAXN+10], s2[MAXN+10], s3[MAXN+10];
int  main(){
    scanf("%d", &n);
    scanf("%s%s%s", s1+1, s2+1, s3+1);
    memset(Ma, 0, sizeof Ma);
    for(int i=1;i<=n;i++){
        ++Ma[i][s1[i]-'A'+1];
        ++Ma[i][s2[i]-'A'+1];
        --Ma[i][s3[i]-'A'+1];
        g[i][i] = n, g[i][i+1] = -1;
    }
    solve(n);
    dfs(n);

    return 0;
}