#include <iostream>
#include <vector>

using namespace std;

long long sum(const vector<int> &v)
{
    long long tot = 0;

    for (auto e : v)
        tot += e;

    return tot;
}

int main()
{
    vector<int> v{3, 6, 7, 9};
    cout << sum(v) << "\n"; // 25
}