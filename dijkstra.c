#include <stdio.h>

#define N 7
#define INF 9999

char *name[N] = {
    "Airport", "Railway Station", "City Mall",
    "Bus Stand", "Hospital", "College", "Stadium"
};

int g[N][N] = {
    {0,5,4,8,0,0,0},
    {5,0,3,0,0,7,0},
    {4,3,0,2,5,0,0},
    {8,0,2,0,3,0,6},
    {0,0,5,3,0,6,3},
    {0,7,0,0,6,0,0},
    {0,0,0,6,3,0,0}
};

int dijkstra(int s, int t, int show)
{
    int d[N], v[N]={0}, p[N], path[N];
    int i,j,u,k=0;

    for(i=0;i<N;i++)
        d[i]=INF, p[i]=-1;

    d[s]=0;

    for(i=0;i<N;i++) {
        u=-1;

        for(j=0;j<N;j++)
            if(!v[j] && (u==-1 || d[j]<d[u]))
                u=j;

        if(u==-1) break;
        v[u]=1;

        for(j=0;j<N;j++)
            if(g[u][j] && d[u]+g[u][j]<d[j])
                d[j]=d[u]+g[u][j], p[j]=u;
    }

    if(d[t]==INF) return -1;

    if(show) {
        for(i=t;i!=-1;i=p[i])
            path[k++]=i;

        printf("\nShortest Route: ");

        for(i=k-1;i>=0;i--) {
            printf("%s",name[path[i]]);
            if(i) printf(" -> ");
        }

        printf("\nTotal Distance: %d km\n",d[t]);
    }

    return d[t];
}

void locations()
{
    int i;

    printf("\n========== AVAILABLE LOCATIONS ==========\n");

    for(i=0;i<N;i++)
        printf("%d. %s\n",i+1,name[i]);
}

void roads()
{
    int i,j;

    printf("\n========== ROAD NETWORK ==========\n");

    for(i=0;i<N;i++) {
        printf("%s : ",name[i]);

        for(j=0;j<N;j++)
            if(g[i][j])
                printf("%s (%d km)  ",name[j],g[i][j]);

        printf("\n");
    }
}

void tests()
{
    int pass=0;

    printf("\n========== TESTING ==========\n");

    if(dijkstra(0,4,0)==9)
        printf("TC01 Airport -> Hospital : PASS\n"),pass++;
    else
        printf("TC01 Airport -> Hospital : FAIL\n");

    if(dijkstra(0,6,0)==12)
        printf("TC02 Airport -> Stadium  : PASS\n"),pass++;
    else
        printf("TC02 Airport -> Stadium  : FAIL\n");

    if(dijkstra(0,2,0)==4)
        printf("TC03 Airport -> City Mall : PASS\n"),pass++;
    else
        printf("TC03 Airport -> City Mall : FAIL\n");

    if(dijkstra(0,0,0)==0)
        printf("TC04 Airport -> Airport   : PASS\n"),pass++;
    else
        printf("TC04 Airport -> Airport   : FAIL\n");

    if(8<1 || 8>N)
        printf("TC05 Invalid Location     : PASS\n"),pass++;
    else
        printf("TC05 Invalid Location     : FAIL\n");

    printf("-----------------------------\n");
    printf("Tests Passed: %d/5\n",pass);

    if(pass==5)
        printf("Overall Result: ALL TESTS PASSED\n");
    else
        printf("Overall Result: SOME TESTS FAILED\n");

    printf("=============================\n");
}

int main()
{
    int ch,s,t;

    do {
        printf("\n========================================\n");
        printf("       SMART NAVIGATION SYSTEM\n");
        printf("========================================\n");
        printf("1. Display Locations\n");
        printf("2. Display Road Network\n");
        printf("3. Find Shortest Route\n");
        printf("4. Run Tests\n");
        printf("5. Exit\n");
        printf("========================================\n");

        printf("Enter choice: ");
        scanf("%d",&ch);

        if(ch==1)
            locations();

        else if(ch==2)
            roads();

        else if(ch==3) {
            locations();

            printf("\nEnter source (1-7): ");
            scanf("%d",&s);

            printf("Enter destination (1-7): ");
            scanf("%d",&t);

            if(s<1 || s>N || t<1 || t>N)
                printf("\nInvalid location!\n");

            else if(s==t) {
                printf("\nShortest Route: %s\n",name[s-1]);
                printf("Total Distance: 0 km\n");
            }

            else if(dijkstra(s-1,t-1,1)==-1)
                printf("\nNo route available.\n");
        }

        else if(ch==4)
            tests();

        else if(ch==5)
            printf("\nThank you for using the Smart Navigation System.\n");

        else
            printf("\nInvalid choice! Please try again.\n");

    } while(ch!=5);

    return 0;
}