//
// Created by os on 6/18/23.
//

//kod u ovom fajlu je preuzet sa vezbi

#ifndef PROJECT_BASE_LIST_HPP
#define PROJECT_BASE_LIST_HPP

template <typename T>
class List{
public:
    List(): head(nullptr), tail(nullptr){}

    void addFirst(T* data);
    void addLast(T* data);
    T* removeFirst();
    T* removeLast();
    T* peekFirst() const;
    T* peekLast() const;

private:
    struct Node{
    T* data;
    Node* next;

    Node(T* data, Node* next = nullptr): data(data), next(next){}
    };
    Node* head, *tail;
};

template <typename T>
inline void List<T>::addFirst(T *data) {
    Node* node = new Node(data, head);
    head = node;
    if(!tail)
        tail = head;
}

template <typename T>
inline void List<T>::addLast(T* data){
    Node* node = new Node(data);
    if(!tail){
        tail = node;
        head = node;
    }
    else{
        tail->next = node;
        tail = node;
    }
}

template <typename T>
inline T* List<T>::removeFirst() {
    if(!head)
        return nullptr;
    Node* node = head;
    head = head->next;
    if(!head)
        tail = nullptr;
    T* ret = node->data;
    delete node;
    return ret;
}

template <typename T>
inline T* List<T>::removeLast() {
    if(!head || !tail)
        return nullptr;
    Node* previous = nullptr;
    Node* current = head;
    while(current && current != tail){
        previous = current;
        current = current->next;
    }
    Node* node = tail;
    if(previous)
        previous->next = nullptr;
    else
        head = nullptr;
    tail = previous;
    T* ret = node->data;
    delete node;
    return ret;
}

template <typename T>
inline T* List<T>::peekFirst() const {
    if(!head)
        return nullptr;
    return head->data;
}

template <typename T>
inline T* List<T>::peekLast() const {
    if(!head || !tail)
        return nullptr;
    return tail->data;
}

#endif //PROJECT_BASE_LIST_HPP
