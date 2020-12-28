#ifndef SOLUTION_H
#define SOLUTION_H

#include <algorithm>
#include <stack>
#include <unordered_map>
#include <unordered_set>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
  bool hasPathSum(TreeNode* root, int sum) {
    bool result = false;
    using Distance = int;
    if (root) {
      std::stack<std::pair<TreeNode*, Distance>> nodes;
      std::unordered_set<TreeNode*> visited;
      std::unordered_map<TreeNode*, int> distances_to_leafs;

      nodes.emplace(root, root->val);
      visited.insert(root);

      while (!nodes.empty()) {
        auto [next, dist] = nodes.top();
        nodes.pop();
        visited.insert(next);
        if (!next->left && !next->right) {
          distances_to_leafs.emplace(next, dist);
        } else {
          if (next->left) {
            nodes.emplace(next->left, dist + next->left->val);
          }
          if (next->right) {
            nodes.emplace(next->right, dist + next->right->val);
          }
        }
      }
      result = std::find_if(distances_to_leafs.begin(), distances_to_leafs.end(), [sum] (const std::pair<TreeNode*, int> leaf) {
        return leaf.second == sum;
      }) != distances_to_leafs.end();
    }

    return result;
  }
};

#endif // SOLUTION_H
