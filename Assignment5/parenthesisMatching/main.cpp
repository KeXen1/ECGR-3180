/* 
Write a function that returns if a string of paranthesis are matched. 
You are required to use the STL stack datastructure in your code for O(n) time complexity.
See 5.17 in the book for problem description and a stack based algorithm. 
*/
#include <iostream>
#include <stack>
#include <vector>

using namespace std; 
  
// function to check if paranthesis are balanced 
bool areParanthesisBalanced(string expr) {
// Your code here
    stack<char> s;
    
    for(auto& character : expr){
        if(character == '(' || character == '{' || character == '['){
            s.push(character);
        } else{
            if(s.empty()) return false;
            
            char lastParan = s.top();
            s.pop();
            if((character == ')' && lastParan != '(') || (character == '}' && lastParan != '{') || (character == ']' && lastParan != '[')){
                return false;
            }
        }
    }

    return s.empty();
} 
  
// Test - DO NOT MODIFY
int main() 
{ 
    vector<string> parans = {"{()}[]", "[[", "))", "{[()]}", "({[])}"}; 
  	
	for(auto expr : parans) {
    	if (areParanthesisBalanced(expr)) 
        	cout << "Balanced" << endl; 
    	else
        	cout << "Not Balanced" << endl;
	} 
    return 0; 
}
