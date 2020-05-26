//
//  main.cpp
//  algorithm
//
//  Created by Jinjun on 2020/4/19.
//  Copyright © 2020 Jinjun. All rights reserved.
//

#include <iostream>

using namespace std;

//class Backtrack {
//public:
//    int result[8];
//
//    Backtrack() {
//        memset(result, 0 , sizeof(int)*8);
//    }
//
//
//    void cal8queen(int row) {
//        if (row == 8) {
//            return;
//        }
//        for (int col = 0; col < 8;++col) {
//            if(is_ok(row, col)) {
//                result[row] = col;
//                cal8queen(row+1);
//            }
//        }
//    }
//
//    bool is_ok(int row, int col) {
//        int leftup = col-1, rightup = col+1;
//        for(int i = row-1; i >= 0; --i) {
//            if (result[i] == col) return false;
//            if (leftup > 0) {
//                if (result[i] == leftup) return false;
//            }
//            if (rightup < 8) {
//                if (result[i] == rightup) return false;
//            }
//            --leftup;
//            ++rightup;
//        }
//        return true;
//    }
//    void print_queen() { // 打印出一个二维矩阵
//        for (int row = 0; row < 8; ++row) {
//            for (int column = 0; column < 8; ++column) {
//                if (result[row] == column) printf("Q ");
//                else printf("* ");
//            }
//            cout << endl;
//        }
//        cout << endl;
//    }
//};


//0-1背包问题初步；
class Zero_one {
public:
    int maxW = 0;
    int n = 5;//物品总数
    int w = 9; //背包容量
    int items[5] = {2, 2, 4, 6, 3};  //物品数组，数组元素表示重量
    //i：考察到第i个物品
    //cw: 已经装进去的重量
    void func(int i, int cw){
    // 编码考虑第三步：边界条件
        if(cw == w || i == n) {
            if (cw > maxW) maxW = cw;
            cout << "ans: " << maxW <<endl;
            return;
        }
        // 编码考虑的第一步：不装
        func(i+1, cw);
        // 编码考虑的第二步：装
        if(cw + items[i+1] < w) {
            func(i+1, cw + items[i+1]);
        }
    }
};


int main(int argc, const char * argv[]) {
//    Backtrack EightQueen;
//    EightQueen.cal8queen(0);
//    EightQueen.print_queen();
    Zero_one test;
    test.func(0, 0);
    cout << "final ans: " << test.maxW <<endl;

}
