#pragma once
#include <windows.h>

class WindowManager
{
public:
    //シングルトン
    static WindowManager& Instance()
    {
        static WindowManager instance;
        return instance;
    }

    //ウィンドウのサイズ取得
    int Width() const { return width; }
    int Height() const { return height; }

    //HWNDをセットする関数
    void SetHWND(HWND h) { hwnd = h; }

    //呼ばれた瞬間のウィンドウのサイズに更新
    void UpdateSize()
    {
        RECT rc;
        GetClientRect(hwnd, &rc);
        width = rc.right - rc.left;
        height = rc.bottom - rc.top;
    }

private:
    WindowManager() = default;
    HWND hwnd = nullptr;
    int width = 0;
    int height = 0;
};