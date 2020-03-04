#include<stdio.h>
#include<math.h>
#include<stdlib.h>

typedef struct Oras
{
    int x,y;
}Oras;
typedef struct Centrala
{
    int x,y;
}Centrala;
typedef struct Matrice
{
    int m,t,i,v,b;
    //marcat taiat incomjurat barat
}Matrice;


int main(int argc, char *argv[])
{
    FILE *fisier,*file; 
    fisier = fopen (argv[1], "r"); 
    file = fopen (argv[2], "w"); 
    int N,M;
    fscanf(fisier,"%d%d",&N,&M);
    Matrice A[M+1][N+1],copy[M+1][N+1];
    Oras O[N];
    Centrala C[M];
    for(int i=1;i<=M;i++)
    {
        for(int j=1;j<=N;j++)
         {
            A[i][j].i=0;
            A[i][j].m=0;
            A[i][j].t=0;
            A[i][j].b=0;
         }       
    }
   
    for(int i=1;i<=N;i++)
    { 
        fscanf(fisier,"%d%d",&O[i].x,&O[i].y);
    }

    for(int i=1;i<=M;i++)
    {
        fscanf(fisier,"%d%d",&C[i].x,&C[i].y);
    }
    
    for(int i=1;i<=M;i++)
        for(int j=1;j<=N;j++)
        {
            A[i][j].v = abs(C[i].x-O[j].x) + abs(C[i].y-O[j].y);   
            copy[i][j].v=A[i][j].v;
        }


   
    //minim pe linii
    for(int i=1;i<=M;i++)
    {int min=999999;
        for(int j=1;j<=N;j++)
            if(A[i][j].v<min)
                min=A[i][j].v;
         for(int j=1;j<=N;j++)
            A[i][j].v=A[i][j].v-min;
    }
    //minim pe coloane
    for(int j=1;j<=N;j++)
    {int min=999999;
        for(int i=1;i<=M;i++)
            if(A[i][j].v<min)
                min=A[i][j].v;
         for(int i=1;i<=M;i++)
            A[i][j].v=A[i][j].v-min;
    }

    while(0!=1){

        int i,j,l;
        int ok=1;
   
        while(ok==1)
        {  
            int s=N+1,z;
            ok=0;
            l=1;
            for(i=1;i<=M;i++)
            {   
                z=0;
                for(j=1;j<=N;j++)
                    {
                        if(A[i][j].v==0 && A[i][j].b==0 && A[i][j].i==0)
                            z++;
                    }
                if(z<s && z!=0)
                    {s=z;l=i;}
            }
            if(s!=N+1)
                for( j=1;j<=N;j++)
                {
                    if(A[l][j].v==0 && A[l][j].i==0 && A[l][j].b==0)
                    {   
                        A[l][j].i=-1;
                        break;
                    }
                }

            //barez pe coloana 
                for(i=1;i<=M;i++)
                    if(A[i][j].v==0  && A[i][j].i==0 && A[i][j].b==0) 
                        {A[i][j].b=-1;}
            
            //barez pe linie
                for(j=1;j<=N;j++)
                if(A[l][j].v==0 && A[l][j].i==0 && A[l][j].b==0) 
                        {A[l][j].b=-1;}

            
            //caut sa vad daca mai exista vreun zero ca sa repet ce am facut pana acum

            for(i=1;i<=M;i++)
            {    for(j=1;j<=N;j++)
                    if(A[i][j].v==0 && A[i][j].i==0 && A[i][j].b==0)
                        ok=1;
            }
        
        }//  
    
    //verific daca s-a obtinut cuplaj maxim:exista pe linie si coloana doar unul inconjurat 
    int a=0,k=1;
    for(int i=1;i<=M;i++)
    {   a=0;
        for(int j=1;j<=N;j++)
            if(A[i][j].i==-1)
                a++;
        if (a !=1)
            k=0;
    }
    for(int j=1;j<=N;j++)
    {   a=0;
        for(int i=1;i<=M;i++)
            if(A[i][j].i==-1)
                a++;
        if (a != 1)
            {k=0;}
    }
  
 
          
    if(k==1)
    {  for(j=1;j<=N;j++) 
            for(i=1;i<=M;i++)
                A[i][j].v=copy[i][j].v; 

        for(j=1;j<=N;j++)
        {   
            for(i=1;i<=M;i++)
                if(A[i][j].i==-1)
                    fprintf(file,"%d \n",(i-1));
        }

        return 0;
    }
    //acum marchez si tai liniile
    //1.marchez liniile fara 0 incadrat
    int v=0;
    while(v==0)
    { 
        v=1;
        //int z=0;
        for(i=1;i<=M;i++)
        {   
            a=0;
                for(j=1;j<=N;j++)
                    if(A[i][j].i==-1 && A[i][j].v==0 )
                        a++;
                if(a==0)//marchez linia
                { 
                    for(j=1;j<=N;j++)
                    {
                        A[i][j].m=-1;
                       
                    }
                }
            }

      
        //2.marchez coloanele care contin 0 barate pe liniile marcate 
        for(int i=1;i<=M;i++)
        {
            int z=0;
            for(int j=1;j<=N;j++)
                if(A[i][j].m==-1)
                   z++;
            if(z==N)
                for(int j=1;j<=N;j++)
                    if(A[i][j].b==-1 && A[i][j].v==0)
                    {
                        int c;
                        for(c=1;c<=M;c++)
                        A[c][j].m=-1;
                     }
        }
    //3.marchez liniile care contin un 0 incadrat pe coloanele deja marcate
        for(int i=1;i<=M;i++)
        {
            a=0;int s;
            for(int j=1;j<=N;j++)
                if(A[i][j].v==0 && A[i][j].i==-1 && A[i][j].m ==-1)
                {
                    int c;s=0;
                    //trebuie sa verific daca coloana e marcata
                    for(c=1;c<=M;c++)
                        if(A[c][j].m==-1)
                            s++;
                    if(s==M)
                        a++;
                }
        s=0;
        for(int j=1;j<=N;j++)
            if(A[i][j].m==-1)
                s++;
        

        if (a==1 && s<N)
        {
           for(int j=1;j<=N;j++)
            A[i][j].m=-1;            
        } 
           
    }
    //verific daca trebuie sa repet
    //1.
    for(int i=1;i<=M;i++)
        {int b=0;
            a=0;
            for(int j=1;j<=N;j++)
                if(A[i][j].v==0 && A[i][j].i==-1)
                    a=1;
            for(int j=1;j<=N;j++)
                if(A[i][j].m==-1)
                    b++;
            if(a==0 && b<N)
            {   
                for(int j=1;j<=N;j++)
                    if(A[i][j].m==-1)
                        a++;
                if(a<N)
                    v=0;
            }
        }
    //2.    
    for(int i=1;i<=M;i++)
        {
            a=0;
            for(int j=1;j<=N;j++)
                if(A[i][j].m==-1)
                    a++;
            if(a==N)
            {
                a=0;
                for(int j=1;j<=N;j++)
                    if(A[i][j].v==0 && A[i][j].b==-1)
                        {
                            int c,s=0;
                            for(c=1;c<=M;c++)
                                if(A[c][j].m==-1)
                                    s++;
                            if(s<M)
                                v=0;
                        }
            }
            
        }
    //3.
        for(int i=1;i<=M;i++)
        {
            a=0;int b=0,s=0,c;
            for(int j=1;j<=N;j++)
                if(A[i][j].i==-1 && A[i][j].v==0 && A[i][j].m==-1)
                {   s=0;
                    for(c=1;c<=M;c++)
                        if(A[c][j].m==-1)
                            s++;
                    if(s==M)
                        a++;

                }
            for(int j=1;j<=N;j++)
            if(A[i][j].m==-1)
                b++;
            if(a==1 && b<N)
            {
                for(int j=1;j<=N;j++)
                    if(A[i][j].i==-1 && A[i][j].v==0 && A[i][j].m==-1)
                        break;
                int c,s=0;
                for(c=1;c<=M;c++)
                    if(A[c][j].m==-1)
                        s++;
                if(s==M)
                    v=0;
            }
        }
    }       
    //tai liniile nemarcate si coloanele marcate
    int q=0;
    for(int i=1;i<=M;i++)
    {   q=0;
            for(int j=1;j<=N;j++)
                if(A[i][j].m==0)
                    q++;
        if(q>0)
            for(int j=1;j<=N;j++)
                A[i][j].t= A[i][j].t-1;  
    }

    for(int j=1;j<=N;j++)
    {   q=0;
            for(int i=1;i<=M;i++)
                if(A[i][j].m==-1)
                    q++;
        if(q==M)
            for(int i=1;i<=M;i++)
                A[i][j].t= A[i][j].t-1;  
    }
    //caut minorant
    q=999999;
    for(int i=1;i<=M;i++)
        {   
            for(int j=1;j<=N;j++)
                if(A[i][j].t==0 && A[i][j].v<q && A[i][j].v != 0)
                    q = A[i][j].v;
        }
    //il scad elementelor netaiate si il adaug elementelor taiate de doua ori
    for(int i=1;i<=M;i++)
        {   for(int j=1;j<=N;j++)
                if(A[i][j].t==0 && A[i][j].v!=0)
                    A[i][j].v=A[i][j].v-q;
                 else
                    if(A[i][j].t==-2)
                        A[i][j].v=A[i][j].v+q;
                 
        }

    //aici aduc parametrii matricei A la forma initiala
    for(int i=1;i<=M;i++)
    {
        for(int j=1;j<=N;j++)
         {
            A[i][j].i=0;
            A[i][j].m=0;
            A[i][j].t=0;
            A[i][j].b=0;
         }       
    }
   
} 
    return 0;
}