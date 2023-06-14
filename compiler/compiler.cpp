#include <Windows.h>
#include <CommCtrl.h>
#include <fstream>
#include <string>
#include <iostream>

#pragma comment(lib, "Comctl32.lib")

#define CODE_TXT_PATH L"../module/code.txt"
#define CFFX_PATH L"../module/cffx.txt"
#define YFFX_PATH L"../module/yffx.txt"
#define YYFX_PATH L"../module/yyfx.txt"
#define CFFX_CMD "D:\\Code\\Cpp\\compiler\\module\\cffx.exe<D:\\Code\\Cpp\\compiler\\module\\code.txt"
#define YFFX_CMD "D:\\Code\\Cpp\\compiler\\module\\yffx.exe<D:\\Code\\Cpp\\compiler\\module\\code.txt"
#define YYFX_CMD "D:\\Code\\Cpp\\compiler\\module\\yyfx.exe<D:\\Code\\Cpp\\compiler\\module\\code.txt"




HWND hEdit;
std::wstring filePath;

std::string ConvertLineEndings(const std::string& text)
{
    std::string convertedText;
    for (size_t i = 0; i < text.length(); ++i)
    {
        // if (text[i] == L'\r')  // 当前字符是 CR
        // {
        //     if (i + 1 < text.length() && text[i + 1] == L'\n')  // 下一个字符是 LF
        //     {
        //         // 将 CR LF 转换为 CRLF
        //         convertedText += "\r\n";
        //         ++i;  // 跳过下一个字符
        //     }
        //     else
        //     {
        //         // 只有 CR，将其转换为 CRLF
        //         convertedText += "\r\n";
        //     }
        // }
        if (text[i] == '\n')  // 当前字符是 LF
        {
            // 将 LF 转换为 CRLF
            convertedText += "\r\n";
        }
        else
        {
            // 其他字符保持不变
            convertedText += text[i];
        }
    }
    return convertedText;
}

