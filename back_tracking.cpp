#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

vector<int> selected_nums;
vector<vector<int>> res;

void bt(int n, int k)
{
    if (k > n)
    {
        if (accumulate(selected_nums.begin(), selected_nums.end(), 0) == 10)
            res.push_back(selected_nums);
        return;
    }

    selected_nums.push_back(k);
    bt(n, k + 1);

    selected_nums.pop_back();
    bt(n, k + 1);
}

void sol(int n)
{
    if (n * (n + 1) / 2 < 10)
        cout << "[]\n";

    selected_nums.push_back(1);
    bt(n, 2);
    selected_nums.pop_back();
    bt(n, 2);

    for (auto v : res)
    {
        for (auto e : v)
            cout << e << " ";
        cout << '\n';
    }
}

int main()
{
    sol(5);
    // sol(2, 10);
    // sol(7, 10);

    return 0;
}
