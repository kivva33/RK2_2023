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
    std::cout << "Node was destroyed\n";
}
Graph::Graph() : Graph::Graph(0){}
Graph::Graph(int countNodes){
    head = nullptr;
}
Graph::~Graph(){
    std::cout << "graph was destroyed\n";
    head = nullptr;
}
int Graph::buildTreeBFS(int countNodes){
    assert(countNodes > 0);
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
}
int Graph::buildTreeDFS(int countNodes){

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

}
/*функция обхода дерева в ширину
        при обходе графа записать результат в файл с название bfs_res
        Формат файла 0{1,2,3}\n 1{4,5}\n 2{6,7}\n 3{8,9}\n 4{10}\n 5{11}\n 6{12}\n 7{13}\n 8{14}\n 9{15}
\n -- новая строка
*/
void Graph::DFS(){

}
std::pair<bool, std::list<int>> Graph::searchDFS(int nameNode){}
std::pair<bool, std::list<int>> Graph::searchBFS(int nameNode){

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

NodeD* DoubleLinkedList::GetHead(){
    return Head;
}

NodeD* DoubleLinkedList::GetTail(){
    return Tail;
}

Node* DoubleLinkedList::get_element(){
    std::cout << "\nnone code\n\n";
}
bool DoubleLinkedList::get_information(){
    if(Head == nullptr)
        return true;
    return false;
}
void printDHead(DoubleLinkedList& l){
    NodeD* p = l.GetHead();
    if(p == nullptr){
        return;
    }
    while(p->next != nullptr) {
        std::cout << p->nameNode << std::endl;
        p = p->next;
    }
}
void printDTail(DoubleLinkedList& l){
    NodeD* p = l.GetTail();
    if(p == nullptr)
        return;
    p = p->prev;
    while(p != nullptr) {
        std::cout << p->nameNode << std::endl;
        p = p->prev;
    }
}

Node* FILO::get_element(){
    if(Tail->prev == nullptr){
        return 0;
    }
    Tail = Tail->prev;
    Tail->next = nullptr;
    return Tail->nameNode;
}
bool FILO::get_information(){
    if(Tail->prev == nullptr)
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
