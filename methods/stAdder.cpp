// StatAdder.cpp: определяет точку входа для консольного приложения.
//input files: saR.txt, enU.txt, meN.txt 
//output files: stE.txt

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <array>

using namespace std;

//in
string const STAT_FILE_NAME = "saR.txt";
string const SCALE_FILE_NAME = "enQ.txt";
string const NAMES_FILE_NAME = "meN.txt";
string const TEMP_FILE_NAME = "tmp.txt";
//out
string const OUT_FILE_NAME = "stE.txt";

const int MAX_COLS = 40;
const int MAX_ROWS = 2000;
string scaleLetters;

class Method //method statistic with name
{
public:
	Method()
	{
		table_.resize(MAX_ROWS, vector<int>(MAX_COLS));
	}
	bool setCell(int & i, int & j, int & dig)
	{
		if (i >= 0 && i < MAX_ROWS && j >= 0 && j < MAX_COLS) {
			if (i > rows_) rows_ = i;
			if (j > cols_) cols_ = j;
			table_[i][j] = dig; return true;

		}
		return false;
	}
	void setName(string s) { name_ = s; }
	string getName() const { return name_; }
	int getCell(int & i, int & j) const { return table_[i][j]; }
	vector<int> getRow(int index) { return table_[index]; }
	bool findLen(int len)
	{
		for (int row = 0; row < rows_; row++)
		{
			if (table_[row][0] == len) return true;
			return false;
		}
	}
	void addRow(vector<int> rw)
	{

		for (int row = 0; row < rows_; row++)
		{
			if (table_[row][0] == rw[0])
			{
				for (int col = 1; col < cols_; col++)
				{
					table_[row][col] += rw[col];
				}
				return;
			}
			if (table_[row][0] < rw[0])
			{
				if (row + 1 >= rows_)
				{
					table_.insert(table_.begin() + row + 2, rw);
					rows_++;
					return;
				}


				if (table_[row + 1][0] > rw[0])
				{
					table_.insert(table_.begin() + row + 1, rw);
					rows_++;
					return;
				}

			}
			else if (table_[row][0] > rw[0] && row == 0)
			{
				table_.insert(table_.begin(), rw);
				rows_++;
				return;
			}
		}
	}

	int getRowsNumber() const { return rows_ + 1; }
	int getColsNumber() const { return cols_ + 1; }
private:
	int rows_ = 0;
	int cols_ = 0;
	vector<vector<int>> table_;       //row: text length, overall texts, char errors
	string name_;
};

class MethodNames
{
public:
	MethodNames()
	{
		nums_.reserve(10);
		names_.reserve(10);
	}
	void addNum(int & num)
	{
		nums_.push_back(num);
		number_++;
	}
	void addName(string name)
	{
		if (names_.size() + 1 <= number_) {
			names_.push_back(name);
		}
	}
	string getName(int num)
	{
		return names_[num];
	}
	bool findNum(int num)
	{
		if (find(nums_.begin(), nums_.end(), num) != nums_.end())
			return true;

		return false;
	}
private:
	int number_ = 0;
	vector<int> nums_;
	vector<string> names_;

};

