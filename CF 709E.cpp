/**
Codeforces 709 E
#Tree DP
#Accept
sz[x]: ��xΪ����������С
submax[x]: ��xΪ����������������е��Ĵ�С
max1[x]: ��xΪ���������ϳߴ�����
max2[x]: ���������δ��
**/

#include<bits/stdc++.h>
using namespace std;
const int N = 4e5+10;

vector<int> G[N];
int n, sz[N], ans[N], submax[N], max1[N], max2[N];

void Dfs_1(int now, int fa)
{
    sz[now] = 1;
    submax[now] = 0;
    for(auto x : G[now])
    {
        if(x == fa) continue;

        Dfs_1(x, now);
        sz[now] += sz[x];

        if(submax[x] > submax[now])
        {
            max2[now] = max1[now];
            max1[now] = x;
            submax[now] = submax[x];
        }
        else if(submax[x] > submax[max2[now]])
            max2[now] = x;
    }
    if(sz[now] <= n/2)
        submax[now] = sz[now];
}

void Dfs_2(int now, int fa, int maxx) ///maxx: ���������е������ֵ
{
    int flag = 1;
    for(auto x : G[now])
    {
        if(x == fa)  /// �Ӹ��ڵ�ת�ƹ���
        {
            int tmp = n-sz[now];
            if(tmp>n/2 && tmp-maxx>n/2)
                flag = 0;
            continue;
        }
        if(sz[x]>n/2 && sz[x]-submax[x]>n/2)
            flag = 0;
    }
    ans[now] = flag;

    for(auto x : G[now])  ///���ӽڵ�ת�ƹ���
    {
        if(x == fa) continue;

        int tmp;
        if(n-sz[x] <= n/2)
            tmp = n-sz[x];
        else
        {
            if(max1[now] == x)
                tmp = max(maxx, submax[max2[now]]);
            else
                tmp = max(maxx, submax[max1[now]]);
        }
        Dfs_2(x, now, tmp);
    }

}

int main()
{
    scanf("%d", &n);
    for(int i=1; i<n; i++)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    Dfs_1(1, 0);
    Dfs_2(1, 0, 0);

    for(int i=1; i<=n; i++)
        printf("%d ", ans[i]);

    return 0;
}
