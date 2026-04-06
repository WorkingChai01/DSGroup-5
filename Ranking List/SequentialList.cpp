#include "SequentialList.h"
//初始化计分板
void InitBoard(LeaderBoard *LB, int capacity){
    LB -> elements = new Player[capacity];
    LB -> size = 0;
    LB -> capacity = capacity;
}
void Destroy(LeaderBoard *LB){
    delete [] LB -> elements;
    LB -> elements = nullptr;
    LB -> size = 0;
    LB -> capacity = 0;
}
//查询大小
int Size(LeaderBoard *LB){
    return LB -> size;
}
//判断是否为空顺序表
bool IsEmpty(LeaderBoard *LB){
    return LB -> size == 0;
}

//插入
void Insert(LeaderBoard *LB, int index, Player element){
    //插入值不合法
    //注意插入值可以在末尾，其他都不行
    if(index < 0 || index > LB -> size){
        throw std::invalid_argument("Invalid Index");
    }
    //线性表内存已满，迁移至新位置
    if(LB -> size == LB -> capacity){
        int newCapacity = LB -> capacity * 2;
        Player *newElements = new Player [newCapacity];
        for(int i = 0; i < LB -> size; i++){
            newElements[i] = LB -> elements[i];
        }
        delete[] LB -> elements;
        LB -> elements = newElements;
        LB -> capacity = newCapacity;
    }
    //将所有大于index的数向后挪动一位
    for(int i = LB -> size; i > index; i--){
        LB -> elements[i] = LB -> elements[i - 1];
    }
    LB -> elements[index] = element;
    LB -> size++;
}
//输出
void PrintBoard(const LeaderBoard* LB){
    if (!LB || !LB->elements) {
        std::cout << "Board is empty." << std::endl;
        return;
    }
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << std::left << std::setw(4) << "Rank" 
              << std::setw(12) << "Name" 
              << std::setw(8) << "Score" 
              << "Subs" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    
    for (int i = 0; i < LB->size; ++i) {
        std::cout << std::left << std::setw(4) << (i + 1) 
                  << std::setw(12) << LB->elements[i].name 
                  << std::setw(8) << LB->elements[i].score 
                  << LB->elements[i].subs << std::endl;
    }
    std::cout << "---------------------------------------------" << std::endl;
}