#include<stdio.h>
#include<stdlib.h>

int x, y;//Coordinate components value
char matriX1[8][8], matriX2[8][8];//matrix
char tab1[8][8], tab2[8][8];//shoot table
char name1[25], name2[25];//names
//Coordinate components
int Y(){
    int y;
    scanf("%i", &y);
    return y;
}
int TransfX(){
    char column;
    int result;
    column=getchar();
    if (column=='A' || column=='a')
        result=1;
    else if (column=='B' || column=='b')
        result=2;
    else if (column=='C' || column=='c')
        result=3;
    else if (column=='D' || column=='d')
        result=4;
    else if (column=='E' || column=='e')
        result=5;
    else if (column=='F' || column=='f')
        result=6;
    else if (column=='G' || column=='g')
        result=7;
    else if (column=='H' || column=='h')
        result=8;
    else
        result=9;
    return result;
}

int position(int n, int c){
    int po;
    printf("\tDeploy\n\tShip N.%i(cells #%i)\n\n\tPosition: 1.Vertical\n\t\t  2.Horizontal\n\tAnswer: ",n,c);
    scanf("%i", &po);
    while(po<1 || po>2){
        printf("\tEnter a valid coordinate\n\tCoordinate: \n");
        scanf("%i", &po);
    }
    return po;
}
//Avoid repeating text
//arrangement
void coordinates(){
    printf("\tCoordinate: ");
    x=TransfX();
    y=Y();
    while(y<1 || y>8 || x<1 || x>8){
        printf("\n\tRetry!\n\tCoordinate: ");
        x=TransfX();
        y=Y();
    }
}//y<1 || x<1
void coordinates6(){
    x=TransfX();
    y=Y();
    while(y>6 || y<1 || x<1 || x>8){
        printf("\n\tRETRY!!\n\tCoordinate: ");
        x=TransfX();
        y=Y();
    }
}//y<6
void coordinates7(){
    x=TransfX();
    y=Y();
    while(y>7 || y<1 || x<1 || x>8){
        printf("\n\tRETRY!!\n\tCoordinate: ");
        x=TransfX();
        y=Y();
    }
}//y>7
void coordinatesX6(){
    x=TransfX();
    y=Y();
    while(x>6 || x<1 || y<1 || y>8){
        printf("\n\tRETRY!!\n\tCoordinate: ");
        x=TransfX();
        y=Y();
    }
}//x>6
void coordinatesX7(){
    x=TransfX();
    y=Y();
    while(x>7 || x<1 || y<1 || y>8){
        printf("\n\tRETRY!!\n\tCoordinate: ");
        x=TransfX();
        y=Y();
    }
}//x>7
void error(){
    system("cls");
    printf("\tInvalid Action");
}//Overlapping ship
void attackCoordError(){
    printf("\tWrong Coordinate.\t¡¡RETRY!!\n\tCoordinate: ");
    x=TransfX();
    y=Y();
}//Wrong Coordinates

