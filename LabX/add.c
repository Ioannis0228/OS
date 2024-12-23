#include <stdio.h>

void add(int* x,int* y,int* z,int* sum){
        *sum = (*x)+(*y)+(*z);
}

int main(){
        int x=1,y=1,z=1,sum;
        printf("Give 3 integers you want to add\n");
        scanf("%d %d %d",&x,&y,&z);
        add(&x,&y,&z,&sum);
        printf("Sum = %d\n",sum);
        return 0;
}
