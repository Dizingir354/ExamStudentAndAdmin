#include<iostream>
#include<list>
#include<vector>
#include"Application.h"
#include"Test.h"
#include<fstream>


using namespace std;



int main()
{
	setlocale(LC_ALL, "Russian");
	Application* app = nullptr;
	app->menu();

	system("pause");
}