#include<stdio.h>
#include<stdlib.h>

int x, y;
char matriz1[8][8], matriz2[8][8],tab1[8][8],tab2[8][8], nombre1[25],nombre2[25];

void fin(){
    printf("      Tablero %s\t\t\t      Ataques %s\n",nombre1,nombre1);
    printf("   A  B  C  D  E  F  G  H\t\t   A  B  C  D  E  F  G  H\n");
    for(y=0; y<8; y++){
        printf("%i  ", y+1);
        for(x=0; x<8; x++){
            printf("%c  ",matriz1[y][x]);
            if(x==7){
                printf("\t\t");
                printf("%i  ", y+1);
                for(x=0;x<8;x++){
                printf("%c  ",tab1[y][x]);
                }
            }
        }
        printf("\n");
    }
    printf("\n\n");
    printf("\n\n      Tablero %s\t\t\t      Ataques %s\n",nombre2,nombre2);
    printf("   A  B  C  D  E  F  G  H\t\t   A  B  C  D  E  F  G  H\n");
    for(y=0; y<8; y++){
        printf("%i  ", y+1);
        for(x=0; x<8; x++){
            printf("%c  ",matriz2[y][x]);
            if(x==7){
                printf("\t\t");
                printf("%i  ", y+1);
                for(x=0;x<8;x++){
                printf("%c  ",tab2[y][x]);
                }
            }
        }
        printf("\n");
    }
}

int position(int n, int c){
    printf("\n\tChoose a point on the grid.\n\tNote: ships will go down or to the right of this point.\n" );
    printf("\tPlayer: %s\n\tShip N.%i(boxes: %i)\n\n\tOrientacion: 1.Vertical\n\t\t     2.Horizontal\n\tRespuesta: ", nombre1,n,c);
    scanf("%i", &position);
    
    while(position<1 || position>2){
        printf("Introduzca una orientacion correcta\n");
        scanf("%i", &position);
    }
    return position;
}
void coordinates(int x, int y){
    printf("Enter the coordinates\n");
    x=letrax();
    y=letray();
            
    while(y<1 || y>8 || x<1 || x>8){
        printf("\nERROR Vuelva a introducir la coordenada\n");
        x=letrax();
        y=letray();
    }
    while(matriz1[y-1][x-1]=='X'){
        printf("\nYa se encuentra un barco ahi, vuelva a introducir la coordenada\n");
        x=letrax();
        y=letray();
        while(y>7 || y<1 || x<1 || x>8){
            printf("\nVuelva a introducir la coordenada\n");
            x=letrax();
            y=letray();
        }
    }
}

void men2(int n, int c){
    printf("\tJugador: %s\n\tBarco N.%i(%i casillas)\n\n\tOrientacion: 1.Vertical\n\t\t     2.Horizontal\n", nombre2,n,c);
}

void impretab(){
    printf("\n\t\t\t      Tablero %s\n",nombre1);
    printf("\n\t\t\t\tA  B  C  D  E  F  G  H\n");
    for(y=0; y<8; y++){
        printf("\t\t\t     %i  ", y+1);
        for(x=0; x<8; x++){
            printf("%c  ",tab1[y][x]);
        }
        printf("\n");
    }
    printf("\n\n");
    printf("\t\t\t      Tablero %s\n", nombre2);
    printf("\n\t\t\t\tA  B  C  D  E  F  G  H\n");
    for(y=0; y<8; y++){
        printf("\t\t\t     %i  ", y+1);
        for(x=0; x<8; x++){
            printf("%c  ",tab2[y][x]);
        }
        printf("\n");
    }
}

void impresion(char matriz[8][8]){
    printf("\n\n\n\t\t\t\tA  B  C  D  E  F  G  H\n");
    for(y=0; y<8; y++){
        printf("\t\t\t     %i  ", y+1);
        for(x=0; x<8; x++){
            printf("%c  ",matriz[y][x]);
        }
        printf("\n");
    }
    printf("\n");
}

int letray(){
    int res;
    scanf("%i", &res);
    return res;
}
int letrax(){
    char coord;
    int res;
    printf("\nCoordenada: ");
    //fflush(stdin);
    coord=getchar();
    if (coord=='A' || coord=='a')
        res=1;
    else if (coord=='B' || coord=='b')
        res=2;
    else if (coord=='C' || coord=='c')
        res=3;
    else if (coord=='D' || coord=='d')
        res=4;
    else if (coord=='E' || coord=='e')
        res=5;
    else if (coord=='F' || coord=='f')
        res=6;
    else if (coord=='G' || coord=='g')
        res=7;
    else if (coord=='H' || coord=='h')
        res=8;
    else
        res=9;
    return res;
}

