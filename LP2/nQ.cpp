#include <bits/stdc++.h>
using namespace std;
bool isPossible(int i, int column, int n, vector<string> &chessboard)
{
    int r = 0;
    r = i;
    int c = 0;
    c = column;
    while (r >= 0 && c >= 0)
    {
        if (chessboard[r][c] == 'Q')
        {
            return false;
        }
        r -= 1;
        c -= 1;
    }
    r = i;
    c = column;
    while (c >= 0)
    {
        if (chessboard[r][c] == 'Q')
        {
            return false;
        }
        c -= 1;
    }
    r = i;
    c = column;
    while (r < n && c >= 0)
    {
        if (chessboard[r][c] == 'Q')
        {
            return false;
        }
        r += 1;
        c -= 1;
    }
    return true;
}
void backTracking(int column, int n, vector<string> &chessboard, vector<vector<string>> &result)
{
    if (column == n)
    {
        result.push_back(chessboard);
        return;
    }
    for (int i = 0; i < n; i++)
    {
        if (isPossible(i, column, n, chessboard))
        {
            chessboard[i][column] = 'Q';
            backTracking(column + 1, n, chessboard, result);
            chessboard[i][column] = '.';
        }
    }
}
int main()
{
    int n = 0;
    cout << "\nEnter the number of queens :-> " << endl;
    cin >> n;
    vector<string> chessboard(n, string(n, '.'));
    vector<vector<string>> result;
    backTracking(0, n, chessboard, result);
    cout << "\nTotal possible chessboards are :-> " << result.size() << endl;
    for (int i = 0; i < result.size(); i++)
    {
        cout << "Chessboard " << i + 1 << endl;
        for (int j = 0; j < result[i].size(); j++)
        {
            for (int k = 0; k < result[i][j].size(); k++)
            {
                cout << result[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}