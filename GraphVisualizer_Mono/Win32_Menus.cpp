# include "stdafx.h"
# include "Win32_Menus.h"
# include "GraphVisualizer_Mono.h"

# include "GraphPrinter.h"

using MainWindow::Win32_Menus;

HINSTANCE Win32_Menus::hInst;

void Win32_Menus::SetInstance(const HINSTANCE hInstance)
{
	hInst = hInstance;
}


LRESULT CALLBACK Win32_Menus::WndProc(const HWND hWnd, const UINT message, const WPARAM wParam, const LPARAM lParam)
{
	using Visualizer::GraphPrinter;

	switch (message)
	{
	case WM_COMMAND:
	{
		auto wmId(LOWORD(wParam));
		switch (wmId)
		{
			// Potentially throwing function passed to extern C function
			// Undefined behavior may occur if this function throws
#pragma warning(suppress:5039)
		case IDM_ABOUT:	DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);	break;
		case IDM_EXIT:	DestroyWindow(hWnd);											break;
		default:		return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}																					break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		auto hdc(BeginPaint(hWnd, &ps));
		static GraphPrinter graph;
		graph.Next(hdc);
		EndPaint(hWnd, &ps);
	}																					break;
	case WM_LBUTTONUP:	InvalidateRect(hWnd, NULL, false);								break;
	case WM_DESTROY:	PostQuitMessage(0);												break;
	default:			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return NULL;
}

INT_PTR CALLBACK Win32_Menus::About(const HWND hDlg, const UINT message, const WPARAM wParam, const LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG: return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
	}
	return FALSE;
}