#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// 定义二叉树节点
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class BinaryTreeTraversal {
public:
    // 1. 非递归先序遍历 (Pre-order: Root -> Left -> Right)
    // 思路：利用栈。先入栈根节点，弹出并访问。
    // 关键点：因为栈是后进先出，所以要先压入右孩子，再压入左孩子。
    void iterativePreOrder(TreeNode* root) {
        if (root == nullptr) return;

        stack<TreeNode*> s;
        s.push(root);

        cout << "先序遍历: ";
        while (!s.empty()) {
            TreeNode* node = s.top();
            s.pop();
            cout << node->val << " ";

            // 先压右，再压左，这样左孩子会先被弹出处理
            if (node->right) s.push(node->right);
            if (node->left) s.push(node->left);
        }
        cout << endl;
    }

    // 2. 非递归中序遍历 (In-order: Left -> Root -> Right)
    // 思路：尽力往左走，把沿途节点压栈。
    // 当无法继续往左时，弹出栈顶元素访问，然后转向右子树。
    void iterativeInOrder(TreeNode* root) {
        stack<TreeNode*> s;
        TreeNode* curr = root;

        cout << "中序遍历: ";
        while (curr != nullptr || !s.empty()) {
            // 步骤1：一直向左走，直到为空
            while (curr != nullptr) {
                s.push(curr);
                curr = curr->left;
            }

            // 步骤2：弹出栈顶节点（即最左节点）
            curr = s.top();
            s.pop();
            
            // 步骤3：访问节点
            cout << curr->val << " ";

            // 步骤4：转向右子树
            curr = curr->right;
        }
        cout << endl;
    }

    // 3. 非递归后序遍历 (Post-order: Left -> Right -> Root)
    // 思路：这是最难的一个。需要一个指针(lastVisited)记录上一次访问的节点，
    //以此判断是“从左子树返回”还是“从右子树返回”。
    void iterativePostOrder(TreeNode* root) {
        if (root == nullptr) return;

        stack<TreeNode*> s;
        TreeNode* curr = root;
        TreeNode* lastVisited = nullptr;

        cout << "后序遍历: ";
        while (curr != nullptr || !s.empty()) {
            // 步骤1：一直向左走
            while (curr != nullptr) {
                s.push(curr);
                curr = curr->left;
            }

            // 步骤2：查看栈顶元素（但不弹出，因为还要判断右子树）
            curr = s.top();

            // 步骤3：如果右子树存在，且没有被访问过，则转向右子树
            if (curr->right != nullptr && curr->right != lastVisited) {
                curr = curr->right;
            } 
            // 步骤4：否则（右子树为空，或右子树已经访问过），可以访问当前节点
            else {
                cout << curr->val << " ";
                lastVisited = curr; // 标记当前节点已访问
                s.pop();            // 弹出
                curr = nullptr;     // 重置curr，防止下一轮循环再次进入“向左走”的逻辑
            }
        }
        cout << endl;
    }
};

int main() {
    // 构建一个简单的二叉树用于测试
    //       1
    //      / \
    //     2   3
    //    / \
    //   4   5
    
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    BinaryTreeTraversal traversal;

    // 执行遍历
    traversal.iterativePreOrder(root);   // 预期: 1 2 4 5 3
    traversal.iterativeInOrder(root);    // 预期: 4 2 5 1 3
    traversal.iterativePostOrder(root);  // 预期: 4 5 2 3 1

    return 0;
}