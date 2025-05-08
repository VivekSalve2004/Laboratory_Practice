#include<bits/stdc++.h>
using namespace std;

vector<int> bfs(vector<vector<int>> &ans)
{
    vector<int> v;
    queue<int> q;
    vector<int> visited(ans.size() , 0);

    q.push(0);
    visited[0] = 1;

    while(!q.empty())
    {
      int front = q.front();
      q.pop();
      v.push_back(front);

      for(auto it : ans[front])
      {
          if(!visited[it])
          {
              visited[it] = 1;
              q.push(it);
          }
      }
    } 
    return v;
}

int main()
{
  cout<<"Hello World "<<endl;

  vector<vector<int>> ans(5);

  ans[0].push_back(1);
  ans[0].push_back(2);
  ans[1].push_back(3);
  ans[2].push_back(4);
  vector<int> k = bfs(ans);

  for(auto it : k)
  {
    cout<<it<<" ";
  }
  cout<<endl;

  return 0;
}
