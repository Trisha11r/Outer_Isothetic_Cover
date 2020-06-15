#include <stdio.h>
#include <stdlib.h>
struct cod
{
    int  x;
    int y;
};
int main(int argc , char* argv[])
{
    if(argc != 2)
    {
        printf("%s integer value of grid\n",argv[0]);
        return 0;
    }
    int g = atoi(argv[1]) + 1;
    //g=grid size
    FILE *op =fopen("image_cont.svg","w");
    FILE *ip =fopen("photo.pgm","r");
    int i=0,j;
    char ch ;
    char type[3];
    while((ch = fgetc(ip)) != '\n')
    {
        type[i] = ch ;
        i++;
    }
/*  Ignore Comments  */
    while((ch = fgetc(ip)) != '\n');
    int row,col,max,count,fill,k,l;
    fscanf(ip,"%d %d",&col,&row);
    fscanf(ip,"%d",&max);
    int image[row+1][col+1];
    int cp[row+1][col+1];
    for(i = 0 ; i < row ;i++)
    {
        for(j = 0 ; j < col ; j++)
        {
            fscanf(ip,"%d",&image[i+1][j+1]);
            cp[i][j]=0;
        }
    }
    struct cod init;
    fprintf(op,"<svg width=\"%d\" height=\"%d\">\n",col,row);
    fprintf(op,"<rect width=\"%d\" height=\"%d\" style=\"fill:rgb(255,255,255)\" />\n",col,row);
    for(i = g ; i < col ;i = i + g)
    {
        fprintf(op,"<line x1=\"%d.5\" y1=\"0\" x2=\"%d.5\" y2=\"%d\" style=\"stroke:rgb(200,200,200);stroke-width:1\" />\n",i,i,row-1);
    }
    for(i = g ; i < row ;i = i + g)
    {
        fprintf(op,"<line x1=\"0\" y1=\"%d.5\" x2=\"%d\" y2=\"%d.5\" style=\"stroke:rgb(200,200,200);stroke-width:1\" />\n",i,col-1,i);
    }
    fprintf(op,"<polygon points=\"");
    int hello[row][col];
    int flag = 1;
    for(j = 0 ; (j < row) && (flag) ; j++)
    {
        for(i = 0 ; i < col ; i++)
        {
            if(image[j+1][i+1] == 0)
            {
                   init.x = j;
                   init.y = i;
                   flag = 0;
                   break;
            }
        }
    }
    int points=1;
    printf("%d,%d\n",init.y,init.x);
    fprintf(op," %d.0,%d.0",init.y,init.x);
    int prev = 7,pres;
    struct cod a[8],present;
    present.x =init.x ; 
    present.y = init.y;
    do
    {
        flag = 1;
        while(flag)
        {
            prev = prev + 1;
            if (prev == 8)
               prev = 0;
            pres = prev;
            switch(prev)
            {
                case 0 : if(image[present.x+1][present.y] == 0)
                         {
                            
/*                                present.x;*/
                                present.y--;   
                                prev = 4 ;
                                flag = 0;
                         }
                         break;  
                case 1 : if(image[present.x+2][present.y] == 0)
                         {
                            flag = 0;
                            present.y--;   
                            present.x++;
                            prev = 5 ;
                         }
                         break;
                case 2 : if(image[present.x+2][present.y+1] == 0)
                         {
                            flag = 0;
/*                            present.x++;*/
                            present.x++;   
                            prev = 6 ;
                         }
                         break;  
                case 3 : if(image[present.x + 2][present.y+2] == 0)
                         {
                            flag = 0;
                            present.x++;
                            present.y++;   
                            prev = 7 ;
                         }
                         break;
                case 4 : if(image[present.x + 1][present.y+2] == 0)
                         {
                            flag = 0;
                            present.y++;
/*                            present.y--;   */
                            prev = 0 ;
                         }
                         break;  
                case 5 : if(image[present.x][present.y+2] == 0)
                         {
                            flag = 0    ; 
                            present.x--   ;
                            present.y++ ;   
                            prev = 1    ;
                         }
                         break;  
                case 6 : if(image[present.x][present.y+1] == 0)
                         {
                            flag = 0;
/*                            present.x--;*/
                            present.x--;   
                            prev = 2 ;
                         }
                         break;  
                case 7 : if(image[present.x][present.y] == 0)
                         {
                            flag = 0;
                            present.x--;
                            present.y--;   
                            prev = 3 ;
                         }
                         break;    
                
            }
            
        }
        if(prev != pres)
        {
            fprintf(op," %d.0,%d.0",present.y,present.x);
            cp[present.x][present.y]=1;
            points++;
        }        
    }while((present.x != init.x) || (present.y != init.y) );
/*    getchar();*/
    fprintf(op,"\" style=\"fill:black;\"/>\n</svg>");
    FILE *kp=fopen("kapa.pgm","w");
    for(i=0;i<row;i++)
    {
        count = 0;
        for(j=0;j<col;j++)
        {
            if(cp[i][j]==1)
            {
                count=(count+1)%2;
            }
            if(count)
            {
                fprintf(kp,"1\n");
            }
            else
            {
                fprintf(kp,"0\n");
            }
        }
    }

    printf("%d\n",(points));
}