void skipLine(ifstream & fin)
{
	fin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void getNumbers(vector<int> & result, const string & s) { //get numbers from string
	bool found = false;
	int number = 0;

	for (string::size_type i = 0; i < s.length(); i++) {
		const char ch = s[i];
		if (ch >= '0' && ch <= '9') {
			const int digit = ch - '0';
			number = number * 10 + digit;
			found = true;
		}
		else {
			if (found) {
				result.push_back(number);

				number = 0;
				found = false;
			}
		}
	}

	if (found) {
		result.push_back(number);
	}
}

void readMethodNames(ifstream & fin, MethodNames &mn)
{
	int nM;
	fin >> nM;
	for (int iM = 0; iM < nM; iM++)
	{
		int n;
		fin >> n;
		mn.addNum(n);
	}
	for (int iM = 0; iM < nM; iM++)
	{
		string s;
		fin >> s;
		mn.addName(s);
	}
}

void readMethods(ifstream & fin, vector<Method> & methods, MethodNames & mn, int cols) //reading error statistic table about methods
{
	int nFrags;
	char c;
	int nMethods;
	fin >> nFrags >> nMethods >> c;

	for (int iF = 0; iF < nFrags; iF++)
	{
		skipLine(fin);
		for (int iM = 0; iM < nMethods * 2 + 1; iM++)
		{
			skipLine(fin);
		}

	}
	skipLine(fin);
	for (int iM = 0; iM < nMethods; iM++) {

		Method cMethod;
		string line;
		vector<int> numbers;
		getline(fin, line);
		if (mn.findNum(iM + 1))
		{
			cMethod.setName(mn.getName(iM));
		}
		skipLine(fin);
		while (line != "")
		{
			getline(fin, line);
		}


		skipLine(fin);


		numbers.reserve(100);
		int row = 0;
		line = "0";
		while (getline(fin, line))
		{
			if (line == "") break;
			numbers.clear();
			getNumbers(numbers, line);
			for (int iCol = 0; iCol < cols; iCol++)
			{
				cMethod.setCell(row, iCol, numbers[iCol]);
			}
			row++;
		}

		if (mn.findNum(iM + 1))
		{
			methods.push_back(cMethod);
		}

	}
}

void readExistedMethods(ifstream & fin, vector<Method> & methods, int cols)
{

	string line;
	vector<int> numbers;
	numbers.reserve(100);
	getline(fin, line);
	getNumbers(numbers, line);
	int n = numbers[0];

	for (int iM = 0; iM < n; iM++)
	{
		Method cMethod;
		getline(fin, line);
		cMethod.setName(line);
		skipLine(fin);
		int  row = 0;
		while (getline(fin, line))
		{

			if (line == "") break;
			numbers.clear();
			getNumbers(numbers, line);
			for (int iCol = 0; iCol < cols; iCol++)
			{
				cMethod.setCell(row, iCol, numbers[iCol]);
			}
			row++;

		}
		methods.push_back(cMethod);

	}
}

void printMethods(ofstream & fout, vector<Method> & methods)
{
	fout << methods.size() << endl;
	for (auto & method : methods)
	{
		fout << method.getName() << endl;
		int cols = scaleLetters.size();

		for (int i = 0; i < cols; i++)
		{
			fout << scaleLetters[i] << '\t';
		}
		fout << endl;

		for (int row = 0; row < method.getRowsNumber(); row++)
		{
			for (int col = 0; col < cols; col++)
			{
				fout << method.getCell(row, col) << '\t';
			}
			fout << endl;
		}
		fout << endl;
	}

}

void methodConjunction(Method & nMethod, Method & eMethod)
{
	for (int row = 0; row < nMethod.getRowsNumber(); row++)
	{
		eMethod.addRow(nMethod.getRow(row));
	}
}

void mergingMethods(vector<Method> & nMethods, vector<Method> & eMethods)
{

	for (auto & nMethod : nMethods)
	{
		bool methodExist = false;
		for (auto & eMethod : eMethods)
		{
			if (eMethod.getName() == nMethod.getName())
			{
				methodConjunction(nMethod, eMethod);
				methodExist = true;
				break;
			}

		}
		if (!methodExist) eMethods.push_back(nMethod);
	}
}

string readScaleLetters(ifstream & fin)
{
	int dig;
	string s;
	fin >> dig >> dig >> dig >> dig;
	s.reserve(dig);
	for (int i = 0; i < dig; i++)
	{
		char c;
		fin >> c;
		s += c;

	}
	return s;
}

int StatAdder()
{
	setlocale(LC_ALL, "rus");

	ifstream fin;
	ofstream fout;

	fin.open(SCALE_FILE_NAME, ios_base::in);
	if (!fin.is_open())
		return 1;
	scaleLetters = "NK";
	scaleLetters += readScaleLetters(fin);
	fin.close(); //enQ.txt reading complete

	fin.open(NAMES_FILE_NAME, ios_base::in);
	if (!fin.is_open())
		return 1;
	MethodNames mn;
	readMethodNames(fin, mn);
	fin.close(); //meN.txt reading complete

	vector<Method> newMethods;
	newMethods.reserve(10);
	vector<Method> existedMethods;
	existedMethods.reserve(10);

	fin.open(STAT_FILE_NAME, ios_base::in);
	if (!fin.is_open())
		return 1;
	readMethods(fin, newMethods, mn, scaleLetters.size());
	fin.close();


	fin.open(OUT_FILE_NAME, ios_base::in);
	if (fin.is_open())
	{
		readExistedMethods(fin, existedMethods, scaleLetters.size());
		mergingMethods(newMethods, existedMethods);
	}
	else
	{
		existedMethods = newMethods;
	}
	fin.close();





	fout.open(OUT_FILE_NAME, ios_base::out);
	printMethods(fout, existedMethods);
	fout.close();


	return 0;
}

