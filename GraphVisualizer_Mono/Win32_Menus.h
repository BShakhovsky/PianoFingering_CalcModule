# pragma once

namespace MainWindow
{
	class Win32_Menus abstract : private boost::noncopyable
	{
		Win32_Menus() = delete;
		~Win32_Menus() = delete;
	public:
		static LRESULT CALLBACK WndProc(HWND, UINT message, WPARAM, LPARAM);
		static INT_PTR CALLBACK About(HWND, UINT message, WPARAM, LPARAM);

		static void SetInstance(HINSTANCE);
	private:
		static HINSTANCE hInst;
	};
}