void printTab(){
    int i, j, caract, n;
    n=65;
    
    printf("\n\t\t\t      %s's table\n\n\n\n\t\t\t\t",name1);
    for(i = 0; i <8; i++){
        caract=n+i;
        printf("%c  ", caract);
    }
    printf("\n");
    
    for(y=0; y<8; y++){
        printf("\t\t\t     ");
        printf("%i  ", y+1);
        for(x=0; x<8; x++){
            printf("%c  ",tab1[y][x]);
        }
        printf("\n");
    }
    printf("\n\n\t\t\t      %s's table\n\n\n\n\t\t\t\t", name2);
    for(i = 0; i <8; i++){
        caract=n+i;
        printf("%c  ", caract);
    }
    printf("\n");
    for(y=0; y<8; y++){
        printf("\t\t\t     %i  ", y+1);
        for(x=0; x<8; x++){
            printf("%c  ",tab2[y][x]);
        }
        printf("\n");
    }
}
void printMatrix(char matrix[][8]){
    int i, j, caract, n;
    n=65;
    printf("\n\n\n\t\t\t\t");
    for(i = 0; i <8; i++){
        caract=n+i;
        printf("%c  ", caract);
    }
    printf("\n");
    
    for(y=0; y<8; y++){
        printf("\t\t\t     ");
        printf("%i  ", y+1);
        for(x=0; x<8; x++){
            printf("%c  ",matrix[y][x]);
        }
        printf("\n");
    }
    printf("\n");
}
void dataPlayer1(char name1, int countShip, int s1, int s2, int s3, int n, int i, char ships[][8], int matriX1[][8]){
    c=2;//Ships(1,2) 2 cells(x2) with overlimit coords y>7 and x>7
    while(s3<=1){
        printf("\n\tDeploy Patrol #%i!!",countShip);
        countShip ++,
        printMatrix(matriX1);
        po = position(n,c);
        //Vertical
        if (po==1){
            printf("\tCoordinate: ");
            coordinates7();//Overlimit(vertical) is y>7
            while(matriX1[y-1][x-1]=='*'){//When the coord break the overlimit
                printf("\tThis space has already been chosen, choose another space: ");
                coordinates7();
            }
            
            i=0;
            while(i<2){
                //checks if the ship collide
                if(matriX1[y-1][x-1]=='*'){
                    while(i>0){
                        y--;
                        matriX1[y-1][x-1]=' ';
                        i--;
                    }
                    error();
                    i=3;
                }else{
                    matriX1[y-1][x-1]='*';//printing the ship
                    y++;
                    i++;
                }
                if (i==2){
                    s3++;
                    n++;//Counter ship
                    system("cls");
                }
            }
        }else{
            printf("\tCoordinate: ");//Horizontal
            coordinatesX7();
            while(matriX1[y-1][x-1]=='*'){//When the coords break the overlimit
               printf("\tThis space has already been chosen, choose another space: ");
               coordinatesX7();
           }
           
            i=0;
            while(i<2){
                //checks if the ships collide
                if(matriX1[y-1][x-1]=='*'){
                    while(i>0){
                        x--;
                        matriX1[y-1][x-1]=' ';
                        i--;
                    }
                    error();
                    i=3;
                }else{
                    matriX1[y-1][x-1]='*';//printing
                    x++;
                    i++;
                }
                if (i==2){
                    s3++;
                    n++;//counter ship
                    system("cls");
                }
            }
        }
    }
    system("cls");
    
    c=3;//ships(2,3) 3 cells(x2) with the overlimit coords y>6 and x>6
    while(s2<=1){
        printf("\n\tDeploy Submarine #%i!!\n", countShip);
        countShip ++;
        printMatrix(matriX1);
        po = position(n,c);
        //Column
        if (po==1){
            printf("\tCoordinate: ");
            coordinates6();//In this function we use y>6 to checks the valid column
            
            while(matriX1[y-1][x-1]=='*'){
                printf("\tThis space has already been chosen, choose another space: ");//Checks the space
                coordinates6();
            }
            i=0;//Vertical
            while(i<3){
                //checks if the ships collide
                if(matriX1[y-1][x-1]=='*'){
                    while(i>0){
                        y--;
                        matriX1[y-1][x-1]=' ';
                        i--;
                    }
                    error();
                    i=4;
                //Row
                }else{
                    matriX1[y-1][x-1]='*';//Printing vertical
                    y++;
                    i++;
                }
                if (i==3){
                    s2++;
                    n++;//count the ship
                    system("cls");
                }
            }
        }else{
            printf("\tCoordinate: ");
            coordinatesX6();//In this function we use x>6 to checks the valid column
            while(matriX1[y-1][x-1]=='*'){
                printf("\tThis space has already been chosen, choose another space: ");//Checks the space
                coordinatesX6();
            }
            i=0;//Horizontal
            while(i<3){
                //checks if the ships collide
                if(matriX1[y-1][x-1]=='*'){
                    while(i>0){
                        x--;
                        matriX1[y-1][x-1]=' ';
                        i--;
                    }
                    error();
                    i=4;
                }else{
                    matriX1[y-1][x-1]='*';//Printing the ship Horizontal
                    x++;
                    i++;
                }
                if(i==3){
                    s2++;
                    n++;//To count
                    system("cls");
                }
            }
        }
    }
    system("cls");
    
    c=4;//ship5 4 cells
    printf("\n\tPosition your ships player %s\n\n", name1);
    printf("\tDeploy Battleship!!");
    while(s1==0){
        printMatrix(matriX1);
        po = position(n,c);
        //Vertical
        if (po==1){
            coordinates();
            
            //checks if column input by the user is valid
            if(y<=5){
                for(i=0;i<4;i++){
                    matriX1[y-1][x-1]='*';//Printing the ship(vertical)
                    y++;//Increasing y
                    s1=1;
                }
                n++;//number to count the ships
                system("cls");
            }else{
                error();
            }
        }else{
            coordinates();
            //checks if row input by the user is valid
            if(x<=5){
                for(i=0;i<4;i++){
                    matriX1[y-1][x-1]='*';//Printing the ship(horizontal)
                    x++;//Increasing x
                    s1=1;
                }
                n++;//number to count the ships
                system("cls");
            }else{
                error();
            }
        }
    }
    
    //Load matrix player1 
    for(y=0; y<8; y++){
        for(x=0; x<8; x++){
            if (matriX1[y][x]=='*')
            ships1[y][x]=1;
            else
            ships1[y][x]=0;
        }
    }
    system("cls");

    //Printing the ships matrix to player1
    printMatrix(matriX1);
    printf("\t%s, enter to continue...",name1);
    getch();
    system("cls");
    n=1;//Initializing the ships counter
    countShip=1;
}

