/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
using namespace std;
#include "symtable.h"
SymbolTable::SymbolTable(){
    size=0;
    root=nullptr;
}
SymEntry* findMin(SymEntry* root){
    SymEntry* temp=root;
    while(temp->left!=nullptr){
        temp=temp->left;
    }
    return temp;
}
SymEntry* deletenodeinbst(SymEntry*& root, string k) {
    if (root == nullptr) {
        return root;
    }
    else if (root->key == k) {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        else if (root->left == nullptr && root->right != nullptr) {
            SymEntry* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr && root->left != nullptr) {
            SymEntry* temp = root->left;
            delete root;
            return temp;
        }
        else if (root->left != nullptr && root->right != nullptr) {
            SymEntry* temp = findMin(root->right);
            root->key = temp->key;
            // Update the val pointer as well
            UnlimitedRational *k=root->val;
            root->val = temp->val;
            temp->val=k;
            root->right = deletenodeinbst(root->right, temp->key);
            return root;
        }
    }
    else if (root->key > k) {
        root->left = deletenodeinbst(root->left, k);
        return root;
    }
        root->right = deletenodeinbst(root->right, k);
        return root;
    
}

SymEntry* insertsym(SymEntry* &root,string k,UnlimitedRational* v){
    if(root==nullptr){
        return new SymEntry(k,v);
    }
    if(root->key>k){
        root->left=insertsym(root->left,k,v);
    }else{
        root->right=insertsym(root->right,k,v);
    }
    return root;
}
SymEntry* searchInBST(SymEntry* &root,string k){
    if(root->key==k){
        return root;
    }
    else if(root->key>k){
        return searchInBST(root->left,k);
    }
    return searchInBST(root->right,k);
}
static void Destructor(SymEntry* root){
    if(root==nullptr){
        return;
    }
    Destructor(root->left);
    Destructor(root->right);
    delete root->val;
    delete root;
}
void SymbolTable::insert(string k, UnlimitedRational* v){
    this->root=insertsym(root,k,v);
    this->size++;
    return;
}
UnlimitedRational*SymbolTable::search(string k){
    SymEntry* res=searchInBST(root,k);
    return res->val;
}
void SymbolTable::remove(string k){
    root=deletenodeinbst(root,k);
    size--;
}
SymEntry* SymbolTable::get_root(){
    return root;
}
int SymbolTable::get_size(){
    return size;
}
SymbolTable:: ~SymbolTable(){
    Destructor(root);
    size=0;
    root=nullptr;
}
// int main()
// {
//     SymbolTable *r = new SymbolTable();
//     UnlimitedInt *ap = new UnlimitedInt("-1");
//     UnlimitedInt *aq = new UnlimitedInt("5");

//     UnlimitedRational *a = new UnlimitedRational(ap, aq);
//     cout << "first fraction: " << a->get_frac_str() << "\n";

//     UnlimitedInt *bp = new UnlimitedInt("6");
//     UnlimitedInt *bq = new UnlimitedInt(24);
//     UnlimitedRational *b = new UnlimitedRational(bp, bq);
//     cout << "second fraction: " << b->get_frac_str() << "\n";
//     r->insert("a", a);
//     r->insert("b", b);
//     UnlimitedRational *res = a->add(a, b);
//     cout << "addition: " << res->get_frac_str() << endl;
//     r->insert("add", res);

//     res = a->sub(a, b);
//     cout << "subtraction : " << res->get_frac_str() << endl;

//     r->insert("sub", res);

//     res = res->mul(a, b);
//     cout << "multipication: "<< res->get_frac_str() << endl;
//     r->insert("mul", res);

//     res = a->div(a, b);
//     cout << "division: " << res->get_frac_str() << endl;
//     r->insert("div", res);

//     cout << "r ka size: " << r->get_size() << "\n";
//     cout << r->search("a")->get_frac_str() << "  a\n";
//     r->remove("a");
//     cout << "after remove a size:  " <<r->get_size() << "\n";
//     cout << r->search("b")->get_frac_str() << "  b\n";

//     r->remove("b");
//      cout << "after remove b size: " << r->get_size() << "\n";

//     cout << r->search("add")->get_frac_str() << "  add\n";
//     r->remove("add");
//     cout << "after remove add size: " << r->get_size() << "\n";

//     cout << r->search("sub")->get_frac_str() << "  sub\n";
//     r->remove("sub");
//     cout << "after emve sub size; " << r->get_size() << "\n";

//     cout << r->search("mul")->get_frac_str() << "  mul\n";
//     r->remove("mul");
//     cout << "after remove mul size; " << r->get_size() << "\n";

//     cout << r->search("div")->get_frac_str() << "  div\n";
//     r->remove("div");
//     cout << "after remove div size: " << r->get_size() << "\n";

//     delete r;
//     return 0;
// }