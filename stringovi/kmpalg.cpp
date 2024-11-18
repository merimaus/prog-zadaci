#include <iostream>
#include <cstring>

using namespace std;

class String
{
    char *chars;
    unsigned int length;

public:
    String()
    {
        length = 0;
        chars = nullptr;
    }

    String(const char *other)
    {
        length = strlen(other);
        chars = new char[length + 1];
        for (unsigned int i = 0; i < length; i++)
        {
            chars[i] = other[i];
        }
        chars[length] = '\0';
    }

    String(const String &other)
    {
        length = other.length;
        chars = new char[length + 1];
        for (unsigned int i = 0; i < length; i++)
        {
            chars[i] = other.chars[i];
        }
        chars[length] = '\0';
    }

    ~String()
    {
        delete[] chars;
    }

    String operator=(const char *other)
    {
        length = strlen(other);
        delete[] chars;
        chars = new char[length + 1];
        for (unsigned int i = 0; i < length; i++)
        {
            chars[i] = other[i];
        }
        chars[length] = '\0';
        return *this;
    }

    String operator=(const String &other)
    {
        if (this == &other)
        {
            return *this;
        }
        delete[] chars;
        length = other.length;
        chars = new char[length + 1];
        for (unsigned int i = 0; i < length; i++)
        {
            chars[i] = other.chars[i];
        }
        chars[length] = '\0';
        return *this;
    }

    char &operator[](unsigned int index)
    {
        return chars[index];
    }

    const char &operator[](unsigned int index) const
    {
        return chars[index];
    }

    friend ostream &operator<<(ostream &o, const String &other)
    {
        for (unsigned int i = 0; i < other.length; i++)
        {
            o << other.chars[i];
        }
        return o;
    }

    void compute(const String &subStr, int a[])
    {
        int len = 0;
        a[0] = 0;
        for (int i = 1; i < subStr.length; i++)
        {
            while (len > 0 && subStr[i] != subStr[len])
            {
                len = a[len - 1];
            }
            if (subStr[i] == subStr[len])
            {
                len++;
            }
            a[i] = len;
        }
    }

    void compute_reverse(const String &subStr, int a[])
    {
        int n = subStr.length;
        int len = 0;
        a[n - 1] = 0;
        for (int i = n - 2; i >= 0; i--)
        {
            while (len > 0 && subStr[i] != subStr[n - len - 1])
            {
                len = a[n - len];
            }
            if (subStr[i] == subStr[n - len - 1])
            {
                len++;
            }
            a[i] = len;
        }
    }
    int *findAllSubStr(const String &subStr)
    {
        int *r = new int[length];
        int *a = new int[subStr.length];
        int count = 0;
        compute(subStr, a);

        int j = 0;
        for (int i = 0; i < length; i++)
        {
            while (j > 0 && chars[i] != subStr[j])
            {
                j = a[j - 1];
            }
            if (chars[i] == subStr[j])
            {
                j++;
            }
            if (j == subStr.length)
            {
                r[count++] = i - j + 1;
                j = a[j - 1];
            }
        }

        int *res = new int[count];
        for (int i = 0; i < count; i++)
        {
            res[i] = r[i];
        }
        delete[] r;
        delete[] a;
        return res;
    }

    int findFirstSubStr(const String &subStr)
    {
        int *a = new int[subStr.length];
        compute(subStr, a);

        int j = 0;
        for (int i = 0; i < length; i++)
        {
            while (j > 0 && chars[i] != subStr[j])
            {
                j = a[j - 1];
            }
            if (chars[i] == subStr[j])
            {
                j++;
            }
            if (j == subStr.length)
            {
                delete[] a;
                return i - j + 1;
            }
        }

        delete[] a;
        return -1;
    }

    int findLastSubStr(const String &subStr)
    {
        int *a = new int[subStr.length];
        compute_reverse(subStr, a);

        int j = subStr.length - 1;
        for (int i = length - 1; i >= 0; i--)
        {
            while (j > 0 && chars[i] != subStr[j])
            {
                j = a[j - 1];
            }
            if (chars[i] == subStr[j])
            {
                j--;
            }
            if (j == -1)
            {
                delete[] a;
                return i;
            }
        }

        delete[] a;
    }

    int *findAllSubStrReverse(const char *subStr)
    {
        int n = strlen(subStr);
        int *r = new int[length];
        int *a = new int[n];
        int count = 0;

        compute_reverse(subStr, a);

        int j = n - 1;
        for (int i = length - 1; i >= 0; i--)
        {
            while (j < n - 1 && chars[i] != subStr[j])
            {
                j = n - a[j + 1] - 1;
            }
            if (chars[i] == subStr[j])
            {
                j--;
            }
            if (j == -1)
            {
                r[count++] = i;
                j = n - a[0] - 1;
            }
        }

        int *res = new int[count];
        for (int i = 0; i < count; i++)
        {
            res[i] = r[i];
        }
        delete[] r;
        delete[] a;
        return res;
    }

    int *rabinKarpSum(const String &subStr)
    {
        int *res = new int[length];
        int count = 0;

        int patternhash = 0, texthash = 0;

        for (int i = 0; i < subStr.length; ++i)
        {

            patternhash += (subStr[i] - 'a' + 1);
            texthash += (chars[i] - 'a' + 1);
        }

        for (int i = 0; i <= length - subStr.length; ++i)
        {
            if (patternhash == texthash)
            {
                int j = 0;
                for (; j < subStr.length; ++j)
                {
                    if (chars[i + j] != subStr[j])
                        break;
                }
                if (j == subStr.length)
                {
                    res[count++] = i;
                }
            }

            if (i < length - subStr.length)
            {
                texthash -= (chars[i] - 'a' + 1);
                texthash += (chars[i + subStr.length] - 'a' + 1);
            }
        }

        int *finalres = new int[count];
        for (int i = 0; i < count; ++i)
        {
            finalres[i] = res[i];
        }

        delete[] res;
        return finalres;
    }
};

int main()
{
    int n = 0;
    char asd[100], barano[100];
    cin >> asd >> barano;
    String text = asd;
    cout << text << endl;

    cout << text.findFirstSubStr(barano) << endl;
    cout << text.findLastSubStr(barano) << endl;

    int *norm = text.findAllSubStr(barano);
    n = sizeof(norm) / sizeof(int);
    for (int i = 0; i < n + 2; i++)
    {
        cout << norm[i] << endl;
    }

    int *rev = text.findAllSubStrReverse(barano);
    n = sizeof(rev) / sizeof(int);
    for (int i = 0; i < n + 2; i++)
    {
        cout << rev[i] << endl;
    }

    int *sum = text.rabinKarpSum(barano);
    n = sizeof(sum) / sizeof(int);
    for (int i = 0; i < n + 2; i++)
    {
        cout << sum[i] << endl;
    }

    return 0;
}