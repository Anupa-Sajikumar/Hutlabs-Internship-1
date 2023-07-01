#include <iostream>
#include <vector>

using namespace std;

struct Slab {
    int size;
    bool isFree;
};

vector<Slab*> slabs;

void initializeSlabs(int numSlabs, int slabSize) {
    slabs.resize(numSlabs);
    for (int i = 0; i < numSlabs; i++) {
        slabs[i] = static_cast<Slab*>(malloc(sizeof(Slab)));
        slabs[i]->size = slabSize;
        slabs[i]->isFree = true;
    }
}

void* allocateSlab(int size) {
    for (Slab* slab : slabs) {
        if (slab->isFree && slab->size >= size) {
            slab->isFree = false;
            return slab;
        }
    }
    return nullptr;
}

void deallocateSlab(void* address) {
    Slab* slab = static_cast<Slab*>(address);
    slab->isFree = true;
}

void printSlabs() {
    cout << "Slabs:" << endl;
    for (const Slab* slab : slabs) {
        cout << "Size: " << slab->size << ", Free: " << (slab->isFree ? "Yes" : "No") << endl;
    }
    cout << endl;
}

void cleanup() {
    for (Slab* slab : slabs) {
        free(slab);
    }
    slabs.clear();
}

int main() {
    int numSlabs, slabSize;
    cout << "Enter the number of slabs: ";
    cin >> numSlabs;
    cout << "Enter the size of each slab: ";
    cin >> slabSize;

    initializeSlabs(numSlabs, slabSize);

    int choice;
    while (true) {
        cout << "1. Allocate Slab" << endl;
        cout << "2. Deallocate Slab" << endl;
        cout << "3. Print Slabs" << endl;
        cout << "-1. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == -1) {
            break;
        }

        switch (choice) {
            case 1: {
                int size;
                cout << "Enter the size of slab to allocate: ";
                cin >> size;
                void* address = allocateSlab(size);
                if (address != nullptr) {
                    cout << "Slab allocated at address: " << address << endl;
                } else {
                    cout << "Insufficient memory to allocate slab." << endl;
                }
                break;
            }
            case 2: {
                void* address;
                cout << "Enter the address to deallocate: ";
                cin >> address;
                deallocateSlab(address);
                cout << "Slab deallocated successfully." << endl;
                break;
            }
            case 3:
                printSlabs();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    cleanup();

    return 0;
}