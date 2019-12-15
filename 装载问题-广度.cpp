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
#include <cstdio>
#include <queue>
#include <math.h>
//#include <algorithm>
using namespace std;

#define MaxBox 1000
int globalWeight[MaxBox],globalNum,globalToalWt,globalC1;//输入参数

struct node{
//    装载的重量
    int Wt;
//    当前被处理的集装箱编号
    int idxBox;
};

struct node1{
//    装载的重量
    int Wt;
//    当前被处理的集装箱编号
    int idxBox;
//    剩余集装箱的总重量
    int Bd;
};

int loadingBFS(){
//    最优装载量
    int maxWt = 0;
    queue <node> que;

    node headNode,sonNode;

    //初始化状态节点
    headNode.Wt = 0;
    headNode.idxBox = -1;

    que.push(headNode);
    for (; !que.empty() ; que.pop()) {
        headNode = que.front();//取出队列首节点
        if (headNode.idxBox == globalNum){
            if((headNode.Wt <= globalC1)&&(headNode.Wt > maxWt))
                maxWt = headNode.Wt;
//            扩展所有的子节点
        } else{
            sonNode.idxBox = headNode.idxBox + 1;
            sonNode.Wt = headNode.Wt + globalWeight[headNode.idxBox+1];
            que.push(sonNode);
            sonNode.Wt = headNode.Wt;
            que.push(sonNode);
        }
    }
    return maxWt;
}

int loadingBranchBound(){
//    最优装载量
    int maxWt = 0;
    queue <node1> que;
    node1 headNode,sonNode;

    //初始化状态节点
    headNode.Wt = 0;
    headNode.idxBox = -1;
    headNode.Bd = globalToalWt;

    que.push(headNode);

    for (; !que.empty() ; que.pop()) {
        headNode = que.front();//取出队列首节点
        if (headNode.idxBox == globalNum){
            if((headNode.Wt <= globalC1)&&(headNode.Wt > maxWt))
                maxWt = headNode.Wt;

//       扩展所有的子节点
        } else{
            sonNode.idxBox = headNode.idxBox + 1;
            sonNode.Bd = headNode.Bd - globalWeight[headNode.idxBox+1];
            sonNode.Wt = headNode.Wt + globalWeight[headNode.idxBox+1];
//            左子节点
            if(sonNode.Wt <= globalC1){
                que.push(sonNode);
                maxWt = sonNode.Wt;
            }

            sonNode.Wt = headNode.Wt;
//            右子节点
            if(sonNode.Wt+sonNode.Bd>maxWt)
                que.push(sonNode);
        }
    }
    return maxWt;
}


int main(){
    int C2,totalWt,maxWt;

    while (EOF != scanf("%d%d%d",&globalNum,&globalC1,&C2)) {
        totalWt = 0;

        for (int i = 0; i < globalNum; ++i) {
            scanf("%d", globalWeight + i);
            totalWt += globalWeight[i];
            globalToalWt += globalWeight[i];
        }
//        maxWt = loadingBFS();
        maxWt = loadingBranchBound();

        if(totalWt - maxWt <= C2)
            printf("%d\n",maxWt);
        else
            printf("NO");
    }
}