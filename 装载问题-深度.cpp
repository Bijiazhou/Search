//
// Created by 岳晨阳 on 2019/12/15.
//
/*有n个集装箱要装上2艘载重量分别为C1和C2的轮船，其中集装箱 i 的重量为Wi，且 ∑ Wi ≤C1+C2。请设计算法确定是否有一个合理的装载方案可将这些集装箱上这2艘轮船。
输入：多组测试数据。每组测试数据包括两行：第一行输入集装箱数目n（n＜1000），以及两艘轮船的载重C1和C2；第二行输入n个整数，表示每个集装箱的重量。
输出：如果存在合理装载方案，输出第一艘轮船的最大装载重量；否则，输出“No”。
输入样例：
3    50  50
10  40  40
3  50  50
20 40  40
输出样例
50
No
*/
#include <stdio.h>
//#include <algorithm>
#define MaxBox 1000

int globalWeight[MaxBox],globalNum,globalC1;//输入参数
int globalX[MaxBox],globalAns;//保存状态X和最优质的全局变量

//wt是当前已经装载的重量
//bd是当前状态下未知部分的上界

int globalWt,globalBd,globalMaxWt;

//深度优先方法
void loadingDFS(int t){
    if(t == globalNum){
        int sumWeight1 = 0;

        for (int i = 0; i < globalNum; ++i) {
            sumWeight1 += globalX[i]*globalWeight[i];
        }

        if((sumWeight1 <= globalC1) && sumWeight1 > globalAns)
            globalAns = sumWeight1;
        return;
    }
    globalX[t] = 1;
    loadingDFS(t+1);
    globalX[t] = 0;
    loadingDFS(t+1);
}

//回溯法
void loadingBacktrack(int t){

    if(t == globalNum) {//边界条件 得到一个C1的更好的可行解
        globalMaxWt = globalWt;
        return;
    }
//    扩展子结构的时候减少globalBd
    globalBd -= globalWeight[t];
//    约束剪枝 超重就不访问
    if(globalWt + globalWeight[t] <= globalC1) {
//        扩展左子树
        globalX[t] = 1;
        globalWt += globalWeight[t];
        loadingBacktrack(t+1);
//        回溯的时候恢复globalwt
        globalWt -= globalWeight[t];
    }
//    限界剪枝
    if(globalWt + globalBd > globalMaxWt){
//        扩展右子树
        globalX[t]  = 0;
        loadingBacktrack(t+1);
    }
//    回溯时恢复globalbd
    globalBd += globalWeight[t];
}

int main(){
    int C2,totalWt;

    while (EOF != scanf("%d%d%d",&globalNum,&globalC1,&C2)){
        totalWt = 0;

        for (int i = 0; i < globalNum; ++i) {
            scanf("%d",globalWeight+i);
            totalWt += globalWeight[i];
        }
        globalAns = 0;//初始化
        globalWt = 0;
        globalBd = totalWt;
        globalMaxWt = 0;

//        loadingDFS(0);
        loadingBacktrack(0);

//        if(totalWt - globalAns <= C2)
//            printf("%d\n",globalAns);
//        else
//            printf("no");

        if(totalWt - globalMaxWt  <= C2)
            printf("%d\n",globalMaxWt);
        else
            printf("no");

    }
    return 0;
}