/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"
SymEntry::SymEntry(string k, UnlimitedRational* v){
    key=k;
    val=v;
    left=nullptr;
    right=nullptr;
}
SymEntry::SymEntry(){
    key="undef";
    val=new UnlimitedRational(0,0);
    left=nullptr;
    right=nullptr;
}
SymEntry::~SymEntry(){
    key="deleted";
    delete val;
}