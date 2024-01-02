#include <iostream>
#include <string>
#include <windows.h>
#include <vector>


int main(int arc, char** argv) {
	size_t n;

	std::cout << "Enter size of array: ";
	std::cin >> n;

	std::vector<int> array(n);

		std::cout << "Enter " << n << " elements of array: ";
		for (size_t i = 0; i < n; i++) {
			std::cin >> array[i];
		}


	std::cout << std::endl;

	std::wstring cmd_info = L"\"Child.exe\" ";
	cmd_info += std::to_wstring(n);
	cmd_info += L" ";
	for (size_t i = 0; i < n; i++) {
		cmd_info += std::to_wstring(array[i]);
		if (i != n - 1) {
			cmd_info += L" ";
		}
	}

	wchar_t* stemp = new wchar_t[cmd_info.length()];
	wcscpy_s(stemp, cmd_info.length() + 1, cmd_info.c_str());

	STARTUPINFO si;
	PROCESS_INFORMATION piApp;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USECOUNTCHARS | STARTF_USEPOSITION | STARTF_USEFILLATTRIBUTE;
	si.dwFillAttribute = FOREGROUND_GREEN;
	si.dwY = 1000;
	si.dwYCountChars = 90000;

	// Установить высоту (Y) смещения от верхнего левого угла экрана.

	if (!CreateProcess(nullptr, stemp, nullptr, nullptr, FALSE, CREATE_NEW_CONSOLE, nullptr, nullptr, &si, &piApp)) {
		std::cout << "New process is not working" << std::endl;
		return 0;
	}

	std::cout << "Process is working" << std::endl;

	WaitForSingleObject(piApp.hProcess, INFINITE);
	CloseHandle(piApp.hThread);
	CloseHandle(piApp.hProcess);

	std::cout << "Process was closed" << std::endl;

	return 0;
}