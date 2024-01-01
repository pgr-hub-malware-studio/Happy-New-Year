// Happy New Year.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#include <iostream>
#include <vector>
#include <tchar.h>
#include <windows.h>
#define MAX_LINES 20
#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502884
#endif
void DrawFireworks(HWND hwnd, std::vector<POINT>& lines)
{
    HDC hdc = GetDC(hwnd);

    // 获取窗口尺寸
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);

    // 获取窗口中心坐标
    int centerX = rand() % (clientRect.right - clientRect.left);
    int centerY = rand() % (clientRect.bottom - clientRect.top);

    // 循环绘制多条放射状线条
    for (int i = 0; i < MAX_LINES; ++i) {
        // 随机生成线条的角度
        double angle = (rand() % 360) * (M_PI / 180.0);

        // 随机生成线条的长度
        int length = rand() % 100 + 50;

        // 计算线条的终点坐标
        int endX = centerX + (int)(length * cos(angle));
        int endY = centerY + (int)(length * sin(angle));

        // 添加线条的起点和终点到容器中
        lines.push_back({ centerX, centerY });
        lines.push_back({ endX, endY });
    }

    // 随机生成线条的颜色
    COLORREF color = RGB(rand() % 256, rand() % 256, rand() % 256);

    // 创建画笔
    HPEN hPen = CreatePen(PS_SOLID, 2, color);
    HGDIOBJ hOldPen = SelectObject(hdc, hPen);

    // 绘制所有线条
    Polyline(hdc, lines.data(), lines.size());

    // 删除画笔
    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);

    // 释放设备上下文
    ReleaseDC(hwnd, hdc);
}
void main()
{
    int i;
    int x, y;
    PAINTSTRUCT ps;
    RECT clientRect;
    SIZE textSize;
    HWND hWnd = GetDesktopWindow();
    HDC hdc = GetWindowDC(hWnd);
    GetClientRect(hWnd, &clientRect);
    srand((unsigned)time(NULL));
    for (i = 1; i <= 20; i++)
    {
        FillRect(hdc, &clientRect, (HBRUSH)GetStockObject(BLACK_BRUSH));
        std::vector<POINT> lines;
        DrawFireworks(hWnd, lines);
        Sleep(rand()%1000+1);
    }
    FillRect(hdc, &clientRect, CreateSolidBrush(RGB(255, 0, 0)));
    BeginPaint(hWnd, &ps);
    HFONT hFont = CreateFont(60, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, VARIABLE_PITCH, _T("楷体"));
    HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
    SetTextColor(hdc, RGB(255, 215, 0));
    GetTextExtentPoint32(hdc, _T("新年快乐"), _tcslen(_T("新年快乐")), &textSize);
    x = (clientRect.right - clientRect.left) / 2;
    y = (clientRect.bottom - clientRect.top) / 2;
    TextOut(hdc, x, y, _T("新年快乐"), _tcslen(_T("新年快乐")));
    SelectObject(hdc, hOldFont);
    DeleteObject(hFont);
    EndPaint(hWnd, &ps);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