void results(){
    int i, j, caract, n;
    n=65;
    
    printf("\t\t      %s's table\t\t\t      %s's table\n\t\t   ",name1,name2);
    //Row of characters
    for(i = 0; i <8; i++){
        caract=n+i;
        printf("%c  ", caract);// first table
    }
    printf("\t\t   ");
    for(i = 0; i <8; i++){
        caract=n+i;
        printf("%c  ", caract);//second table
    }
    printf("\n");
    //Column of numbers
    for(y=0; y<8; y++){
        printf("\t\t%i  ", y+1);
        //Printing the registers
        for(x=0; x<8; x++){
            printf("%c  ",matriX1[y][x]);//Player1´s table
            //Printing the column of numbers
            if(x==7){
                printf("\t\t");
                printf("%i  ", y+1);
                //Printing the registers
                for(x=0;x<8;x++){
                printf("%c  ",matriX2[y][x]);//Player2´s table
                }
            }
        }
        printf("\n");
    }

    printf("\n\n\n\n\t\t      %s's attacks\t\t\t      %s's attacks\n\t\t   ",name1,name2);
    //Row of characters
    for(i = 0; i <8; i++){
        caract=n+i;
        printf("%c  ", caract);// first table
    }
    printf("\t\t   ");
    for(i = 0; i <8; i++){
        caract=n+i;
        printf("%c  ", caract);//second table
    }
    printf("\n");
    //Column of numbers
    for(y=0; y<8; y++){
        printf("\t\t%i  ", y+1);
        //Printing the registers of player1
        for(x=0; x<8; x++){
            printf("%c  ",tab1[y][x]);//Player 2´s attacks
            //Printing the column of numbers
            if(x==7){
                printf("\t\t");
                printf("%i  ", y+1);
                //Printing the registers of player2
                for(x=0;x<8;x++){
                printf("%c  ",tab2[y][x]);//Player 2´s attacks
                }
            }
        }
        printf("\n");
    }
}

