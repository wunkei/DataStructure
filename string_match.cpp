#include <iostream>
#include <cstring>
using namespace std;

int SimpleMatch(const char* S, const char* P)
{
    int n = strlen(S);
    int m = strlen(P);

    for (int i = 0; i <= n - m; i++)
    {
        int j = 0;
        while (j < m && S[i + j] == P[j])
            j++;

        if (j == m)
            return i;  // 找到了
    }

    return -1;  // 未找到
}

int main()
{
    const char* S = "hello world";
    const char* P = "world";

    cout << "匹配位置: " << SimpleMatch(S, P) << endl;
    return 0;
}
