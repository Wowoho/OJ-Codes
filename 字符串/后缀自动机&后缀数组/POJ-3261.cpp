#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=20010;
int wa[MAXN],wb[MAXN],wv[MAXN],Ws[MAXN*100];
int cmp(int *r,int a,int b,int l)
{
    return r[a]==r[b]&&r[a+l]==r[b+l];
}
/**< 传入参数：str,sa,len+1,ASCII_MAX+1 */
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
//求height数组
/**< str,sa,len */
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
    int cnt=1, sum = -1;
    for(int i=1; i<=len+1; i++)
    {
        if(height[i]<x)
        {
            sum = max(sum, cnt);
            cnt = 1;
            //printf("%d %d\n", sum, i);
        }
        else if(height[i]>=x)
            cnt ++;
    }
    //puts("");
    return sum >= k;
}

void print(int len);

int str[MAXN], tmp[MAXN];
int main()
{
    int len, k, max_x;
    while(~scanf("%d%d", &len, &k))
    {
        memset(height, 0, sizeof height);
        max_x = 0;
        for(int i=0; i<len; i++)
        {
            scanf("%d", &str[i]);
            tmp[i] = str[i];

        }
        sort(tmp, tmp+len);
        for(int i=0; i<len; i++)
        {
            str[i] = lower_bound(tmp, tmp+len, str[i]) - tmp + 1;
            //printf("%d ", str[i]);///
        }
        //puts("");

        da(str, sa, len+1, len+1);
        calheight(str, sa, len);

        int L=0, R=len, mid;
        while(L < R)
        {
            mid = (L+R)/2;
            if(check(mid, len, k))
                L = mid+1;
            else
                R = mid;

            //printf("%d %d\n", L, R);
        }
        printf("%d\n", L-1);

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
            printf("%d",str[j]);
        puts("");
    }
    puts("");
    puts("-------------After sort---------------");
    for(int i=1; i<=len; ++i)
    {
        printf("sa[%2d ] = %2d\t",i,sa[i]);
        for(int j=sa[i]-1; j<len; ++j)
            printf("%d",str[j]);
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
    puts("------------------END-----------------");
}
