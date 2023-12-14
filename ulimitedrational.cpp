/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include<string>
using namespace std;
#include "ulimitedrational.h"
bool compareIntegerStrings(const std::string& a, const std::string& b) {
    if (a[0] == '-' && b[0] != '-') {
        return false;
    } else if (a[0] != '-' && b[0] == '-') {
        return true; 
    } else if (a[0] == '-') {
        
        if (a.length() > b.length()) {
            return false;
        } else if (a.length() < b.length()) {
            return true;
        }
        for (size_t i = 1; i < a.length(); ++i) {
            if (a[i] > b[i]) {
                return false;
            } else if (a[i] < b[i]) {
                return true;
            }
        }
        return true;
    } else {
        if (a.length() > b.length()) {
            return true;
        } else if (a.length() < b.length()) {
            return false;
        }
        for (size_t i = 0; i < a.length(); ++i) {
            if (a[i] > b[i]) {
                return true;
            } else if (a[i] < b[i]) {
                return false;
            }
        }
        return true;
    }
}
UnlimitedInt* GCD(UnlimitedInt* a,UnlimitedInt* b){
     if(b->to_string()=="0"){
        return new UnlimitedInt(a->to_string());
     }
     else if(a->to_string()=="0"){
        return new UnlimitedInt(b->to_string());
     }
     else if(compareIntegerStrings(a->to_string(),b->to_string())){
        a=UnlimitedInt::mod(a,b);
        return GCD(a,b);
     }
      else{
         b=UnlimitedInt::mod(b,a);
         return GCD(a,b);
     }
}
UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den){
    p=num;
    q=den;
    if(p->get_sign()>0 && q->get_sign()>0){
        UnlimitedInt* c=GCD(p,q);
        p=UnlimitedInt::div(p,c);
        q=UnlimitedInt::div(q,c);
        delete c;
    }
    else if(p->get_sign()==-1 && q->get_sign()==1){
        UnlimitedInt* P=new UnlimitedInt(p->to_string().substr(1,p->get_size()));
        UnlimitedInt* c=GCD(P,q);
        P=UnlimitedInt::div(P,c);
        q=UnlimitedInt::div(q,c);
        UnlimitedInt * n=new UnlimitedInt("-"+P->to_string());
        p=n;
    }
    else if(p->get_sign()==1 && q->get_sign()==-1){
        UnlimitedInt* Q=new UnlimitedInt(q->to_string().substr(1,q->get_size()));
        UnlimitedInt* c=GCD(p,Q);
        p=UnlimitedInt::div(p,c);
        Q=UnlimitedInt::div(Q,c);
        UnlimitedInt * n=new UnlimitedInt("-"+Q->to_string());
        q=n;
        // delete Q;
        // delete n;
    }
    else if(p->get_sign()==-1 && q->get_sign()==-1){
        UnlimitedInt* P=new UnlimitedInt(p->to_string().substr(1,p->get_size()));
        UnlimitedInt* Q=new UnlimitedInt(q->to_string().substr(1,q->get_size()));
        UnlimitedInt* c=GCD(P,Q);
        P=UnlimitedInt::div(P,c);
        Q=UnlimitedInt::div(Q,c);
        p=P;
        q=Q;
    }
}
UnlimitedRational::UnlimitedRational(){
    p=new UnlimitedInt(0);
    q=new UnlimitedInt(0);

}
UnlimitedRational::~UnlimitedRational(){
    delete p;
    delete q;
}
UnlimitedInt* UnlimitedRational::get_p(){
    return p;
}
UnlimitedInt*UnlimitedRational::get_q(){
    return q;
}
string UnlimitedRational::get_p_str(){
    return p->to_string();
}
string UnlimitedRational::get_q_str(){
    return q->to_string();
}
string UnlimitedRational::get_frac_str(){
    if(q->get_sign()==0){
        return "0/0";
    }
    return p->to_string()+"/"+q->to_string();
}
UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1, UnlimitedRational* i2){
        if(i1->get_q_str()=="0"){
            return i1;
        }
        else if(i2->get_q_str()=="0"){
            return i2;
        }
        else if(i2->get_p_str()=="0"){
            return i1;
        }
        else if(i1->get_p_str()=="0"){
            return i2;
        }
        else{
            UnlimitedInt* den1=i1->get_q();
            UnlimitedInt* den2=i2->get_q();
            UnlimitedInt* resden=UnlimitedInt::mul(den1,den2);
            UnlimitedInt* num1= i1->get_p();
            UnlimitedInt* num2=i2->get_p();
            num1=UnlimitedInt::mul(num1,den2);
            num2=UnlimitedInt::mul(num2,den1);
            UnlimitedInt* resnum=UnlimitedInt::add(num1,num2);
            UnlimitedRational* res=new UnlimitedRational(resnum,resden);
            return res;
        }

}
UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1,UnlimitedRational* i2){
    if(i1->get_q_str()=="0"){
            return i1;
        }
    else if(i2->get_q_str()=="0"){
        return i2;
    }
    else if(i2->get_p_str()=="0"){
        return i1;
    }
    else{
        if(i2->get_p()->get_sign()==1){
            UnlimitedInt* num2=new UnlimitedInt("-"+i2->get_p_str());
            UnlimitedRational* I2=new UnlimitedRational(num2,i2->get_q());
            return add(i1,I2);
        }
        else {
            UnlimitedInt* num2=new UnlimitedInt(i2->get_p_str().substr(1,i2->get_p()->get_size()));
            UnlimitedRational* I2=new UnlimitedRational(num2,i2->get_q());
            return add(i1,I2);
        }
    }
}
UnlimitedRational*UnlimitedRational::mul(UnlimitedRational* i1, UnlimitedRational* i2){
    if(i1->get_q_str()=="0"){
            return i1;
        }
    else if(i2->get_q_str()=="0"){
        return i2;
    }
    else{
        UnlimitedInt* resnum=UnlimitedInt::mul(i1->get_p(),i2->get_p());
        UnlimitedInt* resden=UnlimitedInt::mul(i1->get_q(),i2->get_q());
        return new UnlimitedRational(resnum,resden);
    }
}
UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1, UnlimitedRational* i2){
    if(i1->get_q_str()=="0"){
            return i1;
        }
    else if(i2->get_q_str()=="0"){
        return i2;
    }
    else if(i2->get_p_str()=="0"){
        return new UnlimitedRational();
    }
    else{
        UnlimitedInt* P=i2->get_q();
        UnlimitedInt* Q=i2->get_p();
        UnlimitedRational* I2=new UnlimitedRational(P,Q);
        return mul(i1,I2);
    }
}
// int main(){
//     UnlimitedInt* p=new UnlimitedInt("696969");
//     UnlimitedInt* q=new UnlimitedInt(4);
//     UnlimitedInt* A=new UnlimitedInt(0);
//     UnlimitedInt* B=new UnlimitedInt("4");
//     UnlimitedRational* a=new UnlimitedRational(p,q);
//     //cout<<a->get_frac_str();
//     UnlimitedRational* b=new UnlimitedRational(A,B);
//     UnlimitedRational* c=UnlimitedRational::div(a,b);
//     UnlimitedRational* d=UnlimitedRational::add(a,b);
//     cout<<c->get_frac_str()<<endl;
//     cout<<d->get_frac_str();

// }