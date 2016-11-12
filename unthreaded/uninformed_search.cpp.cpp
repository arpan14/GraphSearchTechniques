#include<bits/stdc++.h>
using namespace std;
int r,c;
struct mat
{

    int a[9][9];
    int height;
    int index;
    int parent_index;
    list < pair <int,int> > pairs[10];
};
void display(mat &obj)
{
    int i,j;
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            cout<<obj.a[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}
/*
int check_visited(list<mat> visited,mat current,vector<mat> all_nodes)
{   if(visited.empty())
        return 0;
    list<mat> :: iterator it;
    int i,j;
    for(it=visited.begin();it!=visited.end();it++)
    {
        for(i=0;i<r;i++)
        {
            for(j=0;j<c;j++)
            {
                mat cur=*it;
                if(cur.a[i][j]!=current.a[i][j])
                    return 0;
            }
        }
    }
    if(current.parent_index==-1 || current.parent_index==0)
    {   return 0;
    }
    else
    {

        int prev_index=current.parent_index;
        int prev_prev_index=all_nodes.at(prev_index).parent_index;
        mat prev_node=all_nodes.at(prev_prev_index);
        int i,j;
        for(i=0;i<r;i++)
        {
            for(j=0;j<c;j++)
            {
                if(current.a[i][j]!=prev_node.a[i][j])
                    return 0;
            }
        }
    }
    return 1;
}
*/

int check_visited(list<mat> visited,mat current,vector<mat> all_nodes)
{
    if(current.parent_index==-1 || current.parent_index==0)
    {   return 0;
    }
    else
    {

        int prev_index=current.parent_index;
        int prev_prev_index=all_nodes.at(prev_index).parent_index;
        mat prev_node=all_nodes.at(prev_prev_index);
        int i,j;
        for(i=0;i<r;i++)
        {
            for(j=0;j<c;j++)
            {
                if(current.a[i][j]!=prev_node.a[i][j])
                    return 0;
            }
        }
        return 1;
    }
}

void push_queue(list<mat> &q,mat &obj,list<mat> &visited,int &nodes,vector<mat> &all_nodes,int parent_index,int choice)
{
    if(!all_nodes.size())
    {
        obj.parent_index=-1;
        all_nodes.push_back(obj);
    }
    else
    {
        obj.parent_index=parent_index;
        obj.index=nodes;
        nodes++;
        all_nodes.push_back(obj);
    }
    if(!choice)
    {
        q.push_back(obj);
    }
    else
    {
        if(!check_visited(visited,obj,all_nodes))
        {
            q.push_back(obj);
            visited.push_back(obj);
        }
    }
}

void swapleft(int bi,int bj,mat a,list<mat> &q,int &nodes,list<mat> &visited,vector<mat> &all_nodes,int choice)
{   if(bj<=0)
        return ;
    swap(a.a[bi][bj],a.a[bi][bj-1]);
    push_queue(q,a,visited,nodes,all_nodes,a.index,choice);
}

void swapright(int bi,int bj,mat a,list<mat> &q,int &nodes,list<mat> &visited,vector<mat> &all_nodes,int choice)
{   if(bj>=c-1)
        return ;
    swap(a.a[bi][bj],a.a[bi][bj+1]);
    push_queue(q,a,visited,nodes,all_nodes,a.index,choice);
}


void swapup(int bi,int bj,mat a,list<mat> &q,int &nodes,list<mat> &visited,vector<mat> &all_nodes,int choice)
{   if(bi<=0)
        return ;
    swap(a.a[bi][bj],a.a[bi-1][bj]);
    push_queue(q,a,visited,nodes,all_nodes,a.index,choice);
}

void swapdown(int bi,int bj,mat a,list<mat> &q,int &nodes,list<mat> &visited,vector<mat> &all_nodes,int choice)
{   if(bi>=r-1)
        return ;
    swap(a.a[bi][bj],a.a[bi+1][bj]);
    push_queue(q,a,visited,nodes,all_nodes,a.index,choice);
}

int check(mat a,mat b)
{
    int flag=1;
    int i,j;
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            if(a.a[i][j]!=b.a[i][j])
            {
                flag=0;
                break;
            }
        }
        if(flag==0)
            break;
    }
    return flag;
}
void calculateZeroIndex(int &bi,int &bj,mat obj)
{
    int i,j,fl=1;
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            if(obj.a[i][j]==0)
            {
                bi=i;
                bj=j;
                fl=0;
            }
        }
        if(fl==0)
            break;
    }
}
void print_path(vector<mat> all_nodes,stack<int>path_indexes)
{
    while(!path_indexes.empty())
    {
        int index=path_indexes.top();
        path_indexes.pop();
        display(all_nodes.at(index));
    }
}
void dfs(mat st,mat en,int choice)
{   list<mat> q;
    list<mat> visited;
    vector<mat> all_nodes;
    int i,j,bi,bj;
    int nodes=0;
    int iters=0;
    st.index=nodes;
    nodes++;
    push_queue(q,st,visited,nodes,all_nodes,st.index,choice);
    while(!q.empty())
    {   mat obj=q.back();
        int fl=1;
        for(i=0;i<r;i++)
        {
            for(j=0;j<c;j++)
            {
                if(obj.a[i][j]==0)
                {
                    bi=i;
                    bj=j;
                    fl=0;
                }
            }
            if(fl==0)
                break;
        }
        iters++;
        if(check(obj,en))
        {   cout<<"Number of nodes enqueued="<<nodes<<endl;
            cout<<"Number of iterations="<<iters<<endl;
            stack<int> path_indexes ;
            mat goal=obj;
            while(goal.parent_index!=-1)
            {
                path_indexes.push(goal.index);
                goal=all_nodes.at(goal.parent_index);
            }
            path_indexes.push(goal.index);
            print_path(all_nodes,path_indexes);
            return ;
        }
        q.pop_back();

        calculateZeroIndex(bi,bj,obj);
        swapup(bi,bj,obj,q,nodes,visited,all_nodes,choice);

        calculateZeroIndex(bi,bj,obj);
        swapleft(bi,bj,obj,q,nodes,visited,all_nodes,choice);

        calculateZeroIndex(bi,bj,obj);
        swapright(bi,bj,obj,q,nodes,visited,all_nodes,choice);

        calculateZeroIndex(bi,bj,obj);
        swapdown(bi,bj,obj,q,nodes,visited,all_nodes,choice);
    }
}

