#include <iostream>
#include <list>

struct Node {//структура, в которой хранится ячейка
    Node();
    Node(int nameNode);
    ~Node();

    Node* parent;
    std::list<Node*> listChilds;//класс списка, реализованный кем-то очень хорошим
    int name;
    static int countNodes;
};
class Graph {//
private :
    Node* head;
    void buildTreeDFS(Node* parent, int countNodes);
    void DFS(Node* parent, FILE* f);
public :
    Graph();
    Graph(int countNodes);
    ~Graph();
    int buildTreeBFS(int countNodes);
    int buildTreeDFS(int countNodes);
    void BFS();
    void DFS();

    std::pair<bool, std::list<int>> searchDFS(int nameNode);
    std::pair<bool, std::list<int>> searchBFS(int nameNode);
};

class IData{
public:
    virtual void push_back(Node* node) = 0;
    virtual Node* get_element() = 0;
};

class NodeD {
public:
    NodeD* next;
    NodeD* prev;
    Node* nameNode;
    static int countNodes;
};
class DoubleLinkedList : public IData{
protected:
    NodeD* Head;
    NodeD* Tail;
public:
    DoubleLinkedList();
    ~DoubleLinkedList();
    void deletenode(NodeD* l);
    void deletelist();
    void push_back(Node* nameNode) override;
    virtual Node* get_element() override;
    virtual bool get_information();
};

class FIFO : public DoubleLinkedList {
public:
    Node *get_element() override;
    bool get_information() override;
};

void task_1();