#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int g,ROW,COL;
struct cod
{
    int  x;
    int y;
};
bool ua(int **image ,struct cod *);
bool u2(int **image, struct cod *present);
bool u3(int **image, struct cod *present);
bool u4(int **image,struct cod *);
int main(int argc , char* argv[])
{
    if(argc != 2)
    {
        printf("%s integer value of grid\n",argv[0]);
        return 0;
    }
    g = atoi(argv[1])+1;
    //g=grid size
    FILE *op =fopen("image_cont.svg","w");
    FILE *ip =fopen("photo.pgm","r");
    int i=0,j ;
    char ch ;
    char type[3] ;
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
    int **p = (int **)malloc((row+2)*sizeof(int *));
    for(i = 0 ; i < row ;i++)
    {
        p[i] = (int *)malloc((col+2)*sizeof(int));
        p[i][0]=p[i][col]=1;
        image[i][0]=image[i][col]=1;
        for(j = 0 ; j < col ; j++)
        {
            fscanf(ip,"%d",&image[i][j]);
            p[i][j] = image[i][j];
        }
    }
    image[0][0]=1;
    struct cod init,present;
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
/*    fprintf(op,"<polygon points=\"");*/
    int hello[row][col];
    int flag = 1;
    ROW = row;
    COL = col;
    for(j = g ; (j <= row) && (flag) ; j+=(g))
    {
        
        for(i = g ; i <= col ; i+=(g))
        {
            for(k=i;(k<=(i+g))&&(k<=col);k++)
            {
                if(image[j][k] == 0)
                {
                       flag = 0;
                       break;
                }
            }
            if(!flag)
            {
               init.x=j;
               init.y=i;     
                break;
            }
        }
    }
    printf(" %d,%d",init.x,init.y);
    struct cod tap;
    for(j = g  ; (j < row-g) && (!flag) ; j+=(g))
    {
        
        for(i = g  ; i < col-g ; i+=(g))
        {
            tap.x = j ;
            tap.y = i ;
            if((!(ua(p,&tap)))&&(u4(p,&tap))&&(!(u3(p,&tap))))
            {
                flag = 0 ;
                break;
            }
            else if((ua(p,&tap))&&(u4(p,&tap))) 
                break;
        }
        if(!flag)
        {
            init.x = j ;
            init.y = i ;
            printf("\n%d %d\n",j,i);
            break;
        }
    }
    int direction = 2;
    int points=1;
    fprintf(op,"<polyline points=\"");
    int prev = 4,pres;
    int c = 0;
    bool r1,r2,r3,r4;
    int square = 0 ;
    present.x = init.x ; 
    present.y = init.y;
    fprintf(op," %d.5,%d.5",init.y,init.x);
    do
    {
        c = 0;
        square = 0 ;
        r1 = ua(p,&present);
        r2 = u2(p,&present);
        r3 = u3(p,&present);
        r4 = u4(p,&present);
        if(r1==true)
        {
            c++;
            square += 1;
        }
        if(r2==true)
        {
            c++;
            square += 2;
        }
        if(r3==true)
        {
            c++;
            square += 3;
        }
        if(r4==true)
        {
            c++;
            square += 4;
        }
        if(c==2)
        {
           if(square%2)
           {
                c = 0;
           }
           else
            c = 4;
        }
        direction = (direction + c)%4;
        if(direction == 0)
        {
            present.y = present.y + g ;
        }
        else if(direction == 1)
        {
            present.x = present.x - g ;
        }
        else if(direction == 2 )
        {
            present.y = present.y - g ;
        }
        else
        {
            present.x = present.x + g ;
        }
/*
        r takes the type of occupancy, in case two cells are occupied then we take the modulo
        of the the exact occupied cell no. say
                then sum of the cell type is the type of oocupancy .
                So assuming that direction 0 mive 
*/
        fprintf(op," %d.5,%d.5",present.y,present.x);
    }while((present.x != init.x) || (present.y != init.y));
    //      The following line has not been tested .
    fprintf(op,"\" style=\"fill:none;stroke:red;\"/>\n</svg>");
    return 0;
}
bool ua(int **image, struct cod *present)
{
    int i;
    for( i = present->y ; i < (present->y+g+1)&&(i<COL)&&(i>=0) ; i++ )
    {
        if((present->x <= ROW)&&(present->x >=0)&&( image[present->x][i]==0 ))
        {
            return true;
        }
    }
    for(i = present->y ; i < (present->y+g+1)&&(i<COL)&&(i>=0) ; i++)
    {
        if((present->x-g >= 0)&&(present->x-g <= ROW)&&( image[present->x-g][i] == 0 )) 
        {
            return true;
        }
    }
    for(i = present->x-g ; i < (present->x+1)&&(i<ROW)&&(i>=0) ; i++)
    {
        if(image[i][present->y]==0)
        {
            return true;
        }
    }
    for(i = present->x-g ; i < (present->x+1)&&(i<ROW)&&(i>=0) ; i++)
    {
        if((present->y+g <=COL)&&(present->y+g >= 0)&&(image[i][present->y+g]==0))
        {
            return true;
        }
    }
    return false;
}
bool u4(int **image, struct cod *present)
{
    int i;
    for( i = present->y  ; (i < present->y+g+1)&&(i<COL)&&(i>=0) ; i++ )
    {
        if( (present->x <= ROW)&&(present->x >=0)&&(image[present->x][i]==0) )
        {
            return true;
        }
    }
    for(i = present->y ; (i < present->y+g+1)&&(i<COL)&&(i>=0); i++)
    {
        if((present->x+g <= ROW)&&(present->x+g >= 0)&&( image[present->x+g][i] == 0 ))
        {
            return true;
        }
    }
    for(i = present->x ; i < (present->x+g+1)&&(i<ROW)&&(i>=0) ; i++)
    {
        if(((present->y <= COL)&&(present->y >= 0)&&image[i][present->y]==0))
        {
            return true;
        }
    }
    for(i = present->x ; i < (present->x+g+1)&&(i<ROW)&&(i>=0) ; i++)
    {
        if((present->y-g >= 0)&&(present->y-g <= COL)&&(image[i][present->y+g]==0))
        {
            return true;
        }
    }
    return false;
}
bool u3(int **image, struct cod *present)
{
    int i;
    for( i = present->y ; (i > present->y-g-1)&&(i<COL)&&(i>=0) ; i-- )
    {
        if( (present->x <= ROW)&&(present->x >=0)&&(image[present->x][i]==0) )
        {
            return true;
        }
    
        if((present->x+g <= ROW)&&(present->x+g >= 0)&&( image[present->x+g][i] == 0 ))
        {
            return true;
        }
    }
    for(i = present->x ; i < (present->x+g+1)&&(i<ROW)&&(i>=0) ; i++)
    {
        if((present->y <= COL)&&(present->y >= 0)&&(image[i][present->y]==0))
        {
            return true;
        }
    
        if((present->y-g >= 0)&&(present->y-g <= COL)&&(image[i][present->y-g]==0))
        {
            return true;
        }
    }
    return false;
}

bool u2(int **image, struct cod *present)
{
    int i;
    for( i = present->y ; (i > present->y-g-1)&&(i<COL)&&(i>=0) ; i-- )
    {
        if( (present->x <= ROW)&&(present->x >=0)&&(image[present->x][i]==0) )
        {
            return true;
        }
    
        if((present->x-g < ROW)&&(present->x-g >=0)&&( image[present->x-g][i] == 0 ))
        {
            return true;
        }
    }
    for(i = present->x ; i > (present->x-g-1)&&(i<ROW)&&(i>=0) ; i-- )
    {
        if((present->y <= COL)&&(present->y >= 0)&&(image[i][present->y]==0))
        {
            return true;
        }
    
        if((present->y-g >= 0)&&(present->y-g >= 0)&&(image[i][present->y-g]==0))
        {
            return true;
        }
    }
    return false;
}
