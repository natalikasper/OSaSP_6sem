#include <windows.h> 
#include <iostream> 
using namespace std;
#define _SECOND 10000000 // одна секунда для ожидающего таймера 
HANDLE hTimer; // ожидающий таймер 

DWORD WINAPI thread1(LPVOID)
{
	TCHAR Buffer[256] = TEXT("Hello natasha");
	HANDLE hOut;
	DWORD dwNumberOfBytes;
	FILE* fp;
	TCHAR stdPath[30] = TEXT("F:\\Laba11.txt");
	hOut = CreateFile(stdPath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile(hOut, Buffer, 256, &dwNumberOfBytes, NULL);
		printf("\n__File WRITE:");
		getchar();
	return 0;
}

DWORD WINAPI thread2(LPVOID)
{
	cout << endl << "\nWait Timer" << endl;
	// ждем сигнал от ожидающего таймера 
	WaitForSingleObject(hTimer, INFINITE);
	// выводим сообщение 
	TCHAR Buffer[256];
	HANDLE hIn;
	DWORD dwNumberOfBytes;
	FILE* fp;
	TCHAR stdPath[30] = TEXT("F:\\Laba11.txt");
	hIn = CreateFile(stdPath, GENERIC_ALL, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		printf("\n__File READ:");
		wcout << "Hello Natasha" << endl;
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

	_int64 qwTimeInterval; // время задержки для таймера 
	// создаем ожидающий таймер  

	hTimer = CreateWaitableTimer(NULL, FALSE, NULL);
	if (hTimer == NULL)
		return GetLastError();
	// время задержки для таймера = 10 секунд
	qwTimeInterval = -10 * _SECOND;
	// инициализируем таймер 
	if (!SetWaitableTimer(
		hTimer, // дескриптор таймера 
		(LARGE_INTEGER*)&qwTimeInterval, // временной интервал 
		0, // непериодический таймер 
		NULL, // процедуры завершения нет 
		NULL, // параметров к этой процедуре нет 
		FALSE // режим сбережения энергии не устанавливать 
	))
	{
		cout << "Set waitable timer failed." << endl
			<< "The last error code: " << GetLastError() << endl;
		return 0;
	}
	// запускаем поток 
	hThread1 = CreateThread(NULL, 0, thread1, NULL, 0, &IDThread1);
	hThread2 = CreateThread(NULL, 0, thread2, NULL, 0, &IDThread2);
	if (hThread1 == NULL)
		return GetLastError();
	if (hThread2 == NULL)
		return GetLastError();
	// ждем, пока поток закончит работу 
	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE);
	// закрываем дескрипторы 
	CloseHandle(hThread1);
	CloseHandle(hThread2);
	CloseHandle(hTimer);
	return 0;
}