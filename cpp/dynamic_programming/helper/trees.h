#include <list>

class TreeNode{
    public:
        int index, value = 0;
        bool visited = false;
        list<TreeNode*> children;

        TreeNode(int index){
            this->index = index;
        }

        void appendChild(TreeNode* node){
            children.push_back(node);
        }

        TreeNode* getChild(int index){
            list<TreeNode*>::iterator it = children.begin();
            advance(it, index);
            return *it;
        }
};

TreeNode* generateConnectedTree(int treeSize, int degree){
    srand (time(NULL));
    int generatedNodes = 0;
    TreeNode* root = new TreeNode(generatedNodes++);
    list<TreeNode*> nodes;
    nodes.push_back(root);
    list<TreeNode*>::iterator it;
    TreeNode* node;
    for(int i=generatedNodes; i<treeSize; i++){
        node = new TreeNode(generatedNodes++);
        int index = rand() % nodes.size();
        it = nodes.begin();
        advance(it, index);
        (*it)->appendChild(node);
        if((*it)->children.size() >= degree){
            nodes.erase(it);
        }
        nodes.push_back(node);
    }
    return root;
}

TreeNode* generatePerfectTree(int treeSize, int degree){
    int generatedNodes =0, childrenIndex =0;
    list<TreeNode*> nodes;
    TreeNode* root = new TreeNode(generatedNodes++);
    TreeNode* child;
    TreeNode* node = root;
    for(;generatedNodes < treeSize;){
        //add children
        for(int j=0; j<degree && generatedNodes < treeSize; j++){
            child = new TreeNode(generatedNodes++);
            node->appendChild(child);
            nodes.push_back(child);
        }
        node = nodes.front();
        nodes.pop_front();
    }
    return root;
}