// methods.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "C:/Users/taron/Documents/newfrags/LIB/LIB/stdafx.h" //Заголовок библиотеки LIB.lib
#include <time.h>
#include <windows.h>
#include <stdio.h>
#include <string>
#include <clocale> 
#include <vector>
#include <filesystem>
#include <fstream>
using namespace std;
namespace fs = std::experimental::filesystem;
void solvingRUS()
{
	time_t start, end;
	time(&start);
	staT(0);
	time(&end);
	printf_s("staT completed at %f secs\n", difftime(end, start));

	reduce();
	time(&end);
	printf_s("reduce completed at %f secs\n", difftime(end, start));
	staT(1);
	time(&end);
	printf_s("staT completed at %f secs\n", difftime(end, start));
	formU();
	formB();
	time(&end);
	printf_s("formUB completed at %f secs\n", difftime(end, start));

	JAC(0); //1
	time(&end);
	printf_s("JAC completed at %f secs\n", difftime(end, start));
	DAT(0); //2
	time(&end);
	printf_s("DAT completed at %f secs\n", difftime(end, start));
	MAP(0); //3
	time(&end);
	printf_s("MAP completed at %f secs\n", difftime(end, start));
	JAC(2); //4
	time(&end);
	printf_s("JAC+DAT completed at %f secs\n", difftime(end, start));
	MAP(4); //5
	time(&end);
	printf_s("JAC+DAT+MAP completed at %f secs\n", difftime(end, start));
	
	
}

void solvingUNI()
{
	time_t start, end;
	time(&start);
	staT(0);
	time(&end);
	printf_s("staT completed at %f secs\n", difftime(end, start));

	reduce();
	time(&end);
	printf_s("reduce completed at %f secs\n", difftime(end, start));
	staT(1);
	time(&end);
	printf_s("staT completed at %f secs\n", difftime(end, start));
	formU();
	formB();
	time(&end);
	printf_s("formUB completed at %f secs\n", difftime(end, start));

	JAC(0); //1
	time(&end);
	printf_s("JAC completed at %f secs\n", difftime(end, start));
	MAP(0); //2
	time(&end);
	printf_s("MAP completed at %f secs\n", difftime(end, start));

	MAP(1); //3
	time(&end);
	printf_s("JAC+MAP completed at %f secs\n", difftime(end, start));
	JAC(3); //3
	time(&end);
	printf_s("JAC+MAP+JAC completed at %f secs\n", difftime(end, start));
}
void decoding()
{
	staT(0);
	reduce1();
	staT(1);
	formU();
	formB();
	//methods
	JAC(0);
	DAT(0);
	MAP(0);
	JAC(2);
	MAP(4);
	printf_s("Decoding complete \n");
}

void evaluation(int k)
{
	int M[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	staR(k, M);
	printf_s("Evaluation complete \n");
}

int renameFiles()
{
	int filesFound = 0;
	string path = "samples/";
	string nameTo;
	vector<string> fileNames;
	for (const auto & entry : fs::directory_iterator(path))
	{
		fileNames.push_back(entry.path().string());
		filesFound++;
	}

	for (int i = 0; i < filesFound; i++)
	{
		nameTo = path + to_string(i+1) + ".txt";
		fs::rename(fileNames[i], nameTo);
	}
	return filesFound;
}

void testing()
{
	time_t start, end;
	time(&start);
	int filesFound = renameFiles();
	
	printf_s("%d files found \n", filesFound);

	for (int iFile = 1; iFile <= filesFound; iFile++)
	{
		printf_s("Start %d file processing... \n", iFile);

		fs::remove("input.txt");
		fs::remove("ouR.txt");

		string copyFrom = "samples/" + to_string(iFile) + ".txt";
		fs::copy(copyFrom, fs::current_path(), fs::copy_options::overwrite_existing);
		fs::rename(to_string(iFile) + ".txt", "input.txt");

		ofstream fout;
		fout.open("ouR.txt", ios_base::out);
		fout << "0 0\n";
		fout.close();

		decoding();
		evaluation(5);
		StatAdder();
		printf_s("Statistic is added \n");
		time(&end);
		printf_s(" %d / %d file processing complete! %f seconds\n", iFile, filesFound, difftime(end, start));
	}

	system("pause");
	
}



int main()
{
	//Модули (8):                    //Модули выгружены в библиотеку LIB.lib, заголовочный файл "C:\Users\kotov.NSTU\Desktop\LIB\LIB\LIB\stdafx.h"
	//
	//       int formS()             //Форма текста без пробела для Nf текстовых фрагментов, записанных в файле inT.txt
	//       int formU()             //Форма униграмм для Nf текстовых фрагментов, записанных в файле inT.txt
	//       int formB()             //Форма биграмм для Nf текстовых фрагментов, записанных в файле inT.txt
	//       int UPO()               //Метод частотного упорядочивания
	//       int MAP(int M)          //Метод аппроксимации по Пирсону на основе эталонной таблицы биграмм enB.txt.
	//       int JAC(int M)          //Метод Якобсена  двумерного упорядочивания на основе эталонной таблицы биграмм enB.txt.
	//       int reduce()            //Модуль выделения фрагментов с заданными свойствами и/или номерами из input.txt в inT.txt
	//       int staR(int N,int M[]) //Модуль статистической обработки результатов.
	setlocale(LC_CTYPE, "Russian");
	
	//solvingRUS();
	//solvingUNI();
	evaluation(6);
	//StatAdder();

	//testing();
	
    return 0;
}

