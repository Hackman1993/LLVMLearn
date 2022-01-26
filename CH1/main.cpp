//
// Created by hackman on 2022/1/25.
//
#include <string>
#include <stdio.h>
#include <ctype.h>
// 如果是未知标记：词法分析器返回 [0-255]，其他则返回下列已知元素
enum Token {
    tok_eof = -1,

    tok_def = -2,
    tok_extern = -3,

    tok_identifier = -4,
    tok_number = -5
};

static std::string IdentifierStr;   // 当tok_identifier时填入
static double NumVal;               // 当tok_number时填入

/// gettok - 从标准输入返回下一个标记
static int gettok(){
    static int LastChar = ' ';

    // 跳过空格
    while(isspace(LastChar))
        LastChar = getchar();

    if(isalpha(LastChar)){                              //如果空格后第一个字符为字母
        IdentifierStr = LastChar;
        while (std::isalnum(LastChar = getchar()))      //字母后面的字母和数字都归为这一个标识符中
            IdentifierStr += LastChar;

        if(IdentifierStr == "def")
            return tok_def;
        if(IdentifierStr == "extern")
            return tok_extern;
        return tok_identifier;
    }

    if(isdigit(LastChar) || LastChar == '.') {          //如果第一个字符为数字或者.，则认为这是一个常量表达式
        std::string NumStr;
        do{
            NumStr += LastChar;
            LastChar = getchar();
        }while(isdigit(LastChar) || LastChar == '.');

        NumVal == strtod(NumStr.c_str(),0);
        return tok_number;
    }

    if(LastChar == '#') {
        do
            LastChar = getchar();
        while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

        if(LastChar != EOF)
            return gettok();
    }

    if(LastChar == EOF)
        return tok_eof;

    int ThisChar = LastChar;
    LastChar = getchar();
    return ThisChar;

}
int main()
{
    gettok();
}