#include<windows.h>
#include<math.h>
#include <stdlib.h>
#include <stdio.h>
#define pi 3.14159265358979323846

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char ProgName[]="Лабораторна робота 4 (2 формула)";


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
            double coefficient = 1 - 1*0.005 - 4*0.005 - 0.27;
            double** A = mulmr(coefficient, T, 11, 11);
            double B[11][11];
            printf("Matrix for oriented graph\n");
            for (int i = 0; i < 11; i++) {
                for (int j = 0; j < 11; j++) {
                    printf("%g ", A[i][j]);
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
                            Arc(hdc, nx[j], ny[j], nx[j]-40, ny[j]-40, nx[j], ny[j], nx[j], ny[j]);
                            arrow(1.56, nx[j], ny[j]);
                            continue;
                        }
                        if  ((A[j][i]==1) && (i>j)) {
                            nx0=(nx[i]+nx[j])/2 - (ny[i]-ny[j])/(scaler*0.6);
                            ny0=(ny[i]+ny[j])/2 + (nx[i]-nx[j])/(scaler*0.6);
                            R=sqrt(pow(nx[i]-nx0, 2) + pow(ny[i]-ny0, 2));
                            Arc(hdc, nx0-R, ny0-R, nx0+R, ny0+R, nx[i], ny[i], nx[j], ny[j]);
                            arrow(atan2(ny[j]-ny[i],nx[j]-nx[i])-atan2(sqrt(pow(nx[j]-nx[i],2)+pow(ny[j]-ny[i],2)),R)/2,nx[j],ny[j]);
                            continue;
                        }
                        if (((i==0) && (j==10))||((i==10) && (j==0))||(i==j+1)||(i==j-1)) {
                            MoveToEx(hdc, nx[i], ny[i], NULL);
                            LineTo(hdc, nx[j], ny[j]);
                            arrow(atan2(ny[j]-ny[i],nx[j]-nx[i]),nx[j],ny[j]);
                            continue;
                        }

                        if ((i < 5) && ((j < 5))){
                            nx0=(nx[i]+nx[j])/2 + (ny[i]-ny[j])/(scaler);
                            ny0=(ny[i]+ny[j])/2 - (nx[i]-nx[j])/(scaler);
                            R=sqrt(pow(nx[i]-nx0, 2) + pow(ny[i]-ny0, 2));
                            Arc(hdc, nx0-R, ny0-R, nx0+R, ny0+R, nx[j], ny[j], nx[i], ny[i]);
                            arrow(atan2(ny[j]-ny[i],nx[j]-nx[i])+atan2(sqrt(pow(nx[j]-nx[i],2)+pow(ny[j]-ny[i],2)),R)/2,nx[j],ny[j]);
                            continue;
                        }
                        if ((i>=4) &&(i < 9)&& (j>=4) &&(j < 9)) {
                            nx0=(nx[i]+nx[j])/2 + (ny[i]-ny[j])/(scaler);
                            ny0=(ny[i]+ny[j])/2 - (nx[i]-nx[j])/(scaler);
                            R=sqrt(pow(nx[i]-nx0, 2) + pow(ny[i]-ny0, 2));
                            Arc(hdc, nx0-R, ny0-R, nx0+R, ny0+R, nx[j], ny[j], nx[i], ny[i]);
                            arrow(atan2(ny[j]-ny[i],nx[j]-nx[i])+atan2(sqrt(pow(nx[j]-nx[i],2)+pow(ny[j]-ny[i],2)),R)/2,nx[j],ny[j]);
                            continue;
                        }
                        if (((i>=8) || (i==0)) && ((j>=8)||(j==0))) {
                            nx0=(nx[i]+nx[j])/2 + (ny[i]-ny[j])/(scaler);
                            ny0=(ny[i]+ny[j])/2 - (nx[i]-nx[j])/(scaler);
                            R=sqrt(pow(nx[i]-nx0, 2) + pow(ny[i]-ny0, 2));
                            Arc(hdc, nx0-R, ny0-R, nx0+R, ny0+R, nx[j], ny[j], nx[i], ny[i]);
                            arrow(atan2(ny[j]-ny[i],nx[j]-nx[i])+atan2(sqrt(pow(nx[j]-nx[i],2)+pow(ny[j]-ny[i],2)),R)/2,nx[j],ny[j]);
                            continue;
                        }
                        MoveToEx(hdc, nx[i], ny[i], NULL);
                        LineTo(hdc, nx[j], ny[j]);
                        arrow(atan2(ny[j]-ny[i],nx[j]-nx[i]),nx[j],ny[j]);
                    }
                }
            }
            SelectObject(hdc, BPen);
            TextOut(hdc, num, num,  "Напрямлений", 11);

            for(i=0;i < 11;i++){
                Ellipse(hdc, nx[i]-dx,ny[i]-dy,nx[i]+dx,ny[i]+dy);
                TextOut(hdc, nx[i]-dtx,ny[i]-dy/2,  nn[i], 2);
            }

            //граф конденсації
            void drawgraph(HDC hdc, int startA[11][11], int components[11][11]) {

            int drawVert[11] = { 0,0,0,0,0,0,0,0,0,0,0 };
            char *nn[20] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20"};
            int dtx = 5, radius = 16, end, xDif, yDif, dx, dy, koef;

            for (int i = 0;i < 11; i++) {
                for (int j = 0;j < 11; j++) {
                    if (components[i][j] == 0) continue;
                    for (int count = 0;count < 11;count++) {
                        if (startA[j][count]) {
                            for (int count2 = 0; count2 < 11;count2++) {
                                if (components[count2][count]) {
                                    MoveToEx(hdc, nx[i]+len, ny[i]+len, NULL);
                                    LineTo(hdc, nx[count2]+len, ny[count2]+len);
                                    xDif = nx[i] - nx[count2];
                                    yDif = ny[i] - ny[count2];
                                    if (xDif == 0 && yDif == 0) {
                                        dx = 0;
                                        dy = 0;
                                    } else {
                                        koef = sqrt(xDif * xDif + yDif * yDif) / radius;
                                        dx = xDif / koef;
                                        dy = yDif / koef;
                                        arrow(1.56, nx[j]+len, ny[j]+len);
                                    }
                                }
                            }
                        }
                    }
                    drawVert[i] = 1;
                }
            }
            for (int i = 0;i < 11;i++) {
                if (drawVert[i]) {
                    Ellipse(hdc, nx[i]+1.7*len - radius, ny[i]+(-2)*num - radius, nx[i]+1.7*len + radius, ny[i]+(-2)*num + radius);
                    TextOut(hdc, nx[i]+1.7*len - dtx, ny[i]+(-2)*num - 8, nn[i], 1);
                }
            }
            TextOut(hdc, num+(len+2*num), num,  "Граф конденсації", 16);
        }

        //матриця досяжності, компоненти, матриця зв'язності, граф конденсації
            double **Matrix(double **A, int n){
                int reachA[n][n];
                int transA[n][n];

                int num, counter = 1, countery = 1;
                char text[11];
                int newA[n][n];
                int usedVerticles[11] = { 0,0,0,0,0,0,0,0,0,0,0 };

                int components[11][11] = {
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
                };

                for (int i = 0; i < n; i++)
                    for (int j = 0; j < n; j++)
                        reachA[i][j] = A[i][j];
                for (int k = 0; k < n; k++) {
                    for (int i = 0; i < n; i++) {
                        for (int j = 0; j < n; j++) {
                            reachA[i][j] = reachA[i][j] || (reachA[i][k] && reachA[k][j]);
                        }
                    }
                }
                printf("Reached matrix \n");
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if(i == j)
                            printf("1 ");
                        else
                            printf ("%d ", reachA[i][j]);
                    }
                    printf("\n");
                }

                printf("Connected matrix \n");
                double **matrix[11][11];
                for (int i = 0; i < n; i++){
                    for (int j = 0; j < n; j++) {
                        transA[i][j] = reachA[j][i];
                        if ((transA[i][j] == 1) && (reachA[i][j] == 1)) matrix[i][j] = 1;
                        if ((transA[i][j] == 0) && (reachA[i][j] == 0)) matrix[i][j] = 0;
                        if ((transA[i][j] == 0) && (reachA[i][j] == 1)) matrix[i][j] = 0;
                        if ((transA[i][j] == 1) && (reachA[i][j] == 0)) matrix[i][j] = 1;
                        printf ("%d ", matrix[i][j]);
                    }
                    printf("\n");
                }

           //для графа конденсації
            for (int count = 0; count < n; count++) {
                counter = 1;
            for (int i = 0; i < n; i++) {
                if (usedVerticles[i] == 1) continue;
                for (int j = 0; j < n; j++) {
                    if ( transA[count][j] !=  transA[i][j]) break;
                    if (j == n - 1) {
                        usedVerticles[i] = 1;
                        components[countery][i] = 1;
                        counter++;
                    }
                }
            }
        }
        printf("Components:\n ");
        int **component[]={};
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i]==matrix[j]) {
                component[i]=i+1;
                printf("%d\n ", component[i]);
                }
            }
            }
        drawgraph(hdc, reachA, components);
        }
            Matrix(A,11);

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
