#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

struct Block {
    int size;
    bool isFree;
    Block* next;
    Block* prev;
};

vector<Block*> memoryBlocks;
int totalMemorySize;

void initializeMemory(int size) {
    totalMemorySize = size;
    Block* initialBlock = new Block();
    initialBlock->size = size;
    initialBlock->isFree = true;
    initialBlock->next = nullptr;
    initialBlock->prev = nullptr;
    memoryBlocks.push_back(initialBlock);
}

void* allocateMemory(int size) {
    // Find the smallest available block that can accommodate the required size
    int blockSize = totalMemorySize;
    Block* selectedBlock = nullptr;

    while (blockSize >= size) {
        // Find the first free block with size >= required size
        for (Block* block : memoryBlocks) {
            if (block->size == blockSize && block->isFree) {
                selectedBlock = block;
                break;
            }
        }

        // If no suitable block is found, split the larger block
        if (selectedBlock == nullptr) {
            blockSize /= 2;
        } else {
            break;
        }
    }

    // If no suitable block is found, return nullptr
    if (selectedBlock == nullptr) {
        return nullptr;
    }

    // Mark the selected block as used
    selectedBlock->isFree = false;

    // Split the selected block into two halves until the required size is achieved
    while (selectedBlock->size > size) {
        Block* newBlock = new Block();
        newBlock->size = selectedBlock->size / 2;
        newBlock->isFree = true;

        // Adjust the pointers
        newBlock->next = selectedBlock->next;
        if (selectedBlock->next != nullptr) {
            selectedBlock->next->prev = newBlock;
        }
        newBlock->prev = selectedBlock;
        selectedBlock->next = newBlock;

        selectedBlock->size = selectedBlock->size / 2;
        selectedBlock = newBlock;
        memoryBlocks.push_back(newBlock);
    }

    return selectedBlock;
}

void deallocateMemory(void* address) {
    Block* block = static_cast<Block*>(address);
    block->isFree = true;

    // Merge adjacent free blocks
    while (block->prev != nullptr && block->prev->isFree) {
        Block* prevBlock = block->prev;
        prevBlock->size = prevBlock->size + block->size;

        if (block->next != nullptr) {
            prevBlock->next = block->next;
            block->next->prev = prevBlock;
        } else {
            prevBlock->next = nullptr;
        }

        memoryBlocks.erase(remove(memoryBlocks.begin(), memoryBlocks.end(), block), memoryBlocks.end());
        delete block;
        block = prevBlock;
    }

    while (block->next != nullptr && block->next->isFree) {
        Block* nextBlock = block->next;
        block->size = block->size + nextBlock->size;
        block->next = nextBlock->next;

        if (nextBlock->next != nullptr) {
            nextBlock->next->prev = block;
        }

        memoryBlocks.erase(remove(memoryBlocks.begin(), memoryBlocks.end(), nextBlock), memoryBlocks.end());
        delete nextBlock;
    }
}

void printMemoryBlocks() {
    for (Block* block : memoryBlocks) {
        cout << "Block: Size = " << block->size << ", Free = " << (block->isFree ? "Yes" : "No") << endl;
    }
    cout << endl;
}

void cleanup() {
    for (Block* block : memoryBlocks) {
        delete block;
    }
    memoryBlocks.clear();
}

int main() {
    int totalMemorySize;
    cout << "Enter the total size of memory: ";
    cin >> totalMemorySize;

    initializeMemory(totalMemorySize);

    int choice;
    while (true) {
        cout << "1. Allocate Memory" << endl;
        cout << "2. Deallocate Memory" << endl;
        cout << "3. Print Memory Blocks" << endl;
        cout << "-1. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == -1) {
            break;
        }

        switch (choice) {
            case 1: {
                int size;
                cout << "Enter the size of memory to allocate: ";
                cin >> size;
                void* address = allocateMemory(size);
                if (address != nullptr) {
                    cout << "Memory allocated at address: " << address << endl;
                } else {
                    cout << "Insufficient memory to allocate." << endl;
                }
                break;
            }
            case 2: {
                void* address;
                cout << "Enter the address to deallocate: ";
                cin >> address;
                deallocateMemory(address);
                cout << "Memory deallocated successfully." << endl;
                break;
            }
            case 3:
                printMemoryBlocks();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    cleanup();

    return 0;
}