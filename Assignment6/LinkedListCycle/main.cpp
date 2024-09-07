#include <iostream>
#include <unordered_set>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
 
class Solution {
public:
    bool hasCycle(ListNode *head) {
        unordered_set<ListNode*> visitedNodes;
        ListNode* currentNode = head;
        while(currentNode != nullptr){
            if(visitedNodes.find(currentNode) != visitedNodes.end()){
                return true;
            }
            visitedNodes.insert(currentNode);
            currentNode = currentNode->next;
        }
        return false;
    }
};

/* Two Pointers method
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode *slowPtr = head, *fastPtr = head;
        while (fastPtr != nullptr && fastPtr->next != nullptr) {
            slowPtr = slowPtr->next;
            fastPtr = fastPtr->next->next;
            if (slowPtr == fastPtr) {
                return true;
            }
        }
        return false;
    }
};

*/
// Function to create a cycle in the linked list
void createCycle(ListNode* head, int pos) {
    if (pos == -1) return;
    ListNode* tail = head;
    ListNode* cycleNode = nullptr;
    int index = 0;
    while (tail->next != nullptr) {
        if (index == pos) cycleNode = tail;
        tail = tail->next;
        index++;
    }
    tail->next = cycleNode;
}

// Function to print the result
void printResult(bool result) {
    if (result) {
        cout << "Cycle detected." << endl;
    } else {
        cout << "No cycle detected." << endl;
    }
}

int main() {
    Solution solution;

    // Test case 1: List with no cycle
    cout << "Running Test Case 1..." << endl;
    ListNode* head1 = new ListNode(1);
    head1->next = new ListNode(2);
    head1->next->next = new ListNode(3);
    head1->next->next->next = new ListNode(4);
    printResult(solution.hasCycle(head1));
    // Clean up
    delete head1->next->next->next;
    delete head1->next->next;
    delete head1->next;
    delete head1;

    // Test case 2: List with a cycle
    cout << "Running Test Case 2..." << endl;
    ListNode* head2 = new ListNode(1);
    head2->next = new ListNode(2);
    head2->next->next = new ListNode(3);
    head2->next->next->next = new ListNode(4);
    createCycle(head2, 1);
    printResult(solution.hasCycle(head2));
    // Clean up is not necessary as the list contains a cycle

    // Test case 3: Single node with no cycle
    cout << "Running Test Case 3..." << endl;
    ListNode* head3 = new ListNode(1);
    printResult(solution.hasCycle(head3));
    // Clean up
    delete head3;

    // Test case 4: Single node with a cycle
    cout << "Running Test Case 4..." << endl;
    ListNode* head4 = new ListNode(1);
    head4->next = head4;
    printResult(solution.hasCycle(head4));
    // Clean up is not necessary as the list contains a cycle

    // Test case 5: List with multiple nodes and a cycle in the middle
    cout << "Running Test Case 5..." << endl;
    ListNode* head5 = new ListNode(1);
    head5->next = new ListNode(2);
    head5->next->next = new ListNode(3);
    head5->next->next->next = new ListNode(4);
    head5->next->next->next->next = new ListNode(5);
    createCycle(head5, 2);
    printResult(solution.hasCycle(head5));
    // Clean up is not necessary as the list contains a cycle

    return 0;
}