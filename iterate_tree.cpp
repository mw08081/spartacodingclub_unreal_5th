#include <iostream>
#include <vector>

using namespace std;

void pre_order(vector<int> v, int idx)
{
    if (idx >= v.size())
        return;

    cout << v[idx] << " ";
    pre_order(v, idx * 2 + 1);
    pre_order(v, idx * 2 + 2);
}

void in_order(vector<int> v, int idx)
{
    if (idx >= v.size())
        return;

    in_order(v, idx * 2 + 1);
    cout << v[idx] << " ";
    in_order(v, idx * 2 + 2);
}

void post_order(vector<int> v, int idx)
{
    if (idx >= v.size())
        return;

    post_order(v, idx * 2 + 1);
    post_order(v, idx * 2 + 2);
    cout << v[idx] << " ";
}

int main()
{
    vector<int> v = {1, 2, 3, 4, 5, 6, 7};
    pre_order(v, 0);
    cout << '\n';

    in_order(v, 0);
    cout << '\n';

    post_order(v, 0);
    cout << '\n';

    return 0;
}