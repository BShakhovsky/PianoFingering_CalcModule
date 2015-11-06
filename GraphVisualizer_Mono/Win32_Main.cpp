# include "stdafx.h"
# include "Win32_Main.h"
# include "Win32_Menus.h"
# include "GraphVisualizer_Mono.h"

using namespace MainWindow;

Win32_Main::Win32_Main(_In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine) :
	szTitle(),
	szWindowClass()
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
}


ATOM Win32_Main::MyRegisterClass(const HINSTANCE hInstance) const
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof WNDCLASSEX;

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = Win32_Menus::WndProc;
	wcex.cbClsExtra = NULL;
	wcex.cbWndExtra = NULL;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GRAPHVISUALIZER_MONO));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_GRAPHVISUALIZER_MONO);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL Win32_Main::InitInstance(const HINSTANCE hInstance, int nCmdShow) const
{
	nCmdShow = SW_MAXIMIZE;
	Win32_Menus::SetInstance(hInstance);

	auto hWnd(CreateWindowW(szWindowClass, szTitle,
		WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		CW_USEDEFAULT, NULL, CW_USEDEFAULT, NULL, nullptr, nullptr, hInstance, nullptr));
	if (!hWnd) return FALSE;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}


int APIENTRY Win32_Main::operator () (_In_ HINSTANCE hInstance, _In_ int nCmdShow)
{
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_GRAPHVISUALIZER_MONO, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow)) return FALSE;
	auto hAccelTable(LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GRAPHVISUALIZER_MONO)));

	MSG msg;
	while (GetMessage(&msg, nullptr, NULL, NULL))
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

	return static_cast<int>(msg.wParam);
}