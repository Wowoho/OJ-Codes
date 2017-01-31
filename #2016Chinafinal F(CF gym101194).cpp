#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=1000100;

int wa[MAXN],wb[MAXN],wv[MAXN],Ws[MAXN];
int str[MAXN];
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

int ok(int x, int len, int k)
{
    int ans_1, ans_2, ans;
    ans_1 = ans_2 = ans = len+1;
    for(int i=1; i<=k-x+1; i++)
        if(height[Rank[i]] < x && height[Rank[i]+1] < x)
        {
            ans_1 = Rank[i];
            break;
        }
    int flag = 0, state, ths = 0;
    for(int i=1; i<=len; i++)
    {
        while(height[i] < x && i<=len)
            i ++;

        flag = (sa[i-1] <= k);
        while(height[i] >= x && i<=len)
        {
            flag = ((sa[i] <= k) & flag);
            i ++;
        }
        if(flag)
        {
            ans_2 = i-1;
            break;
        }
    }
    if(ans_1 == len+1 && ans_2 == len+1)
        return 0;
    else
        return min(ans_1, ans_2);
}

void print(int len);

int main()
{
    int T;
    int len, k, n, l;
    scanf("%d", &T);
    for(int cas=1; cas<=T; cas++)
    {
        scanf("%d", &n);
        memset(height, 0, sizeof height);
        len = 0;
        for(int i=1; i<=n; i++)
        {
            scanf("%s", tmp);
            l = strlen(tmp);
            if(i==1)
                k = l;
            for(int j=0; j<l; j++)
                str[len++] = tmp[j]-'a';
            str[len++] = 250000+i;
        }

        da(str, sa, len+1, 250001+n);
        calheight(str, sa, len);
        height[1] = 0;

        int L=0, R=k+1, mid, pos;
        while(L < R)
        {
            mid = (L+R)/2;
            if(ok(mid, len, k) == 0)
                L = mid+1;
            else
                R = mid;
        }
        pos = sa[ok(L, len, k)];
        printf("Case #%d: ", cas);
        if(L == k+1)
            puts("Impossible");
        else
        {
            pos = sa[ok(L, len, k)];
            for(int i=pos-1; i<pos+L-1; i++)
                printf("%c", str[i]+'a');
            puts("");
        }
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
//    puts("---------------Belong-----------------");
//    for(int i=1; i<=len; ++i)
//        printf("belong[%2d ] = %2d\n",i,belong[i]);
    puts("------------------END-----------------");
}

