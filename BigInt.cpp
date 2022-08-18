#include "BigInt.h"
#include <vector>

BigInt::BigInt(string s) {
    digits="";
    while(s[0]=='0' && s.length()>1) {
        s.erase(0,1);
    }
    for(int i=s.length()-1; i>=0; i--) {
        if(!isdigit(s[i])) {
            throw "Error: invalid input";
        }
        digits.push_back(s[i]);
    }
}

BigInt::BigInt(unsigned ll n) {
    digits="";
    while(n) {
        digits.push_back(n%10+'0');
        n/=10;
    }
}

BigInt::BigInt(const BigInt& b): digits{b.digits} {}

std::ostream& operator<<(std::ostream& os, const BigInt& b) {
    for(int i=0; i<b.Length(); i++) {
        os << b[i];
    }
    return os;
}

std::istream& operator>>(std::istream& is, BigInt& b) {
    b.digits="";
    string s;
    is >> s;
    for(int i=s.length()-1; i>=0; i--) {
        if(!isdigit(s[i])) {
            throw "Invalid Number";
        }
        b.digits.push_back(s[i]);
    }
    return is;
}

BigInt& BigInt::operator=(const BigInt& b) {
    this->digits=b.digits;
    return *this;
}

void BigInt::removeZeroes() {
    while(digits.back()=='0' && digits.size()>1) {
        digits.pop_back();
    }
}

BigInt& BigInt::operator+=(BigInt b) {
    string sum="";
    char digit;
    bool overflow=false;
    for(int i=0; i<std::max(b.Length(), this->Length()); i++) {
        if(this->Length()<b.Length()) {
            this->digits.push_back('0');
        }
        else if(b.Length()<this->Length()) {
            b.digits.push_back('0');
        }
        if(!overflow) {
            sum.push_back('0');
        }
        digit=this->digits[i]+b.digits[i]-'0';
        
        sum.back()+=digit-'0';
        if(sum.back()>'9') {
            sum.back()-=10;
            sum.push_back('1');
            overflow=true;
        }
        else {
            overflow=false;
        }
    }

    this->digits=sum;
    return *this;
}

BigInt BigInt::operator+(const BigInt& b) const {
    BigInt c{*this};
    c+=b;
    return c;
}

void BigInt::operator++() {
    *this+=1;
}

void BigInt::operator++(int) {
    *this+=1;
}

BigInt& BigInt::operator-=(BigInt b) {
    if(*this<b) {
        std::swap(this->digits, b.digits);
    }

    string result="";
    char currentdigit;
    bool overflow=false;

    for(int i=0; i<std::max(this->Length(), b.Length()); i++) {
        if(b.Length()<this->Length()) {
            b.digits.push_back('0');
        }

        currentdigit=this->digits[i]-b.digits[i]+'0';
        if(overflow) {
            currentdigit--;
        }
        if(currentdigit<'0') {
            currentdigit+=10;
            overflow=true;
        }
        else {
            overflow=false;
        }
        result.push_back(currentdigit);
    }

    this->digits=result;
    this->removeZeroes();
    return *this;
}

BigInt BigInt::operator-(const BigInt& b) const {
    if(b>*this) {
        return b-*this;
    }
    BigInt c=*this;
    c-=b;
    return c;
}

void BigInt::operator--() {
    *this-=1;
}

void BigInt::operator--(int) {
    *this-=1;
}

BigInt& BigInt::operator*=(const BigInt& b) {
    if(b==0) {
        *this=0;
        return *this;
    }

    BigInt c=*this;
    BigInt counter=1;
    while(true) {
        if(counter+counter>b) {
            break;
        }
        *this+=*this;
        counter+=counter;
    }

    BigInt ceil=*this+*this;

    bool goFromBelow=(ceil-b>b-*this);

    if(goFromBelow) {
        for(BigInt i=counter; i!=b; i++) {
            *this+=c;
        }
        return *this;
    }
    else {
        *this=ceil;
        for(BigInt i=counter+counter; i!=b; i--) {
            *this-=c;
        }
        return *this;
    }
}

