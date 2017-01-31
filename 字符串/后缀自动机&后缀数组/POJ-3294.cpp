#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1000100;

int wa[MAXN],wb[MAXN],wv[MAXN],Ws[MAXN];
int str[MAXN], belong[MAXN];
char tmp[MAXN];

int cmp(int *r,int a,int b,int l)
{
    return r[a]==r[b]&&r[a+l]==r[b+l];
}
///**< 传入参数：str,sa,len+1,ASCII_MAX+1 */
void da(const int *r,int *sa,int n,int m)
{
    int i,j,p,*x=wa,*y=wb,*t;
    for(i=0; i<m; i++) Ws[i]=0;
    for(i=0; i<n; i++) Ws[x[i]=r[i]]++;
    for(i=1; i<m; i++) Ws[i]+=Ws[i-1];
    for(i=n-1; i>=0; i--) sa[--Ws[x[i]]]=i;
    for(j=1,p=1; p<n; j*=2,m=p)
    {
        for(p=0,i=n-j; i<n; i++) y[p++]=i;
        for(i=0; i<n; i++) if(sa[i]>=j) y[p++]=sa[i]-j;
        for(i=0; i<n; i++) wv[i]=x[y[i]];
        for(i=0; i<m; i++) Ws[i]=0;
        for(i=0; i<n; i++) Ws[wv[i]]++;
        for(i=1; i<m; i++) Ws[i]+=Ws[i-1];
        for(i=n-1; i>=0; i--) sa[--Ws[wv[i]]]=y[i];
        for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1; i<n; i++)
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
    return;
}
int sa[MAXN],Rank[MAXN],height[MAXN];
///*< str,sa,len */
void calheight(const int *r,int *sa,int n)
{
    int i,j,k=0;
    for(i=1; i<=n; i++) Rank[sa[i]]=i;
    for(i=0; i<n; height[Rank[i++]]=k)
        for(k?k--:0,j=sa[Rank[i]-1]; r[i+k]==r[j+k]; k++);
    // Unified
    for(int i=n; i>=1; --i) ++sa[i],Rank[i]=Rank[i-1];
}

bool check(int x, int len, int k)
{
    int mark[105], cnt=0, tot=-1;
    memset(mark, 0, sizeof mark);
    for(int i=1; i<=len; i++)
    {
        if(height[i] < x)
        {
            cnt = 0;
            memset(mark, 0, sizeof mark);
            mark[belong[sa[i]]] = 1;
        }
        else
        {
            if(mark[belong[sa[i]]] == 0)
            cnt ++;
            mark[belong[sa[i]]] = 1;
        }
        tot = max(tot, cnt);

//        for(int j=1; j<=3; j++)
//            printf("%d ", mark[j]);
//        printf("##%d %d %d\n", x, cnt, i);
    }
    return tot >= k-1;
}

void Find_Pos(int x, int len, int k)
{
    int mark[105], cnt=0, tot=-1;
    memset(mark, 0, sizeof mark);
    for(int i=1; i<=len; i++)
    {
        if(height[i] < x)
        {
            if(cnt >= k-1)
            {
                for(int j=sa[i-1]-1; j<sa[i-1]+x-1; j++)
                    printf("%c", str[j]+'a');
                puts("");
            }

            cnt = 0;
            memset(mark, 0, sizeof mark);
            mark[belong[sa[i]]] = 1;
        }
        else
        {
            if(mark[belong[sa[i]]] == 0)
            cnt ++;
            mark[belong[sa[i]]] = 1;
        }
    }
}

void print(int len);

int main()
{
    int len, k, n, l;
    while(~scanf("%d", &n) && n)
    {
        memset(height, 0, sizeof height);
        len = 0;
        for(int i=1; i<=n; i++)
        {
            scanf("%s", tmp);
            l = strlen(tmp);
            for(int j=0; j<l; j++)
            {
                str[len++] = tmp[j]-'a';
                belong[len] = i;
            }
            str[len++] = 100+i;
            belong[len] = 0;
        }

        //for(int i=0; i<len; i++) printf("%d ", str[i]); puts("");

        da(str, sa, len+1, 101+n);
        calheight(str, sa, len);

        int L=0, R=len, mid;
        while(L < R)
        {
            mid = (L+R)/2;
            if(check(mid, len, n/2+1))
                L = mid+1;
            else
                R = mid;
        }
        //printf("%d\n", L-1);
        if(L == 1)
            puts("?");
        else
            Find_Pos(L-1, len, n/2+1);

        puts("");
        //print(len);
    }
    return 0;
}

///*=======================*///
void print(int len)
{
    puts("--------------All Suffix--------------");
    for(int i=1; i<=len; ++i)
    {
        printf("%d:\t",i);
        for(int j=i-1; j<len; ++j)
            printf("%d ",str[j]);
        puts("");
    }
    puts("");
    puts("-------------After sort---------------");
    for(int i=1; i<=len; ++i)
    {
        printf("sa[%2d ] = %2d\t",i,sa[i]);
        for(int j=sa[i]-1; j<len; ++j)
            printf("%d ",str[j]);
        puts("");
    }
    puts("");
    puts("---------------Height-----------------");
    for(int i=1; i<=len; ++i)
        printf("height[%2d ]=%2d \n",i,height[i]);
    puts("");
    puts("----------------Rank------------------");
    for(int i=1; i<=len; ++i)
        printf("Rank[%2d ] = %2d\n",i,Rank[i]);
    puts("---------------Belong-----------------");
    for(int i=1; i<=len; ++i)
        printf("belong[%2d ] = %2d\n",i,belong[i]);
    puts("------------------END-----------------");
}
