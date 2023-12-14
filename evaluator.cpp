/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include<iostream>
#include "evaluator.h"
Evaluator::Evaluator(){
    symtable = new SymbolTable();
}
ExprTreeNode* buildExpressionTree(vector<string>& code, int& index) {
    if (index >= code.size()) {
        return nullptr;
    }

    string token = code[index];
    index++;
    ExprTreeNode* node = new ExprTreeNode();
    if(token == "(") {
        node->left = buildExpressionTree(code,index);
        if(index<code.size()) {
            if (code[index] == "+") {
                node->type = "ADD";
                index++;
                node->right = buildExpressionTree(code,index);
            } else if (code[index] == "-") {
                node->type = "SUB";
                index++;
                node->right = buildExpressionTree(code,index);
            } else if (code[index] == "*") {
                node->type = "MUL";
                index++;
                node->right = buildExpressionTree(code,index);
            } else if (code[index] == "/") {
                node->type = "DIV";
                index++;
                node->right = buildExpressionTree(code,index);
            }
        }
        index++;
    }
    else if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
        // Handle numeric values.
        string s = token;
        UnlimitedInt* a = new UnlimitedInt(s);
        UnlimitedInt* b = new UnlimitedInt("1");
        UnlimitedRational* V = new UnlimitedRational(a, b);
        node->val = V;
        node->evaluated_value=node->val;
        node->type = "VAL";
    } else if (token[0] <= 'z' && token[0]>= 'A'){
        // Handle variables.
        node->type = "VAR";
        node->id=token;
    }
    
    else if (index<code.size() && token == ")") {
        // If the current token is '(', create a left child and descend.
        index++;
    }
 return node;
}


void Evaluator::parse(vector<string> code) {
        ExprTreeNode* root = new ExprTreeNode();
        root->type = "EQUAL";
        root->left = new ExprTreeNode();
        root->left->type = "VAR";
        root->left->id = code[0];
        code.erase(code.begin(), code.begin() + 2);
        int index = 0;
        root->right = buildExpressionTree(code, index);
        expr_trees.push_back(root);
}
Evaluator::~Evaluator(){
    //Clean up the expr_trees vector
    for (auto tree : expr_trees) {
        ////delete tree;
    }
    expr_trees.clear();

    //Clean up the SymbolTable
    delete symtable;
}
// Define a recursive function to evaluate the expression tree
UnlimitedRational* evaluateExpression(ExprTreeNode* node, SymbolTable* st) {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->type == "VAL") {
        node->evaluated_value=node->val;
        return node->val;
    } else if (node->type == "VAR") {
            node->val=st->search(node->id);
            return node->val;
        
    } else if (node->type == "ADD") {
        // If it's an addition node, evaluate left + right
        UnlimitedRational* leftValue = evaluateExpression(node->left,st);
        UnlimitedRational* rightValue = evaluateExpression(node->right,st);
        node->evaluated_value=UnlimitedRational::add(leftValue,rightValue);
         return node->evaluated_value;
    } else if (node->type == "SUB") {
         UnlimitedRational* leftValue = evaluateExpression(node->left,st);
        UnlimitedRational* rightValue = evaluateExpression(node->right,st);
        node->evaluated_value=UnlimitedRational::sub(leftValue,rightValue);
         return node->evaluated_value;
    } else if (node->type == "MUL") {
         UnlimitedRational* leftValue = evaluateExpression(node->left,st);
        UnlimitedRational* rightValue = evaluateExpression(node->right,st);
        node->evaluated_value=UnlimitedRational::mul(leftValue,rightValue);
        return node->evaluated_value;
    }
        UnlimitedRational* leftValue = evaluateExpression(node->left,st);
        UnlimitedRational* rightValue = evaluateExpression(node->right,st);
        node->evaluated_value=UnlimitedRational::div(leftValue,rightValue);
         return node->evaluated_value;
}

void Evaluator::eval() {
    for(int i=0;i<expr_trees.size();i++){
        ExprTreeNode* root = expr_trees[i];
        UnlimitedRational* a=evaluateExpression(root->right, symtable);
        symtable->insert(root->left->id,a);
}
}
// }
// int main() {
//     vector<string> a(11);
//     a[0] = "v";
//     a[1] = ":=";
//     a[2] = "(";
//     a[3] = "13";
//     a[4] = "+";
//     a[5] = "(";
//     a[6] = "2";
//     a[7] = "/";
//     a[8] = "51";
//     a[9] = ")";
//     a[10] = ")";

//     vector<string> b(15);

//     b[0] = "v2";
//     b[1] = ":=";
//     b[2] = "(";
//     b[3] = "(";
//     b[4] = "v";
//     b[5] = "+";
//     b[6] = "3";
//     b[7] = ")";
//     b[8] = "+";
//     b[9] = "(";
//     b[10] = "v";
//     b[11] = "+";
//     b[12] = "25";
//     b[13] = ")";
//     b[14] = ")";
//     Evaluator *c = new Evaluator();
//     c->parse(a);
//     c->parse(b);
    
//     // std::vector<std::string> tokenVector;
//     // bool parseError = false;
//     // checkParseTreeBasic(c->expr_trees[c->expr_trees.size() - 1], tokenVector, parseError, true);
//     // p(tokenVector);
//     c->eval();

//     std::cout << c->symtable->search("v")->get_frac_str() << "   v\n";

//     std::cout << c->symtable->search("v2")->get_frac_str() << "   v\n";
//     delete c;
//     return 0;
// } 

