#ifndef CPP_PILOT_HSE_HEAP_H
#define CPP_PILOT_HSE_HEAP_H

#include <queue>
#include <string>

#include "trie.h"

class PriorityQueue {
public:
    void Insert(Trie::Node* item);

    void Pop();

    Trie::Node* Front() const;

    int8_t Size() const;

    ~PriorityQueue();

private:
    struct LeftistNode {
        Trie::Node* data;
        int8_t distance;
        LeftistNode* left;
        LeftistNode* right;

        LeftistNode(Trie::Node* data);

        static int8_t GetDistance(PriorityQueue::LeftistNode* node);
    };

    LeftistNode* Merge(LeftistNode* left_node, LeftistNode* right_node);

    LeftistNode* root_ = nullptr;
    int8_t size_ = 0;
    std::vector<LeftistNode*> nodes_;
};

#endif  // CPP_PILOT_HSE_HEAP_H
