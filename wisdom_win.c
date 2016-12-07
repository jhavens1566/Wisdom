#include <time.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getQuotes(const char *fn);
void parseQuotes();
int GetNewlineCount(const char *s);
const char *newQuote();

const char *quote;
    
HFONT g_hfFont = NULL;
BOOL g_bOpaque = TRUE;
COLORREF g_rgbText = RGB(0, 0, 0);
COLORREF g_rgbBackground = RGB(255, 255, 255);

COLORREF g_rgbCustom[16] = {0};

void DrawClientSize(HWND hwnd, HDC hdc, RECT *prc, HFONT hf)
{
    char szSize[100];
    char szTitle[] = "These are the dimensions of your client area:";
    SelectObject(hdc, hf);
    int h = 0;
    int w = 0;
    // printf("%s\n",quote);
    char quote_tmp[4096];
    strcpy(quote_tmp, quote);
    char *token = strtok(quote_tmp, "\n");
    for( int count = 0; token != NULL; count++ ) {
        SIZE sizer;
        GetTextExtentPoint32(hdc,token,strlen(token),&sizer);
        token = strtok(NULL, "\n");
        if (sizer.cx > w) w = sizer.cx;
        h=sizer.cy;
    }
    h = h * (GetNewlineCount(quote) + 1);
    RECT newRect = {0,0,w,h};
    AdjustWindowRect(&newRect, WS_OVERLAPPEDWINDOW, FALSE);
    int x=(GetSystemMetrics(SM_CXSCREEN)-w)/2;
    int y=(GetSystemMetrics(SM_CYSCREEN)-h)/2;
    SetWindowPos(hwnd,HWND_TOPMOST,x,y,newRect.right-newRect.left,newRect.bottom-newRect.top,0);
    GetClientRect(hwnd, prc);
    DrawText(hdc, quote, -1, prc, DT_WORDBREAK);
}

const char g_szClassName[] = "WisdomWindowClass";

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_KEYDOWN:
        case WM_LBUTTONDOWN:    
        {
            quote = newQuote();
            InvalidateRect (hwnd, NULL, TRUE);
            UpdateWindow(hwnd);
        }
        break;      
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        case WM_SIZE:
        {
            InvalidateRect (hwnd, NULL, TRUE);
            UpdateWindow(hwnd);
        }
        
        case WM_PAINT:
        {
            // printf("paint");
            RECT rcClient;
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            HFONT g_hfFont = CreateFont(36, 0, 0, 0, 0, FALSE, 0, 0, 0, 0, 0, 0, 0, "Arial");

            GetClientRect(hwnd, &rcClient);

            DrawClientSize(hwnd, hdc, &rcClient, g_hfFont);

            EndPaint(hwnd, &ps);
        }
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    srand(time(NULL)); //randomize the randomizer with not so random current time
    rand(); //throw away first rand, for some reason the first is always about the same
    getQuotes("THEMETER"); //populate the quote_array and set quote_count
    // printf("END METER %d %s\n", quote_count, quote_array[30]);
    getQuotes("QUOTES"); //populate the quote_array and set quote_count
    // printf("END QUOTES %d %s\n", quote_count, quote_array[100]);
    parseQuotes();
    quote = newQuote();
    
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    //Step 1: Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindow(
        g_szClassName,
        "Wisdom",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    
    // Step 3: The Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}
