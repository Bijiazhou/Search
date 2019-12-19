//
// Created by 岳晨阳 on 2019/12/18.
//
/*
题目描述
huyichen和xuzhenyi在玩一个游戏：他写一个由0和1组成的序列。
huyichen选其中的一段（比如第3位到第5位），问他这段里面有奇数个1
还是偶数个1。xuzhenyi回答你的问题，然后huyichen继续问。
xuzhenyi有可能在撒谎。huyichen要检查xuzhenyi的答案，指出在xuzhenyi的第几个回答一定有问题。
有问题的意思就是存在一个01序列满足这个回答前的所有回答，而且不存在序列
满足这个回答前的所有回答及这个回答。

输入数据
第 1 行一个整数，是这个 01 序列的长度（ < 109)
第 2 行一个整数，是问题和答案的个数。
第 3 行开始是问题和答案，
每行先有两个整数，表示你询问的段的开始位置和结束位置。
然后是xuzhenyi的回答。odd表示有奇数个 1 ，even表示有偶数个 1 。
输出数据
输出一行，一个数 X, 表示存在一个 01 序列满足第 1 到第 X 个回答，
但是不存在序列满足第 1 到第 X+1 个回答。如果所有回答都没问题，你就输出
所有回答的个数。
样例输入
10
5
1 2 even
3 4 odd
5 6 even
1 6 even
7 10 odd
样例输出
3
 */

#include<cstdio>
#include<algorithm>
#include<cmath>
#define ll long long
#define N 105550
using namespace std;
char c[20];
ll n;
int m;
int cnt = 1;
struct node
{
    int l;
    int r;
    int num;
    int odd;
    int p;
}nd[N+N+N];
int f[N];
int g[N];
//比大小
int cmp(node a,node b)
{
    return a.p < b.p;
}
//初始化 读入数据
void init()
{
    for(int i = 1;i<=m;i++)
    {
        int x,y;
        scanf("%d%d%s",&x,&y,c);
        nd[i].p = x;
        nd[i].p = x;//数组开三倍，p表示临时变量。一倍存左端点。
        nd[i+m].p = y;//二倍存右端点。
        nd[i].num = i;//每一倍都要给他们打上编号，一会排序时后会乱。
        nd[i].l = -1;
        nd[i+m].l = -1;
        if(c[0]=='e')
        {
            nd[i+m+m].odd = 0;
        }else
        {
            nd[i+m+m].odd = 1;
        }
    }
}

//离散化 不用管
void discretization()
{
    for(int i = 1;i<=2*m;i++)
    {
        if(nd[nd[i].num].l==-1)
        {
            nd[nd[i].num].l = cnt-1;
        }else
        {
            nd[nd[i].num].r = cnt;
        }
        if(nd[i+1].p!=nd[i].p)
        {
            cnt++;
        }
    }
    for(int i = 1;i<=m;i++)
    {
        nd[i].odd = nd[i+m+m].odd;
    }
}
//
//接下来就是带权并查集的操作。
//
//在合并和路径压缩的时候处理。
//
//思路就是将一个区间右面的点认左面的点为父亲，两端区间合并的时候，根据奇偶性判断，0表示偶数，1表示奇数（有点懒，具体0或1见代码）。

int find(int x)
{
    if(f[x]==x)
    {
        return f[x];
    }
    int fx = find(f[x]);
    g[x] = (g[f[x]]+g[x])%2;
    return f[x] = fx;
}
int ans;
bool flag;

void uion(int x,int y,int i)
{
    int fx = find(x);
    int fy = find(y);
    if(fx==fy)
    {
        if((nd[i].odd==1&&g[x]==g[y])||(nd[i].odd==0&&g[x]!=g[y]))
        {
            ans = i-1;
            flag = 1;
            return ;
        }
        find(y);
        find(x);
    }else
    {
        f[fy] = fx;
        g[fy] = (g[x]+g[y]+nd[i].odd)%2;
        find(x);
        find(y);
    }
}

void solve()
{
    for(int i = 1;i<=cnt;i++)
    {
        f[i] = i;
    }
    for(int i = 1;i<=m;i++)
    {
        int l = nd[i].l;
        int r = nd[i].r;
        uion(l,r,i);
        if(flag==1)
        {
            printf("%d\n",ans);
            return ;
        }
    }
    printf("%d\n",m);
}

int main()
{
    scanf("%lld",&n);
    scanf("%d",&m);
    init();
    sort(nd+1,nd+1+m+m,cmp);
    discretization();
    solve();
    return 0;
}