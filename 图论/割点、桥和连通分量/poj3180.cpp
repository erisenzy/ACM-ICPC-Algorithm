#include <cstring>
#include <cstdio>

#define min(a,b) (a<b)?a:b;

using namespace std;

const int MaxN = 10005;
const int MaxE = 50005;

/*----------Tarjan Template Start----------*/

struct TEdge
{
    int u,v,next;
}Edge[MaxE];
int head[MaxN],index;

int dfn[MaxN];  //dfn[u]:遍历到u点的时间; 
int low[MaxN];  //low[u]:u或u的子树能够追溯到的最早的栈中节点的次序号
int grp[MaxN];  //grp[u]:u属于的连通分量的编号
int vis[MaxN];  //v是否在栈中
int ind[MaxN],oud[MaxN],inc,ouc; //点的入度和出度数

int stack[MaxN],top,scc,cnt;

void AddEdge(int u, int v)
{
    index++;
    Edge[index].u=u;
    Edge[index].v=v;
    Edge[index].next=head[u];
    head[u]=index;
}

void Tarjan(int u)
{
    int v,i;
    dfn[u]=low[u]=++cnt;//开始时dfn[u]==low[u]
    stack[top++]=u;     //当前点进栈
    vis[u]=1;
    for (i=head[u];i!=-1;i=Edge[i].next)
    {
        v=Edge[i].v;
        if (dfn[v]==0) //如果v点还未遍历
        {
            Tarjan(v); //向下遍历
            low[u]=min(low[u],low[v]) //确保low[u]最小
        }
        else if (vis[v] && low[u]>dfn[v]) low[u] = dfn[v];
        //v在栈中，修改low[u]          
    }
    if (dfn[u]==low[u])     //u为该强连通分量中遍历所成树的根
    {
        scc++;
        do
        {
            v=stack[--top]; //栈中所有到u的点都属于该强连通分量，退栈
            vis[v]=0;
            grp[v]=scc;
        } while (u!=v);
    }
}

void InitEdge()
{
    index=0;
    memset(head,-1,sizeof(head));
}

void CountDeg(int NodeNum)
{
    int i,u,v;
    memset(ind,0,sizeof(ind));
    memset(oud,0,sizeof(oud)); 
    for (u=1;u<=NodeNum;u++)
    {
    	for (i=head[u];i!=-1;i=Edge[i].next)
    	{
            v=Edge[i].v;
            if (grp[u]!=grp[v])
            {
                ind[grp[v]]++;
                oud[grp[u]]++;
            } 
    	}
    }
    inc=ouc=0;
    for (i=1;i<=scc;i++)
    {
        if (ind[i]==0) inc++;
        if (oud[i]==0) ouc++;
    }
}

void Solve(int NodeNum)
{
    int u;
    scc=top=cnt=0;
    memset(dfn,0,sizeof(dfn));
    memset(vis,0,sizeof(vis));
    for (u=1;u<=NodeNum;u++) if (dfn[u]==0) Tarjan(u);
    CountDeg(NodeNum);
}

/*----------Tarjan Template Over----------*/

int n,m,ans,num[MaxN]; 

int main()
{
    freopen("poj3180.txt","r",stdin);
    freopen("poj3180ans.txt","w",stdout);
    int i,u,v;
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        InitEdge();
        for (i=1;i<=m;i++)
        {
            scanf("%d%d",&u,&v);
            AddEdge(u,v);
        }
        Solve(n);
        memset(num,0,sizeof(num));
        ans=0;
        for (i=1;i<=n;i++) num[grp[i]]++;
        for (i=1;i<=scc;i++) if (num[i]>=2) ans++;
        printf("%d\n",ans);
    }
} 
