#ifndef CPP_PILOT_HSE_TRIE_H
#define CPP_PILOT_HSE_TRIE_H

#include <map>
#include <vector>
#include <string>

#include "my_char.h"

class Trie {
public:
    using Code = std::string;

    static void AddOne(Code& code);

    static void MultTwo(Code& code);

    class Node {
    public:
        static bool Exists(const Node* node);

        static Node* Merge(Node* A, Node* B);

        bool LeftExists() const;

        bool RightExists() const;

        bool IsLeaf() const;

        std::pair<size_t, MyChar> GetDataToCompare() const;

        MyChar GetDataInLeaf() const;

        Node* GetLeftChild() const;

        Node* GetRightChild() const;

        static bool IsLess(const Node& left_node, const Node& right_node);

    public:
        Node() {
        }

        Node(MyChar data, size_t occurrences);

        Node* left_ = nullptr;
        Node* right_ = nullptr;

    private:
        MyChar data_ = 0;
        size_t occurrences_ = 0;
    };

    void Dfs(Node* vertex, size_t len, std::map<int8_t, std::vector<MyChar>>& lengths);

    void BuildFromCodes(const std::map<MyChar, Code>& codes);

    Trie(const std::map<MyChar, size_t>& count_occurrences);

    Trie() {
    }

    void AddNode(MyChar data, Code code);

    ~Trie() {
        nodes_.clear();
    }

    void BuildTrie();

    std::map<MyChar, Code> GetCodes();

    std::map<int8_t, std::vector<MyChar>> GetLengths();

    Node* root_;

private:
    std::vector<Node*> nodes_;
};

#endif  // CPP_PILOT_HSE_TRIE_H
