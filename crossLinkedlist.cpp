#include <iostream>
using namespace std;


struct OLNode {
    int row, col;
    int value;
    OLNode* right;     
    OLNode* down;     

    OLNode(int r, int c, int v)
        : row(r), col(c), value(v), right(nullptr), down(nullptr) {}
};


struct CrossList {
    int rows, cols, nums;
    OLNode** rowHead;   
    OLNode** colHead;     

    CrossList(int r, int c)
        : rows(r), cols(c), nums(0)
    {
        rowHead = new OLNode*[r]();
        colHead = new OLNode*[c]();
    }

    ~CrossList() {
        for (int i = 0; i < rows; i++) {
            OLNode* p = rowHead[i];
            while (p) {
                OLNode* temp = p;
                p = p->right;
                delete temp;
            }
        }
        delete[] rowHead;
        delete[] colHead;
    }
};


void insert(CrossList &M, int r, int c, int val) {
    if (val == 0) return; 

    OLNode* node = new OLNode(r, c, val);


    if (!M.rowHead[r] || M.rowHead[r]->col > c) {
        node->right = M.rowHead[r];
        M.rowHead[r] = node;
    } else {
        OLNode* p = M.rowHead[r];
        while (p->right && p->right->col < c) p = p->right;
        node->right = p->right;
        p->right = node;
    }


    if (!M.colHead[c] || M.colHead[c]->row > r) {
        node->down = M.colHead[c];
        M.colHead[c] = node;
    } else {
        OLNode* p = M.colHead[c];
        while (p->down && p->down->row < r) p = p->down;
        node->down = p->down;
        p->down = node;
    }

    M.nums++;
}


void printMatrix(const CrossList &M) {
    for (int i = 0; i < M.rows; i++) {
        OLNode* p = M.rowHead[i];
        for (int j = 0; j < M.cols; j++) {
            if (p && p->col == j) {
                cout << p->value << " ";
                p = p->right;
            } else {
                cout << "0 ";
            }
        }
        cout << endl;
    }
}


int main() {
    CrossList M(4, 5);  

    insert(M, 0, 1, 5);
    insert(M, 0, 3, 8);
    insert(M, 1, 2, 3);
    insert(M, 3, 0, 6);

    cout << "Ï¡Êè¾ØÕóÊä³ö:" << endl;
    printMatrix(M);

    return 0;
}
