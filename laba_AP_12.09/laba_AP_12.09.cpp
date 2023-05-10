// laba_AP_12.09.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <memory>
#include <vector>
#include <queue>
#include <algorithm>

class Node {
public:
    int value;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

void insert(std::shared_ptr<Node>& root, int value) {
    if (!root) {
        root = std::make_shared<Node>(value);
        return;
    }

    if (value < root->value) {
        insert(root->left, value);
    }
    else {
        insert(root->right, value);
    }
}
std::shared_ptr<Node> createBinarySearchTree(const std::vector<int>& elements) {
    std::shared_ptr<Node> root = nullptr;
    for (int element : elements) {
        insert(root, element);
    }
    return root;
}

bool findElement(const std::shared_ptr<Node>& root, int k) {
    if (!root) {
        return false;
    }
    if (root->value == k) {
        return true;
    }
    if (k < root->value) {
        return findElement(root->left, k);
    }
    return findElement(root->right, k);
}
void printTree(const std::shared_ptr<Node>& root, int indent = 0) {
    if (!root) {
        return;
    }

    printTree(root->right, indent + 4);
    std::cout << std::string(indent, ' ') << root->value << std::endl;
    printTree(root->left, indent + 4);
}
void deleteLeaf(std::shared_ptr<Node>& root, int k) {
    if (!root) {
        return;
    }
    if (root->left && root->left->value == k && !root->left->left && !root->left->right) {
        root->left.reset();
        return;
    }
    if (root->right && root->right->value == k && !root->right->left && !root->right->right) {
        root->right.reset();
        return;
    }
    if (k < root->value) {
        deleteLeaf(root->left, k);
    }
    else {
        deleteLeaf(root->right, k);
    }
}
void deleteNodeWithOneChild(std::shared_ptr<Node>& root, int k) {
    if (!root) {
        return;
    }

    if (root->left && root->left->value == k && (!root->left->left ^ !root->left->right)) {
        root->left = root->left->left ? root->left->left : root->left->right;
        return;
    }
    if (root->right && root->right->value == k && (!root->right->left ^ !root->right->right)) {
        root->right = root->right->left ? root->right->left : root->right->right;
        return;
    }
    if (k < root->value) {
        deleteNodeWithOneChild(root->left, k);
    }
    else {
        deleteNodeWithOneChild(root->right, k);
    }
}
std::shared_ptr<Node> balanceBST(std::vector<int>& elements, int start, int end) {
    if (start > end) {
        return nullptr;
    }

    int mid = (start + end) / 2;
    std::shared_ptr<Node> root = std::make_shared<Node>(elements[mid]);
    root->left = balanceBST(elements, start, mid - 1);
    root->right = balanceBST(elements, mid + 1, end);
    return root;
}

void inorderTraversal(const std::shared_ptr<Node>& root, std::vector<int>& elements) {
    if (!root) {
        return;
    }
    inorderTraversal(root->left, elements);
    elements.push_back(root->value);
    inorderTraversal(root->right, elements);
}

void balance(std::shared_ptr<Node>& root) {
    std::vector<int> elements;
    inorderTraversal(root, elements);
    root = balanceBST(elements, 0, elements.size() - 1);
}
int minValue(const std::shared_ptr<Node>& node) {
    std::shared_ptr<Node> current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current->value;
}
std::shared_ptr<Node> deleteNodeWithTwoChildren(std::shared_ptr<Node> root, int k) {
    if (!root) {
        return nullptr;
    }

    if (k < root->value) {
        root->left = deleteNodeWithTwoChildren(root->left, k);
    }
    else if (k > root->value) {
        root->right = deleteNodeWithTwoChildren(root->right, k);
    }
    else {
        if (!root->left) {
            return root->right;
        }
        else if (!root->right) {
            return root->left;
        }

        root->value = minValue(root->right);
        root->right = deleteNodeWithTwoChildren(root->right, root->value);
    }

    return root;
}
std::shared_ptr<Node> deleteNodeWithAllChildren(std::shared_ptr<Node> root, int k) {
    if (!root) {
        return nullptr;
    }

    if (k < root->value) {
        root->left = deleteNodeWithAllChildren(root->left, k);
    }
    else if (k > root->value) {
        root->right = deleteNodeWithAllChildren(root->right, k);
    }
    else {
        return nullptr;
    }

    return root;
}
void printMenu() {
    std::cout << "\nChoose an action:\n";
    std::cout << "1. Create a binary tree\n";
    std::cout << "2. Display the binary tree\n";
    std::cout << "3. Add a new element maintaining order\n";
    std::cout << "4. Balance the binary search tree\n";
    std::cout << "5. Remove a tree element with no child nodes\n";
    std::cout << "6. Remove a tree element with one child node\n";
    std::cout << "7. Remove a tree element with two child nodes\n";
    std::cout << "8. Remove a tree element with all its child nodes\n";
    std::cout << "9. Determine if the search tree contains an element with value k\n";
}
int main() {
    std::shared_ptr<Node> bst = nullptr;

    int choice;
    while (true) {
        printMenu();
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int n;
            std::cout << "Enter the number of elements: ";
            std::cin >> n;
            std::vector<int> elements(n);
            std::cout << "Enter the elements: ";
            for (int i = 0; i < n; ++i) {
                std::cin >> elements[i];
            }
            bst = createBinarySearchTree(elements);
            break;
        }
        case 2: {
            printTree(bst);
            break;
        }
        case 3: {
            int value;
            std::cout << "Enter the value: ";
            std::cin >> value;
            insert(bst, value);
            break;
        }
        case 4: {
            balance(bst);
            std::cout << "Binary search tree balanced.\n";
            break;
        }
        case 5: {
            int value;
            std::cout << "Enter the value: ";
            std::cin >> value;
            deleteLeaf(bst, value);
            break;
        }
        case 6: {
            int value;
            std::cout << "Enter the value: ";
            std::cin >> value;
            deleteNodeWithOneChild(bst, value);
            break;
        }
        case 7: {
            int k;
            std::cout << "Enter the value of the element to be deleted: ";
            std::cin >> k;
            bst = deleteNodeWithTwoChildren(bst, k);
            std::cout << "Element with two child nodes removed.\n";
            break;
        }
        case 8: {
            int k;
            std::cout << "Enter the value of the element to be deleted: ";
            std::cin >> k;
            bst = deleteNodeWithAllChildren(bst, k);
            std::cout << "Element with all its child nodes removed.\n";
            break;
        }
        case 9: {
            int k;
            std::cout << "Enter the value k: ";
            std::cin >> k;
            if (findElement(bst, k)) {
                std::cout << "Element found.";
            }
        }
        default:
            std::cout << "Incorrect choice, try again.\n";
        }
    }
    return 0;
}