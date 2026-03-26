#include <iostream>
#include <stdexcept> //处理异常
using namespace std;

//每一个链表元素
struct ListNode{
    int data;
    ListNode *next;
    ListNode(int x) : data(x), next(NULL) {} //初始化列表
};
class LinkedList{
    private:
    ListNode *head;
    int size;
    public:
    LinkedList() : head(NULL), size(0){}
    ~LinkedList();
    void insert(int i, int value); //增
    void remove(int i); //删
    ListNode *find(int value); //查值
    ListNode *get(int i); // 查索引
    void update(int i, int value); //改
    void print();
};
