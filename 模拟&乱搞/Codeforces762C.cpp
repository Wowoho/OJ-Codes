#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+10;

int stck[N], top=0;
int la, lb;
char a[N], b[N];

int main()
{
    int i = 0;
    int ans=0, posL, posR;
    scanf("%s%s", a, b);
    stck[0] = -1;
    la = strlen(a);
    lb = strlen(b);
    posL = posR = -2;
    int L = 0;
    int R = la-1;
    while(L < la)
    {
        if(a[L] == b[i])
        {
            stck[++top] = L;
            i ++;
        }
        L ++;
    }

//    for(i=1; i<=top; i++)
//        printf("%d ", stck[i]);
//    puts("");

    ans = top;
    posL = top-1;
    i = lb-1;
    int cnt = 0;
    while(R >= 0)
    {
        if(a[R] == b[i])
        {
            cnt ++;
            i --;
        }
        while((R <= stck[top] || i<top) && top>0) ///×¢ÒâÏ¸½Ú£¡£¡£¡
            top --;
        R --;
        if(ans < top + cnt)
        {
            ans = top +cnt;
            posL = top-1;
            posR = cnt;
        }
        //printf("%d %d %d %d %d\n", i, R, cnt, top, ans);
    }
    if(ans == 0)
        puts("-");
    //printf("%d %d %d\n", ans, posL, posR);
    for(int j=0; j<=posL; j++)
        printf("%c", b[j]);
    //printf(" ");
    for(int j=lb-posR; j<lb; j++)
        printf("%c", b[j]);
//    for(i=1; i<=top; i++)
//        printf("%d ", stck[i]);

    return 0;
}