void modified_bfs(mat st,mat en,int choice)
{   list<mat> q;
    int i,j,bi,bj;
    int nodes=0;
    int iters=0;
    list<mat> visited;
    vector<mat> all_nodes;
    st.index=nodes;
    nodes++;
    push_queue(q,st,visited,nodes,all_nodes,st.index,choice);
    while(!q.empty())
    {   mat obj=q.front();
        int fl=1;
        for(i=0;i<r;i++)
        {
            for(j=0;j<c;j++)
            {
                if(obj.a[i][j]==0)
                {
                    bi=i;
                    bj=j;
                    fl=0;
                }
            }
            if(fl==0)
                break;
        }
        iters++;
        if(check(obj,en))
        {   cout<<"Number of nodes enqueued="<<nodes<<endl;
            cout<<"Number of iterations="<<iters<<endl;
            stack<int> path_indexes ;
            mat goal=obj;
            while(goal.parent_index!=-1)
            {   path_indexes.push(goal.index);
                goal=all_nodes.at(goal.parent_index);
            }
            path_indexes.push(goal.index);
            print_path(all_nodes,path_indexes);
            return;
        }
        q.pop_front();

        calculateZeroIndex(bi,bj,obj);
        swapleft(bi,bj,obj,q,nodes,visited,all_nodes,choice);

        calculateZeroIndex(bi,bj,obj);
        swapright(bi,bj,obj,q,nodes,visited,all_nodes,choice);

        calculateZeroIndex(bi,bj,obj);
        swapup(bi,bj,obj,q,nodes,visited,all_nodes,choice);

        calculateZeroIndex(bi,bj,obj);
        swapdown(bi,bj,obj,q,nodes,visited,all_nodes,choice);
    }
}

void bfs(mat st,mat en,int choice)
{   list<mat> q;
    int i,j,bi,bj;
    int nodes=0;
    int iters=0;
    list<mat> visited;
    vector<mat> all_nodes;
    st.index=nodes;
    nodes++;
    push_queue(q,st,visited,nodes,all_nodes,st.index,choice);
    while(!q.empty())
    {   mat obj=q.front();
        int fl=1;
        iters++;
        if(check(obj,en))
        {   cout<<"Number of nodes enqueued="<<nodes<<endl;
            cout<<"Number of iterations="<<iters<<endl;
            stack<int> path_indexes ;
            mat goal=obj;
            while(goal.parent_index!=-1)
            {   path_indexes.push(goal.index);
                goal=all_nodes.at(goal.parent_index);
            }
            path_indexes.push(goal.index);
            print_path(all_nodes,path_indexes);
            return ;
        }

        q.pop_front();

        calculateZeroIndex(bi,bj,obj);
        swapleft(bi,bj,obj,q,nodes,visited,all_nodes,choice);

        calculateZeroIndex(bi,bj,obj);
        swapright(bi,bj,obj,q,nodes,visited,all_nodes,choice);

        calculateZeroIndex(bi,bj,obj);
        swapup(bi,bj,obj,q,nodes,visited,all_nodes,choice);

        calculateZeroIndex(bi,bj,obj);
        swapdown(bi,bj,obj,q,nodes,visited,all_nodes,choice);
    }
}

