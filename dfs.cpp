#include<bits/stdc++.h>
using namespace std;

void dfs(vector<vector<int>> &ans,vector<int> &v,vector<int> &visited,int front)
{
    visited[front] = 1;
    v.push_back(front);

    for(auto it : ans[front])
    {
        if(!visited[it])
        {
            dfs(ans,v,visited,it);
        }
    }
}

int main()
{
  cout<<"Hello World "<<endl;

  vector<vector<int>> ans(5);

  ans[0].push_back(1);
  ans[0].push_back(2);
  ans[1].push_back(3);
  ans[2].push_back(4);

  vector<int> v;
  vector<int> visited(ans.size() , 0);
  dfs(ans,v,visited,0);

  for(auto it : v)
  {
    cout<<it<<" ";
  }
  cout<<endl;

  return 0;
}
