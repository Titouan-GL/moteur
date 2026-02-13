#include "node.h"

Node::Node()
{
    children = std::set<Node*>();
    parent = nullptr;
}

Node::Node(Node* parent){
    children = std::set<Node*>();
    this->parent = parent;

}

std::set<Node*> Node::getChildren() const{
    return children;
}

void Node::addChild(Node* &c){
    children.insert(c);
}

void Node::addChildren(std::set<Node*> &c){
    for (std::set<Node*>::iterator itr = c.begin(); itr != c.end(); ++itr) {
        children.insert(*itr);
    }
}

Node* Node::getParent() const{
    return parent;
}

void Node::setParent(Node* &p){
    Node* self = this;
    parent->removeChild(self);
    parent = p;
}

void Node::removeChild(Node* &c){
    if(c->getParent() != nullptr){
        c->removeParent();
    }
    children.erase(c);
}

void Node::removeParent(){
    Node* self = this;
    Node* temp_parent = parent;
    parent = nullptr;
    temp_parent->removeChild(self);
}
