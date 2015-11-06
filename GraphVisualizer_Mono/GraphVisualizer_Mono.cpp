# include "stdafx.h"
# include "GraphVisualizer_Mono.h"
# include "Win32_Main.h"

using MainWindow::Win32_Main;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	Win32_Main(hPrevInstance, lpCmdLine)(hInstance, nCmdShow);
}