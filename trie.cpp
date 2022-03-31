#include <algorithm>
#include <vector>
#include <string>

#include "heap.h"
#include "trie.h"

bool Trie::Node::Exists(const Node* node) {
    return node != nullptr;
}

bool Trie::Node::LeftExists() const {
    return Exists(this->left_);
}

bool Trie::Node::RightExists() const {
    return Exists(this->right_);
}

bool Trie::Node::IsLeaf() const {
    return !this->LeftExists() && !this->RightExists();
}

Trie::Node::Node(MyChar data, size_t occurrences) {
    data_ = data;
    occurrences_ = occurrences;
}

MyChar Trie::Node::GetDataInLeaf() const {
    return this->data_;
}

Trie::Node* Trie::Node::GetLeftChild() const {
    return this->left_;
}

Trie::Node* Trie::Node::GetRightChild() const {
    return this->right_;
}

Trie::Node* Trie::Node::Merge(Node* A, Node* B) {
    Node* C = new Node(NON, A->occurrences_ + B->occurrences_);
    C->left_ = A;
    C->right_ = B;
    return C;
}

std::pair<size_t, MyChar> Trie::Node::GetDataToCompare() const {
    if (!Exists(this)) {
        return std::make_pair(0, 0);
    }
    return std::make_pair(this->occurrences_, this->data_);
}

bool Trie::Node::IsLess(const Trie::Node& left_node, const Trie::Node& right_node) {
    return left_node.GetDataToCompare() < right_node.GetDataToCompare();
}

void Trie::Dfs(Node* vertex, size_t current_len, std::map<int8_t, std::vector<MyChar>>& lengths) {
    if (!Node::Exists(vertex)) {
        return;
    }
    if (vertex->IsLeaf()) {
        lengths[current_len].push_back(vertex->GetDataInLeaf());
        return;
    }
    Dfs(vertex->GetLeftChild(), current_len + 1, lengths);
    Dfs(vertex->GetRightChild(), current_len + 1, lengths);
}

std::map<MyChar, Trie::Code> TransformToCanonical(const std::map<int8_t, std::vector<MyChar>>& lengths) {
    std::map<MyChar, Trie::Code> result;
    Trie::Code current_mask;

    for (auto[len, vec]: lengths) {
        std::sort(vec.begin(), vec.end());
        while (static_cast<uint8_t>(current_mask.size()) < len) {
            Trie::MultTwo(current_mask);
        }
        for (auto data: vec) {
            result[data] = current_mask;
            Trie::AddOne(current_mask);
        }
    }
    return result;
}

std::map<MyChar, Trie::Code> Trie::GetCodes() {
    std::map<int8_t, std::vector<MyChar>> lengths;
    Dfs(root_, 0, lengths);
    return TransformToCanonical(lengths);
}

std::map<int8_t, std::vector<MyChar>> Trie::GetLengths() {
    std::map<int8_t, std::vector<MyChar>> lengths;
    Dfs(root_, 0, lengths);
    for (auto&[len, vec]: lengths) {
        std::sort(vec.begin(), vec.end());
    }
    return lengths;
}

void Trie::BuildTrie() {
    PriorityQueue queue;
    for (const auto& node: nodes_) {
        queue.Insert(node);
    }
    while (queue.Size() > 1) {
        Node* A = queue.Front();
        queue.Pop();
        Node* B = queue.Front();
        queue.Pop();
        Node* C = Node::Merge(A, B);
        nodes_.push_back(C);
        queue.Insert(C);
    }
    root_ = queue.Front();
}

Trie::Trie(const std::map<MyChar, size_t>& count_occurrences) {
    for (const auto &[ch, occurrences]: count_occurrences) {
        Node* current_node = new Node(ch, occurrences);
        nodes_.push_back(current_node);
    }
}

void Trie::AddNode(MyChar ch, Code code) {
    Node* v = root_;
    for (size_t i = 0; i < code.size(); i++) {
        if (code[i] == '1') {
            if (!v->RightExists()) {
                nodes_.push_back(new Node(ch, 1));
                v->right_ = nodes_.back();
            }
            v = v->GetRightChild();
        } else {
            if (!v->LeftExists()) {
                nodes_.push_back(new Node(ch, 1));
                v->left_ = nodes_.back();
            }
            v = v->GetLeftChild();
        }
    }
}

void Trie::BuildFromCodes(const std::map<MyChar, Code>& codes) {
    nodes_.push_back(new Node());
    root_ = nodes_.back();
    for (auto &[ch, code]: codes) {
        AddNode(ch, code);
    }
}

void Trie::AddOne(Trie::Code& code) {
    if (code.back() == '0') {
        code.back() = '1';
        return;
    }
    code.back() = '0';
    MyChar pos = code.size() - 2;
    while (true) {
        if (code[pos] == '0') {
            code[pos] += 1;
            break;
        }
        code[pos] = '0';
        if (pos == 0) {
            break;
        }
        pos -= 1;
    }
    if (std::count(code.begin(), code.end(), '1') == 0) {
        code[0] = '1';
    }
}

void Trie::MultTwo(Trie::Code& code) {
    code += "0";
}
