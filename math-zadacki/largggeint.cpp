#include<iostream>
#include<string>
#include<vector>
#include<cmath>
using namespace std;

class LargeInt
{
    private:
        vector<int> num;
        bool sign;

    public:
    
    LargeInt() : sign(false){}
    LargeInt(const string &s)
    {
        sign = (s[0] == '-');
        for(int i = s.size()-1; i>=sign; i--)
        {
            num.push_back(s[i] - '0');
        }

    }

    LargeInt operator+(const LargeInt &a)
    {
        LargeInt b("0");
        b.num.clear();
        int carry = 0;
        int n = max(num.size(), a.num.size());
        for(int i = 0; i < n; i++)
        {
            if(i < num.size()) carry += num[i];
            if(i < a.num.size()) carry += a.num[i];
            b.num.push_back(carry % 10);
            carry /= 10;
        }
        if(carry) b.num.push_back(carry);
        return b;

    }

    LargeInt operator-(const LargeInt &a)
    {
        LargeInt b("0");
        b.num.clear();
        int carry = 0;
        int n = max(num.size(), a.num.size());
        for(int i = 0; i < n; i++)
        {
            if(i < num.size()) carry += num[i];
            if(i < a.num.size()) carry -= a.num[i];
            if(carry < 0)
            {
                b.num.push_back(carry + 10);
                carry = -1;
            }
            else
            {
                b.num.push_back(carry);
                carry = 0;
            }
        }
        while(b.num.size() > 1 && b.num.back() == 0) b.num.pop_back();
        return b;
    }

    LargeInt operator*(const LargeInt &a)
    {
        LargeInt b("0");
        b.num.clear();
        b.num.resize(num.size() + a.num.size());
        for(int i = 0; i < num.size(); i++)
        {
            for(int j = 0; j < a.num.size(); j++)
            {
                b.num[i + j] += num[i] * a.num[j];
                b.num[i + j + 1] += b.num[i + j] / 10;
                b.num[i + j] %= 10;
            }
        }
        while(b.num.size() > 1 && b.num.back() == 0) b.num.pop_back();
        return b;
    }
    LargeInt operator/(const LargeInt& other) const {
    if (other == LargeInt("0")) {
        return LargeInt("0");
    }

    LargeInt result;
    LargeInt current;
    LargeInt dividend = abs(*this);
    LargeInt divisor = abs(other);

    result.num.resize(dividend.num.size(), 0);

    for (int i = dividend.num.size() - 1; i >= 0; --i) {
        current.num.insert(current.num.begin(), dividend.num[i]);
        if (current.num.size() > 1 && current.num.back() == 0) {
            current.num.pop_back();
        }

        int x = 0;
        while (current >= divisor) {
            current = current - divisor;
            ++x;
        }
        result.num[i] = x;
    }

    while (result.num.size() > 1 && result.num.back() == 0) {
        result.num.pop_back();
    }

    result.sign = sign != other.sign;
    if (result.num.size() == 1 && result.num[0] == 0) {
        result.sign = false;
    }

    return result;
}
    
    bool operator==(const LargeInt &a) const
    {
        return num==a.num && sign==a.sign;
    }
    
    LargeInt abs(const LargeInt &a) const {
    LargeInt result = a;
    result.sign = false;
    return result;
    
    bool LargeInt::operator>(const LargeInt& other) const {
    return other < *this;
}

bool LargeInt::operator<=(const LargeInt& other) const {
    return !(*this > other);
}

bool LargeInt::operator>=(const LargeInt& other) const {
    return !(*this < other);
}

    
    
};
    

    void print()
    {
        if(sign) cout << '-';
        for(int i = num.size() - 1; i >= 0; i--)
        {
            cout << num[i];
        }
        cout << endl;
    }
};

int main()
{
    string a, b;
    cin >> a >> b;
    LargeInt A(a), B(b);
    (A + B).print();
    (A - B).print();
    (A * B).print();
    (A / B).print();
    return 0;
}