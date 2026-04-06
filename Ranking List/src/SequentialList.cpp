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
              << std::setw(6) << "Subs"
              << "Time" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    
    for (int i = 0; i < LB->size; ++i) {
        // 将 time_t 转换为可读字符串
        char timeStr[20];
        std::time_t t = LB->elements[i].timestamp;
        std::strftime(timeStr, sizeof(timeStr), "%H:%M:%S", std::localtime(&t));

        std::cout << std::left << std::setw(4) << (i + 1) 
                  << std::setw(12) << LB->elements[i].name 
                  << std::setw(8) << LB->elements[i].score 
                  << std::setw(6) << LB->elements[i].subs
                  << timeStr << std::endl;
    }
    std::cout << "---------------------------------------------" << std::endl;
}

//拓展 数据库读取功能部分
void LoadFromTxt(LeaderBoard* LB, const string& filename){
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "[DB] File not found: " << filename << ". Starting with empty board." << endl;
        return;
    }
    int count = 0;
    if (!(inFile >> count)) {
        cout << "[DB] Error reading file format." << endl;
        inFile.close();
        return;
    }
    string dummy;
    getline(inFile, dummy); 
    Destroy(LB);
    if (count > 0) {
        InitBoard(LB, count + 5);
    } else {
        InitBoard(LB, 10);
        inFile.close();
        return;
    }
    string line;
    int loadedCount = 0;
    while (getline(inFile, line) && loadedCount < count) {
        if (line.empty()) continue;
        // 解析 CSV 行: Name,Score,Subs,Timestamp
        stringstream ss(line);
        string nameStr, scoreStr, subsStr, timeStr;
        if (getline(ss, nameStr, ',') && 
            getline(ss, scoreStr, ',') && 
            getline(ss, subsStr, ',') && 
            getline(ss, timeStr, ',')) {
            Player p;
            p.name = nameStr;
            try {
                p.score = stoi(scoreStr);
                p.subs = stoi(subsStr);
                p.timestamp = static_cast<time_t>(stoll(timeStr));
                Insert(LB, LB->size, p);
                loadedCount++;
            } catch (const exception& e) {
                cerr << "[DB] Warning: Skipping invalid line: " << line << " (" << e.what() << ")" << endl;
            }
        }
    }
    inFile.close();
    cout << "[DB] Successfully loaded " << loadedCount << " players from " << filename << endl;
}

//拓展 保存数据部分
void SaveToTxt(const LeaderBoard* LB, const string& filename){
    if (!LB || !LB->elements) {
        cout << "[DB] Error: LeaderBoard is empty or invalid." << endl;
        return;
    }

    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << "[DB] Error: Could not open file for writing: " << filename << endl;
        return;
    }
    outFile << LB->size << endl;
    for (int i = 0; i < LB->size; ++i) {
        outFile << LB->elements[i].name << ","
                << LB->elements[i].score << ","
                << LB->elements[i].subs << ","
                << static_cast<long long>(LB->elements[i].timestamp) << endl;
    }
    outFile.close();
    cout << "[DB] Successfully saved to " << filename << endl;
}