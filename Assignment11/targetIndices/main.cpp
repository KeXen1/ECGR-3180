#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> targetIndices(vector<int>& nums, int target) {
        vector<int> result;
        int maxVal = *max_element(nums.begin(), nums.end());
        vector<int> count(maxVal + 1, 0);
        
        if(nums.empty()) return result;
        
        for(int val : nums){
            count[val]++;
        }
        
        if (target > maxVal) return result; 
        
        int countLessThanTarget = 0;
        for(int i = 0; i < target; i++){
            countLessThanTarget += count[i]; 
        }
        
        for(int i = 0; i < count[target]; i++){
            result.push_back(countLessThanTarget + i);
        }
        
        return result; 
    }
};

void runTest(vector<int> nums, int target, vector<int> expected) {
    Solution sol;
    vector<int> result = sol.targetIndices(nums, target);
    
    if (result == expected) {
        cout << "Test passed!" << endl;
    } else {
        cout << "Test failed." << endl;
        cout << "Expected: ";
        for (int idx : expected) {
            cout << idx << " ";
        }
        cout << "\nGot: ";
        for (int idx : result) {
            cout << idx << " ";
        }
        cout << endl;
    }
}

int main() {
    // Test cases
    runTest({1, 2, 5, 2, 3}, 2, {1, 2});
    runTest({1, 2, 5, 2, 3}, 3, {3});
    runTest({1, 2, 5, 2, 3}, 5, {4});
    runTest({1, 2, 5, 2, 3}, 4, {});
    runTest({1, 1, 1, 1, 1}, 1, {0, 1, 2, 3, 4});
    runTest({1, 1, 1, 1, 1}, 2, {});
    
    return 0;
}