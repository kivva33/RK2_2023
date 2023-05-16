#include "tasks_rk2.h"
#include "iterator"
#include "cassert"
int Node::countNodes = 0;

Node::Node() : Node::Node(0){}
Node::Node(int nameNode){
    name = countNodes++;
    parent = nullptr;
}
Node::~Node(){
    std::destroy(listChilds.begin(),listChilds.end());
    std::cout << "\nNode was destroyed\n";
}
Graph::Graph() : Graph::Graph(0){}
Graph::Graph(int countNodes){
    head = nullptr;
}
Graph::~Graph(){
    std::cout << "\ngraph was destroyed\n";
    head = nullptr;
}
static int count = 0;

int Graph::buildTreeBFS(int countNodes){
    if(countNodes < 0)
        return -1;
    FIFO* stack = new FIFO;
    head = new Node;
    stack->push_back(head);
    Node* parent;
    int node = 0;
    head->name = node++;
    int count = countNodes, nowcount = 0;
    while(countNodes){
        parent = stack->get_element();
        for(int i = 0; i < countNodes; i++) {
            Node* f = new Node;
            f->parent = parent;
            f->name = node++;
            parent->listChilds.push_back(f);
            stack->push_back(f);
            nowcount++;
        }
        if(count == nowcount){
            countNodes--;
            nowcount = 0;
            count *= countNodes;
        }
    }
    return 0;
}
int Graph::buildTreeDFS(int countNodes){
    if(countNodes < 0)
        return -1;
    head = new Node;
    count = 0;
    head->name = count++;
    buildTreeDFS(head, countNodes);
    return 0;
}
void Graph::buildTreeDFS(Node* parent, int countNodes){
    if(countNodes > 0)
        for(int i = 0; i < countNodes; i++){
            Node* f = new Node;
            f->name = count++;
            parent->listChilds.push_back(f);
            buildTreeDFS(f, countNodes - 1);
        }
}

void Graph::BFS(){
    FILE* f = fopen("bfs_res", "w");
    FIFO* stack = new FIFO;
    stack->push_back(head);
    Node* parent;
    while(!stack->get_information()){
        parent = stack->get_element();
        fprintf(f, "%d%c", parent->name, '{');
        for(std::list <Node*> :: iterator it = parent->listChilds.begin(); it != parent->listChilds.end(); it++){
            fprintf(f, "%d",(*it)->name);
            if (!(std::next(it) == parent->listChilds.end())){
                fprintf(f, "%c ", ',');
            }
            if((*it)->listChilds.size()) {
                stack->push_back(*it);
            }
        }
       fprintf(f, "%c\n",'}');
    }
    fclose(f);


}
void Graph::DFS(){
    FILE* f = fopen("dfs_res", "w");
    DFS(head, f);
    fclose(f);
}
void Graph::DFS(Node* parent, FILE* f) {
    fprintf(f, "%d", parent->name);
    if(parent->listChilds.size()){
        fprintf(f, "%c", '{');
    }
    for (std::list<Node *>::iterator it = parent->listChilds.begin(); it != parent->listChilds.end(); it++) {
            DFS(*it, f);
        if (!(std::next(it) == parent->listChilds.end()))
            fprintf(f, "%c", ',');
    }
    if(parent->listChilds.size())
        fprintf(f, "%c", '}');

}

std::pair<bool, std::list<int>> Graph::searchDFS(int nameNode){
    std::cout << std::endl;
}
std::pair<bool, std::list<int>> Graph::searchBFS(int nameNode){
    std::cout << std::endl;
}
DoubleLinkedList::DoubleLinkedList(){
    Head = nullptr;
    Tail = nullptr;
}

DoubleLinkedList::~DoubleLinkedList(){
    deletelist();
}

void DoubleLinkedList::deletenode(NodeD* l){
    delete l;
}

void DoubleLinkedList::deletelist(){
    NodeD* p = Head;
    p = p->next;
    while(p != Tail){
        deletenode(p->prev);
        p = p->next;
    }
    deletenode(p);
    Head = nullptr;
    Tail = nullptr;
}

void DoubleLinkedList::push_back(Node* nameNode){
    if(Head == nullptr){
        Head = new NodeD;
        Tail = new NodeD;
        Head->prev = nullptr;
        Head->next = Tail;
        Tail->prev = Head;
        Tail->next = nullptr;
        Head->nameNode = nameNode;
    }
    else{
        NodeD* p = new NodeD;
        Tail->nameNode = nameNode;
        Tail->next = p;
        p->prev = Tail;
        p->next = nullptr;
        Tail = p;
    }
}

Node* DoubleLinkedList::get_element(){
    std::cout << "\nnone code\n\n";
}

bool DoubleLinkedList::get_information(){
    if(Head == nullptr)
        return true;
    return false;
}

Node* FIFO::get_element(){
    if(Head->next == nullptr){
        return 0;
    }
    Node* i = Head->nameNode;
    Head = Head->next;
    Head->prev = nullptr;
    return i;
}

bool FIFO::get_information() {
    if(Head->next == nullptr)
        return true;
    return false;
}

void task_1(){
    Graph p;
    p.buildTreeDFS(3);
    p.DFS();

    p.buildTreeBFS(3);
    p.BFS();
}