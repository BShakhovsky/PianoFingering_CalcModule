# pragma once

namespace MainWindow
{
	class Win32_Main : private boost::noncopyable
	{
		Win32_Main() = delete;
	public:
		explicit Win32_Main(_In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine);
		~Win32_Main() = default;

		ATOM MyRegisterClass(HINSTANCE hInstance) const;
		BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) const;

		int APIENTRY operator () (_In_ HINSTANCE hInstance, _In_ int nCmdShow);
	private:
		static const int MAX_LOADSTRING = 100;

		WCHAR szTitle[MAX_LOADSTRING];			// The title bar text
		WCHAR szWindowClass[MAX_LOADSTRING];	// the main window class name
	};
}