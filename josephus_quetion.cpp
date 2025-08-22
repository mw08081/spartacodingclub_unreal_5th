#include <iostream>
#include <queue>

using namespace std;

int main()
{
    queue<int> q;
    int n, k, cnt = 0;
    cin >> n >> k;

    for (auto i = 1; i < n + 1; i++)
        q.push(i);

    while (q.size() != 1)
    {
        for (auto i = 0; i < k - 1; i++)
        {
            q.push(q.front());
            q.pop();
        }
        q.pop();
    }
    cout << q.front();

    return 0;
}