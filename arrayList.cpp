#include <iostream>
using namespace std;
template <class elemType>
class arrayList {
    elemType *itemsArray;
    int length;
    int maxSize ;
    public:
    arrayList(int maxSize = 100) {//O(1)
        if (maxSize < 1) {
            cout << "maxSize must be greater than 0" << endl;
        }
        else {
            length = 0;
            this->maxSize = maxSize;
            itemsArray = new elemType[maxSize];
            assert(itemsArray != NULL);//This line is a sanity check to ensure that memory allocation succeeded.
            /* Purpose of assert
                 1.assert(condition) is a debugging macro from <cassert>.
                 -If the condition is false, the program crashes immediately with an error message.
                 -If the condition is true, nothing happens (execution continues normally).
                 2. Why Check itemsArray != NULL?
                 -new elemType[maxSize] allocates memory for the array.
                 -If allocation fails (e.g., out of memory), new throws an exception in modern C++ (does not return NULL).
             */
        }
    }
    ~arrayList() {//O(1)
        delete[] itemsArray;
    }
    // COPY CONSTRUCTOR
    arrayList(const arrayList &other) {//O(n)
        itemsArray = new elemType[other.maxSize];
        assert(itemsArray != NULL); //terminate if unable to allocate memory space
        length = other.length;
        maxSize = other.maxSize;
        for (int i = 0; i < length; i++) { //Deep copy : safe
            itemsArray[i] = other.itemsArray[i];
        }
    }
    // OVERLOAD '=' OPERATOR
    //prototype explain :
    //(arrayList)-> To allow chaining (a = b = c , a = (b = c))
    //(&)->for returning the obl itself not a copy of it
    arrayList& operator=(const arrayList& other) {//O(n)
        //this: Pointer to the current object (left side of =, e.g., 'a' in a = b).
        //&other:Address of the assigned-from object(right side of =, e.g., b in a = b).
        if (this != &other) {  // Skip if self-assignment
            delete[] itemsArray;
            itemsArray = new elemType[other.maxSize];
            for (int i = 0; i < other.length; i++) {
                itemsArray[i] = other.itemsArray[i];
            }
        }
        return *this;
    }
    //const : This function does not modify the object's state
    bool isEmpty() const { //O(1)
        return length == 0;
    }
    bool isFull() const { //O(1)
        return length == maxSize;
    }
    int ListSize() const { //O(1)
        return length;
    }
    int maxListSize() const { //O(1)
        return maxSize;
    }
    void print() const {//O(n)
        for (int i = 0; i < length; i++) {
            cout << itemsArray[i] << " ";
        }
        cout << endl;
    }
    bool isItemEqual(int location , const elemType &item) const {//O(1)
        return item == itemsArray[location];
    }
    void insertAt(int index, const elemType &item) {//O(n)
        if (index > length || index < 0 || isFull() ) {
            cout << "The index is out of bound." << endl;
        }
        else {
            for (int i = length; i > index; i--) { //shifting right first
                itemsArray[i] = itemsArray[i - 1];
            }
            itemsArray[index] = item;
            length++;
        }
    }
    void insertEnd(const elemType &item) {//O(1)
        if (isFull() || length >= maxSize) {
            cout << "The list is full." << endl;
            return;
        }
        //   0    1     2     Index
        // { 44 , -8 , 7 } Length = 3
        // to insert 90
        //   0    1    2  ->(3)    Index
        // { 44 , -8 , 7  , 90}    Length = 4
        itemsArray[length] = item; //insert item at the end
        length++;
    }
    void insert(const elemType &insertItem) {//O(n)
        // insert at the end but not allowing duplicates
        int location;
        if (isEmpty()) {
            itemsArray[length++] = insertItem;
        }
        else if (length == maxSize) {
            cout << "The list is full." << endl;
        }
        else {
            location = seqSearch(insertItem);
            if (location == -1) { //the item to be inserted is not in the list
                itemsArray[length++] = insertItem;
            }
            else {
                cout <<"NO DUPLICATES ALLOWED !!" << endl;
            }
        }
    }
    void removeAt(const int& index) { //remove by giving the index only , O(n)
        if (isEmpty() || index >= length || index < 0) {
            cout << "The list is empty or out of range by the location number" << endl;
            return;
        }
        for (int i = index; i < length; i++) { //shifting left first
            itemsArray[i] = itemsArray[i + 1];
        }
        length--;
    }
    void remove(const elemType &item) { //remove by giving the element only , O(n)
        if (isEmpty()) {
            cout << "The list is empty." << endl;
            return;
        }
        int location = seqSearch(item);
        if (location != -1) {
            removeAt(location);
        }
        else {
            cout << "No such item in the list !" << endl;
        }
    }
    void retrieveAt(int index, elemType &item) const {//O(1)
        if (isEmpty()) {
            cout << "The list is empty." << endl;
            return;
        }
        if (index > length) {
            cout << "The index is out of bound." << endl;
            return;
        }
        item = itemsArray[index];
    }
    void replaceAt(int index, const elemType &item) {//O(1)
        if (isEmpty() || index >= length || index < 0) {
            cout << "ERROR!" << endl;
            return;
        }
        itemsArray[index] = item;
    }
    void clearList() {//O(1)
        length = 0;
    }
    int seqSearch(const elemType &item) const {
        if (isEmpty()) {
            cout << "The list is empty." << endl;
            return 0;
        }
        bool isFound = false;
        int location ;
        for (location = 0; location < length; location++) {
            if (item == itemsArray[location]) {
                isFound = true;
                break;
            }
        }
        if (isFound) {
            return location;
        }
        return -1;
    }

};
int main() {

    return 0;
}