BigInt BigInt::operator*(const BigInt& b) const {
    BigInt c=*this;
    c*=b;
    return c;
}

BigInt& BigInt::operator/=(const BigInt& b) {
    if(b==0) {
        throw "Error: cannot divide by zero";
    }

    if(b>*this) {
        this->digits="0";
        return *this;
    }
    
    BigInt bb=b;
    BigInt result=0;
    std::vector<BigInt> a={1};
    while(bb<*this) {
        bb+=bb;
        a.emplace_back(a.back()*2);
    }
    a.pop_back();

    for(int i=a.size()-1; i>=0; i--) {
        if(*this>=a.at(i)*b) {
            result+=a.at(i);
            *this-=a.at(i)*b;
            if(*this==0) {
                break;
            }
        }
    }

    *this=result;
    return *this;
}

BigInt BigInt::operator/(const BigInt& b) const {
    BigInt c=*this;
    c/=b;
    return c;
}

BigInt& BigInt::operator^=(const BigInt& b) {
    BigInt c=*this;
    for(BigInt i=1; i!=b; i++) {
        *this*=c;
    }
    return *this;
}

BigInt BigInt::operator^(const BigInt& b) const {
    BigInt c=*this;
    c^=b;
    return c;
}

BigInt& BigInt::operator%=(const BigInt& b) {
    if(b>*this) {
        return *this;
    }

    std::vector<BigInt> nums;
    BigInt counter=b;

    while(counter<=*this) {
        nums.emplace_back(counter);
        counter+=counter;
    }
    for(int i=nums.size()-1; i>=0; i--) {
        if(nums.at(i)<=*this) {
            *this-=nums.at(i);
        }
    }

    return *this;
}

BigInt BigInt::operator%(const BigInt& b) const {
    BigInt c=*this;
    c%=b;
    return c;
}


bool BigInt::operator==(const BigInt& b) const {
    return this->digits==b.digits;
}

bool BigInt::operator!=(const BigInt& b) const {
    return this->digits!=b.digits;
}

bool BigInt::operator>(const BigInt& b) const {
    if(b.Length()!=this->Length()) {
        return this->Length()>b.Length();
    }
    for(int i=this->Length()-1; i>=0; i--) {
        if(this->digits[i]!=b.digits[i]) {
            return this->digits[i]>b.digits[i];
        }
    }
    return false;
}

bool BigInt::operator>=(const BigInt& b) const {
    if(*this==b) {
        return true;
    }
    return *this>b;
}

bool BigInt::operator<(const BigInt& b) const {
    return !(*this>=b);
}

bool BigInt::operator<=(const BigInt& b) const {
    return !(*this>b);
}


char BigInt::operator[](const int& n) const {
    if(n>=this->Length() || n<0) {
        throw "Index Error";
    }
    return this->digits[this->Length()-n-1];
}


// Functions

int BigInt::Length() const{
    return digits.length();
}

BigInt factorial(int n) {
    BigInt result=1;
    for(BigInt i=2; i<=n; i++) {
        result*=i;
    }

    return result;
}

BigInt sqrt(const BigInt& b) {
    if(b.Length()<4) {
        BigInt res=0;
        int counter=0;
        int add=3;
        while(true) {
            if((res+1)*(res+1)>b) {
                return res;
            }
            counter+=add;
            add+=2;
            res++;
        }
    }
    
    BigInt lowerbound;
    string l="10";
    BigInt result;
    string r="55";
    BigInt upperbound;
    string u="100";
    
    for(int i=0; i<b.Length()/2-2; i++) {
        l.push_back('0');
        r.push_back('0');
        u.push_back('0');
    }
    if(b.Length()%2==1) {
        l.push_back('0');
        r.push_back('0');
        u.push_back('0');
    }

    lowerbound=l;
    result=r;
    upperbound=u;

    while(true) {
        if(result*result>b) {
            upperbound=result;
            result=(result+lowerbound)/2;
        }
        else {
            if(result*result<=b && (result+1)*(result+1)>b) {
                return result;
            }
            lowerbound=result;
            result=(result+upperbound)/2;
        }
    }
}