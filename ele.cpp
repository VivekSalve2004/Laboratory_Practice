#include<bits/stdc++.h>
using namespace std;

class Process
{
    public:
    int id;
    string pname;

    Process()
    {
        id = 0;
        pname = "";
    }
    friend class Election;
};

class Election
{
    int num;
    Process *p;
    int *flag;

    int highest(Process p[])
    {
        int pos = 0,max = 0;
        for(int i=0;i<num;i++)
        {
            if(p[i].id > max)
            {
                max = p[i].id;
                pos = i;
            }
        }
        return pos;
    }

    int find_pos(int id)
    {
        for(int i=0;i<num;i++)
        {
            if(p[i].id == id)
            {
                return i;
            }
        }
        return 0;
    }

    public:
    void input()
    {
        cout<<"Enter no of processes "<<endl;
        cin>>num;

        p = new Process[num];
        flag = new int[num];

        for(int i=0;i<num;i++)
        {
            cout<<"Enter name of process "<<endl;
            cin>>p[i].pname;
            cout<<"Enter id of process "<<endl;
            cin>>p[i].id;
        }
        int pos = highest(p);
        cout<<"Process named "<<p[pos].pname<<" has crased : ID "<<p[pos].id<<endl;
    }

    Process bully(Process coordinator)
    {
        for(int i=0;i<num;i++)
        {
            flag[i] = 0;
        }
        int crash = highest(p);
        flag[crash] = 1;

        for(int i=0;i<num;i++)
        {
            if(p[i].id > coordinator.id)
            {
                cout<<"Election message sent from current coordinator "<<coordinator.id<<" to process "<<p[i].id<<endl;
            }
            else
            {
                flag[i] = 1;
            }
        }

        for(int i=0;i<num;i++)
        {
            if(flag[i] != 1 && p[i].id > coordinator.id)
            {
                cout<<"Process "<<p[i].id<<" has taken over from coordinator "<<coordinator.id<<endl;
                flag[coordinator.id] = 1;
                coordinator = p[i];
            }
        }

        for(int i=0;i<num;i++)
        {
            if(flag[i] == 0)
            {
                coordinator = bully(coordinator);
            }
        }

        return coordinator;
    }

    void ring(Process coordinator)
    {
        vector<int>vec;
        int crash = highest(p);
        int pos = find_pos(crash);
        int count = 0,i=pos;
        while(count < num)
        {
            if(i != crash)
            {
                vec.push_back(coordinator.id);
                i = (i+1) % num;
            }
            count++;
        }
        vector<int>::iterator it;

        cout<<"Message is [";
        for(int i=0;i<count;i++) {
            cout<<vec[i]<<" ";
        }
        cout<<"]"<<endl;
        int coord_id = *max_element(vec.begin(), vec.end());
        int final_coord_pos = find_pos(coord_id);
        cout<<"Final coordinator is: "<<p[final_coord_pos].pname<<endl;
    }
};

int main()
{
    Election e;
    Process i_coord;
    Process f_coord;

    cout<<"Enter name of process that detected coordinator crash"<<endl;
    cin>>i_coord.pname;
    cout<<"Enter id of process that detected coordinator crash"<<endl;
    cin>>i_coord.id;

    f_coord = e.bully(i_coord);
    e.ring(i_coord);

    return 0;
}