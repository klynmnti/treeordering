#include "Tree.h"
/* Print Orders function */
// outputs the pre, in, and post orders of tree
void printOrders(Tree *tree) {
    cout << "Preorder = ";
    tree->preOrder();
    cout << endl << "Inorder = ";
    tree->inOrder();
    cout << endl << "Postorder = ";
    tree->postOrder();
    cout << endl;
}
/* Menu function */
// determines which function to call based on user input
int menu() {
    int choice = 0;
    cout << endl << "Enter menu choice: ";
    cout << endl;
    cout 
        << "1. Insert" << endl
        << "2. Remove" << endl
        << "3. Print" << endl
        << "4. Search" << endl
        << "5. Quit" << endl;
    cin >> choice;
    cin.clear();
    cin.ignore(256, '\n');
    return choice;
}
/* Main */
int main() {
    // create a Tree object
    Tree tree;
    int choice = menu();
    string entry;
    // determine user input and call insert, remove, order, & search functions accordingly
    while (choice != 5) {
        if (choice == 1) {
            cout << "Enter movie title to insert: ";
            getline(cin, entry);
            cout << endl;
            tree.insert(entry);
        } 
        else if (choice == 2) {
            cout << "Enter movie title to remove: ";
            getline(cin, entry);
            cout << endl;
            tree.remove(entry);
        } 
        else if (choice == 3) {
            printOrders(&tree);
        } 
        else if (choice == 4) {
            cout << "Enter movie title to search for: ";
            getline(cin, entry);
            cout << endl;
            if (tree.search(entry)) {
                cout << "Found" << endl;
            } 
            else {
                cout << "Not Found" << endl;
            }
        }
        choice = menu();
    }
    
    return 0;
}
