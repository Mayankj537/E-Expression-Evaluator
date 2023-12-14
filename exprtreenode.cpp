/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

ExprTreeNode::ExprTreeNode() : type(""), id(""),val(nullptr), evaluated_value(nullptr), left(nullptr), right(nullptr) {}

ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v){
    type="";
    id="";
    val=nullptr;
    evaluated_value=nullptr;
    left=nullptr;
    right=nullptr;
}

ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v){
    type="";
    val=nullptr;
    evaluated_value=nullptr;
    left=nullptr;
    right=nullptr;
}

ExprTreeNode::~ExprTreeNode() {
// // Delete the value if it exists
if (val != nullptr) {
        delete val;
    }

    // // Delete the evaluated value if it exists
    if (evaluated_value != nullptr) {
        delete evaluated_value;
    }
}
