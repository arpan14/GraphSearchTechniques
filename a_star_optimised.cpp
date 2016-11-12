#include<bits/stdc++.h>
using namespace std;
int r,c;
struct Point
{
    int x;
    int y;
};
struct mat
{

    int a[9][9];
    int index;
    int parent_index;
    int f;
    int g;
    int h;
    Point pt[10];
    list < pair <int,int> > pairs[10];

    bool operator < (const mat& rhs) const {
        return f > rhs.f;
}
};

void setCoordinates(mat &obj)
{
    int i,j;
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
        {
            obj.pt[obj.a[i][j]].x=i;
            obj.pt[obj.a[i][j]].y=j;
        }
    }
}

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
bool compare(const mat& a,const mat& b)
{
    if(a.f==b.f)
        return a.g<a.g;
    return a.f<b.f;
}
*/
void calculateHeuristic(mat &st,mat goal)
{
    int i;
    int heuristic=0;
    for(i=1;i<r*c;i++)
    {
        heuristic+=abs(st.pt[i].x-goal.pt[i].x)+abs(st.pt[i].y-goal.pt[i].y);
        //cout<<heuristic<<endl;
    }
    st.h=heuristic;
    //cout<<"h "<<heuristic<<endl;
}

int check_prev_node(vector<mat> all_nodes,mat current)
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

int checkClosedSet(mat a,vector<mat> Set)
{   int i,j;
    vector<mat> ::iterator it;

    int flag=0;

    for(it=Set.begin();it!=Set.end();it++)
    {
        mat b=*it;
        flag=0;
        for(i=0;i<r;i++)
        {
            for(j=0;j<c;j++)
            {
                if(a.a[i][j]==b.a[i][j])
                    flag=1;
                else
                {
                    flag=0;
                    break;
                }
            }
            if(!flag)
                break;
        }
        if(flag)
        {   //cout<<"closed list exit"<<endl;
            return flag;

        }

    }
    //cout<<"closed list exit"<<endl;
    return flag;
}

int checkOpenSet(mat a,priority_queue<mat> Set)
{
    int i,j;

    priority_queue<mat> temp=Set;
    int flag=0;
    while(!temp.empty())
    {
        mat b=temp.top();
        temp.pop();
        flag=0;
        for(i=0;i<r;i++)
        {
            for(j=0;j<c;j++)
            {
                if(a.a[i][j]==b.a[i][j])
                    flag=1;
                else
                {
                    flag=0;
                    break;
                }
            }
            if(!flag)
                break;
        }
        if(flag)
        {
            return flag;
        }
    }
    return flag;
}



void push_open_list(vector<mat> &closed_set,priority_queue<mat> &open_set,mat &obj,mat goal_obj,int &nodes,vector<mat> &all_nodes,int parent_index,int parent_g,int choice)
{
    if(checkClosedSet(obj,closed_set) ||checkOpenSet(obj,open_set))
        return ;

    if(!all_nodes.size())
    {
        obj.parent_index=-1;
    }
    else
    {   obj.parent_index=parent_index;
        obj.g=parent_g+1;
    }
    obj.index=nodes;
    nodes++;

    setCoordinates(obj);
    calculateHeuristic(obj,goal_obj);
    if(choice==0)
        obj.f=obj.h;
    else
        obj.f=obj.g+obj.h;

    open_set.push(obj);
    //display(obj);
  //  cout<<"heuristic "<<obj.h<<endl;
   // cout<<"g value "<<obj.g<<endl;
    //cout<<"f value "<<obj.f<<endl;
    all_nodes.push_back(obj);
}

void swapleft(int bi,int bj,mat a,mat goal_obj,vector<mat> &closed_set,priority_queue<mat> &open_set,int &nodes,vector<mat> &all_nodes,int choice)
{   if(bj<=0)
        return ;
    swap(a.a[bi][bj],a.a[bi][bj-1]);
    push_open_list(closed_set,open_set,a,goal_obj,nodes,all_nodes,a.index,a.g,choice);
}

