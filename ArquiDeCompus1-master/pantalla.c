#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <termios.h>
#include <sys/ioctl.h>
int DELAY = 20;

extern void init_carrera();
extern void init_pool();

void panel();
void menu();
int login();
void autoFantastico();
int delayc(int);
void autoFantasticoAlg();
void carrera();
void pool();
void choque();
void tenis();
void tenis2();
void suicide();

const char led[] = {7,8,25,24,23,18,15,14};

unsigned char datosAuto[]= {
        0x80,
        0x40,
        0x20,
        0x10,
        0x08,
        0x04,
        0x02,
        0x01,
};

unsigned char datosChoque[] = {
        0x81,
        0x42,
        0x24,
        0x18,
        0x18,
        0x24,
        0x42,
        0x81,
};

unsigned char datosCarrera[] = {
        0x80,
        0x80,
        0x40,
        0x40,
        0x20,
        0x20,
        0x10,
        0x10,
        0x88,
        0x48,
        0x24,
        0x14,
        0x0A,
        0x06,
        0x03,
        0x01,
};

unsigned char datosTenis[] ={
        0x81,
        0xC1,
        0xA1,
        0x91,
        0x89,
        0x85,
        0x83,
        0x83,
        0x85,
        0x89,
        0x91,
        0xA1,
        0xC1,
};




unsigned char datosSuicide[]={
        0x80,
        0x40,
        0x80,
        0x40,
        0x20,
        0x40,
        0x80,
        0x40,
        0x20,
        0x10,
        0x20,
        0x40,
        0x80,
        0x40,
        0x20,
        0x10,
        0x08,
        0x10,
        0x20,
        0x40,
        0x80,
        0x40,
        0x20,
        0x10,
        0x08,
        0x04,
        0x08,
        0x10,
        0x20,
        0x40,
        0x80,
        0x40,
        0x20,
        0x10,
        0x08,
        0x04,
        0x02,
        0x04,
        0x08,
        0x10,
        0x20,
        0x40,
        0x80,
        0x40,
        0x20,
        0x10,
        0x08,
        0x04,
        0x02,
        0x01,
        0x02,
        0x04,
        0x08,
        0x10,
        0x20,
        0x40,
        0x80,
};

char password[6];

int main() {
    strcpy(password, "kevin");


    if(login() == 0){
        printf("\nContraseña correcta\n");
        panel();
            return 0;
    }else{
        return 0;
    }
    return 0;
}

int ejec;
void panel() {
    printf("\n/////////////////////////////////////////////////////////////////////////////\n");
    printf("\nBienvenidos al proyecto de Arquitectura de Software I por Murature y Schröder \n");
    printf("\n/////////////////////////////////////////////////////////////////////////////\n");
    menu();
}

void menu(){
    ejec=1;
    do{
            char n;
        printf("\n1- Auto fantastico\n");
        printf("\n2- El choque\n");
        printf("\n3- Pool\n");
        printf("\n4- Tenis\n");
        printf("\n5- Carrera\n");
        printf("\n6- Suicida\n");
        printf("\n0- Salir\n");

            printf("\n/////////////////////////////////////////////////////////////////////////////\n");

            n = getchar();
            initscr();
            clear();
            switch(n){
            case'0':
                exit(-1);
            case '1':
                printf("Auto fantastico");
                printf("\nPresione f para salir\n");
                do{
                    autoFantasticoAlg();
                }while (ejec);
            case '2':
                clear();
                printf("El choque");
                printf("\nPresione f para salir\n");
                do{
                    choque();
                }while(ejec);
            case '3':
                clear();
                printf("Pool");
                printf("\nPresione f para salir\n");
                do{
                    init_pool();
                }while(ejec);
            case '4':
                clearenv();
                printf("Tenis");
                printf("\nPresione f para salir\n");
                do{
                    tenis();
                }while(ejec);
            case '5':
                clearenv();
                printf("Carrera");
                printf("\nPresione f para salir\n");
                do{
                    init_carrera();
                }while(ejec);
            case '6':
                clear();
                printf("Suicida");
                printf("\nPresione f para salir\n");
                do{
                    suicide();
                }while(ejec);
            default:
            break;
            }
        }while(TRUE);
}


int login(){
    initscr();
    noecho();
    int error = 0;
    char c;
    char ingreso[5];
    do {
        printf("Ingrese su password de 5 dígitos:\n");

        for (int i = 0; i < 5; i++) {
            c = getch();
            ingreso[i] = c;
            printf("*");
        }
        if(strcmp(password, ingreso) != 0){
            error++;
            printf("\n Contraseña Incorrecta \n");
        }
    }while(error < 3 && strcmp(password, ingreso) != 0);
    echo();
    endwin();
    return strcmp(password, ingreso);

}
void output(unsigned char b){
    initscr();
    for(int i = 8; i > 0; i--){
        if((b&1) == 1){
            printf("*");
        }else printf("_");
        b = b >> 1;
    }
    printf("\r");
    fflush(stdout);
    endwin();
}


int tomadelay(int n){
    if (DELAY<44) {
        if (n == 0) {
            DELAY = DELAY + 4;
            return DELAY;
        }
    }
    if (DELAY>4)
        if (n==1){
            DELAY= DELAY-4;
            return  DELAY;
        }
    return DELAY;
}


int delayc(int a) {
    initscr();
    noecho();
    cbreak();
    int c;
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    c = getch();
    nocbreak();
    if(c == KEY_UP){
        a = tomadelay(1);
    }
    if(c==KEY_DOWN){
        a = tomadelay(0);
    }
    if (c==102){ //finaliza con f, cbreak no me deja con intro
        echo();
        endwin();
        ejec=0;
        menu();
    }
    for (int j = 0; j < a; j++) {
        unsigned int i = 0x4fffff; //raspberry 0x3fffff
        while (i)i--;
    }
    echo();
    endwin();
    return  a;
}




void autoFantasticoAlg() {
    output(1);
    DELAY = delayc(DELAY);
    int i = 2;
    do {
        output(i);
        DELAY = delayc(DELAY);
        i *= 2;
    } while (i <= 64);
    do {
        output(i);
        DELAY = delayc(DELAY);
        i /= 2;
    } while (i > 0);
}

void  pool(){
    int i = 128;
    do{
        output(i+16);
        DELAY = delayc(DELAY);
        if (i==32)
            i/=2;
        i /=2;
    }while (i>0);
}

void autoFantastico() {
    for(int i = 0; i < 8; i++){
        output(datosAuto[i]);
        DELAY = delayc(DELAY);
    }
    for(int i = 7; i != 0; i--){
        output(datosAuto[i]);
        DELAY = delayc(DELAY);
    }
}

void carrera(){
    for(int i = 0; i < 16; i++){
        output(datosCarrera[i]);
        DELAY = delayc(DELAY);
    }
}
void choque(){
    for(int i = 0; i < 8; i++){
        output(datosChoque[i]);
        DELAY = delayc(DELAY);
    }
}

void tenis(){
    for(int i = 0; i < 13; i++){
        output(datosTenis[i]);
        DELAY = delayc(DELAY);
    }
}

void tenis2(){
    int i = 64;
    do {
        output(i + 129);
        DELAY = delayc(DELAY);
        i/=2;
    }while(i>2);
    do{
        output(i+129);
        DELAY = delayc(DELAY);
        i*=2;
    }while (i<65);
}

void suicide(){
    for(int i = 0; i < 57 ; i++){
        output(datosSuicide[i]);
        DELAY = delayc(DELAY);
    }
}