void main(){
    ////////Statements////////
    int ships1[8][8],ships2[8][8];
    int bet, countShip, po, i, s1, s2, s3,gamestatus,sum,n,c;
    bet=0;
    sum=0;
    gamestatus=1;
    countShip=1;
    n=1;
    s1=0;
    s2=0;
    s3=0;
    
    //To align the items
    for(int j=0; j<8; j++){
        for(int k=0; k<8; k++){
            matriX1[j][k]=' ';
            matriX2[j][k]=' ';
            tab1[j][k]=' ';
            tab2[j][k]=' ';
        }
    }
    ////////Input Data////////
    printf("\t>>>>>BATTLESHIP<<<<<\n");
    printf("\tPlayer 1's name: ");
    gets(name1);
    printf("\tPlayer 2's name: ");
    gets(name2);
    system("cls");
    
    ////////SHIPS PLAYER1////////
    dataPlayer1(name1, countShip, s1,  s2,  s3,  n, i, ships[][8], matriX1[][8])
    
    ////////SHIPS PLAYER2////////
    s3=0; c=2;//Ships(1,2) 2 cells(x2) with overlimit coords y>7 and x>7
    while(s3<=1){
        printf("\n\tDeploy Kraken #%i!!\n", countShip);
        countShip ++;
        printMatrix(matriX2);
        po = position(n,c);

        if (po==1){
            printf("\tCoordinate:");
            coordinates7();
            while(matriX2[y-1][x-1]=='*'){
                printf("\n\tThis space has already been chosen, choose another space: \n");
                coordinates7();
            }
            i=0;
            while(i<2){
                if(matriX2[y-1][x-1]=='*'){
                    while(i>0){
                        y--;
                        matriX2[y-1][x-1]=' ';
                        i--;
                    }
                    error();
                    i=3;
                }else{
                    matriX2[y-1][x-1]='*';
                    y++;
                    i++;
                }
                if (i==2){
                    s3++;
                    n++;
                    system("cls");
                }
            }
        }else{
            printf("\n\tDeploy Submarine #%i!!\n", countShip);
            countShip ++;
            printf("\tCoordinate: ");
            coordinatesX7();
            while(matriX2[y-1][x-1]=='*'){
                printf("\n\tThis space has already been chosen, choose another space: \n");
                coordinatesX7();
            }
            i=0;
            while(i<2){
                if(matriX2[y-1][x-1]=='*'){
                    while(i>0){
                        x--;
                        matriX2[y-1][x-1]=' ';
                        i--;
                    }
                    error();
                    i=3;
                }else{
                    matriX2[y-1][x-1]='*';
                    x++;
                    i++;
                }
                if (i==2){
                    s3++;
                    n++;
                    system("cls");
                }
            }
        }
    }
    system("cls");
    
    s2=0; c=3;//ships(3,4) 3 cells(x2) with the overlimit coords y>6 and x>6
    while(s2<=1){
        printf("\n\tDeploy Black pearl #%i!!\n", countShip);
        countShip ++;
        printMatrix(matriX2);
        po = position(n,c);
        if (po==1){
            printf("\tCoordinate: ");
            coordinates6();
            while(matriX2[y-1][x-1]=='*'){
                printf("\tThis space has already been chosen, choose another space: ");
                coordinates6();
            }
            i=0;
            while(i<3){
                if(matriX2[y-1][x-1]=='*'){
                    while(i>0){
                        y--;
                        matriX2[y-1][x-1]=' ';
                        i--;
                    }
                    error();
                    i=4;
                }else{
                    matriX2[y-1][x-1]='*';
                    y++;
                    i++;
                }
                if (i==3){
                    s2++;
                    n++;
                    system("cls");
                }
            }
        }else{
            printf("\tCoordinate: ");
            coordinatesX6();
            while(matriX2[y-1][x-1]=='*'){
                printf("\n\tThis space has already been chosen, choose another space: \n");
                coordinatesX6();
            }
            i=0;
            while(i<3){
                if(matriX2[y-1][x-1]=='*'){
                    while(i>0){
                        x--;
                        matriX2[y-1][x-1]=' ';
                        i--;
                    }
                    error();
                    i=4;
                }else{
                    matriX2[y-1][x-1]='*';
                    x++;
                    i++;
                }
                if(i==3){
                    s2++;
                    n++;
                    system("cls");
                }
            }
        }
    }
    system("cls");
    
    s1=0; c=4;//ship5 4 cells
    printf("\tDeploy Wadering dutch!!");
    while(s1==0){
        printMatrix(matriX2);
        po = position(n,c);
        
        if (po==1){
            coordinates();
            if(y<=5){
                for(i=0;i<4;i++){
                    matriX2[y-1][x-1]='*';
                    y++;
                    s1=1;
                }
                n++;
                system("cls");
            }else{
                error();
            }
        }else{
            coordinates();
            if(x<=5){
                for(i=0;i<4;i++){
                    matriX2[y-1][x-1]='*';
                    x++;
                    s1=1;
                }
                n++;
                system("cls");
            }else{
                error();
            }
        }
    }
    
    //Load matrix player2
    for(y=0; y<8; y++){
        for(x=0; x<8; x++){
            if (matriX2[y][x]=='*')
            ships2[y][x]=1;
            else
            ships2[y][x]=0;
        }
    }

    //Printing the ships matrix to player2
    printMatrix(matriX2);
    printf("\t%s, press enter to continue...\n", name2);
    getch();
    system("cls");

    ////////ATTACK////////
    while(gamestatus==1){
        sum=0;
        bet += 1;//Counter round/turn
        printTab();
        
        printf("Initial bet #%i", bet);
        
        //Player1 turn
        printf("\n\n\t%s's turn\n\tCoordinate: ", name1);
        x=TransfX();
        y=Y();
        
        //Coords breaks the overlimit of the table
        while (x<1 || x>8 || y<1 || y>8){
            printf("\tWrong coordinate.\n\tRETRY!!\n\tCoordinate: \n");
            x=TransfX();
            y=Y();
        }
        //Space has been chosen
        while(tab1[y-1][x-1]=='+' || tab1[y-1][x-1]=='-'){
                attackCoordError();
                
                while (x<1 || x>8 || y<1 || y>8){
                    attackCoordError();
                }
        }
        system("cls");
        //printing the shoot
        if (ships2[y-1][x-1]==1){
            tab1[y-1][x-1]='+';
            ships2[y-1][x-1]=0;
            printf("\tHIT!!\n");
        }else{
            tab1[y-1][x-1]='-';
            printf("\tMISS!!\n");
        }
        //To continue entering coordinates
        for (y=0; y<8; y++){
            for (x=0; x<8; x++){
                sum+=ships2[y][x];
            }
        }
        
        if (sum==0)
            gamestatus=2;
        //Player2 turn
        else{
            sum=0;
            printTab();
            
            printf("Initial bet #%i\n\n", bet);
            printf("\t%s's turn\n\tCoordinate: ", name2);
            x=TransfX();
            y=Y();
            
            //Coords breaks the overlimit of the table
            while (x<1 || x>8 || y<1 || y>8){
                attackCoordError();
            }
            //Space has been chosen
            while(tab2[y-1][x-1]=='+' || tab2[y-1][x-1]=='-'){
                printf("\tRepeated target\n");
                x=TransfX();
                y=Y();  
                
                while (x<1 || x>8 || y<1 || y>8){
                    attackCoordError();
                }
            }
            system("cls");
            //printing the shoot
            if (ships1[y-1][x-1]==1){
                tab2[y-1][x-1]='+';
                ships1[y-1][x-1]=0;
                printf("\tHIT!!\n");
            }else{
                tab2[y-1][x-1]='-';
                printf("\tMISS!!\n");
            }
            //To continue entering coordinates
            for (y=0; y<8; y++){
                for (x=0; x<8; x++){
                    sum+=ships1[y][x];
                }
            }
        }
        if (sum==0)
            gamestatus=2;
    }

    ////////WINNER////////
    sum=0;
    for (y=0; y<8; y++){
        for (x=0; x<8; x++){
            sum+=ships1[y][x];
        }
    }
    system("cls");

    if (sum==0){
        printf("\n\n\n\t\t      %s LOSER :(\t\t\t      %s WINNER!!!\n\n\n",name1, name2);
        results();
    }else{
        printf("\n\n\n\t\t      %s WINNER!!!\t\t\t      %s LOSER :(\n\n\n",name1, name2);
        results();
    }
}

