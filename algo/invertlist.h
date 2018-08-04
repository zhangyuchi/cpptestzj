#ifndef CPPTEST_INVERTLIST_H
#define CPPTEST_INVERTLIST_H

struct Node{
    int v;
    Node* next;
};

class InvertList{
public:
    InvertList()=default;
    Node* Run(Node* head){
        if (head == nullptr){
            return head;
        }
        Node *node = head;
        Node *prev = nullptr;
        Node *tail = nullptr;
        while(node != nullptr){
            Node *next = node->next;
            if (next == nullptr)
                tail = node;
            node->next=prev;
            prev = node;
            node = next;
        }

        return tail;
    }
};

#endif