void dataPlayer1(char nombre1[25]){
    int po,i,b1,b2,b3,barcos1[8][8],barcos2[8][8],res,sum,n,c;

    sum=0;
    n=1;
    
    //Barco1 P1
    b1=0;
    c=4;
    while(b1==0){
        impresion(matriz1);
        po = position(n, c);
    }
        if (po==1){
            coordinates(x,y);
            
            if(y<=5){
                for(i=0;i<4;i++){
                    matriz1[y-1][x-1]='X';
                    y++;
                    b1=1;
                }
                n++;
                system("cls");
            }else{
                system("cls");
                printf("No se puede colocar el barco ahi. ");
            }
        }
        else{
            coordinates(x,y);
        }
        if(x<=5){
            for(i=0;i<4;i++){
                matriz1[y-1][x-1]='X';
                x++;
                b1=1;
        }
        n++;
        system("cls");
        }
        else{
            system("cls");
            printf("No se puede colocar el barco ahi. ");
            }
            
    system("cls");
    system("cls");

    //Para el Barco 2P1
    b2=0;
    c=3;
    while(b2<=1){
        impresion(matriz1);
        po = position(n, c);
    }
        if (po==1){
            coordinates(x,y);
            i=0;
            
            while(i<3){
                if(matriz1[y-1][x-1]=='X'){
                    while(i>0){
                        y--;
                        matriz1[y-1][x-1]='.';
                        i--;
                    }
                    system("cls");
                    printf("El barco intercepta con otro. ");
                    i=4;
                }
                else{
                    matriz1[y-1][x-1]='X';
                    y++;
                    i++;
                }
                if (i==3){
                    b2++;
                    n++;
                    system("cls");
                }
            }
        }else{
            coordinates(x,y);
            i=0;
            while(i<3){
                if(matriz1[y-1][x-1]=='X'){
                    while(i>0){
                        x--;
                        matriz1[y-1][x-1]='.';
                        i--;
                    }
                    system("cls");
                    printf("El barco intercepta con otro. ");
                    i=4;
                }else{
                    matriz1[y-1][x-1]='X';
                    x++;
                    i++;
                }
                if(i==3){
                    b2++;
                    n++;
                    system("cls");
                }
            }
        }
    

    system("cls");

    //Para el Barco N3 P1
    b3=0;
    c=2;
    while(b3<=1){
        impresion(matriz1);
        po = position(n, c);
    }
        if (po==1){
            
            coordinates(x,y);
            
            i=0;
            while(i<2){
                if(matriz1[y-1][x-1]=='X'){
                    while(i>0){
                        y--;
                        matriz1[y-1][x-1]='.';
                        i--;
                    }
                    system("cls");
                    printf("El barco intercepta con otro. ");
                    i=3;
                }
                else{
                    matriz1[y-1][x-1]='X';
                    y++;
                    i++;
                }
                if (i==2){
                    b3++;
                    n++;
                    system("cls");
                }
            }
        }else{
           coordinates(x,y);
            i=0;
            while(i<2){
                if(matriz1[y-1][x-1]=='X'){
                    while(i>0){
                        x--;
                        matriz1[y-1][x-1]='.';
                        i--;
                    }
                    system("cls");
                    printf("El barco intercepta con otro. ");
                    i=3;
                }else{
                    matriz1[y-1][x-1]='X';
                    x++;
                    i++;
                }
                if (i==2){
                    b3++;
                    n++;
                    system("cls");
                }
            }
        }
    

    //Cargar matriz 1 y 0 de player1
    for(y=0; y<8; y++){
        for(x=0; x<8; x++){
            if (matriz1[y][x]=='X')
            barcos1[y][x]=1;
            else
            barcos1[y][x]=0;
        }
    }

    system("cls");

    //visualizacion de los barcos P1
    impresion(matriz1);
    printf("%s\n",nombre1);
    printf("\nPresione una tecla para continuar\n");
    getch();
    system("cls");

    n=1;
    
}
void dataPlayer2(char nombre2[25]){
    int po, o,i,b1,b2,b3,barcos1[8][8],barcos2[8][8],res,sum,n,c;
    sum=0;
    n=1;
    res=1;
    //Barco1 P2
    b1=0;
    c=4;
    while(b1==0){
        impresion(matriz2);
        po = position(n, c);
    }
        if (o==1){
            printf("Introduzca la coordenada de la esquina superior del barco\n");
            x=letrax();
            y=letray();
            while(y<1 || y>8 || x<1 || x>8){
                printf("Vuelva a introducir la coordenada\n");
                x=letrax();
                y=letray();
            }
            if(y<=5){
                for(i=0;i<4;i++){
                    matriz2[y-1][x-1]='X';
                    y++;
                    b1=1;
                }
                n++;
                system("cls");
            }else{
                system("cls");
                printf("No se puede colocar el barco ahi. ");
            }
        }else{
           coordinates(x,y);
            }
            if(x<=5){
                for(i=0;i<4;i++){
                    matriz2[y-1][x-1]='X';
                    x++;
                    b1=1;
                }
                n++;
                system("cls");
            }else{
                system("cls");
                printf("No se puede colocar el barco ahi. ");
            }
        
    

    system("cls");

    //Para el Barco 2P2
    b2=0;
    c=3;
    while(b2<=1){
        impresion(matriz2);
        po = position(n, c);
    }
        if (o==1){
            coordinates(x,y);
            i=0;
            while(i<3){
                if(matriz2[y-1][x-1]=='X'){
                    while(i>0){
                        y--;
                        matriz2[y-1][x-1]='.';
                        i--;
                    }
                    system("cls");
                    printf("El barco intercepta con otro. ");
                    i=4;
                }
                else{
                    matriz2[y-1][x-1]='X';
                    y++;
                    i++;
                }
                if (i==3){
                    b2++;
                    n++;
                    system("cls");
                }
            }
        }else{
            printf("Introduzca la coordenada de la esquina izquierda del barco\n");
            x=letrax();
            y=letray();
            while(x>6 || x<1 || y<1 || y>8){
                printf("\nVuelva a introducir la coordenada\n");
                x=letrax();
                y=letray();
            }
            while(matriz2[y-1][x-1]=='X'){
                printf("\nYa se encuentra un barco ahi, vuelva a introducir la coordenada\n");
                x=letrax();
                y=letray();
                while(x>6 || x<1 || y<1 || y>8){
                    printf("\nVuelva a introducir la coordenada\n");
                    x=letrax();
                    y=letray();
                }
            }
            i=0;
            while(i<3){
                if(matriz2[y-1][x-1]=='X'){
                    while(i>0){
                        x--;
                        matriz2[y-1][x-1]='.';
                        i--;
                    }
                    system("cls");
                    printf("El barco intercepta con otro. ");
                    i=4;
                }
                else{
                    matriz2[y-1][x-1]='X';
                    x++;
                    i++;
                }
                if(i==3){
                    b2++;
                    n++;
                    system("cls");
                }
            }
        }
    
    system("cls");

    //Para el Barco 3P2
    c=2;
    b3=0;
    while(b3<=1){
        impresion(matriz2);
        men2(n,c);
        //fflush(stdin);
        scanf("%i", &o);
        while(o<1 || o>2){
            printf("Introduzca una orientacion correcta\n");
            //fflush(stdin);
            scanf("%i", &o);
        }

        if (o==1){
            printf("Introduzca la coordenada de la esquina superior del barco\n");
            x=letrax();
            y=letray();
            while(y>7 || y<1 || x<1 || x>8){
                printf("\nVuelva a introducir la coordenada\n");
                x=letrax();
                y=letray();
            }
            while(matriz2[y-1][x-1]=='X'){
                printf("\nYa se encuentra un barco ahi, vuelva a introducir la coordenada\n");
                x=letrax();
                y=letray();
                while(y>7 || y<1 || x<1 || x>8){
                    printf("\nVuelva a introducir la coordenada\n");
                        x=letrax();
                        y=letray();
                }
            }
            i=0;
            while(i<2){
                if(matriz2[y-1][x-1]=='X'){
                    while(i>0){
                        y--;
                        matriz2[y-1][x-1]='.';
                        i--;
                    }
                    system("cls");
                    printf("El barco intercepta con otro. ");
                    i=3;
                }
                else{
                    matriz2[y-1][x-1]='X';
                    y++;
                    i++;
                }
                if (i==2){
                    b3++;
                    n++;
                    system("cls");
                }
            }
        }
        else{
           printf("Introduzca la coordenada de la esquina superior del barco\n");
            x=letrax();
            y=letray();
            while(x>7 || x<1 || y<1 || y>8){
                printf("\nVuelva a introducir la coordenada\n");
                x=letrax();
                y=letray();
            }
            while(matriz2[y-1][x-1]=='X'){
                printf("\nYa se encuentra un barco ahi, vuelva a introducir la coordenada\n");
                x=letrax();
                y=letray();
                while(x>7 || x<1 || y<1 || y>8){
                    printf("\nVuelva a introducir la coordenada\n");
                    x=letrax();
                    y=letray();
                }
            }
            i=0;
            while(i<2){
                if(matriz2[y-1][x-1]=='X'){
                    while(i>0){
                        x--;
                        matriz2[y-1][x-1]='.';
                        i--;
                    }
                    system("cls");
                    printf("El barco intercepta con otro. ");
                    i=3;
                }
                else{
                    matriz2[y-1][x-1]='X';
                    x++;
                    i++;
                }
                if (i==2){
                    b3++;
                    n++;
                    system("cls");
                }
            }
        }
    }

    //Cargar matriz 1 y 0 de player2
    for(y=0; y<8; y++){
        for(x=0; x<8; x++){
            if (matriz2[y][x]=='X')
                barcos2[y][x]=1;
            else
                barcos2[y][x]=0;
        }
    }

    system("cls");

    //visualizacion de los barcos P2
    impresion(matriz2);
    printf("%s\n", nombre2);
    printf("\nPresione una tecla para continuar\n");
    getch();
    system("cls");
}