void swapright(int bi,int bj,mat a,mat goal_obj,vector<mat> &closed_set,priority_queue<mat> &open_set,int &nodes,vector<mat> &all_nodes,int choice)
{   if(bj>=c-1)
        return ;
    swap(a.a[bi][bj],a.a[bi][bj+1]);
    push_open_list(closed_set,open_set,a,goal_obj,nodes,all_nodes,a.index,a.g,choice);
}


void swapup(int bi,int bj,mat a,mat goal_obj,vector<mat> &closed_set,priority_queue<mat> &open_set,int &nodes,vector<mat> &all_nodes,int choice)
{   if(bi<=0)
        return ;
    swap(a.a[bi][bj],a.a[bi-1][bj]);
    push_open_list(closed_set,open_set,a,goal_obj,nodes,all_nodes,a.index,a.g,choice);
}

void swapdown(int bi,int bj,mat a,mat goal_obj,vector<mat> &closed_set,priority_queue<mat> &open_set,int &nodes,vector<mat> &all_nodes,int choice)
{   if(bi>=r-1)
        return ;
    swap(a.a[bi][bj],a.a[bi+1][bj]);
    push_open_list(closed_set,open_set,a,goal_obj,nodes,all_nodes,a.index,a.g,choice);
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

void displayResults(mat obj,int &nodes,int &iters,vector<mat>all_nodes)
{
    cout<<"Number of nodes enqueued="<<nodes<<endl;
    cout<<"Number of iterations="<<iters<<endl;

    stack<int> path_indexes ;

    mat goal=obj;
    while(goal.parent_index!=-1)
    {
        path_indexes.push(goal.index);
        goal=all_nodes.at(goal.parent_index);
    }
    path_indexes.push(goal.index);
    cout<<"length of the path: "<<path_indexes.size()<<endl;
    print_path(all_nodes,path_indexes);
    return ;
}
void astar(mat st,mat en,int choice)
{   cout<<"IN A-STAR"<<endl;

    vector<mat> all_nodes;
    priority_queue<mat> openset;
    vector<mat> openvector;
    vector<mat> closedset;
    int i,j,bi,bj;
    int nodes=0;
    int iters=0;
    st.parent_index=-1;
    push_open_list(closedset,openset,st,en,nodes,all_nodes,st.parent_index,0,choice);
    mat final_goal;
    int gf=0;
    while(!openset.empty())
    {
        mat obj=openset.top();
        //display(obj);
        //cout<<"f value: "<<obj.f<<endl;
        openset.pop();
        closedset.push_back(obj);
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
        {
            if(gf==1 && final_goal.f>obj.f)
            {
                final_goal=obj;
            }
            else if(gf==0)
            {
                gf=1;
                final_goal=obj;
            }

        }
        if(gf==1 && final_goal.f<=obj.f)
                break;
        calculateZeroIndex(bi,bj,obj);
        swapleft(bi,bj,obj,en,closedset,openset,nodes,all_nodes,choice);

        calculateZeroIndex(bi,bj,obj);
        swapright(bi,bj,obj,en,closedset,openset,nodes,all_nodes,choice);

        calculateZeroIndex(bi,bj,obj);
        swapup(bi,bj,obj,en,closedset,openset,nodes,all_nodes,choice);

        calculateZeroIndex(bi,bj,obj);
        swapdown(bi,bj,obj,en,closedset,openset,nodes,all_nodes,choice);


    }
    displayResults(final_goal,nodes,iters,all_nodes);
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
        setCoordinates(st);

        mat en;
        for(i=0;i<r;i++)
        {
            for(j=0;j<c;j++)
            {
                cin>>en.a[i][j];
            }
        }
        makePairs(en);
        setCoordinates(en);

        if(checkSolvable(st,en,bi,bj))
        {
            
            clock_t start = clock();
            //bestfirst(st,en,0);
            clock_t stop = clock();
            double elapsed = (double)(stop - start) * 1000.0 / (double)CLOCKS_PER_SEC;
            cout<<"Best First elapsed time:"<<elapsed<<endl;
            

            start = clock();
            astar(st,en,1);
            stop = clock();
            elapsed = (double)(stop - start) * 1000.0 / (double)CLOCKS_PER_SEC;
            cout<<"A STAR elapsed time:"<<elapsed<<endl;
        }
        else
        {
            cout<<"The state is not solvable"<<endl;
        }
    }
}
