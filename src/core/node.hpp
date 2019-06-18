#pragma once

// a node in the scene graph. can have either one or no parent and any
// number of children

#include <memory>
#include <list>

class Node;

typedef std::shared_ptr<Node>   NodePtr;
typedef std::list<NodePtr>      NodeList;

class Node : public std::enable_shared_from_this<Node>
{
public:
    static NodePtr create(std::string name);

    Node(std::string name);
    Node(Node& other);
    ~Node();

    std::string name();
    NodePtr     parent();
    NodeList    children();
    NodePtr     find(std::string name);
    NodePtr     root();

    void addChild(NodePtr node);
    void removeChild(NodePtr node);
    void setParent(NodePtr node);

private:
    std::string name_;
    NodePtr     parent_;
    NodeList    children_;
};