std::string OffConvertLineEndings(const std::string& text)
{
    std::string convertedText;
    for (size_t i = 0; i < text.length(); ++i)
    {
        if (text[i] == L'\r')  // 当前字符是 CR
        {
            if (i + 1 < text.length() && text[i + 1] == L'\n')  // 下一个字符是 LF
            {
                // 将 CR LF 转换为 CRLF
                convertedText += "\n";
                ++i;  // 跳过下一个字符
            }
        }
        else
        {
            // 其他字符保持不变
            convertedText += text[i];
        }
    }
    return convertedText;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    printf("%d/n", LOWORD(wParam));
    switch (message)
    {
    case WM_COMMAND:
    {
        if (LOWORD(wParam) == 1) // "打开文件"按钮的ID为1
        {
            wchar_t szFile[MAX_PATH] = CODE_TXT_PATH;
            filePath = szFile;
            std::ifstream file(filePath);
            if (file)
            {
                std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                std::cout << "content" << std::endl;
                file.close();

                // 将回车符格式转换为 CRLF 格式
                std::string convertedContent = ConvertLineEndings(content);
                SetWindowTextA(hEdit, convertedContent.c_str());
            }
            // OPENFILENAME ofn;
            // wchar_t szFile[MAX_PATH] = L"";

            // ZeroMemory(&ofn, sizeof(ofn));
            // ofn.lStructSize = sizeof(ofn);
            // ofn.hwndOwner = hWnd;
            // ofn.lpstrFile = szFile;
            // ofn.nMaxFile = sizeof(szFile);
            // ofn.lpstrFilter = L"Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
            // ofn.nFilterIndex = 1;
            // ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

            // if (GetOpenFileName(&ofn))
            // {
            //     filePath = szFile;

            //     std::ifstream file(filePath);
            //     if (file)
            //     {
            //         std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            //         std::cout << "content" << std::endl;
            //         file.close();

            //         // 将回车符格式转换为 CRLF 格式
            //         std::string convertedContent = ConvertLineEndings(content);
            //         SetWindowTextA(hEdit, convertedContent.c_str());
            //     }
            // }
        }
        else if (LOWORD(wParam) == 2) // "保存"按钮的ID为2
        {
            wchar_t szFile[MAX_PATH] = CODE_TXT_PATH;
            filePath = szFile;
            if (!filePath.empty())
            {
                int length = GetWindowTextLengthA(hEdit) + 1;
                char* buffer = new char[length];
                GetWindowTextA(hEdit, buffer, length);
                std::string convertedContent = OffConvertLineEndings(buffer);
                std::ofstream file(filePath);
                if (file)
                {
                    file << convertedContent;
                    file.close();
                    system(CFFX_CMD);
                    // system(YFFX_CMD);
                    system(YYFX_CMD);
                    MessageBox(hWnd, L"文件保存成功并运行！", L"提示", MB_OK | MB_ICONINFORMATION);
                }
                delete[] buffer;
                
            }
            else
            {
                MessageBox(hWnd, L"保存路径有误！", L"错误", MB_OK | MB_ICONERROR);
            }
        }
        else if (LOWORD(wParam) == 3){
            wchar_t szFile[MAX_PATH] = CFFX_PATH;
            filePath = szFile;
            std::ifstream file(filePath);
            if (file)
            {
                std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                std::cout << "content" << std::endl;
                file.close();

                // 将回车符格式转换为 CRLF 格式
                std::string convertedContent = ConvertLineEndings(content);
                SetWindowTextA(hEdit, convertedContent.c_str());
            }
        }
        else if (LOWORD(wParam) == 4){
            wchar_t szFile[MAX_PATH] = YFFX_PATH;
            filePath = szFile;
            std::ifstream file(filePath);
            if (file)
            {
                std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                std::cout << "content" << std::endl;
                file.close();

                // 将回车符格式转换为 CRLF 格式
                std::string convertedContent = ConvertLineEndings(content);
                SetWindowTextA(hEdit, convertedContent.c_str());
            }
        }
        else if (LOWORD(wParam) == 5){
            wchar_t szFile[MAX_PATH] = YYFX_PATH;
            filePath = szFile;
            std::ifstream file(filePath);
            if (file)
            {
                std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                std::cout << "content" << std::endl;
                file.close();

                // 将回车符格式转换为 CRLF 格式
                std::string convertedContent = ConvertLineEndings(content);
                SetWindowTextA(hEdit, convertedContent.c_str());
            }
        }
    }
    break;
    case WM_SIZE:
    {
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);

        // 调整编辑框的位置和大小
        SetWindowPos(hEdit, NULL, 0, 0, width, height - 30, SWP_NOZORDER);

        // 将按钮放置在窗口底部
        int buttonWidth = 100;
        int buttonHeight = 20;
        int buttonMargin = 10;
        int buttonCount = 5;
        int buttonX = (width - buttonWidth*buttonCount - buttonMargin*buttonCount) / 2;
        int buttonY = height - buttonHeight - buttonMargin;
        SetWindowPos(GetDlgItem(hWnd, 1), NULL, buttonX, buttonY, buttonWidth, buttonHeight, SWP_NOZORDER);
        SetWindowPos(GetDlgItem(hWnd, 2), NULL, buttonX + buttonWidth + buttonMargin, buttonY, buttonWidth, buttonHeight, SWP_NOZORDER);
        SetWindowPos(GetDlgItem(hWnd, 3), NULL, buttonX + buttonWidth*(buttonCount-3) + buttonMargin*(buttonCount-3), buttonY, buttonWidth, buttonHeight, SWP_NOZORDER);
        SetWindowPos(GetDlgItem(hWnd, 4), NULL, buttonX + buttonWidth*(buttonCount-2) + buttonMargin*(buttonCount-2), buttonY, buttonWidth, buttonHeight, SWP_NOZORDER);
        SetWindowPos(GetDlgItem(hWnd, 5), NULL, buttonX + buttonWidth*(buttonCount-1) + buttonMargin*(buttonCount-1), buttonY, buttonWidth, buttonHeight, SWP_NOZORDER);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(icex);
    icex.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&icex);

    WNDCLASSEX wc;
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = L"MyWindowClass";
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, L"窗口注册失败！", L"错误", MB_OK | MB_ICONERROR);
        return 0;
    }

    HWND hWnd = CreateWindowEx(
        0,
        L"MyWindowClass",
        L"PL0程序解析",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL, L"窗口创建失败！", L"错误", MB_OK | MB_ICONERROR);
        return 0;
    }

    int clientWidth = 300;
    int clientHeight = 300;
    hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), NULL,
    WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL,
    10, 10, clientWidth - 20, clientHeight - 50,
    hWnd, NULL, hInstance, NULL);


    if (!hEdit)
    {
        MessageBox(NULL, L"编辑框创建失败！", L"错误", MB_OK | MB_ICONERROR);
        return 0;
    }

    CreateWindow(
        L"BUTTON",
        L"打开源码",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10, 10, 100, 30,
        hWnd,
        (HMENU)1,
        hInstance,
        NULL
    );

    CreateWindow(
        L"BUTTON",
        L"保存并运行",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        120, 10, 100, 30,
        hWnd,
        (HMENU)2,
        hInstance,
        NULL
    );

    CreateWindow(
        L"BUTTON",
        L"词法分析",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10, 10, 100, 30,
        hWnd,
        (HMENU)3,
        hInstance,
        NULL
    );

    CreateWindow(
        L"BUTTON",
        L"语法分析",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10, 10, 100, 30,
        hWnd,
        (HMENU)4,
        hInstance,
        NULL
    );

    CreateWindow(
        L"BUTTON",
        L"语义分析",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        10, 10, 100, 30,
        hWnd,
        (HMENU)5,
        hInstance,
        NULL
    );

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

