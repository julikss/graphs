#include<windows.h>
#include<math.h>
#include <stdlib.h>
#include <stdio.h>
#define pi 3.14159265358979323846

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char ProgName[]="Лабораторна робота 4(1 формула)";


double** randm(int rows, int cols) {
                double** matrix = (double**)malloc(rows * sizeof(double*));

                for (int i = 0; i < rows; i++)
                    matrix[i] = (double*)malloc(cols * sizeof(double));

                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        matrix[i][j] =  2.0 * rand()/RAND_MAX;
                    }
                }
                return matrix;
    }

double** mulmr(double coef, double **matrix, int rows, int cols) {
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        matrix[i][j] = matrix[i][j] * coef;
                        if(matrix[i][j] > 1.0) {
                            matrix[i][j] = 1;
                        } else matrix[i][j] = 0;
                        }
                }
                return matrix;
    }

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hWnd;
    MSG lpMsg;
    WNDCLASS w;
    w.lpszClassName=ProgName;
    w.hInstance=hInstance;
    w.lpfnWndProc=WndProc;
    w.hCursor=LoadCursor(NULL, IDC_ARROW);
    w.hIcon=0;
    w.lpszMenuName=0;
    w.hbrBackground = LTGRAY_BRUSH;
    w.style=CS_HREDRAW|CS_VREDRAW;
    w.cbClsExtra=0;
    w.cbWndExtra=0;

    if(!RegisterClass(&w))
        return 0;
    hWnd=CreateWindow(ProgName,
        "ЛР 4. Виконала Ю.Д. Легенька",
        WS_OVERLAPPEDWINDOW,
        200,
        20,
        1340,
        900,
        (HWND)NULL,
        (HMENU)NULL,
        (HINSTANCE)hInstance,
        (HINSTANCE)NULL);

    ShowWindow(hWnd, nCmdShow);

    while(GetMessage(&lpMsg, hWnd, 0, 0)) {
            TranslateMessage(&lpMsg);
            DispatchMessage(&lpMsg);
        }
    return(lpMsg.wParam);
    }

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
    {
    HDC hdc;
    PAINTSTRUCT ps;

    void arrow(float fi, int px,int py){
            px=px-16*cos(fi);
            py=py-16*sin(fi);
            int lx,ly,rx,ry;
            lx = px-15*cos(fi+0.3);
            rx = px-15*cos(fi-0.3);
            ly = py-15*sin(fi+0.3);
            ry = py-15*sin(fi-0.3);
            MoveToEx(hdc, lx, ly, NULL);
            LineTo(hdc, px, py);
            LineTo(hdc, rx, ry);
      }

    switch(messg){
        case WM_PAINT :
            hdc=BeginPaint(hWnd, &ps);

            char *nn[20] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20"};
            int nx[11] = {};
            int ny[11] = {};
            int num = 50 ;
            int len = 400;

            Rectangle(hdc, num/2, num/2, 2*len+5*num, len+num-10);

            for(int i = 0; i < 11; i++) {
                if(i == 0) {
                    nx[i] = num;
                    ny[i] = num + sqrt(3)*len/2;
                } else if(i < 5) {
                    nx[i] = nx[i - 1] + len/4*cos(pi/3);
                    ny[i] = ny[i - 1] - len/4*sin(pi/3);
                } else if(i < 9) {
                    nx[i] = nx[i - 1] + len/4*cos(pi/3);
                    ny[i] = ny[i - 1] + len/4*sin(pi/3);
                } else {
                    nx[i] = nx[i - 1] - len/3;
                    ny[i] = ny[i - 1];
                }
            }
            int i, dx = 16, dy = 16, dtx = 5;
            HPEN BPen = CreatePen(PS_SOLID, 2, RGB(50, 0, 255));
            HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

            srand(0414);
            double** T = randm(11, 11);
            double coefficient = 1 - 1*0.01 - 4*0.01 - 0.3;
            double** A = mulmr(coefficient, T, 11, 11);
            double B[11][11];
            printf("Matrix for oriented graph\n");
            for (int i = 0; i < 11; i++) {
                for (int j = 0; j < 11; j++) {
                    printf("%g ", A[i][j]);
                }
                printf("\n");
            }
            printf("Matrix for non-oriented graph\n");
            for (int i = 0; i < 11; i++) {
                for (int j = 0; j < 11; j++) {
                    if (j <i) {
                        B[i][j] =  A[j][i];
                    }
                    else {
                        B[i][j] =  A[i][j];
                    }
                    printf("%g ", B[i][j]);
                }
                printf("\n");
            }

            int scaler = 1.1;
            int nx0, ny0, R;
            SelectObject(hdc, KPen);

            for (int i = 0; i < 11; i++){
                for (int j = 0; j < 11; j++){
                    if (A[i][j] == 1){
                        if (i == j){
                            Arc(hdc, nx[j], ny[j], nx[j]-40, ny[j]-40, nx[j], ny[j], nx[j], ny[j]); //напрямлений
                            arrow(1.56, nx[j], ny[j]);
                            Arc(hdc, nx[j]+(len+2*num), ny[j], nx[j]+(len+2*num)-40, ny[j]-40, nx[j]+(len+2*num), ny[j], nx[j]+(len+2*num), ny[j]);//ненапрямлений із зсувом по х
                            continue;
                        }
                        if  ((A[j][i]==1) && (i>j)) {
                            nx0=(nx[i]+nx[j])/2 - (ny[i]-ny[j])/(scaler*0.6); //тут тільки напрямлений
                            ny0=(ny[i]+ny[j])/2 + (nx[i]-nx[j])/(scaler*0.6);
                            R=sqrt(pow(nx[i]-nx0, 2) + pow(ny[i]-ny0, 2));
                            Arc(hdc, nx0-R, ny0-R, nx0+R, ny0+R, nx[i], ny[i], nx[j], ny[j]);
                            arrow(atan2(ny[j]-ny[i],nx[j]-nx[i])-atan2(sqrt(pow(nx[j]-nx[i],2)+pow(ny[j]-ny[i],2)),R)/2,nx[j],ny[j]);
                            continue;
                        }
                        if (((i==0) && (j==10))||((i==10) && (j==0))||(i==j+1)||(i==j-1)) {
                            MoveToEx(hdc, nx[i], ny[i], NULL);//напрямлений
                            LineTo(hdc, nx[j], ny[j]);
                            arrow(atan2(ny[j]-ny[i],nx[j]-nx[i]),nx[j],ny[j]);
                            if (j >= i) {
                                MoveToEx(hdc, nx[i]+(len+2*num), ny[i], NULL);//ненапрямлений із зсувом по х
                                LineTo(hdc, nx[j]+(len+2*num), ny[j]);
                            }
                            continue;
                        }

                        if ((i < 5) && ((j < 5))){
                            nx0=(nx[i]+nx[j])/2 + (ny[i]-ny[j])/(scaler);
                            ny0=(ny[i]+ny[j])/2 - (nx[i]-nx[j])/(scaler);
                            R=sqrt(pow(nx[i]-nx0, 2) + pow(ny[i]-ny0, 2));
                            Arc(hdc, nx0-R, ny0-R, nx0+R, ny0+R, nx[j], ny[j], nx[i], ny[i]);//напрямлений
                            arrow(atan2(ny[j]-ny[i],nx[j]-nx[i])+atan2(sqrt(pow(nx[j]-nx[i],2)+pow(ny[j]-ny[i],2)),R)/2,nx[j],ny[j]);
                            if (j >= i) Arc(hdc, nx0+(len+2*num)-R, ny0-R, nx0+(len+2*num)+R, ny0+R, nx[j]+(len+2*num), ny[j], nx[i]+(len+2*num), ny[i]);//непапрямлений із зсувом
                            continue;
                        }
                        if ((i>=4) &&(i < 9)&& (j>=4) &&(j < 9)) {
                            nx0=(nx[i]+nx[j])/2 + (ny[i]-ny[j])/(scaler);
                            ny0=(ny[i]+ny[j])/2 - (nx[i]-nx[j])/(scaler);
                            R=sqrt(pow(nx[i]-nx0, 2) + pow(ny[i]-ny0, 2));
                            Arc(hdc, nx0-R, ny0-R, nx0+R, ny0+R, nx[j], ny[j], nx[i], ny[i]);//напрямлений
                            arrow(atan2(ny[j]-ny[i],nx[j]-nx[i])+atan2(sqrt(pow(nx[j]-nx[i],2)+pow(ny[j]-ny[i],2)),R)/2,nx[j],ny[j]);
                            if (j >= i) Arc(hdc, nx0+(len+2*num)-R, ny0-R, nx0+(len+2*num)+R, ny0+R, nx[j]+(len+2*num), ny[j], nx[i]+(len+2*num), ny[i]);//ненапрямлений
                            continue;
                        }
                        if (((i>=8) || (i==0)) && ((j>=8)||(j==0))) {
                            nx0=(nx[i]+nx[j])/2 + (ny[i]-ny[j])/(scaler);
                            ny0=(ny[i]+ny[j])/2 - (nx[i]-nx[j])/(scaler);
                            R=sqrt(pow(nx[i]-nx0, 2) + pow(ny[i]-ny0, 2));
                            Arc(hdc, nx0-R, ny0-R, nx0+R, ny0+R, nx[j], ny[j], nx[i], ny[i]);//напрямлений
                            arrow(atan2(ny[j]-ny[i],nx[j]-nx[i])+atan2(sqrt(pow(nx[j]-nx[i],2)+pow(ny[j]-ny[i],2)),R)/2,nx[j],ny[j]);
                            if (j >= i) Arc(hdc, nx0+(len+2*num)-R, ny0-R, nx0+(len+2*num)+R, ny0+R, nx[j]+(len+2*num), ny[j], nx[i]+(len+2*num), ny[i]);//ненапрямлений
                            continue;
                        }
                        MoveToEx(hdc, nx[i], ny[i], NULL);//напрямлений
                        LineTo(hdc, nx[j], ny[j]);
                        arrow(atan2(ny[j]-ny[i],nx[j]-nx[i]),nx[j],ny[j]);
                        if (j >= i) {
                            MoveToEx(hdc, nx[i]+(len+2*num), ny[i], NULL);//ненапрямлений
                            LineTo(hdc, nx[j]+(len+2*num), ny[j]);
                        }
                    }
                }
            }
            SelectObject(hdc, BPen);
            TextOut(hdc, num, num,  "Напрямлений", 11);
            TextOut(hdc, num+(len+2*num), num,  "Ненапрямлений", 13);

            for (int k=0; k<2;k++){
                for(i=0;i < 11;i++){
                    Ellipse(hdc, nx[i]+(len+2*num)*k-dx,ny[i]-dy,nx[i]+(len+2*num)*k+dx,ny[i]+dy);
                    TextOut(hdc, nx[i]+(len+2*num)*k-dtx,ny[i]-dy/2,  nn[i], 2);
                }
            }

            //степені
            int deg[11]={0,0,0,0,0,0,0,0,0,0,0}, degpl[11]={0,0,0,0,0,0,0,0,0,0,0}, degmi[11]={0,0,0,0,0,0,0,0,0,0,0};
            char text[14];
            for(i=0;i < 11;i++){
                for(int j=0;j < 11;j++){
                    degpl[i]+=A[i][j];
                    sprintf_s(text, 12, "deg(+)%d= %d", i+1, degpl[i]);
                    TextOutA(hdc, nx[i]+20-dtx,ny[i]+20-dy/2, text, 12);
                    degmi[i]+=A[j][i];
                    sprintf_s(text, 12, "deg(-)%d= %d", i+1, degmi[i]);
                    TextOutA(hdc, nx[i]+20-dtx,ny[i]+35-dy/2, text, 12);
                }
            }
            for(i=0;i < 11;i++){
                for(int j=0;j < 11;j++){
                    if (i==j) {
                        deg[i]+=2*B[i][j];
                    }
                    else {
                        deg[i]+=B[i][j];
                    }
                    sprintf_s(text, 9, "deg%d= %d", i+1, deg[i]);
                    TextOutA(hdc, nx[i]+20+(len+2*num)-dtx,ny[i]+20-dy/2, text, 9);
                }
            }

            //Однорідність, ізольовані та висячі вершини
            char flag[13]=" Однорідний ";
            for(i=0;i < 11;i++){
                if (i!=0 && deg[i]!=deg[i-1]) strcpy(flag, "Hеоднорідний");
                if (degpl[i]+degmi[i]==0) TextOutA(hdc, nx[i]+20-dtx,ny[i]+50-dy/2, "ізол.", 5);//ізольованість вершин напрямл.
                if (degpl[i]+degmi[i]==1) TextOutA(hdc, nx[i]+20-dtx,ny[i]+50-dy/2, "вис.", 4);//висячі вершини напрямл.
                if (deg[i]==0) TextOutA(hdc, nx[i]+20+(len+2*num)-dtx,ny[i]+35-dy/2, "ізол.", 5);//ізольованість вершин ненапрямл.
                if (deg[i]==1) TextOutA(hdc, nx[i]+20+(len+2*num)-dtx,ny[i]+35-dy/2, "вис.", 4);//висячі вершини ненапрямл.
            }
            TextOut(hdc, num+(len+2*num), num+20, flag, 13);

            double sqA[11][11]; //шлях довжиною 2
            TextOut(hdc, num/2, num+len, "Шл. довж. 2:", 12);
            int xt=num/2+90, yt=num+len;
            for(i=0;i < 11;i++){
                for(int j=0;j < 11;j++){
                    sqA[i][j]=0;
                    for(int k=0;k < 11;k++){
                        sqA[i][j]=sqA[i][j]+A[i][k]*A[k][j];
                    }
                    if (sqA[i][j]>0) {
                            sqA[i][j]=1;
                            for(int k=0;k < 11;k++){
                                if (A[i][k]==1 && A[k][j]==1) {
                                    memset(text,0,9);
                                    sprintf_s(text, 9, "%d,%d,%d ", i+1, k+1, j+1);
                                    TextOutA(hdc, xt-dtx,yt, text, 9);
                                    xt=xt+60;
                                }
                            }
                    }
                }
                xt=num/2+90;
                yt=yt+15;
            }

            double cubA[11][11]; //шлях довжиною 3
            TextOut(hdc, num/2, yt+10, "Шл. довж. 3:", 12);
            xt=num/2+90; yt=yt+10;
            for(i=0;i < 11;i++){
                for(int j=0;j < 11;j++){
                    cubA[i][j]=0;
                    for(int k=0;k < 11;k++){
                        cubA[i][j]=cubA[i][j]+sqA[i][k]*A[k][j];
                    }
                    if (cubA[i][j]>0) {
                        for(int k=0;k < 11;k++){
                            if (sqA[i][k]==1 && A[k][j]==1) {
                                for(int m=0;m < 11;m++){
                                    if (A[i][m]==1 && A[m][k]==1) {
                                        cubA[i][j]=1;
                                        memset(text,0,12);
                                        sprintf_s(text, 12, "%d,%d,%d,%d ", i+1, m+1, k+1, j+1);
                                        TextOutA(hdc, xt-dtx,yt, text, 12);
                                        xt=xt+65;
                                    }
                                }

                            }
                        }
                    }
                }
                xt=num/2+90;
                yt=yt+15;
            }

            EndPaint(hWnd, &ps);

            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return(DefWindowProc(hWnd, messg, wParam, lParam));
    }
    return 0;
}
