#include <iostream>
#include <queue>

using namespace std; 

class MyStack {
public:
    queue<int> queue1;
    queue<int> queue2;
    
    MyStack() {}
    
    void push(int x) {
        queue2.push(x);
        
        while(queue1.empty() != true){
            queue2.push(queue1.front());
            queue1.pop();
        }
        
        swap(queue1, queue2);
    }
    
    int pop() {
        int result = queue1.front();
        queue1.pop();
        
        return result;
    }
    
    int top() {
        return queue1.front();
    }
    
    bool empty() {
        return queue1.empty();
    }
};

// Test Code
int main(){
    MyStack myStack;
    
    myStack.push(1);
    myStack.push(2);
    
    cout << myStack.top() << endl; // return 2
    cout << myStack.pop() << endl; // return 2
    cout << myStack.top() << endl; // return 1 due to 2 being popped
    
    if(myStack.empty()){
        cout << "True" << endl;
    } else {
        cout << "False" << endl; // return False
    }
    
    return 0;
}