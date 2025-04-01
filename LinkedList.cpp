#include <iostream>
using namespace std;

template <class T>
class Node {  // Node [data | pointer to next node]
    T data;
    Node* next;  // Pointer should have same type as what it points to

public:
    Node() : next(nullptr) {};
    Node(T data) : data(data), next(nullptr) {};
};

template <class Type>
class LinkedListIterator {
    Node<Type>* current; // Pointer to current node

public:
    // Type aliases (STL convention)
    using value_type = Type;
    using difference_type = std::ptrdiff_t;
    using pointer = Type*;
    using reference = Type&;
    using iterator_category = std::forward_iterator_tag;

    LinkedListIterator() : current(nullptr) {}

    /**
     * @brief Construct from node pointer
     * @param node Pointer to node to start iteration from
     */
    explicit LinkedListIterator(Node<Type>* node) : current(node) {}

    /**
     * @brief Dereference operator - access current node's data
     * @return Reference to current node's data
     * @throws std::out_of_range if iterator is invalid
     */
    Type& operator*() {
        if (!current) {
            throw std::out_of_range("Dereferencing null iterator");
        }
        return current->data;
    }

    /**
     * @brief Arrow operator - access current node's members
     * @return Pointer to current node's data
     */
    Type* operator->() {
        return &(operator*());
    }

    /**
     * @brief Prefix increment (++it)
     * @return Reference to advanced iterator
     */
    LinkedListIterator& operator++() {
        if (current) {
            current = current->next;
        }
        return *this;
    }

    /**
     * @brief Postfix increment (it++)
     * @return Copy of iterator before advancement
     */
    LinkedListIterator operator++(int) {
        LinkedListIterator temp = *this;
        ++(*this);
        return temp;
    }

    /**
     * @brief Equality comparison
     * @param other Iterator to compare with
     * @return true if both point to same node
     */
    bool operator==(const LinkedListIterator& other) const {
        return current == other.current;
    }

    /**
     * @brief Inequality comparison
     * @param other Iterator to compare with
     * @return true if point to different nodes
     */
    bool operator!=(const LinkedListIterator& other) const {
        return !(*this == other);
    }
};

// Building unSorted LinkedList
template <class T>
class LinkedList {
    int size{};      // Number of elements in the linked list
    Node<T>* head; // Starting point (pointer to first node)
    Node<T>* tail; // Points to last node

public:
    LinkedList(){
        destroyList(); //Destroy all previous nodes and reset all data items
    }

    //  Destroys all nodes in the list
    void destroyList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        size = 0;
    }
    bool isEmpty() const {
        return head == nullptr;
    }
    void print () const {
        Node<T>* current = head;
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
    }
    int length() const {
        return size;
    }
    T front() const {
        assert(head != nullptr);
        return head->data; //return the info of the first node
    }
    T back() const {
        assert(tail != nullptr);
        return tail->data;
    }
    LinkedListIterator<T> begin() const {
        return LinkedListIterator<T>(head);
    }
    LinkedListIterator<T> end() const {
        return LinkedListIterator<T>(nullptr);
    }
    /*
    The end() iterator isn't supposed to point to the last element -
    it's supposed to point to where you'd put a new element
    if you were doing insertion at the end.
    For linked lists, this is always nullptr.
                            For list: [A] -> [B] -> [C] -> nullptr
    (end() = nullptr):
    begin() -> A
    ++ -> B
    ++ -> C
    ++ -> nullptr (end())
    Processes: A, B, C

    (end() = tail/C):
    begin() -> A
    ++ -> B
    ++ -> C (equal to end(), stops)
    Processes: A, B (misses C)
     */

    /**
     * @brief Makes a deep copy of another linked list
     * @param otherList The list to copy from
     * Steps:
     * 1. Clears current list if not empty
     * 2. Handles case when source list is empty
     * 3. Copies first node separately (needs to set 'head')
     * 4. Copies remaining nodes in sequence
     * 5. Maintains proper tail pointer and size
     */
    void copyList(const LinkedList<T>& otherList) {
        // 1. Clear current list if not empty
        if (!isEmpty()) {
            destroyList();
        }

        // 2. Handle empty source list case
        if (otherList.head == nullptr) {
            head = tail = nullptr;
            size = 0;
            return;
        }

        // 3. Head requires special handling (must be set once)
        Node<T>* currentOther = otherList.head; //currentOther tracks source position (starts at source head)
        head = new Node<T>(currentOther->data);//Establishes the new list's head node
        Node<T>* currentThis = head; //currentThis tracks destination position
        size = otherList.size; //Copies the total size once (more efficient than incrementing)
        currentOther = currentOther->next; //Advances source pointer to next node

        // 4. Copy remaining nodes
        while (currentOther != nullptr) {
            Node<T>* newNode = new Node<T>(currentOther->data); // Deep copy of data
            currentThis->next = newNode; //(links new node)
            currentThis = newNode; //advances destination pointer
            currentOther = currentOther->next; //moves to next source node
        }

        // 5. Set tail pointer
        tail = currentThis;
    }
    /**
    * @brief Copy constructor - creates a new list as a copy of another
    * @param other The list to copy from
    * Uses copyList() to avoid code duplication
    */
    LinkedList(const LinkedList<T>& other) : head(nullptr), tail(nullptr), size(0) {
        copyList(other);
    }
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            destroyList();  // Clear current contents
            copyList(other);  // Copy new contents
        }
        return *this;
    }

    // Insert node at end of the linked list
    void buildListForward(T data) {
        Node<T>* newNode = new Node<T>(data);

        if (head == nullptr) {  // Empty list check
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;  // Connect current tail to new node
            tail = newNode;        // Update tail to point to new node
        }
        newNode->next = nullptr;   // Always set new node's next to null
        size++;
    }

    // Insert node at beginning of the linked list
    void buildListBackward(T data) {
        Node<T>* newNode = new Node<T>(data);

        if (head == nullptr) {  // Empty list check
            head = newNode;
            tail = newNode;
        }
        else {
            newNode->next = head;  // New node points to current head
            head = newNode;        // Update head to point to new node
        }
        size++;
    }
    bool search(const T& searchItem) const {
        Node<T>* current = head;  // Start at head

        while (current != nullptr) {
            if (current->data == searchItem) {
                return true;  // Found match
            }
            current = current->next;  // Move to next node
        }

        return false;  // Reached end without finding
    }
    bool deleteNode(const T& deleteItem) {
        // Case 1: Empty list
        if (isEmpty()) {
            std::cout << "Cannot delete from empty list." << std::endl;
            return false;
        }

        Node<T>* current = head;
        Node<T>* previous = nullptr;
        bool found = false;

        // Search for the node to delete
        while (current != nullptr && !found) {
            if (current->data == deleteItem) {
                found = true;
            } else {
                previous = current;
                current = current->next;
            }
        }

        // Case 5: Item not found
        if (!found) {
            cout << "Item " << deleteItem << " not found in list." << endl;
            return false;
        }

        // Case 2: Deleting first node
        if (previous == nullptr) {
            head = head->next;
            // If list had only one node
            if (head == nullptr) {
                tail = nullptr;
            }
        }
        // Case 3 & 4: Deleting middle or last node
        else {
            previous->next = current->next;
            // Case 4: Deleting last node
            if (current == tail) {
                tail = previous;
            }
        }

        // Common cleanup for all deletion cases
        cout << "Deleted node with value: " << current->data << std::endl;
        delete current;
        size--;

        return true;
    }
    ~LinkedList() {
        destroyList();  // Reuse the cleanup logic
    }
};


