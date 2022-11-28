#pragma once
#include<iostream>
#include<list>
#include<vector>
#include<string>
#include<fstream>

using namespace std;

namespace Test
{
	class Question
	{
	public:
		string question;
		vector<string> answers;
		int numTrueAnswer;
		friend class Test;
		//friend ostream& operator<<(ostream& os, const Question& t);

		//Question() {};
		void print()
		{
			cout << this->question << endl << endl;
			for (size_t i = 0; i < answers.size(); i++)
			{
				cout << i + 1 << ". " << answers[i] << endl;
			}
		}

		void setQuestion()
		{
			cout << "New question: ";
			getline(cin, this->question);
		}

		void addAnswer()
		{
			cout << "New answer: ";
			string answ;
			getline(cin, answ);
			answers.push_back(answ);
		}

		void Save(ofstream& data) {
			data << question << endl;
			data << answers.size() << endl;
			for (size_t i = 0; i < answers.size(); i++)
			{
				data << answers[i] << endl;
			}
			data << numTrueAnswer << endl;
		}

		void setNumTrueAnswer()
		{
			cout << "Num True answer: ";
			cin >> numTrueAnswer;
			cin.ignore();
		}

		void editAnswer()
		{
			for (size_t i = 0; i < answers.size(); i++)
			{
				cout << i + 1 << ". " << answers[i] << endl;
			}
			int n;
			cin >> n;
			cin.ignore();
			cout << "New answer:";
			string answ;
			getline(cin, answ);
			answers[n - 1] = answ;
		}
	};

	class Test
	{
	public:
		string Category;
		string name;
		vector<Question> questions;

		Test() {}
		Question addQuestion()
		{
			Question q;
			q.setQuestion();
			bool continue_ = false;
			do
			{
				q.addAnswer();
				cout << "1-Yes, 0-No :";
				cin >> continue_;
				cin.ignore();
			} while (continue_);
			q.setNumTrueAnswer();
			return q;
		}

		void SetTestName()
		{
			cout << "Get test's name:";
			getline(cin, name);
		}
		void SetCategoryName()
		{
			cout << "Get Category name:";
			getline(cin, Category);
			string path = "Categorys.txt";
			ifstream ca;
			ca.open(path, ios_base::app);
			string categ;
			int h = 0;
			while (!ca.eof())
			{
				ca >> categ;
				if (categ == Category) {
					h = h + 1;
				}
			}
			ca.close();
			if (h != 1) {
				string path = "Categorys.txt";
				ofstream ca;
				ca.open("Categorys.txt", ios_base::app);
				ca << this->Category << endl;
				ca.close();

			}


		}


		void createTest()
		{
			ofstream data;
			SetCategoryName();
			SetTestName();
			bool continue_ = false;
			do
			{
				questions.push_back(addQuestion());
				cout << "1-Yes, 0-No :";
				cin >> continue_;
				cin.ignore();
			} while (continue_);
			ofstream out("testName.txt", ios::app);
			out << this->name << endl;
			out.close();
			string cat = "categorys\\" + this->name + ".txt";
			data.open(cat);
			data << this->name << endl;
			data << this->questions.size() << endl;
			for (size_t i = 0; i < questions.size(); i++)
			{
				questions[i].Save(data);
			}
			data.close();
		}

		void print()
		{
			cout << "Test's name: " << this->name << endl;
			for (size_t i = 0; i < questions.size(); i++)
			{
				cout << endl << i + 1 << " Question: ";
				questions[i].print();
				cout << endl;
			}
		}
};

