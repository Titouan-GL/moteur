

#pragma once

#include <set>

class Node
{
public:
    Node();
    Node(Node* parent);
    std::set<Node*> getChildren() const;
    void addChild(Node* &c);
    void addChildren(std::set<Node*> &c);
    void removeChild(Node* &c);
    void removeParent();
    Node* getParent() const;
    void setParent(Node* &p);

private:
    std::set<Node*> children;
    Node* parent;
};
