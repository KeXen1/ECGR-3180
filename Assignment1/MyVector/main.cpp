#include <iostream>
#include <stdexcept>

using namespace std;

template<typename T>
class MyVector{
    public:
    // Default Constructor 
    MyVector(){
        dynArr = new T [3];
        nextIndex = 0;
        cap = 3;
    }
    
    // Constructor with size input
    MyVector(int size){
        dynArr = new T [size];
        nextIndex = 0;
        cap = size;
    }
    
    // Copy Constructor
    MyVector(const MyVector& vin){
        nextIndex = vin.nextIndex;
        cap = vin.cap;
        dynArr = new T [cap];
        
        for(int i = 0; i < nextIndex; i++){
            dynArr[i] = vin.dynArr[i];
        }
    }
    
    //Deconstructor
    ~MyVector(){
        delete[] dynArr;
    }
    
    // Copy Assignment Override
    void operator=(const MyVector& vin){
        delete[] dynArr;
        
        nextIndex = vin.nextIndex;
        cap = vin.cap;
        dynArr = new T [cap];
        
        for(int i = 0; i < nextIndex; i++){
            dynArr[i] = vin.dynArr[i];
        }
        
    }
    
    // Pushback
    void pushBack(T ele){
        if(nextIndex < cap){ // pushback the element
            dynArr[nextIndex] = ele;
            nextIndex++; 
        } else { // Out of space... Allocating more...
            cout << "Out of space... Allocating more..." << endl;
            T* temp = new T [cap * 2];
            for(int i = 0; i < cap; i++){
                temp[i] = dynArr[i];
            }
            
            delete[] dynArr;
            
            dynArr = temp;
            
            cap = cap * 2;
            
            dynArr[nextIndex] = ele;
            nextIndex++; 
        }
    }
    
    // Insert at index
    void insert(int i, T ele){
        T* temp = new T [cap + 1];
        for(int j = 0; j < cap; j++){
            if(j < i){
                temp[j] = dynArr[j];
            } else if(j == i){
                temp[j] = ele;
            } else {
                temp[j] = dynArr[j - 1];
            }
        }
        delete[] dynArr;
        
        dynArr = temp;
        nextIndex++;
    }
    
    // At()
    T& at(int i){
        if(i >= nextIndex){
            throw out_of_range("Index out of range");
        }
        return dynArr[i];
    }
    
    // Overloaded [] Operator
    T& operator[](int i){
        if(i >= nextIndex){
            throw out_of_range("Index out of range");;
        }
        return dynArr[i];
    }
    
    // Erase
    void erase(int i){
        T* temp = new T [cap - 1];
        for(int j = 0; j < cap - 2; j++){
            if(j < i){
                temp[j] = dynArr[j];
            } else if(j >= i){
                temp[j] = dynArr[j + 1];
            }
        }
        delete[] dynArr;
        
        dynArr = temp;
        nextIndex--;
    }
    
    // Size()
    int size(){
        return nextIndex;
    }
    
    // Empty()
    bool empty(){
        if(nextIndex == 0){
            return true;
        } else {
            return false;
        }
    }
    
    private:
    T* dynArr;
    int nextIndex;
    int cap;
};

int main(){
    try{
        MyVector<int> v; // Default Constructor
        
        cout << v.empty() << endl; // Empty() Output = 1/True
        
        v.pushBack(3); // pushBack
        v.pushBack(6);
        v.pushBack(9);
        v.pushBack(12); // Allocates more space Output = {3, 6, 9, 12}
        for(int i = 0; i < v.size(); i++){
            cout << v.at(i) << " ";
        }
        cout << endl;
        cout << v.empty() << endl; // Empty() Output = 0/False
        
        MyVector<int> v2(4); // Constructor with size input
        
        v2.pushBack(1);
        v2.pushBack(2);
        v2.pushBack(3);
        v2.pushBack(4); // No allocation should be made
        
        for(int i = 0; i < v2.size(); i++){
            cout << v2[i] << " ";
        }
        cout << endl;
        
        v.insert(2, 10); // Insert Output = {3, 6, 10, 9, 12}
        for(int i = 0; i < v.size(); i++){
            cout << v.at(i) << " ";
        }
        cout << endl;
        
        cout << v.at(2) << endl; // At() Output = 10
        
        cout << v[3] << endl; // Overloaded [] Output = 9
        
        v.erase(3); // Erase Output = {3, 6, 10, 12}
        for(int i = 0; i < v.size(); i++){
            cout << v.at(i) << " ";
        }
        cout << endl;
        
        MyVector<int> v3 = v; // Copy Constructor
        
        cout << v.size() << endl; // size() Output = 4
        
        v2 = v; // Copy Assignment Override
        
        
        for(int i = 0; i < v.size(); i++){
            cout << v.at(i) << " ";
        }
        cout << endl;
        
        for(int i = 0; i < v2.size(); i++){
            cout << v2[i] << " ";
        }
        cout << endl;
        
        for(int i = 0; i < v3.size(); i++){
            cout << v3.at(i) << " ";
        }
        cout << endl;
        
    } catch (out_of_range e){
        cout << e.what() << endl;
    }
    
    return 0; // Destructor
}