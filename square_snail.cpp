#include <iostream>

using namespace std;

int main()
{
    int arr[9][9] = {0};
    int n, c = 0, i = 0, j = 0, v = 1;
    cout << "n: ";
    cin >> n;

    while (v < n * n + 1)
    {
        while (j != n - 1 - c && v < n * n + 1)
            arr[i][j++] = v++;
        while (i != n - 1 - c && v < n * n + 1)
            arr[i++][j] = v++;
        while (j != c && v < n * n + 1)
            arr[i][j--] = v++;
        while (i != 1 + c && v < n * n + 1)
            arr[i--][j] = v++;

        c++;
    }

    for (auto x = 0; x < n; x++)
    {
        for (auto y = 0; y < n; y++)
            cout << arr[x][y] << " ";
        cout << '\n';
    }
}