int checkSolvable(mat a,mat b,int bi,int bj)
{
    //for each pair in start state, check if the inverse is present in the goal state. Return the total count of the inverses.
    int i,j;
    int inverse=0;
    for(i=1;i<=r*c;i++)
    {
        list<pair<int,int> > :: iterator it;
        for(it=a.pairs[i].begin();it!=a.pairs[i].end();it++)
        {
            int x1,y1;
            x1=it->first;
            y1=it->second;
            list<pair<int,int> > :: iterator jt;
            for(jt=b.pairs[y1].begin();jt!=b.pairs[y1].end();jt++)
            {
                int x2,y2;
                x2=jt->first;
                y2=jt->second;
                if(x1==y2 && y1==x2)
                {
                    //indicates presence of an inverse
                    inverse++;
                }
            }
        }
    }

    cout<<"Inverse: "<<inverse<<endl;
    /*
    If the grid width is odd, then the number of inversions in a solvable situation is even.
    If the grid width is even, and the blank is on an even row counting from the bottom (second-last, fourth-last etc), then the number of inversions in a solvable situation is odd.
    If the grid width is even, and the blank is on an odd row counting from the bottom (last, third-last, fifth-last etc) then the number of inversions in a solvable situation is even.
    */
    //change indexes from 0 indexed to 1 indexed
    bi++;
    bj++;
    bool solvable=false;
    int index=r-bi+1;

    if((r%2!=0 && inverse%2==0)|| ((r%2==0 && ((index%2!=0)==(inverse%2==0)))))
    {
       solvable=true;
    }
    return solvable;
}
void makePairs(mat & st)
{   //covert 2d array to 1d array
    int in=0;
    int arr[r*c];
    int i,j;

    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            arr[in++]=st.a[i][j];
        }
    }

    //push pairs to the list of each struct object
    for(i=0;i<r*c-1;i++)
    {
        for(j=i+1;j<r*c;j++)
        {
            if(arr[i]!=0 && arr[j]!=0)
            {
                st.pairs[arr[i]].push_back(make_pair(arr[i],arr[j]));
            }
        }
    }
}

void printPairs(mat obj)
{

    list<pair<int,int> > :: iterator it;
    int i;
    for(i=0;i<=r*c;i++)
    {
        for(it=obj.pairs[i].begin();it!=obj.pairs[i].end();it++)
        {
            cout<<it->first<<" "<<it->second<<endl;
        }
    }
}
int main()
{   freopen("input.txt","r",stdin);
    int testcases;
    cin>>testcases;
    while(testcases--)
    {
        cin>>r>>c;
        int i,j,bi,bj;
        mat st;
        for(i=0;i<r;i++)
        {
            for(j=0;j<c;j++)
            {
                cin>>st.a[i][j];
                if(st.a[i][j]==0)
                {
                    bi=i;
                    bj=j;
                }
            }
        }
        makePairs(st);
        mat en;
        for(i=0;i<r;i++)
        {
            for(j=0;j<c;j++)
            {
                cin>>en.a[i][j];
            }
        }
        makePairs(en);
        if(checkSolvable(st,en,bi,bj))
        {
            clock_t start = clock();
            bfs(st,en,0);
            clock_t stop = clock();
            double elapsed = (double)(stop - start) * 1000.0 / (double)CLOCKS_PER_SEC;
            cout<<"BFS elapsed time:"<<elapsed<<endl;

            start = clock();
            modified_bfs(st,en,1);
            stop = clock();
            elapsed = (double)(stop - start) * 1000.0 / (double)CLOCKS_PER_SEC;
            cout<<"Modified BFS elapsed time:"<<elapsed<<endl;

            /*
            start = clock();
            dfs(st,en,2);
            stop = clock();
            elapsed = (double)(stop - start) * 1000.0 / (double)CLOCKS_PER_SEC;
            cout<<"DFS elapsed time:"<<elapsed<<endl;
            */
        }
        else
        {
            cout<<"The state is not solvable"<<endl;
        }
    }
}
