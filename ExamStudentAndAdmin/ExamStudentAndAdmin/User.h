#pragma once
#include<iostream>
#include<list>
#include<vector>
#include<string>
#include"Test.h"
#include"Application.h"

using namespace std;

class User
{
public:

	int hashPass;
	Test::Test* test = nullptr;
	int mark;

	string login;
	virtual void menu() = 0;


	void Register()
	{

		cout << "Please, enter your login: " << endl;
		getline(cin, login);
		cout << "Enter your password: " << endl;
		string pa;
		hash<string> Pass;
		char ch; //для скрытие пороля

		ch = _getch();

		while (ch != 13)
		{
			pa.push_back(ch);
			cout << ' ';
			ch = _getch();
		}
		cout << endl;
		getline(cin, pa);
		int hashPass = Pass(pa);
		ofstream out;
		out.open("Accounts.txt", ios_base::app);
		out << login << endl;
		out << hashPass << endl;
		out.close();

	}
	void Login()
	{
		cout << "Please, enter your login: " << endl;
		getline(cin, login);
		cout << "Enter your password: " << endl;
		string pa;
		hash<string> Pass;
		getline(cin, pa);
		int hashPass = Pass(pa);
		ifstream out;
		out.open("Accounts.txt");
		int p;
		string l;
		while (cin >> l >> p)
		{
			if (login == l && hashPass == p);
		}
	}
};

class Student : public User
{


	void testing()
	{
		ifstream in("testName.txt");
		string testN;
		vector<string> tn;
		int TrueAnswers = 0;
		while (getline(in, testN))
		{
			tn.push_back(testN);
		}
		in.close();
		for (size_t i = 0; i < tn.size(); i++)
		{
			cout << i + 1 << " " << tn[i] << endl;
		}
		int c;
		cin >> c;
		cin.ignore();
		test = new Test::Test();
		in.open("categorys\\" + tn[c - 1] + ".txt");
		getline(in, test->name);
		int lenQ;
		in >> lenQ;
		string buff;
		getline(in, buff);


		system("cls");
		for (size_t i = 0; i < lenQ; i++)
		{
			Test::Question q;
			getline(in, q.question);
			int lenA;
			in >> lenA;
			getline(in, buff);
			for (size_t i = 0; i < lenA; i++)
			{
				string ans;
				getline(in, ans);
				q.answers.push_back(ans);
			}
			test->questions.push_back(q);
			in >> q.numTrueAnswer;
			getline(in, buff);

			test->print();

			cout << endl << "Please, enter " << i + 1 << " answer: ";

			int answer;
			cin >> answer;
			if (answer == q.numTrueAnswer) TrueAnswers++;

			system("cls");
		}
		in.close();

		mark = (12 / test->questions.size()) * TrueAnswers;
		cout << "Your MARK is: " << mark << endl;


		ofstream Stat("Stats\\" + login + ".txt", ios_base::app);
		Stat << test->name << endl;
		Stat << mark << endl;
		Stat << endl;
		Stat.close();



		system("pause");
	}

	void Statistic()
	{

		system("cls");
		cout << "Your STATISTIC: " << endl;
		string path = "Stats\\" + login + ".txt";
		ifstream Stat;
		Stat.open(path);
		char result;
		while (Stat.get(result))
		{
			cout << result;
		}
		Stat.close();


		system("pause");
	}

	void menu()override
	{

		do {
			system("cls");
			cout << "Menu Student" << endl;
			size_t c = Menu::select_vertical({
			"Testing",
			"Statistic",
			"Exit" },
			HorizontalAlignment::Center, 5);
			switch (c)
			{
			case 0:
				testing();
				break;
			case 1:
				Statistic();
				break;
			case 2:
				return;
			default:
				break;
			}
		} while (true);
	}
};

class Admin : public User
{
	void menu()override
	{
		do {
			system("cls");
			cout << "Menu Admin" << endl;
			size_t c = Menu::select_vertical({
			"Create test",
			"Register",
			"Statistic",
			"Exit"},
			HorizontalAlignment::Center, 5);
			switch (c)
			{
			case 0:
				createTest();
				break;
			case 1:
				Register();
				break;
			case 2:
				AdminStatistic();
				break;
			case 3:
				return;
			default:
				break;
			}
		} while (true);
	}
	void createTest()
	{
		test = new Test::Test;
		test->createTest();
	}

	void AdminStatistic()
	{
		system("cls");
		string path = "logins.txt";
		ifstream name;
		name.open(path);
		string log;
		vector<string> logins;
		while (!name.eof())
		{
			getline(name, login);
			logins.push_back(login);
		}
		name.close();
		for (size_t i = 0; i < logins.size(); i++)
		{
			cout << i + 1 << "." << logins[i] << endl;
		}

		cout << "Please, choise user: " << endl;
		int ch;
		cin >> ch;
		/*do
		{
			cout << "Please, choise user: " << endl;
			int ch;
			cin >> ch;
		} while (!ch > logins.size() || ch < 1);*/

		ch = ch - 1;
		system("cls");
		cout << "Statistic this user: " << endl;
		string way = "Stats\\" + logins[ch] + ".txt";
		ifstream Stat;
		Stat.open(way);
		char result;
		while (Stat.get(result))
		{
			cout << result;
		}
		Stat.close();

		system("pause");
	}
};