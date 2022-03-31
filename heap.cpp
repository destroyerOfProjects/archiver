#include "heap.h"

void PriorityQueue::Insert(Trie::Node* item) {
    LeftistNode* elem = new LeftistNode(item);
    nodes_.push_back(elem);
    root_ = Merge(root_, elem);
    size_ += 1;
}

void PriorityQueue::Pop() {
    if (root_ == nullptr) {
        throw;
    }
    size_ -= 1;
    root_ = Merge(root_->left, root_->right);
}

Trie::Node* PriorityQueue::Front() const {
    if (root_ == nullptr) {
        throw;
    }
    return root_->data;
}

int8_t PriorityQueue::Size() const {
    return size_;
}

PriorityQueue::LeftistNode* PriorityQueue::Merge(PriorityQueue::LeftistNode* left_node,
                                                 PriorityQueue::LeftistNode* right_node) {
    if (left_node == nullptr) {
        return right_node;
    }
    if (right_node == nullptr) {
        return left_node;
    }
    if (Trie::Node::IsLess(*right_node->data, *left_node->data)) {
        std::swap(left_node, right_node);
    }
    left_node->right = Merge(left_node->right, right_node);
    if (PriorityQueue::LeftistNode::GetDistance(left_node->left) <
        PriorityQueue::LeftistNode::GetDistance(left_node->right)) {
        std::swap(left_node->left, left_node->right);
    }
    left_node->distance = PriorityQueue::LeftistNode::GetDistance(left_node->right) + 1;
    return left_node;
}

PriorityQueue::~PriorityQueue() {
    while (!nodes_.empty()) {
        delete nodes_.back();
        nodes_.pop_back();
    }
    delete root_;
}

PriorityQueue::LeftistNode::LeftistNode(Trie::Node* data) : data(data) {
    distance = 0;
    left = 0;
    right = 0;
}

int8_t PriorityQueue::LeftistNode::GetDistance(PriorityQueue::LeftistNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->distance;
}
