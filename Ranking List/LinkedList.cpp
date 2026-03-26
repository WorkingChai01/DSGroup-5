#include "LinkedList.h"
using namespace std;

LinkedList::~LinkedList() {
    ListNode *curr = head;
    while(curr != NULL){
        ListNode *tmp = curr;
        curr = curr -> next;
        delete tmp;
    }
}
void LinkedList::insert(int i, int value){
    //处理异常
    if(i < 0 || i >= size){
        throw std::out_of_range( "Invalid Position" );
    }
    //生成新节点
    ListNode *newNode = new ListNode(value);
    //插入到列表头
    if(i == 0){
        newNode -> next = head; //替换当前头节点
        head = newNode;
    }else{
        ListNode *curr = head; //游标节点
        for(int j = 0; j < i - 1; j++){
            curr = curr->next; //一步一步挪到插入的前一个节点
        }
        newNode->next = curr->next;
        curr->next = newNode;
    }
    size++; //加入新节点
}

void LinkedList::remove(int i){
    //处理异常
    if(i < 0 || i > size){
        throw std::out_of_range( "Invalid Position" );
    }
    //删除列表头
    if(i == 0){
        ListNode *temp = head;
        head = head -> next;
        delete temp;
    }else{
        ListNode *curr = head; //游标节点
        for(int j = 0; j < i - 1; j++){
            curr = curr->next; //一步一步挪到删除的前一个节点
        }
        ListNode *temp = curr -> next; //存储要删除的节点
        curr -> next = temp -> next; //将前置节点的next指向后继节点，跳过需要删除的节点
        delete temp;
    }
    size--;
}

ListNode *LinkedList::find(int value){
    ListNode *curr = head;
    //由于每个元素初始化next指针是NULL，所以如果遇到空的说明链表已遍历完成
    while(curr && curr -> data != value){
        curr = curr -> next;
    }
    return curr;
}

ListNode *LinkedList::get(int i){
    //处理异常
    if(i < 0 || i > size){
        throw std::out_of_range( "Invalid Position" );
    }
    ListNode *curr = head;
    for(int j = 0; j < i; j++){
        //此时直接找到索引节点
        curr = curr->next;
    }
    return curr;
}

void LinkedList::update(int i, int value){
    get(i)->data = value;
}

void LinkedList::print(){
    ListNode *curr = head;
    while(curr){
        cout << curr->data << " ";
        curr = curr -> next;
    }
    cout << endl;
}
