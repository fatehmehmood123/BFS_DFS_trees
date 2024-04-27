#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_map>
#include <cctype>

using namespace std;

class TreeNode {
public:
    string data;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;

    TreeNode(string name) : data(name), left(nullptr), right(nullptr), parent(nullptr) {}

    void add_left_child(TreeNode* node) {
        node->parent = this;
        left = node;
    }

    void add_right_child(TreeNode* node) {
        node->parent = this;
        right = node;
    }

    int get_level() {
        int level = 0;
        TreeNode* p = parent;
        while (p) {
            level++;
            p = p->parent;
        }
        return level;
    }

    void print_tree(int level = 0) {
        string spaces = string(level * 3, ' ');
        string prefix = parent ? spaces + "|__" : "";
        cout << prefix << data << endl;
        if (left)
            left->print_tree(level + 1);
        if (right)
            right->print_tree(level + 1);
    }

    vector<string> preorder() {
        vector<string> traversal_list;
        traversal_list.push_back(data);
        if (left) {
            vector<string> left_preorder = left->preorder();
            traversal_list.insert(traversal_list.end(), left_preorder.begin(), left_preorder.end());
        }
        if (right) {
            vector<string> right_preorder = right->preorder();
            traversal_list.insert(traversal_list.end(), right_preorder.begin(), right_preorder.end());
        }
        return traversal_list;
    }
};

pair<TreeNode*, bool> bfs_search(TreeNode* root, string target) {
    if (!root)
        return {nullptr, false};

    queue<pair<TreeNode*, TreeNode*>> q;
    q.push({root, nullptr});
    while (!q.empty()) {
        auto front = q.front();
        q.pop();
        auto node = front.first;
        auto parent = front.second;

        // Convert node data and target to lowercase
        string node_data_lower = node->data;
        string target_lower = target;
        for (char& c : node_data_lower)
            c = tolower(c);
        for (char& c : target_lower)
            c = tolower(c);

        if (node_data_lower == target_lower)
            return {node, true};
        if (node->left)
            q.push({node->left, node});
        if (node->right)
            q.push({node->right, node});
    }
    return {nullptr, false};
}


pair<TreeNode*, bool> dfs_search(TreeNode* node, string target) {
    if (!node)
        return {nullptr, false};

    stack<pair<TreeNode*, TreeNode*>> st;
    st.push({node, nullptr});
    while (!st.empty()) {
        auto top = st.top();
        st.pop();
        auto current_node = top.first;
        auto parent = top.second;

        // Convert node data and target to lowercase
        string current_data_lower = current_node->data;
        string target_lower = target;
        for (char& c : current_data_lower)
            c = tolower(c);
        for (char& c : target_lower)
            c = tolower(c);

        if (current_data_lower == target_lower)
            return {current_node, true};
        if (current_node->right)
            st.push({current_node->right, current_node});
        if (current_node->left)
            st.push({current_node->left, current_node});
    }
    return {nullptr, false};
}

TreeNode* root;

void build_product_tree() {
    root = new TreeNode("United States");

    TreeNode* USA = new TreeNode("USA");
    TreeNode* Mexico = new TreeNode("Mexico");
    TreeNode* Canada = new TreeNode("Canada");
    TreeNode* MexicoCity = new TreeNode("Mexico City");
    MexicoCity->add_left_child(new TreeNode("Berlin"));
    Mexico->add_right_child(MexicoCity);
    USA->add_right_child(Mexico);

    TreeNode* toronto = new TreeNode("Toronto");
    TreeNode* Montreal = new TreeNode("Montreal");
    TreeNode* Paris = new TreeNode("Paris");
    toronto->add_left_child(new TreeNode("Vancouver"));
    Paris->add_left_child(new TreeNode("London"));
    Paris->add_right_child(new TreeNode("Rome"));
    Montreal->add_left_child(Paris);
    toronto->add_right_child(Montreal);
    Canada->add_left_child(toronto);
    USA->add_left_child(Canada);

    TreeNode* ID = new TreeNode("Intermediate Destinations");
    TreeNode* OC = new TreeNode("Other Continents");
    TreeNode* Europe = new TreeNode("Europe");
    TreeNode* Germany = new TreeNode("Germany");
    TreeNode* Asia = new TreeNode("Asia");
    TreeNode* Frankfurt = new TreeNode("Frankfurt");
    TreeNode* Athens = new TreeNode("Athens");
    TreeNode* Munich = new TreeNode("Munich");
    Munich->add_left_child(new TreeNode("Vienna"));
    Athens->add_left_child(new TreeNode("Budapest"));
    Frankfurt->add_left_child(Munich);
    Germany->add_left_child(Frankfurt);
    Europe->add_right_child(Germany);
    ID->add_left_child(Europe);
    Asia->add_right_child(Athens);
    OC->add_left_child(Asia);
    ID->add_right_child(OC);

    Europe->add_left_child(MexicoCity);
    Asia->add_left_child(Frankfurt);

    root->add_right_child(ID);
    root->add_left_child(USA);
}

int main() {
    build_product_tree();
    root->print_tree();
    cout << "Pre-Order Traversal of the Given Tree is : ";
    vector<string> preorder = root->preorder();
    for (const auto& node : preorder)
        cout << node << " ";
    cout << endl;

    string start_country, target_country;
    cout << "Enter Starting Country : ";
    getline(cin, start_country);
    cout << "Enter Target Country : ";
    getline(cin, target_country);

    TreeNode* node_BFS;
    bool found_start_country_BFS;
    tie(node_BFS, found_start_country_BFS) = bfs_search(root, start_country);
    if (found_start_country_BFS) {
        TreeNode* node_target_country_BFS;
        bool found_target_country_BFS;
        tie(node_target_country_BFS, found_target_country_BFS) = bfs_search(node_BFS, target_country);
        if (found_target_country_BFS)
            cout << target_country << " found using BFS" << endl;
        else
            cout << start_country << " found but " << target_country << " not found using BFS" << endl;
    } else {
        cout << start_country << " not found using BFS" << endl;
    }

    TreeNode* node_DFS;
    bool found_start_country_DFS;
    tie(node_DFS, found_start_country_DFS) = dfs_search(root, start_country);
    if (found_start_country_DFS) {
        TreeNode* node_target_country_DFS;
        bool found_target_country_DFS;
        tie(node_target_country_DFS, found_target_country_DFS) = dfs_search(node_DFS, target_country);
        if (found_target_country_DFS)
            cout << target_country << " found using DFS" << endl;
        else
            cout << start_country << " found but " << target_country << " not found using DFS" << endl;
    } else {
        cout << start_country << " not found using DFS" << endl;
    }

    return 0;
}
