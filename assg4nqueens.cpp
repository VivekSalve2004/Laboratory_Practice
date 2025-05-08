#include<bits/stdc++.h>
using namespace std;

class Nqueens{
    public:
    int n, cnt;
    vector<vector<bool>> arr;
    vector<bool> row;
    vector<bool> col;
    vector<bool> diga;
    vector<bool> digb;

    Nqueens(int n = 4){
        this->n = n;
        cnt = 0;
        arr.resize(n, vector<bool>(n, false));
        row.resize(n, false);
        col.resize(n, false);
        diga.resize(n+n-1, false);
        digb.resize(n+n-1, false);
    }

    void display(){
        for(int i = 0;i<n;i++){
            for(int j = 0;j<n;j++){
                (arr[i][j])? cout<<'Q' : cout<<'.';
                cout<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }

    bool isSafe(int i, int j)
    {
        if(row[i]) return false;
        else if(col[j]) return false;
        else if(diga[i-j+n-1]) return false;
        else if(digb[i+j]) return false;
        else return true;
    }

    void getSoln(int i){
        if(i >= n){
            display();
            cnt++;
            return;
        }
    
        for(int j = 0; j < n; j++){
            if(!isSafe(i, j)) continue;
    
            arr[i][j] = true;
            row[i] = true;
            col[j] = true;
            diga[i - j + n - 1] = true;
            digb[i + j] = true;
    
            getSoln(i + 1);
    
            arr[i][j] = false;
            row[i] = false;
            col[j] = false;
            diga[i - j + n - 1] = false;
            digb[i + j] = false;
        }
    }  
};

int main(){
    int n = 5;
    Nqueens obj(n);
    obj.getSoln(0);
    cout<<obj.cnt<<endl;
    return 0;
}