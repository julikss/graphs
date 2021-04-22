#include<windows.h>
#include<math.h>
#define pi 3.14159265358979323846

double** randm(int rows, int cols){
                double** matrix = (double**)malloc(rows * sizeof(double*));
                for (int i = 0; i < rows; i++)
                    matrix[i] = (double*)malloc(cols * sizeof(double));
                for (int i = 0; i < rows; i++) {
                    for (int j = 0; j < cols; j++) {
                        if (j >= i) {
                            matrix[i][j] =  2.0 * rand()/RAND_MAX;
                        } else matrix[i][j] = matrix[j][i];
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

char ProgName[]="Ëàáîðàòîðíà ðîáîòà 3";

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
        "ËÐ 3 (íåíàïðÿìëåíèé ãðàô). Âèêîíàëà Þ.Ä. Ëåãåíüêà",
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT messg,
                        WPARAM wParam, LPARAM lParam)
    {
    HDC hdc;
    PAINTSTRUCT ps;

    switch(messg){
        case WM_PAINT :
            hdc=BeginPaint(hWnd, &ps);
            char *nn[11] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11"};
            int nx[11] = {};
            int ny[11] = {};
            int num = 100;
            int len = 600;
        for(int i = 0; i < 11; i++)  {
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
        double coefficient = 1 - 2*0.02 - 6*0.005 - 0.25;
        double** A = mulmr(coefficient, T, 11, 11);
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
                    if (j >= i) {
                        if (A[i][j] == 1){
                                if (i == j){
                                Arc(hdc, nx[j], ny[j], nx[j]-40, ny[j]-40, nx[j], ny[j], nx[j], ny[j]);
                                continue;
                            }
                            if (((i==0) && (j==10))||((i==10) && (j==0))||(i==j+1)||(i==j-1)) {
                                MoveToEx(hdc, nx[i], ny[i], NULL);
                                LineTo(hdc, nx[j], ny[j]);
                                continue;
                            }

                            if ((i < 5) && ((j < 5))){
                                nx0=(nx[i]+nx[j])/2 + (ny[i]-ny[j])/(scaler);
                                ny0=(ny[i]+ny[j])/2 -(nx[i]-nx[j])/(scaler);
                                R=sqrt(pow(nx[i]-nx0, 2) + pow(ny[i]-ny0, 2));
                                Arc(hdc, nx0-R, ny0-R, nx0+R, ny0+R, nx[j], ny[j], nx[i], ny[i]);
                                continue;
                            }
                            if ((i>=4) &&(i < 9)&& (j>=4) &&(j < 9)) {
                                nx0=(nx[i]+nx[j])/2 + (ny[i]-ny[j])/(scaler);
                                ny0=(ny[i]+ny[j])/2 - (nx[i]-nx[j])/(scaler);
                                R=sqrt(pow(nx[i]-nx0, 2) + pow(ny[i]-ny0, 2));
                                Arc(hdc, nx0-R, ny0-R, nx0+R, ny0+R, nx[j], ny[j], nx[i], ny[i]);
                                continue;
                            }
                            if (((i>=8) || (i==0)) && ((j>=8)||(j==0))) {
                                nx0=(nx[i]+nx[j])/2 + (ny[i]-ny[j])/(scaler);
                                ny0=(ny[i]+ny[j])/2 - (nx[i]-nx[j])/(scaler);
                                R=sqrt(pow(nx[i]-nx0, 2)+pow(ny[i]-ny0, 2));
                                Arc(hdc, nx0-R, ny0-R, nx0+R, ny0+R, nx[j], ny[j], nx[i], ny[i]);
                                continue;
                            }
                        MoveToEx(hdc, nx[i], ny[i], NULL);
                        LineTo(hdc, nx[j], ny[j]);
                        }
                    }
                }
            }
            SelectObject(hdc, BPen);
            for(i=0;i < 11;i++){
              Ellipse(hdc, nx[i]-dx,ny[i]-dy,nx[i]+dx,ny[i]+dy);
              TextOut(hdc, nx[i]-dtx,ny[i]-dy/2,  nn[i], 2);
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
