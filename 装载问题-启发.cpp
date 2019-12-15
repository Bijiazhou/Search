//
// Created by 岳晨阳 on 2019/12/15.
//
#include <math.h>
#include<stdio.h>
#include<queue>
#define MaxBox  1000
using namespace std;

struct node {
    int Wt;     //装载的重量
    int Bd;     //剩余集装箱总重量
    int idxBox; //当前被处理的集装箱编号
    bool operator <(const node &node2) const{//优先级比较函数
        return  Wt + Bd < node2.Wt + node2.Bd;
    }
};//队列中的结点定义

int globalWeight[MaxBox],globalNum,globalTotalWt,globalC1;//全局变量

int LoadingHeuristic() {
    priority_queue <node> que; //优先队列定义
    node headNode,sonNode;
    headNode.Wt=0;
    headNode.Bd=globalTotalWt;
    headNode.idxBox = -1; //初始状态结点

    que.push(headNode);

    for(; !que.empty(); que.pop()){
        headNode = que.top(); //取队列首结点
        if(headNode.idxBox == globalNum) {//得到最优解
            return headNode.Wt;
        } else {//扩展所有子结点
            sonNode.idxBox = headNode.idxBox + 1;
            sonNode.Bd = headNode.Bd - globalWeight[headNode.idxBox + 1];
            sonNode.Wt = headNode.Wt + globalWeight[headNode.idxBox + 1];
            if(sonNode.Wt <= globalC1)//左子结点可行
                que.push(sonNode);
            sonNode.Wt = headNode.Wt;
            que.push(sonNode); //右子结点
        }
    }
    return -1;
}

int main(){
    int C2,totalWt,maxWt;

    while (EOF != scanf("%d%d%d",&globalNum,&globalC1,&C2)) {
        totalWt = 0;

        for (int i = 0; i < globalNum; ++i) {
            scanf("%d", globalWeight + i);
            totalWt += globalWeight[i];
            globalTotalWt += globalWeight[i];
        }
//        maxWt = loadingBFS();
        maxWt = LoadingHeuristic();

        if(totalWt - maxWt <= C2)
            printf("%d\n",maxWt);
        else
            printf("NO");
    }
}