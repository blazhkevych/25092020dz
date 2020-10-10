/*
Написати програму «Інформаційну систему про студентів». Система містить інформацію про студентів. Кожен студент містить поля: ПІБ, вік.

Забезпечити систему таким меню:

1. Добавити студента в початок списку;
2. Добавити студента в кінець списку;
3. Добавити студента в позицію списку;
4. Видалити студента зі системи;
5. Видалити студентів старше зазначеного віку;
6. Видалити студентів у яких є набір введених символів у прізвищі (Введено «ко» Потрібно видалити студентів Устименко, Петренко, Мокон, Колотило, …);
7. Відсортувати за ПІБ від А-Я;
8. Відсортувати за ПІБ від Я-А;
9. Відсортувати за віком по зростанню;
10. Відсортувати за віком по спаданню;
11. Видалити дублікати студентів.
12. Виведення інформації про всіх студентів;
13. Виведення інформації про конкретного студента.
*/
#include <iostream>
#include <Windows.h>
#include <list>
#include <string>
#include <Windows.h>
#include <functional>

#include "Date.h"
#include "Menu.h"
using namespace std;

class Student
{
private:
	string fullName;
	Date dob;
public:
	Student(string fullName, Date dob) :
		fullName(fullName), dob(dob) {	};

	int GetAge() const { return dob.DifferenceYear(); }
	string GetName() const { return fullName; };
	friend ostream& operator<<(ostream& out, Student& obj);
	friend bool operator==(const Student& left, const Student& right);
};

bool operator==(const Student& left, const Student& right)
{
	return !left.fullName.compare(right.fullName);
}

ostream& operator<<(ostream& out, Student& obj)
{
	out << obj.fullName;
	out << " " << obj.dob.DifferenceYear() << " года.\n";
	return out;
}

Student GetStudFromUser()
{
	string name;
	int day, month, year;

	cout << "Введите имя студента: ";
	getline(cin, name);
	cout << "Введите дату рождения (День, месяц, год): ";
	cin >> day >> month >> year;

	return Student(name, Date(day, month, year));
}

void AddInPosition(int pos, Student nStud, list<Student>& stList)
{
	if (pos > stList.size()) throw "Невозможно вставить в позицию";
	auto iter = stList.begin();
	advance(iter, --pos);
	stList.insert(iter, nStud);
}

void Show(list<Student>& stList)
{
	for (auto i : stList)
		cout << i;
}

Student& Find(string name, list<Student>& stList)
{
	for (auto i : stList)
	{
		if (i.GetName() == name)
			return i;
	}
	throw "Студент не найден.";
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	Color(BACKGROUND, FOREGROUND);
	system("cls");
	const char* s[]{
		"Добавить студента в начало",
		"Добавить студента в конец",
		"Добавить студента в позицию",
		"Удалить студента из системы",
		"Удалить студентов старше указанного возраста",
		"Удалить студентов у которых есть набор введенных символов в фамилии",
		"Отсортировать по ФИО от А-Я",
		"Отсортировать по ФИО от Я-А",
		"Отсортировать по возрасту по возрастанию",
		"Отсортировать по возрасту по убыванию",
		"Удалить дубликаты студентов",
		"Вывод информации обо всех студентах",
		"Вывод информации о конкретном студенте"
	};
	int sizem = sizeof(s) / 4;
	int pm = 0;
	list<Student> stList;

	stList.emplace_front("Чарльз Дарвин", Date(17, 06, 1998));
	stList.emplace_front("Октавиан Август", Date(2, 11, 1995));
	stList.emplace_front("Николай Коперник", Date(19, 4, 2000));
	stList.emplace_front("Майкл Фарадей", Date(6, 5, 1993));
	stList.emplace_back("Джеймс Максвелл", Date(18, 3, 1992));
	stList.emplace_back("Джордж Вашингтон", Date(11, 2, 1987));
	stList.emplace_back("Томас Эдисон", Date(7, 7, 1988));
	stList.emplace_back("Томас Эдисон", Date(7, 7, 1988));
	while (true)
	{
		pm = Menu(s, sizem, pm);
		system("cls");
		try {
			switch (pm)
			{
			case -1: return 0;
			case 0:
				stList.push_front(GetStudFromUser());
				break;
			case 1:
				stList.push_back(GetStudFromUser());
				break;
			case 2:
			{
				int pos = 0;
				cout << "В какую позицию добавить? ";
				cin >> pos;
				AddInPosition(pos, move(GetStudFromUser()), stList);
				break;
			}
			case 3:
			{
				string name;
				cout << "Введите ФИО: ";
				getline(cin, name);
				stList.remove(Student(name, Date()));
				break;
			}
			case 4:
			{
				int age;
				cout << "Введите возраст: ";
				cin >> age;
				stList.remove_if([&age](Student& obj) {return obj.GetAge() > age; });
				Show(stList);
				break;
			}
			case 5:
			{
				string word;
				cout << "Введите набор букв: ";
				getline(cin, word);
				stList.remove_if([&word](Student& obj) {
					return obj.GetName().substr(0, obj.GetName().find(' ')).find(word) != -1; });
				Show(stList);
				break;
			}
			case 6:
				stList.sort([](Student& left, Student& right) {return left.GetName().compare(right.GetName()) < 0; });
				Show(stList);
				break;
			case 7:
				stList.sort([](Student& left, Student& right) {return left.GetName().compare(right.GetName()) > 0; });
				Show(stList);
				break;
			case 8:
				stList.sort([](Student& left, Student& right) {return left.GetAge() < right.GetAge(); });
				Show(stList);
				break;
			case 9:
				stList.sort([](Student& left, Student& right) {return left.GetAge() > right.GetAge(); });
				Show(stList);
				break;
			case 10:
				stList.sort([](Student& left, Student& right) {return left.GetName().compare(right.GetName()) < 0; });
				stList.unique();
				Show(stList);
				break;
			case 11:
				Show(stList);
				break;
			case 12:
			{
				string name;
				cout << "Введите ФИО студента: ";
				getline(cin, name);
				cout << Find(name, stList) << endl;
				break;
			}
			}
			Color(BACKGROUND, 2);
			cout << "\nOK\n";
			_getch();
		}
		catch (const char* exp)
		{
			cout << exp << endl;
			_getch();
		}
	}
}