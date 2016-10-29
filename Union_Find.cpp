//
//  main.cpp
//  Union Find
//
//  Created by Zijian Xie on 2016/10/28.
//  Copyright © 2016年 Jason Xie. All rights reserved.
//

#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Node{
public:
    int data;
    Node* parent;
    int rank;
    bool operator == (Node* node2){
        if(node2->data == data) return true;
        return false;
    }
};

class UnionFind{
private:
    unordered_map<int, Node*> mp;
public:
    void makeSet(int num){
        Node* node = new Node();
        node->data = num;
        node->rank = 0;
        node->parent = node;
        mp[num] = node;
        return;
    }
    
    void unionSet(int num1, int num2){
        Node* p1 = findSet(num1);
        Node* p2 = findSet(num2);
        if(p1 == p2) return;
        
        if(p1->rank >= p2->rank){
            p2->parent = p1;
            p1->rank = p1->rank == p2->rank ? p1->rank : p1->rank + 1;
        }else{
            p1->parent = p2;
        }
    }
    
    Node* findSet(int data){
        Node* node = mp[data];
        if(node->parent == node) return node;
        
        //Compression
        node->parent = findSet(node->parent->data);
        return node->parent;
    }
};

int main(int argc, const char * argv[]) {
    
    UnionFind* uf = new UnionFind();
    uf->makeSet(1);
    uf->makeSet(2);
    uf->makeSet(3);
    uf->makeSet(4);
    uf->makeSet(5);
    uf->makeSet(6);
    uf->makeSet(7);
    uf->makeSet(8);
    uf->makeSet(9);
    uf->makeSet(10);
    
    uf->unionSet(1,2);
    uf->unionSet(3,4);
    uf->unionSet(7,8);
    uf->unionSet(2,6);
    uf->unionSet(2,9);
    uf->unionSet(3,10);
    
    cout<<uf->findSet(1)->data<<endl;
    cout<<uf->findSet(2)->data<<endl;
    cout<<uf->findSet(3)->data<<endl;
    cout<<uf->findSet(4)->data<<endl;
    cout<<uf->findSet(5)->data<<endl;
    cout<<uf->findSet(6)->data<<endl;
    cout<<uf->findSet(7)->data<<endl;
    cout<<uf->findSet(8)->data<<endl;
    cout<<uf->findSet(9)->data<<endl;
    cout<<uf->findSet(10)->data<<endl;

    return 0;
}
