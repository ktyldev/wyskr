#include <algorithm>

#include "core/node.hpp"

NodePtr Node::create(std::string name)
{
    return std::make_shared<Node>(name);
}

Node::Node(std::string name) :
    name_(name),
    parent_(nullptr)
{
}

Node::Node(Node& other)
{
    name_ = other.name();
    parent_ = other.parent();
    children_ = other.children();
}

Node::~Node()
{
}

std::string Node::name()
{
    return name_;
}

NodePtr Node::parent()
{
    return parent_;    
}

NodeList Node::children()
{
    return children_;
}

NodePtr Node::find(std::string name)
{
    // check if this is the node we're looking for
    if (name_ == name)
        return shared_from_this();

    // if this isn't the node we're looking for and there are no
    // children, bail
    if (children_.size() == 0)
        return nullptr;

    // check if one of our children is the node we're looking for
    for (NodeList::const_iterator it = children_.begin(),
        end = children_.end();
        it != end;
        ++it)
    {
        if ((*it)->find(name) != nullptr)
            return *it;
    }

    // recursively look in children
    for (auto&& n : children_)
    {
        if (n->find(name) != nullptr)
            return n;
    }

    // search exhausted; this node and its children aren't what we're
    // looking for
    return nullptr;
}

NodePtr Node::root()
{
    NodePtr parent = parent_;
    NodePtr current = shared_from_this();
    
    while (parent != nullptr)
    {
        current = parent;
        parent = parent_->parent();
    }

    return current;
}

void Node::addChild(NodePtr node)
{
    if (find(node->name()) != nullptr)
        throw "child already added";

    children_.push_back(node);
    node->setParent(shared_from_this());
}

void Node::removeChild(NodePtr node)
{
    bool found = std::find(
        children_.begin(), 
        children_.end(), 
        node) != children_.end();    

    if (!found)
        throw "child not present";

    children_.remove(node);
    node->setParent(nullptr);
}

void Node::setParent(NodePtr node)
{
    parent_ = std::shared_ptr<Node>(node);
}
