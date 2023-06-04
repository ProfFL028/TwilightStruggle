//
// Created by fangli on 2023/5/1.
//

#ifndef DBFROMSCRATCH_BTREE_H
#define DBFROMSCRATCH_BTREE_H

#include <iostream>
#include <vector>

template<class KeyT, class ValueT>
class BTree {
private:
    struct Node {
        bool isLeaf;
        std::vector<KeyT> keys;
        std::vector<ValueT> values;
        std::vector<Node*> children;
        Node(bool isLeaf = false) : isLeaf(isLeaf), keys(), values(), children() {}
        ~Node() {
            for (size_t i = 0; i < children.size(); ++i) {
                delete children[i];
            }
        }
    };
    Node* root;
    const size_t min_children = 2;
    const size_t max_children = 4;

    void split(Node* node, size_t index) {
        Node* new_node = new Node(node->isLeaf);
        new_node->keys.insert(new_node->keys.begin(), node->keys.begin() + index + 1, node->keys.end());
        new_node->values.insert(new_node->values.begin(), node->values.begin() + index + 1, node->values.end());
        new_node->children.insert(new_node->children.begin(), node->children.begin() + index + 1, node->children.end());
        node->keys.erase(node->keys.begin() + index, node->keys.end());
        node->values.erase(node->values.begin() + index, node->values.end());
        node->children.erase(node->children.begin() + index + 1, node->children.end());
        if (node == root) {
            root = new Node(false);
            node->isLeaf = false;
            root->keys.push_back(new_node->keys.front());
            root->children.push_back(node);
            root->children.push_back(new_node);
        } else {
            Node* parent = find_parent(root, node);
            size_t i = 0;
            for (; i < parent->children.size() && parent->children[i] != node; ++i) {}
            parent->keys.insert(parent->keys.begin() + i, new_node->keys.front());
            parent->children.insert(parent->children.begin() + i + 1, new_node);
        }
    }

    Node* find_node(Node* node, const KeyT& key) {
        size_t i = 0;
        while (i < node->keys.size() && key > node->keys[i]) {
            ++i;
        }
        if (node->isLeaf) {
            return node;
        }
        return find_node(node->children[i], key);
    }

    Node* find_parent(Node* node, Node* child) {
        if (node->isLeaf) {
            return nullptr;
        }
        for (size_t i = 0; i < node->children.size(); ++i) {
            if (node->children[i] == child) {
                return node;
            }
            Node* parent = find_parent(node->children[i], child);
            if (parent) {
                return parent;
            }
        }
        return nullptr;
    }

public:
    BTree() : root(nullptr) {}
    ~BTree() {
        delete root;
    }

    void insert(const KeyT& key, const ValueT& value) {
        if (!root) {
            root = new Node(true);
            root->keys.push_back(key);
            root->values.push_back(value);
            return;
        }
        Node* node = find_node(root, key);
        size_t i = 0;
        for (; i < node->keys.size() && key > node->keys[i]; ++i) {}
        if (node->keys.size() < max_children - 1) {
            node->keys.insert(node->keys.begin() + i, key);
            node->values.insert(node->values.begin() + i, value);
        } else {
            node->keys.insert(node->keys.begin() + i, key);
            node->values.insert(node->values.begin() + i, value);
            split(node, max_children / 2 - 1);
        }
    }

    ValueT* find(const KeyT& key) {
        if (!root) {
            return nullptr;
        }
        Node* node = find_node(root, key);
        size_t i = 0;
        for (; i < node->keys.size() && key > node->keys[i]; ++i) {}
        if (i < node->keys.size() && key == node->keys[i]) {
            return &node->values[i];
        } else {
            return nullptr;
        }
    }
};


#endif //DBFROMSCRATCH_BTREE_H