void attack(char nombre1[25], char nombre2[25]){
    int o,i,b1,b2,b3,barcos1[8][8],barcos2[8][8],res,sum,n,c;
    sum=0;
    n=1;
    res=1;
    // Ataques
    while(res==1){
            sum=0;
            impretab();
            printf("\n\n\tTurno %s\n", nombre1);
            x=letrax();
            y=letray();
            while (x<1 || x>8 || y<1 || y>8){
                printf("Coordenada incorrecta\n");
                x=letrax();
                y=letray();
            }
            while(tab1[y-1][x-1]=='A' || tab1[y-1][x-1]=='F'){
                printf("\tYa has atacado ese objetivo\n");
                x=letrax();
                y=letray();
                while (x<1 || x>8 || y<1 || y>8){
                    printf("Coordenada incorrecta\n");
                    x=letrax();
                    y=letray();
                }
            }
            system("cls");
            if (barcos2[y-1][x-1]==1){
                tab1[y-1][x-1]='A';
                barcos2[y-1][x-1]=0;
                printf("\tAcertado\n");
            }
            else{
                tab1[y-1][x-1]='F';
                printf("\tFallado\n");
            }
            for (y=0; y<8; y++){
                for (x=0; x<8; x++){
                    sum+=barcos2[y][x];
                }
            }
        if (sum==0)
            res=2;
        else{
            sum=0;
            impretab();
            printf("\tTurno %s\n", nombre2);
            x=letrax();
            y=letray();
            while (x<1 || x>8 || y<1 || y>8){
                printf("Coordenada incorrecta\n");
                x=letrax();
                y=letray();
            }
            while(tab2[y-1][x-1]=='A' || tab2[y-1][x-1]=='F'){
                printf("\tYa has atacado ese objetivo\n");
                x=letrax();
                y=letray();
                while (x<1 || x>8 || y<1 || y>8){
                    printf("Coordenada incorrecta\n");
                    x=letrax();
                    y=letray();
                }
            }
            system("cls");
            if (barcos1[y-1][x-1]==1){
                tab2[y-1][x-1]='A';
                barcos1[y-1][x-1]=0;
                printf("\tAcertado\n");
            }
            else{
                tab2[y-1][x-1]='F';
                printf("\tFallado\n");
            }
            for (y=0; y<8; y++){
                for (x=0; x<8; x++){
                    sum+=barcos1[y][x];
                }
            }
        }
        if (sum==0)
            res=2;
    }
    
}
void winner(){
    int o,i,b1,b2,b3,barcos1[8][8],barcos2[8][8],res,sum,n,c;
    sum=0;
    n=1;
    res=1;
    //Para escojer el Ganador
    sum=0;
    for (y=0; y<8; y++){
        for (x=0; x<8; x++){
            sum+=barcos1[y][x];
        }
    }

    system("cls");

    if (sum==0){
        printf("\n\n\n\t\t\t\t\t%s GANA\n\n\n",nombre2);
        fin();
    }
    else{
        printf("\n\n\n\t\t\t\t\t%s GANA\n\n\n",nombre1);
        fin();
    }
}
void main(){

    for(y=0; y<8; y++){
        for(x=0; x<8; x++){
            matriz1[y][x]='-';
            matriz2[y][x]='-';
            tab1[y][x]='.';
            tab2[y][x]='.';
        }
    }

    printf("Jugador 1, introduzca su nombre\n");
    gets(nombre1);
    printf("Jugador 2, introduzca su nombre\n");
    gets(nombre2);
    system("cls");
    
    dataPlayer1(nombre1[25]);
    dataPlayer2(nombre2[25]);
    attack(nombre1[25],nombre2[25]);
    winner();
}
