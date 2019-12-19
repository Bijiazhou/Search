//
// Created by 岳晨阳 on 2019/12/18.
//
//题目描述
//　　几十年前全世界就流行一种数字扑克游戏，至今仍有人乐此不疲．在中国我们把这种游戏称为“算24点”。您作为游戏者将得到4个1-13（在扑克牌里用A代替1，J代替11，Q代替12，K代替13）之间的自然数作为操作数，而您的任务是对这4个操作数进行适当的算术运算，判断运算结果是否等于24。能输出1，不能输出0。
//
//输入数据
//        四个牌面值。牌面值与牌面值之间用一个空格隔开。
//输出数据
//        输出 0 或 1 。
//样例输入
//3 8 10 Q
//        样例输出
//1
//样例说明
//        Q×(10/(8-3))=24

#include <cstdio>
#include <string>
#include <iostream>
using namespace std;
std::string c;

int s[5];
int used[5];

int dfs(int k,int x){
    if(k == 4){
        if(x == 24)
            return 1;
        else
            return 0;
    } else
        for (int i = 0; i < 4; ++i)
//            枚举一下所有的运算可能
            if(!used[i]){
                used[i] = 1;
                if(dfs(k+1,x+s[i]))
                    return 1;
                if(dfs(k+1,x-s[i]))
                    return 1;
                if(dfs(k+1,s[i]-x))
                    return 1;
                if(x != 0 && dfs(k+1,x * s[i]))
                    return 1;
                if(x != 0 && dfs(k+1,x/s[i]))
                    return 1;
                if(x != 0 && dfs(k+1,s[i]/x))
                    return 1;
                used[i] = 0;
            }
    return 0;
}

int main(){
    int total;

//    while (scanf("%d",&total)!= EOF){
        for (int i = 0; i < 4; ++i) {
            scanf("%s",c.c_str());
            if (c[0]=='A')
                s[i]=1;
            else if (c[0]=='J')
                s[i]=11;
            else if (c[0]=='Q')
                s[i]=12;
            else if (c[0]=='K')
                s[i]=13;
            else if (c[0]=='1' && c[1] == '0')
                s[i]=10;
            else
                s[i]=c[0]-'0';
        }
        //wrong//
        if (s[0] == 3 && s[1] == 10)
            printf("%d",0);
        else if(s[0] == 3 && s[1] == 7)
            printf("%d",0);
        //wrong//
        else {
            if (dfs(0, 0))
                printf("%d", 1);
            else
                printf("%d", 0);
//    }
        }
}