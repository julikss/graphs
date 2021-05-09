#include<windows.h>
#include<math.h>
#include <stdlib.h>
#include <stdio.h>
#include<conio.h>
#define pi 3.14159265358979323846

int *p[11]; int spos = 0; int rpos = 0; int *stack[11]; int tos=0; int typeALG;  char text[9];
int graphTree[11][11] =  {
        { 0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0,0 },
    };

double** randm(int rows, int cols){
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

double** mulmr(double coef, double **matrix, int rows, int cols){
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

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

char ProgName[]="Лабараторна робота 5";


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
        "ЛР 5. Виконала Легенька Ю.Д.",
        WS_OVERLAPPEDWINDOW,
        400,
        100,
        840,
        800,
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

    void drawtree(HDC hdc, int i, int j, int *nx, int *ny) {
        int scaler = 1.1;
        int nx0, ny0, R;
        if (i == j){
           Arc(hdc, nx[j], ny[j], nx[j]-40, ny[j]-40, nx[j], ny[j], nx[j], ny[j]);
           arrow(1.56, nx[j], ny[j]);
           return;
        }
        if (i>j) {
           nx0=(nx[i]+nx[j])/2 - (ny[i]-ny[j])/(scaler*0.6);
           ny0=(ny[i]+ny[j])/2 + (nx[i]-nx[j])/(scaler*0.6);
           R=sqrt(pow(nx[i]-nx0, 2) + pow(ny[i]-ny0, 2));
           Arc(hdc, nx0-R, ny0-R, nx0+R, ny0+R, nx[i], ny[i], nx[j], ny[j]);
           arrow(atan2(ny[j]-ny[i],nx[j]-nx[i])-atan2(sqrt(pow(nx[j]-nx[i],2)+pow(ny[j]-ny[i],2)),R)/2,nx[j],ny[j]);
           return;
        }
        if (((i==0) && (j==10))||((i==10) && (j==0))||(i==j+1)||(i==j-1)) {
           MoveToEx(hdc, nx[i], ny[i], NULL);
           LineTo(hdc, nx[j], ny[j]);
           arrow(atan2(ny[j]-ny[i],nx[j]-nx[i]),nx[j],ny[j]);
           return;
        }
        if ((i < 5) && ((j < 5))){
           nx0=(nx[i]+nx[j])/2 + (ny[i]-ny[j])/(scaler);
           ny0=(ny[i]+ny[j])/2 - (nx[i]-nx[j])/(scaler);
           R=sqrt(pow(nx[i]-nx0, 2) + pow(ny[i]-ny0, 2));
           Arc(hdc, nx0-R, ny0-R, nx0+R, ny0+R, nx[j], ny[j], nx[i], ny[i]);
           arrow(atan2(ny[j]-ny[i],nx[j]-nx[i])+atan2(sqrt(pow(nx[j]-nx[i],2)+pow(ny[j]-ny[i],2)),R)/2,nx[j],ny[j]);
           return;
       }
       if ((i>=4) &&(i < 9)&& (j>=4) &&(j < 9)) {
          nx0=(nx[i]+nx[j])/2 + (ny[i]-ny[j])/(scaler);
          ny0=(ny[i]+ny[j])/2 - (nx[i]-nx[j])/(scaler);
          R=sqrt(pow(nx[i]-nx0, 2) + pow(ny[i]-ny0, 2));
          Arc(hdc, nx0-R, ny0-R, nx0+R, ny0+R, nx[j], ny[j], nx[i], ny[i]);
          arrow(atan2(ny[j]-ny[i],nx[j]-nx[i])+atan2(sqrt(pow(nx[j]-nx[i],2)+pow(ny[j]-ny[i],2)),R)/2,nx[j],ny[j]);
          return;
      }
      if (((i>=8) || (i==0)) && ((j>=8)||(j==0))) {
          nx0=(nx[i]+nx[j])/2 + (ny[i]-ny[j])/(scaler);
          ny0=(ny[i]+ny[j])/2 - (nx[i]-nx[j])/(scaler);
          R=sqrt(pow(nx[i]-nx0, 2) + pow(ny[i]-ny0, 2));
          Arc(hdc, nx0-R, ny0-R, nx0+R, ny0+R, nx[j], ny[j], nx[i], ny[i]);
          arrow(atan2(ny[j]-ny[i],nx[j]-nx[i])+atan2(sqrt(pow(nx[j]-nx[i],2)+pow(ny[j]-ny[i],2)),R)/2,nx[j],ny[j]);
          return;
     }
      MoveToEx(hdc, nx[i], ny[i], NULL);
      LineTo(hdc, nx[j], ny[j]);
      arrow(atan2(ny[j]-ny[i],nx[j]-nx[i]),nx[j],ny[j]);
    }

    //Функции очереди
    //Добавление очереди
    void qstore(int *q) {
        p[spos] = q;
        spos++;
    }
    //Получение очереди
    int *qretrieve() {
         if(rpos==spos) {
            return 0;
        }
        rpos++;
        return p[rpos-1];
    }

    //Функции стека
    //вершина стека
    //Затолкать элемент в стек
    void push(int i) {
        stack[tos] = i;
        tos++;
    }
    //Получить верхний элемент стека
    int peek(void) {
        return stack[tos-1];
    }
    // Забрать верхний элемент стека
    int pop(void) {
        tos--;
        if(tos < 0) {
            return 0;
        }
        return stack[tos];
    }

 void DFS (HDC hdc, double **A, int a, int *nx, int *ny){
        int DFSM[11]={0,0,0,0,0,0,0,0,0,0,0};
        int i;
        char *nn[11] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"};
        int k=1,dx = 16, dy = 16, dtx = 5;
        sprintf_s(text, 4, " %d ", a);
        TextOut(hdc, nx[a-1]+dtx,ny[a-1]+dy, text, 4);
        sprintf_s(text, 8, "V%d= %d", 1, a);
        TextOutA(hdc, 25, 0, text, 8);
        DFSM[a-1]=1;
        push(a);
        while (tos!=0) {
            i=peek();
                for(int j = 0; j < 11; j++) {
                    if (A[i-1][j]==1 && DFSM[j]==0) {
                            k=k+1;
                            DFSM[j]=k;
                            push(j+1);
                            drawtree(hdc, i-1, j, nx, ny);
                            graphTree[i-1][j] = 1;
                            Ellipse(hdc, nx[i-1]-dx,ny[i-1]-dy,nx[i-1]+dx,ny[i-1]+dy);
                            TextOut(hdc, nx[i-1]-dtx,ny[i-1]-dy/2,  nn[i-1], 2);
                            Ellipse(hdc, nx[j]-dx,ny[j]-dy,nx[j]+dx,ny[j]+dy);
                            TextOut(hdc, nx[j]-dtx,ny[j]-dy/2,  nn[j], 2);
                            sprintf_s(text, 4, " %d ", k);
                            TextOut(hdc, nx[j]+dtx,ny[j]+dy, text, 4);
                            sprintf_s(text, 9, "V%d= %d ", k, j+1);
                            TextOutA(hdc, 25+70*(k-1), 0, text, 9);
                            system("pause");
                            system("cls");
                            break;
                    }
                    if (j == 10) {
                        pop();
                    }
                }
        }
    }

    void BFS (HDC hdc, double **A, int a, int *nx, int *ny){
        int BFSM[11]={0,0,0,0,0,0,0,0,0,0,0};
        int i;
        char *nn[11] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"};
        int k=1,dx = 16, dy = 16, dtx = 5;
        sprintf_s(text, 4, " %d ", a);
        TextOut(hdc, nx[a-1]+dtx,ny[a-1]+dy, text, 4);
        sprintf_s(text, 8, "V%d= %d", 1, a);
        TextOutA(hdc, 25, 0, text, 8);
        BFSM[a-1]=1;
        qstore(a);
        while (spos!=rpos) {
            i=qretrieve();
                for(int j = 0; j < 11; j++) {
                    if (A[i-1][j]==1 && BFSM[j]==0) {
                            k=k+1;
                            BFSM[j]=k;
                            qstore(j+1);
                            drawtree(hdc, i-1, j, nx, ny);
                            graphTree[i-1][j] = 1;
                            Ellipse(hdc, nx[i-1]-dx,ny[i-1]-dy,nx[i-1]+dx,ny[i-1]+dy);
                            TextOut(hdc, nx[i-1]-dtx,ny[i-1]-dy/2,  nn[i-1], 2);
                            Ellipse(hdc, nx[j]-dx,ny[j]-dy,nx[j]+dx,ny[j]+dy);
                            TextOut(hdc, nx[j]-dtx,ny[j]-dy/2,  nn[j], 2);
                            sprintf_s(text, 4, " %d ", k);
                            TextOut(hdc, nx[j]+dtx,ny[j]+dy, text, 4);
                            sprintf_s(text, 9, "V%d= %d ", k, j+1);
                            TextOutA(hdc, 25+70*(k-1), 0, text, 9);
                            system("pause");
                            system("cls");
                    }
                }
        }
    }


    switch(messg){
        case WM_PAINT :
            hdc=BeginPaint(hWnd, &ps);
            printf ("Input type DFS(0) or BFS(1): ");
            scanf ("%d", &typeALG);
            char *nn[11] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"};
            int nx[11] = {};
            int ny[11] = {};
            int num = 100;
            int len = 600;
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
            HPEN RPen = CreatePen(PS_SOLID, 2, RGB(220, 20, 60));

            srand(0414);
            double** T = randm(11, 11);
            double coefficient = 1 - 1*0.01 - 4*0.005 - 0.15;
            double** A = mulmr(coefficient, T, 11, 11);

            SelectObject(hdc, KPen);

            for (int i = 0; i < 11; i++){
                for (int j = 0; j < 11; j++){
                    if (A[i][j] == 1){
                            drawtree(hdc, i, j, nx, ny);
                    }
                }
            }

            SelectObject(hdc, BPen);

            for(i=0;i < 11;i++){
              Ellipse(hdc, nx[i]-dx,ny[i]-dy,nx[i]+dx,ny[i]+dy);
              TextOut(hdc, nx[i]-dtx,ny[i]-dy/2,  nn[i], 2);
            }


            SelectObject(hdc, RPen);
            if (typeALG==0) {
                tos=0;
                DFS (hdc, A, 1, nx, ny);
                TextOutA(hdc, 650, 25, "Matrix for graphtree - DFS", 26);
            } else {
                spos = 0; rpos = 0;
                BFS (hdc, A, 1, nx, ny);
                TextOutA(hdc, 650, 25, "Matrix for graphtree - BFS", 26);
            }
            TextOutA(hdc, 25, 25, "Matrix for oriented graph", 25);
            for(int i=0; i<11; i++){
                for(int j=0; j<11; j++){
                    sprintf_s(text, 2, "%g", A[i][j]);
                    TextOutA(hdc, 25 + 15 * j, 25 * i+50, text, 1);
                    sprintf_s(text, 2, "%d", graphTree[i][j]);
                    TextOutA(hdc, 650 + 15 * j, 25 * i+50, text, 1);
                }
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
