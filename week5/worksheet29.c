struct Node * _nodeAddBST (struct Node *current, TYPE newValue) {
    if (current==null){
        current = new Node (newValue);
    } else {
        if (newValue>current->value){
            if (current->right!=null){
                _nodeAddBST(current->right);
            } else {
                current->right = new Node (newValue);
            }
        } else {
            if (current->left!=null){
                _nodeAddBST(current->left);
            } else {
                current->left = new Node (newValue);
            }
        }
    }
}
 
int containsBST (struct BinarySearchTree *tree, TYPE d) {
    if (tree->root==null){
        return 0;
    }
    struct Node * current = tree->root;
    while (current!=null){
        if (d>current->value){
            current = current.right;
        } else if (d<current->value) {
            current = current.left;
        } else if (d==current->value){
            return 1;
        } else {
            return 0;
        }
    }
}
