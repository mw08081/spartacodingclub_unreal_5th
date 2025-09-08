#include <iostream>
using namespace std;

bool is_leap(int y)
{
    return ((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0));
}

int main()
{
    cout << boolalpha << is_leap(2000) << " " << is_leap(1900) << " " << is_leap(2024) << "\n"; // true false true
}