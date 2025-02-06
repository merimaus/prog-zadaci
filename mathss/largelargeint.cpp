#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

class LargeInt {
private:
    vector<int> num;
    bool sign;

public:
    LargeInt() : sign(false) {}
    LargeInt(const string &s) {
        sign = (s[0] == '-');
        for (int i = s.size() - 1; i >= sign; i--) {
            num.push_back(s[i] - '0');
        }
    }

    bool operator==(const LargeInt &a) const {
        return num == a.num && sign == a.sign;
    }

    LargeInt abs() const {
        LargeInt result = *this;
        result.sign = false;
        return result;
    }

    bool operator>(const LargeInt &other) const {
        return other < *this;
    }

    bool operator<(const LargeInt &other) const {
        if (sign != other.sign) return sign;
        if (num.size() != other.num.size()) return (num.size() < other.num.size()) ^ sign;
        for (int i = num.size() - 1; i >= 0; --i) {
            if (num[i] != other.num[i]) return (num[i] < other.num[i]) ^ sign;
        }
        return false;
    }

    bool operator<=(const LargeInt &other) const {
        return !(*this > other);
    }

    bool operator>=(const LargeInt &other) const {
        return !(*this < other);
    }

    LargeInt operator-() const {
        LargeInt b = *this;
        b.sign = !b.sign;
        return b;
    }

    bool operator!=(const LargeInt &other) const {
        return !(*this == other);
    }

    LargeInt operator+(const LargeInt &a) const {
        if (sign != a.sign) return *this - (-a);

        LargeInt b;
        b.num.clear();
        int carry = 0;
        int n = max(num.size(), a.num.size());
        for (int i = 0; i < n; i++) {
            if (i < num.size()) carry += num[i];
            if (i < a.num.size()) carry += a.num[i];
            b.num.push_back(carry % 10);
            carry /= 10;
        }
        if (carry) b.num.push_back(carry);
        b.sign = sign;
        return b;
    }

    LargeInt operator-(const LargeInt &a) const {
        if (sign != a.sign) return *this + (-a);
        if (abs() < a.abs()) return -(a - *this);

        LargeInt b;
        b.num.clear();
        int carry = 0;
        for (int i = 0; i < num.size(); i++) {
            carry += num[i];
            if (i < a.num.size()) carry -= a.num[i];
            if (carry < 0) {
                b.num.push_back(carry + 10);
                carry = -1;
            } else {
                b.num.push_back(carry);
                carry = 0;
            }
        }
        while (b.num.size() > 1 && b.num.back() == 0) b.num.pop_back();
        b.sign = sign;
        return b;
    }

    LargeInt operator*(const LargeInt &a) const {
        LargeInt b;
        b.num.resize(num.size() + a.num.size(), 0);
        for (int i = 0; i < num.size(); i++) {
            for (int j = 0; j < a.num.size(); j++) {
                b.num[i + j] += num[i] * a.num[j];
                b.num[i + j + 1] += b.num[i + j] / 10;
                b.num[i + j] %= 10;
            }
        }
        while (b.num.size() > 1 && b.num.back() == 0) b.num.pop_back();
        b.sign = sign != a.sign;
        return b;
    }

    LargeInt operator/(const LargeInt &other) const {
        if (other == LargeInt("0")) {
            throw invalid_argument("Division by zero");
        }

        LargeInt result, current;
        LargeInt dividend = abs();
        LargeInt divisor = other.abs();

        result.num.resize(dividend.num.size(), 0);

        for (int i = dividend.num.size() - 1; i >= 0; --i) {
            current.num.insert(current.num.begin(), dividend.num[i]);
            if (current.num.size() > 1 && current.num.back() == 0) current.num.pop_back();

            int x = 0;
            while (current >= divisor) {
                current = current - divisor;
                ++x;
            }
            result.num[i] = x;
        }

        while (result.num.size() > 1 && result.num.back() == 0) result.num.pop_back();
        result.sign = sign != other.sign;
        if (result.num.size() == 1 && result.num[0] == 0) result.sign = false;
        return result;
    }

    LargeInt operator%(const LargeInt &a) const {
        if (a == LargeInt("0")) {
            throw invalid_argument("Modulo by zero");
        }
        return *this - (*this / a) * a;
    }

    friend ostream &operator<<(ostream &os, const LargeInt &a) {
        if (a.sign) os << '-';
        for (int i = a.num.size() - 1; i >= 0; i--) {
            os << a.num[i];
        }
        return os;
    }
    LargeInt gcd(const LargeInt &a) const {
        LargeInt x = abs();
        LargeInt y = a.abs();
        while (y != LargeInt("0")) {
            LargeInt temp = y;
            y = x % y;
            x = temp;
        }
        return x;
    }

    LargeInt lcm(const LargeInt &a) const {
        return (abs() * a.abs()) / gcd(a);
    }

    static void sieveOfEratosthenes(const LargeInt &limit) {
        if (limit.num.size() > 9) {
            cout << "Error: Sieve limit too large to compute in practical memory.\n";
            return;
        }
        long long n = 0;
        for (int i = limit.num.size() - 1; i >= 0; --i) {
            n = n * 10 + limit.num[i];
        }

        vector<bool> isPrime(n + 1, true);
        isPrime[0] = isPrime[1] = false;

        for (long long i = 2; i * i <= n; ++i) {
            if (isPrime[i]) {
                for (long long j = i * i; j <= n; j += i) {
                    isPrime[j] = false;
                }
            }
        }

        cout << "Primes up to " << limit << ": ";
        for (long long i = 2; i <= n; ++i) {
            if (isPrime[i]) cout << i << " ";
        }
        cout << endl;
    }
};

int main() {
    LargeInt a("-12");
    LargeInt b("4");
    cout << "sobiranje " << (a + b) << endl;
    cout << "odzemanje " << (a - b) << endl;
    cout << "mnozenje " << (a * b) << endl;
    cout << "delenje " << (a / b) << endl;
    cout << "modul " << (a % b) << endl;

    LargeInt n("10023456789234567834567");
    LargeInt::sieveOfEratosthenes(n);

    return 0;
}
