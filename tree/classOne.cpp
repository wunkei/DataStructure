#include <iostream>
#include <stack>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

//µ›πÈ±È¿˙
void preorderRecursive(TreeNode* root, std::vector<int>& out) {
    if (!root) return;
    out.push_back(root->val);
    preorderRecursive(root->left, out);
    preorderRecursive(root->right, out);
}

void inorderRecursive(TreeNode* root, std::vector<int>& out) {
    if (!root) return;
    inorderRecursive(root->left, out);
    out.push_back(root->val);
    inorderRecursive(root->right, out);
}

void postorderRecursive(TreeNode* root, std::vector<int>& out) {
    if (!root) return;
    postorderRecursive(root->left, out);
    postorderRecursive(root->right, out);
    out.push_back(root->val);
}

//∑«µ›πÈ±È¿˙
std::vector<int> preorderIter(TreeNode* root) {
    std::vector<int> out;
    std::stack<TreeNode*> st;
    if (root) st.push(root);
    while (!st.empty()) {
        TreeNode* node = st.top();
        st.pop();
        out.push_back(node->val);
        if (node->right) st.push(node->right);
        if (node->left) st.push(node->left);
    }
    return out;
}

std::vector<int> inorderIter(TreeNode* root) {
    std::vector<int> out;
    std::stack<TreeNode*> st;
    TreeNode* cur = root;
    while (cur || !st.empty()) {
        while (cur) {
            st.push(cur);
            cur = cur->left;
        }
        cur = st.top();
        st.pop();
        out.push_back(cur->val);
        cur = cur->right;
    }
    return out;
}

std::vector<int> postorderIter(TreeNode* root) {
    std::vector<int> out;
    if (!root) return out;
    std::stack<TreeNode*> st;
    TreeNode* lastVisited = nullptr;
    TreeNode* cur = root;
    while (cur || !st.empty()) {
        while (cur) {
            st.push(cur);
            cur = cur->left;
        }
        TreeNode* node = st.top();
        if (!node->right || lastVisited == node->right) {
            out.push_back(node->val);
            st.pop();
            lastVisited = node;
        } else {
            cur = node->right;
        }
    }
    return out;
}

void print(const std::string& label, const std::vector<int>& seq) {
    std::cout << label << ": ";
    for (size_t i = 0; i < seq.size(); ++i) {
        std::cout << seq[i] << (i + 1 == seq.size() ? "" : " ");
    }
    std::cout << "\n";
}

int main() {
    //∂˛≤Ê ˜£∫
    //        1
    //      /   \
    //     2     3
    //    / \   /
    //   4   5 6
    TreeNode n1(1), n2(2), n3(3), n4(4), n5(5), n6(6);
    n1.left = &n2;  n1.right = &n3;
    n2.left = &n4;  n2.right = &n5;
    n3.left = &n6;

    std::vector<int> res;

    res.clear(); preorderRecursive(&n1, res);    print("µ›πÈœ»–Ú", res);
    res.clear(); inorderRecursive(&n1, res);     print("µ›πÈ÷––Ú", res);
    res.clear(); postorderRecursive(&n1, res);   print("µ›πÈ∫Û–Ú", res);

    print("∑«µ›πÈœ»–Ú", preorderIter(&n1));
    print("∑«µ›πÈ÷––Ú", inorderIter(&n1));
    print("∑«µ›πÈ∫Û–Ú", postorderIter(&n1));

    return 0;
}