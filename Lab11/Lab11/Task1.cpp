#include <windows.h> 
#include <iostream> 
using namespace std;
#define _SECOND 10000000 // ���� ������� ��� ���������� ������� 
HANDLE hTimer; // ��������� ������ 

DWORD WINAPI thread1(LPVOID)
{
	TCHAR Buffer[256] = TEXT("Hello natasha");
	HANDLE hOut;
	DWORD dwNumberOfBytes;
	FILE* fp;
	TCHAR stdPath[30] = TEXT("F:\\Laba11.txt");
	hOut = CreateFile(stdPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(hOut, Buffer, 256, &dwNumberOfBytes, NULL);
	printf("__File WRITE:");
	getchar();
	return 0;
}

DWORD WINAPI thread2(LPVOID)
{
	cout << endl << "Wait Timer" << endl;
	// ���� ������ �� ���������� ������� 
	WaitForSingleObject(hTimer, INFINITE);
	// ������� ��������� 
	TCHAR Buffer[256];
	HANDLE hIn;
	DWORD dwNumberOfBytes;
	FILE* fp;
	TCHAR stdPath[30] = TEXT("F:\\Laba11.txt");
	hIn = CreateFile(stdPath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	printf("__File READ:");
	ReadFile(hIn, Buffer, 256, &dwNumberOfBytes, NULL);
	wcout << Buffer << endl;
	getchar();
	return 0;
}

int main()
{
	cout << "start" << endl;
	HANDLE hThread1;
	HANDLE hThread2;
	DWORD IDThread1;
	DWORD IDThread2;

	_int64 qwTimeInterval; // ����� �������� ��� ������� 
	// ������� ��������� ������  

	hTimer = CreateWaitableTimer(NULL, FALSE, NULL);
	if (hTimer == NULL)
		return GetLastError();
	// ����� �������� ��� ������� = 10 ������
	qwTimeInterval = -10 * _SECOND;
	// �������������� ������ 
	if (!SetWaitableTimer(
		hTimer, // ���������� ������� 
		(LARGE_INTEGER*)&qwTimeInterval, // ��������� �������� 
		0, // ��������������� ������ 
		NULL, // ��������� ���������� ��� 
		NULL, // ���������� � ���� ��������� ��� 
		FALSE // ����� ���������� ������� �� ������������� 
	))
	{
		cout << "Set waitable timer failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		return 0;
	}
	// ��������� ����� 
	hThread1 = CreateThread(NULL, 0, thread1, NULL, 0, &IDThread1);
	hThread2 = CreateThread(NULL, 0, thread2, NULL, 0, &IDThread2);
	if (hThread1 == NULL)
		return GetLastError();
	if (hThread2 == NULL)
		return GetLastError();
	// ����, ���� ����� �������� ������ 
	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE);
	// ��������� ����������� 
	CloseHandle(hThread1);
	CloseHandle(hThread2);
	CloseHandle(hTimer);
	return 0;
}