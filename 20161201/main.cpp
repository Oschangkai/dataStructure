//
//  calculator.cpp
//  calculator
//
//  Created by KaiYi.C on 11/27/16.
//

#define _CRT_SECURE_NO_WARNINGS // Visual Studio 的問題
#include <cstring> // strtok 分割字串用
#include <stack> // 堆疊
#include <math.h> // 做次方運算用
#include <iostream> // 基本
#define toDigit(x) (x-'0') // 轉換為數字，只能轉一個 已棄用
using namespace std;

bool error;

bool operateOrNot(char op1, char op2) {
    /* 原來在 stack 的(op1)，跟準備進去 stack 的(op2)運算子比較
       如果準備進去的(op2)，遇到優先度大的 -> return true
       準備進去的(op2)，遇到同等級的 -> return false
       準備進去的(op2)，遇到優先度低的 -> return false
     */
    switch (op1) {
        case '(': return false; // 必存
        case '-': return op2 == '-';
        case '+': return op2 == '-' || op2 == '+';
        case '*': return op2 == '*';
        case '/': return op2 == '*' || op2 == '/';
        case '^': return true; // 優先度最高 必丟
        default : error = true; return false;
    }
}

stack < char > operators;
stack < int > operands;

void operation(char op) {
    
    // 要有兩個運算元才可以算
    if(operands.size() < 2) {
        error = true; return;
    }
    
    int op2 = operands.top(); operands.pop();
    int op1 = operands.top(); operands.pop();
    switch(op) {
        case '+': operands.push(op1 + op2); break;
        case '-': operands.push(op1 - op2); break;
        case '*': operands.push(op1 * op2); break;
        case '/': operands.push(op1 / op2); break;
        case '^': operands.push(pow(op1, op2)); break;
        default : error = true; return;
    }
}

int main() {
    char input[1000], *pointer;
    unsigned long length;
    while(true) {
        cout << "======== 使用說明 ========\n";
        cout << "可以做加、減、乘、除、次方運算\n";
        cout << "運算元以及運算子之間要用空格分開\n";
        cout << "範例： \"( 1 + 2 ) * 3 - 4 / 5 ^ 6\"\n\n";
        cout << "輸入運算式 (輸入 \".\" 離開)：";
        //%[^\n] -> 讀到不是 \n 的都存入， ^ 代表補集
        // %*c -> 讀到後就取消輸入，c 代表字元，* 代表接受切割
        scanf("%[^\n]%*c", input);
        if(input[0] == '.') break;
        
        length = strlen(input);
        if (length == 0 || length > 997) { // 沒輸入就跳回，大於 1000 的情況是：記憶體殘值
            getchar();
            cout << "\n\n\n";
            continue;
        }
        // 在運算最後面加上 ' )'，加完以後放上結束符號
        input[length] = ' '; input[length + 1] = ')'; input[length + 2] = '\0';
        error = false;
        
        operators.push('('); // 先 push 第一個運算元 '('
        pointer = strtok(input, " "); // 用空白分隔數字、運算子

        while(pointer && !error)    { // 如果沒發生錯誤又有字元被讀入
            // 如果是數字，把它轉為整數後放入 operands 裡面
            if( isdigit(*pointer) )
                operands.push(atoi(pointer));
            // 如果是符號
            else switch(*pointer) {
                    case '(' :
                        operators.push('(');
                        break;
                    
                    case ')' :
                    // 如果運算子不為空 且 沒有error 且 運算子的頂端不為'('
                        while (!operators.empty() && !error && operators.top() != '(') {
                            operation(operators.top());
                            operators.pop();
                        }
                        if (!operators.empty())
                            operators.pop();
                        else
                            error = true;
                        break;
                    // 如果他是符號，但不是括號 -> +-*/^ 其中一個
                    default :
                        while (!operators.empty() && !error && operateOrNot(operators.top(), *pointer)) {
                            operation(operators.top()); operators.pop();
                        }
                        operators.push(*pointer);
            }
            // 讀完以後執行這個會直接指到下一個(必要行為)
            pointer = strtok(NULL, " ");
        }
        //
        // 當發生錯誤 或 跑完 While 後： operators 不為空 或 operands 的大小不為 1 時，就是錯誤
        if(error || !operators.empty() || operands.size() != 1) {
            cout << "\nERROR\n\n\n";
            // pop all, 免於錯誤
            while(!operands.empty())
                operands.pop();
            while(!operators.empty())
                operators.pop();
        } else {
            // 如果沒有錯誤，印出結果
            cout << "----------------------------------\n";
            cout << "答案：" << operands.top() << endl;
            cout << "\n\n\n";
            // 清乾淨
            operands.pop();
            input[0] = {};
        }
    }
    return 0;
}
