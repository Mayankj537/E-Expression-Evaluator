/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
using namespace std;
#include <string>
bool compareIntStrings(const std::string& a, const std::string& b) {
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
UnlimitedInt::UnlimitedInt(){
    size=0;
    sign=1;
    capacity=50;
    unlimited_int=new int[capacity];
    for(int i=0;i<capacity;i++){
        unlimited_int[i]=0;
    }
}
UnlimitedInt::UnlimitedInt(int i){
    size = 0;
        capacity =100; 
        if(i>0){
            sign=1;
        }
        else if(i==0){
            sign=0;
        }
        else{
            sign=-1;
        }
        i = std::abs(i); 
        unlimited_int = new int[capacity];
        if(i==0){
            unlimited_int[0]=0;
        }
        while (i > 0) {
            if (size == capacity) {
               
                capacity *= 2;
                int* new_unlimited_int = new int[capacity];
                for (int j = 0; j < size; ++j) {
                    new_unlimited_int[j] = unlimited_int[j];
                }
                delete[] unlimited_int;
                unlimited_int = new_unlimited_int;
            }

            unlimited_int[size] = i % 10; 
            i /= 10; 
            size++;
        }
    };
UnlimitedInt::UnlimitedInt(string s){
    size = 0;
        capacity = 100; 
        if(s[0]=='-'){
            sign=-1;
        }
        else{
            sign=1;
        }
        unlimited_int = new int[capacity];
        if(s[0]=='-'){
        while (size<s.size()-1) {
            if (size == capacity) {
                capacity *= 2;
                int* new_unlimited_int = new int[capacity];
                for (int j = 0; j < size; ++j) {
                    new_unlimited_int[j] = unlimited_int[j];
                }
                delete[] unlimited_int;
                unlimited_int = new_unlimited_int;
            }
            int num=s[s.size()-1-size]-'0'; 
            unlimited_int[size]=num;
            size++;
        }
        }
        else if(s=="0"){
            unlimited_int[0]=0;
            sign=0;
        }
        else{
            while (size<s.size()) {
            if (size == capacity) {
                capacity *= 2;
                int* new_unlimited_int = new int[capacity];
                for (int j = 0; j < size; ++j) {
                    new_unlimited_int[j] = unlimited_int[j];
                }
                delete[] unlimited_int;
                unlimited_int = new_unlimited_int;
            }
            int num=s[s.size()-1-size]-'0'; 
            unlimited_int[size]=num; 
            size++;
        }
        }
    };
string stringDivision(string num1, string num2,bool &z) {
   if(!compareIntStrings(num1,num2)){
    return "0";
   }
   int n=num1.length()-num2.length();
   string temp1=num1;
   UnlimitedInt* t1=new UnlimitedInt(temp1);
   string quotient="";
   UnlimitedInt* t3=new UnlimitedInt(quotient);
   for(int i=0;i<=n;i++){
    int res=0;
    string temp2=num2;
    for(int j=0;j<n-i;j++){
        temp2+="0";
    }
    UnlimitedInt* t2=new UnlimitedInt(temp2);
    while(compareIntStrings(t1->to_string(),temp2)){
        t1=UnlimitedInt::sub(t1,t2);
        res++;
    }
    string s=to_string(res);
    quotient+=s;
    delete t2;
}
if(t1->get_sign()==0){
    z=true;
}
delete t1;
delete t3;
    if(quotient.length()!=1 && quotient[0]=='0'){
        return quotient.substr(1,quotient.length());
    }
    else{
        return quotient;
    }

}
string stringMul(string num1,string num2){
     if (num1 == "0" || num2 == "0") {
      return "0";
   }
   string product(num1.size() + num2.size(), 0);
   for (int i = num1.size() - 1; i >= 0; i--) {
      for (int j = num2.size() - 1; j >= 0; j--) {
            int n = (num1[i] - '0') * (num2[j] - '0') + product[i + j + 1];
            product[i + j + 1] = n % 10;
            product[i + j] += n / 10;
      }
   }
   for (int i = 0; i < product.size(); i++) {
      product[i] += '0';
   }
   if (product[0] == '0') {
      return product.substr(1);
   }
   return product;
}
UnlimitedInt::~UnlimitedInt() {
        delete[] unlimited_int;
}
int UnlimitedInt::get_size(){
    if(size==0){
        return 1;
    }
    return size;
}
int* UnlimitedInt::get_array(){
    return unlimited_int;
}
int UnlimitedInt::get_sign(){
    return sign;
}
string UnlimitedInt::to_string(){
    string s="";
    int* arr=this->get_array();
    for(int i=this->get_size()-1;i>=0;i--){
        int num=arr[i];
        s+=std::to_string(num);
    }
    if(this->sign==-1){
        return "-"+s;
    }
    return s;
}
UnlimitedInt*UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2){
    if (i1->sign == 0) {
        UnlimitedInt *res=new UnlimitedInt();
        res->sign=i2->sign;
        res->size=i2->size;
        res->capacity=i2->capacity;
        res->unlimited_int=i2->get_array();
        return res;
    } else if (i2->sign == 0) {
        UnlimitedInt *res=new UnlimitedInt();
        res->sign=i1->sign;
        res->size=i1->size;
        res->capacity=i1->capacity;
        res->unlimited_int=i1->get_array();
        return res;
    }
    else if(i1->sign!=i2->sign){
        if(i1->sign==-1&& i2->sign==1){
            i1->sign=1;
            return UnlimitedInt::sub(i2,i1);
        }
        i2->sign=1;
        return UnlimitedInt::sub(i1,i2);
    }
    int carry = 0;
    int maxsize = std::max(i1->size, i2->size);
    int resultsign = (i1->sign);
    UnlimitedInt* result = new UnlimitedInt(0);
    result->sign = resultsign;

    for (int i = 0; i < maxsize || carry > 0; ++i) {
        int digit1 = (i < i1->size) ? i1->unlimited_int[i] : 0;
        int digit2 = (i < i2->size) ? i2->unlimited_int[i] : 0;

        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        int resultDigit = sum % 10;

        result->unlimited_int[i] = resultDigit;
        result->size++;
    }

    // If there's still a carry left, add it as a new digit
    if (carry > 0) {
        result->unlimited_int[result->size] = carry;
        result->size++;
    }
    return result;
}
UnlimitedInt*UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2){
    int resultsign;
    if(i1->sign==0){
        UnlimitedInt *res=new UnlimitedInt();
        res->sign=-1*(i2->sign);
        res->size=i2->size;
        res->capacity=i2->capacity;
        res->unlimited_int=i2->get_array();
        return res;
    }else if(i2->sign==0){
        UnlimitedInt *res=new UnlimitedInt();
        res->sign=(i1->sign);
        res->size=i1->size;
        res->capacity=i1->capacity;
        res->unlimited_int=i1->get_array();
        return res;
    }
    else if(i1->sign!=i2->sign){
        if(i1->sign==1 && i2->sign==-1){
            i2->sign=1;
            return add(i1,i2);
        }
        if(i1->sign==-1 && i2->sign==1){
            i2->sign=-1;
            return add(i1,i2);
        }
    }else if(i1->sign==1 && i2->sign==1){
        if(i1->size>i2->size){
            resultsign=1;
        }
        else if(i1->size<i2->size){
            resultsign=-1;
        }else{
            int* arr1 = i1->get_array();
            int* arr2 = i2->get_array();
            int i = (i1->get_size()) - 1;

            while (i >= 0 && arr1[i] == arr2[i]) {
            i = i - 1;
            }

            if (i >= 0) {
                if (arr1[i] > arr2[i]) {
                    resultsign = 1;
                } else if (arr1[i] < arr2[i]) {
                    resultsign = -1;
                } else {
                    resultsign = 0;
                }
            } else {
                resultsign = 0; 
            }

        }
    }else if(i1->sign==-1 && i2->sign==-1){
        if(i1->size>i2->size){
            resultsign=-1;
        }
        else if(i1->size<i2->size){
            resultsign=1;
    }else{
            int* arr1=i1->get_array();
            int* arr2=i2->get_array();
            int i=(i1->get_size())-1;
            while(arr1[i]==arr2[i] && i>=0){
                i=i-1;
            }
            if(arr1[i]>arr2[i]){
                resultsign =-1;
            }else if(arr1[i]<arr2[i]){
                resultsign=1;
            }else{
                resultsign=0;
            }
        }
    }
    UnlimitedInt* result = new UnlimitedInt(0); 
result->sign = resultsign;
if(result->sign>=0){
    if(i1->sign==1 && i2->sign==1){
int borrow = 0;
int max_size = std::max(i1->size, i2->size);

for (int i = 0; i < max_size; ++i) {
    int digit1 = (i < i1->size) ? i1->unlimited_int[i] : 0;
    int digit2 = (i < i2->size) ? i2->unlimited_int[i] : 0;

    int subtraction = digit1 - digit2 - borrow;

    if (subtraction < 0) {
        subtraction += 10;
        borrow = 1;
    } else {
        borrow = 0;
    }

    result->unlimited_int[i] = subtraction;
    result->size++;
}
    if (borrow != 0) {
        result->unlimited_int[max_size] = borrow;
        result->size++;
    }
}else if(i1->sign==-1 && i2->sign==-1){
      int borrow = 0;
int max_size = std::max(i1->size, i2->size);

for (int i = 0; i < max_size; ++i) {
    int digit1 = (i < i1->size) ? i1->unlimited_int[i] : 0;
    int digit2 = (i < i2->size) ? i2->unlimited_int[i] : 0;

    int subtraction = digit2- digit1- borrow;

    if (subtraction < 0) {
        subtraction += 10;
        borrow = 1;
    } else {
        borrow = 0;
    }

    result->unlimited_int[i] = subtraction;
    result->size++;
}
    if (borrow != 0) {
        result->unlimited_int[max_size] = borrow;
        result->size++;
    }
}
}
else if(result->sign<0){
    if(i1->sign==1 && i2->sign==1){
int borrow = 0;
int max_size = std::max(i1->size, i2->size);

for (int i = 0; i < max_size; ++i) {
    int digit1 = (i < i1->size) ? i1->unlimited_int[i] : 0;
    int digit2 = (i < i2->size) ? i2->unlimited_int[i] : 0;

    int subtraction = digit2- digit1- borrow;

    if (subtraction < 0) {
        subtraction += 10;
        borrow = 1;
    } else {
        borrow = 0;
    }

    result->unlimited_int[i] = subtraction;
    result->size++;
}
    if (borrow != 0) {
        result->unlimited_int[max_size] = borrow;
        result->size++;
    }

}else if(i1->sign==-1&&i2->sign==-1){
    int borrow = 0;
int max_size = std::max(i1->size, i2->size);

for (int i = 0; i < max_size; ++i) {
    int digit1 = (i < i1->size) ? i1->unlimited_int[i] : 0;
    int digit2 = (i < i2->size) ? i2->unlimited_int[i] : 0;

    int subtraction = digit1 - digit2 - borrow;

    if (subtraction < 0) {
        subtraction += 10;
        borrow = 1;
    } else {
        borrow = 0;
    }

    result->unlimited_int[i] = subtraction;
    result->size++;
}
    if (borrow != 0) {
        result->unlimited_int[max_size] = borrow;
        result->size++;
    }
}
}
        while (result->size > 1 && result->unlimited_int[result->size - 1] == 0) {
            result->size--;
        }

        return result;
}
UnlimitedInt*UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2){
    if(i1->to_string()=="1"){
        return i2;
    }
    else if(i2->to_string()=="1"){
        return i1;
    }
    if(i1->sign==1 && i2->sign==1){
        string s=stringMul(i1->to_string(),i2->to_string());
        return new UnlimitedInt(s);
    }
    else if(i1->sign==-1 && i2->sign==-1){
        UnlimitedInt* t1=new UnlimitedInt(i1->to_string());
        UnlimitedInt* t2=new UnlimitedInt(i2->to_string());
        t1->sign=1;
        t2->sign=1;
        string s=stringMul(t1->to_string(),t2->to_string());
        delete t1;
        delete t2;
        return new UnlimitedInt(s);
    }
    else if(i1->sign==-1 && i2->sign==1){
        UnlimitedInt* t1=new UnlimitedInt(i1->to_string());
        t1->sign=1;
        string s=stringMul(t1->to_string(),i2->to_string());
        string t="-"+s;
        delete t1;
        return new UnlimitedInt(t);
    }
    else{
        UnlimitedInt* t2=new UnlimitedInt(i2->to_string());
        t2->sign=1;
        string s=stringMul(t2->to_string(),i1->to_string());
        string t="-"+s;
        delete t2;
        return new UnlimitedInt(t);
    }
    
}
UnlimitedInt*UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2){
    bool z=false;
    if(i1->sign==1 && i2->sign==1){
        string s=stringDivision(i1->to_string(),i2->to_string(),z);
        return new UnlimitedInt(s);
    }
    else if(i1->sign==-1 && i2->sign==-1){
        string s1=i1->to_string().substr(1,i1->to_string().length());
        string s2=i2->to_string().substr(1,i2->to_string().length());
        string s3=stringDivision(s1,s2,z);
        return new UnlimitedInt(s3);
    }
    else if(i1->sign==1 && i2->sign==-1){
        string s2=i2->to_string().substr(1,i2->to_string().length());
        string s3=stringDivision(i1->to_string(),s2,z);
        if(z){
            UnlimitedInt* res=new UnlimitedInt(s3);
            res->sign=-1;
            return res;
        }
        UnlimitedInt *res=new UnlimitedInt(s3);
        UnlimitedInt *adder=new UnlimitedInt(1);
        res=UnlimitedInt::add(res,adder);
        res->sign=-1;
        return res;
    }
    else{
        string s1=i1->to_string().substr(1,i1->to_string().length());
        string s3=stringDivision(s1,i2->to_string(),z);
        if(z){
            UnlimitedInt* res=new UnlimitedInt(s3);
            res->sign=-1;
            return res;
        }
        UnlimitedInt *res=new UnlimitedInt(s3);
        UnlimitedInt *adder=new UnlimitedInt(1);
        res=UnlimitedInt::add(res,adder);
        res->sign=-1;
        return res;
    }
    }
UnlimitedInt*UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2){
    UnlimitedInt* A=UnlimitedInt::div(i1,i2);
    UnlimitedInt* B=UnlimitedInt::mul(i2,A);
    UnlimitedInt* C=UnlimitedInt::sub(i1,B);
    return C;
}
// int main(){
//     string s="122";
//     UnlimitedInt* a=new UnlimitedInt(s);
//     std::cout<<a->to_string();
// }

