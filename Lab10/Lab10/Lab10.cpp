/*
проц.завершения ас.оп-ций с файлами запуск.в след.случае:
	*над файлом вып-ся ас.оп-ция вводы-вывода
	*когда ас.оп-ция ввода-вывода будет заверш., запуск указ.проц.заверш
*/

/*
1. добавить в проц.заверш вывод времени завершения оп-ции записи в файл
2. создать 2ую проц.заверш, запустить после заверш 2ой проц записи в файл
	вторая оп-ция записи д.старт сразу после завершения первой записи
*/
#include <windows.h> 
#include <iostream> 
#include <string>
#include <stdio.h>
#include <time.h>
using namespace std;

//--
const string currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%X", &tstruct);
	return buf;
}
//--
VOID CALLBACK Proc2(
	DWORD dwErrorCode,					// код возврата 
	DWORD dwNumberOfBytesTransferred,	// количество переданных байтов 
	LPOVERLAPPED lpOverlapped			// асинхронная передача данных 
)
{
	cout << "<< --- Is async proc 2" << endl;
	cout << currentDateTime() << " Процедура завершена с параметрами: " << endl
		<< "Код ошибки: " << dwErrorCode << endl
		<< "\tЧисло  записанных байтов: " << dwNumberOfBytesTransferred << endl
		<< "\tOffsets: " << (*lpOverlapped).OffsetHigh << ' '
		<< (*lpOverlapped).Offset << endl << endl;
}

VOID CALLBACK completion_routine(
	DWORD dwErrorCode,					// код возврата 
	DWORD dwNumberOfBytesTransferred,	// количество переданных байтов 
	LPOVERLAPPED lpOverlapped			// асинхронная передача данных 
)
{
	cout << "<< --- Is async proc 1" << endl;
	cout << currentDateTime() << " Процедура завершена с параметрами: " << endl
		<< "Код ошибки: " << dwErrorCode << endl
		<< "\tЧисло  записанных байтов: " << dwNumberOfBytesTransferred << endl
		<< "\tOffsets: " << (*lpOverlapped).OffsetHigh << ' '
		<< (*lpOverlapped).Offset << endl << endl;
}


// главная программа 
int main()
{
	setlocale(LC_ALL, "Rus");
	VOID(__stdcall * funEnd)(DWORD, DWORD, LPOVERLAPPED) = &completion_routine;
	HANDLE hFile;	// дескриптор файла 
	OVERLAPPED ovl; // структура управления асинхронным доступом к файлу 
	
	// инициализируем структуру OVERLAPPED 
	ovl.Offset = 0;
	ovl.OffsetHigh = 0;

	hFile = CreateFile(L"D:\\demo_file.txt", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_FLAG_OVERLAPPED, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		cerr << "Файл не создан" << endl << "Ошибка: " << GetLastError() << endl;
		cout << "Нажмите любую клавишу";
		cin.get();
		return 0;
	}

	// пишем данные в файл 
	for (int i = 0; i < 4; ++i)
	{
		if (i == 1)
		{
			funEnd = &Proc2;
		}
		else
		{
			funEnd = &completion_routine;
		}
		DWORD dwRet;
		if (!WriteFileEx(hFile, &i, sizeof(i), &ovl, funEnd))
		{
			dwRet = GetLastError();
			if (dwRet == ERROR_IO_PENDING)
				cout << "Write file pending." << endl;
			else
			{
				cout << "Запись закончилась ошибкой" << endl
					<< "Код ошибки: " << dwRet << endl;
				return 0;
			}
		}
		
		SleepEx(INFINITE, TRUE);
		ovl.Offset += sizeof(i);
		cout << "Запись завершена" << endl;
	}
	return 0;
}