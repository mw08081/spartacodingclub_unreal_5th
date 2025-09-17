#include <iostream>
#include <queue>

using namespace std;

int main()
{
    vector<pair<int, int>> param1 = {{1, 2}, {1, 3}, {2, 4}, {2, 5}, {3, 6}, {3, 7}, {4, 8}, {5, 8}, {6, 9}, {7, 9}};
    int param2 = 1;

    // 최고 노드 인덱스 추출
    int max = 0;
    for (auto e : param1)
    {
        if (e.first > max)
            max = e.first;
        if (e.second > max)
            max = e.second;
    }

    // 인접리스트 및 bfs 준비
    vector<int> g[max + 1];
    vector<bool> visited(max + 1, false);
    queue<int> bfs;
    vector<int> answer;

    // 인접리스트로 변환
    for (auto e : param1)
    {
        g[e.first].push_back(e.second);
    }

    bfs.push(param2);
    visited[param2] = true;
    while (!bfs.empty())
    {
        for (auto e : g[bfs.front()])
        {
            if (visited[e] == false)
            {
                bfs.push(e);
                visited[e] = true;
            }
        }

        answer.push_back(bfs.front());
        bfs.pop();
    }

    for (auto e : answer)
        cout << e << " ";
    cout << '\n';

    return 0;
}