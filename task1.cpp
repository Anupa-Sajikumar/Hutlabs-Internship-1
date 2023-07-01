#include <iostream>
#include <cstdlib> // for malloc and free functions

using namespace std;

struct ListNode {
    int data;
    ListNode* next;
};

ListNode* createLinkedList() {
    ListNode* head = nullptr;
    ListNode* current = nullptr;
    int value;

    cout << "Enter the values for the linked list (enter -1 to stop): ";
    while (true) {
        cin >> value;
        if (value == -1) {
            break;
        }

        ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
        newNode->data = value;
        newNode->next = nullptr;

        if (head == nullptr) {
            head = newNode;
            current = newNode;
        } else {
            current->next = newNode;
            current = newNode;
        }
    }

    return head;
}

void displayLinkedList(ListNode* head) {
    ListNode* current = head;
    cout << "Linked List: ";
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void deleteLinkedList(ListNode* head) {
    ListNode* current = head;
    while (current != nullptr) {
        ListNode* temp = current;
        current = current->next;
        free(temp);
    }
}

struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* createBinaryTree() {
    int value;
    cout << "Enter the root value of the binary tree: ";
    cin >> value;
    if (value == -1) {
        return nullptr;
    }

    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = value;

    cout << "Enter the left subtree of " << value << ":\n";
    newNode->left = createBinaryTree();

    cout << "Enter the right subtree of " << value << ":\n";
    newNode->right = createBinaryTree();

    return newNode;
}

void displayBinaryTree(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    cout << "Binary Tree: " << root->data << " ";
    if (root->left != nullptr) {
        cout << root->left->data << " ";
    }
    if (root->right != nullptr) {
        cout << root->right->data << " ";
    }
    cout << endl;

    displayBinaryTree(root->left);
    displayBinaryTree(root->right);
}

void deleteBinaryTree(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    deleteBinaryTree(root->left);
    deleteBinaryTree(root->right);

    free(root);
}

struct GraphNode {
    int data;
    GraphNode** neighbors;
    int numNeighbors;
};

GraphNode* createGraphNode() {
    int value;
    cout << "Enter the value of the graph node: ";
    cin >> value;

    GraphNode* newNode = (GraphNode*)malloc(sizeof(GraphNode));
    newNode->data = value;

    int numNeighbors;
    cout << "Enter the number of neighbors for node " << value << ": ";
    cin >> numNeighbors;

    newNode->numNeighbors = numNeighbors;
    newNode->neighbors = (GraphNode**)malloc(numNeighbors * sizeof(GraphNode*));

    cout << "Enter the neighbors for node " << value << ": ";
    for (int i = 0; i < numNeighbors; i++) {
        int neighborValue;
        cin >> neighborValue;

        GraphNode* neighborNode = (GraphNode*)malloc(sizeof(GraphNode));
        neighborNode->data = neighborValue;
        neighborNode->numNeighbors = 0;
        neighborNode->neighbors = nullptr;

        newNode->neighbors[i] = neighborNode;
    }

    return newNode;
}

void displayGraphNode(GraphNode* node) {
    if (node == nullptr) {
        return;
    }

    cout << "Graph Node: " << node->data << " ";
    cout << "Neighbors: ";
    for (int i = 0; i < node->numNeighbors; i++) {
        cout << node->neighbors[i]->data << " ";
    }
    cout << endl;

    for (int i = 0; i < node->numNeighbors; i++) {
        displayGraphNode(node->neighbors[i]);
    }
}

void deleteGraphNode(GraphNode* node) {
    if (node == nullptr) {
        return;
    }

    for (int i = 0; i < node->numNeighbors; i++) {
        deleteGraphNode(node->neighbors[i]);
    }

    free(node->neighbors);
    free(node);
}

int main() {
    int choice;
    ListNode* linkedList = nullptr;
    TreeNode* binaryTree = nullptr;
    GraphNode* graphNode = nullptr;

    while (true) {
        cout << "-------------------------\n";
        cout << "Menu:\n";
        cout << "1. Create Linked List\n";
        cout << "2. Display Linked List\n";
        cout << "3. Delete Linked List\n";
        cout << "4. Create Binary Tree\n";
        cout << "5. Display Binary Tree\n";
        cout << "6. Delete Binary Tree\n";
        cout << "7. Create Graph\n";
        cout << "8. Display Graph\n";
        cout << "9. Delete Graph\n";
        cout << "0. Exit\n";
        cout << "-------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                linkedList = createLinkedList();
                break;
            case 2:
                displayLinkedList(linkedList);
                break;
            case 3:
                deleteLinkedList(linkedList);
                linkedList = nullptr;
                break;
            case 4:
                binaryTree = createBinaryTree();
                break;
            case 5:
                displayBinaryTree(binaryTree);
                break;
            case 6:
                deleteBinaryTree(binaryTree);
                binaryTree = nullptr;
                break;
            case 7:
                graphNode = createGraphNode();
                break;
            case 8:
                displayGraphNode(graphNode);
                break;
            case 9:
                deleteGraphNode(graphNode);
                graphNode = nullptr;
                break;
            case 0:
                deleteLinkedList(linkedList);
                deleteBinaryTree(binaryTree);
                deleteGraphNode(graphNode);
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }
    }
}