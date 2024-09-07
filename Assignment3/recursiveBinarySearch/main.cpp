#include <iostream>
#include <vector>

using namespace std;

int recursiveBinarySearch(vector<int>& vec, int start, int end, int targetVal){
    
    // Base case
    if(start >= end){
        return -1;
    }
    
    // Find middle of vector
    int mid = ((end - start) / 2) + start;
    
    if(vec[mid] == targetVal){
        return mid; // Base case
    } else if(vec[mid] > targetVal){ // Recursion
        return recursiveBinarySearch(vec, start, mid - 1, targetVal);
    } else {
        return recursiveBinarySearch(vec, mid + 1, end, targetVal);
    }
}

int binarySearch(vector<int>& vec, int targetVal){
	return recursiveBinarySearch(vec, 0, vec.size()-1, targetVal);
}

int main(){
    vector<int> vec1 = {0, 1, 2, 3, 4, 6 , 7, 8, 9, 10};
    vector<int> vec2 = {0, 1, 2, 2, 3, 4, 6 , 7, 9, 9};
    vector<int> vec3 = {2, 2, 2, 3, 5, 6, 7, 8, 9};

        
    cout << "Index of vec1 that matches target value of 5: " << binarySearch(vec1, 5) << endl; // Does not exist 
    cout << "Index of vec2 that matches target value of 9: " << binarySearch(vec2, 9) << endl; // Leftmost case
    cout << "Index of vec2 that matches target value of 2: " << binarySearch(vec2, 2) << endl; // Duplicate entries case
    cout << "Index of vec3 that matches target value of 2: " << binarySearch(vec3, 2) << endl; // Rightmost
    cout << "Index of vec3 that matches target value of 5: " << binarySearch(vec3, 5) << endl; // Middle case
    
    return 0;
}