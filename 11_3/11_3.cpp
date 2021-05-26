#include <iostream>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <errno.h>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;

enum Specialnist { KN, ME, IF, FI, TN }; // перелік спеціальностей  
string specialnistList[] = { "комп науки", "мат і економ", "інформ", "фіз і інформ", "труд навч" }; // масив назв спеціальностей
struct Student
{
	char prizv[100];
	int kurs;
	Specialnist spec;
	int fiz;
	int mat;
	int avarage;
	union
	{
		int prog;
		int chis_metod;
		int pedagog;
	};
};

void Create(char* fname);
void LoadFile(char* fname);
void Sort(char* fname);
void IndexSort(char* fname, char* gname);
int Search(char* fname);

int main()
{
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу
	char fname[61];
	char gname[61];
	char ch;
	int found;
	do
	{
		cout << endl;
		cout << "Select:" << endl;
		cout << "[1] - Введення та збереження інформації;" << endl;
		cout << "[2] - Завантаження та вивід інформації;" << endl;
		cout << "[3] - Сортування" << endl;
		cout << "[4] - Індексне сортування" << endl;
		cout << "[5] - Пошук" << endl << endl;
		cout << "[0] - Завершення роботи." << endl << endl;
		cout << "Ваш вибір: "; cin >> ch;
		switch (ch)
		{
		case '0':
			break;
		case '1':
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << endl;
			cout << "Назва файлу: "; cin.getline(fname, sizeof(fname));
			Create(fname);
			break;
		case '2':
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << endl;
			cout << "Назва файлу: "; cin.getline(fname, sizeof(fname));
			cout << endl;
			LoadFile(fname);
			break;
		case '3':
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << endl;
			cout << "Назва файлу: "; cin.getline(fname, sizeof(fname));
			cout << endl;
			Sort(fname);
			cout << "Файл відсортовано" << endl;
			cout << endl;
			break;
		case '4':
			cin.get(); // очищуємо буфер клавіатури – щоб не було символу
			cin.sync(); // "кінець рядка", який залишився після вводу числа
			cout << endl;
			cout << "Назва файлу: "; cin.getline(fname, sizeof(fname));
			cout << endl;
			cout << "Назва додаткового файлу: "; cin.getline(gname, sizeof(gname));
			cout << endl;
			IndexSort(fname, gname);
			cout << "Відсортований файл створено!" << endl;
			cout << endl;
			break;
		case '5':
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок
			cout << endl;
			cout << "Назва файлу: "; cin.getline(fname, sizeof(fname));
			cout << endl;
			Sort(fname);
			if ((found = Search(fname)) != -1) {
				cout << "Знайдено студента в позиції \'" << found + 1 << "\"" << endl;
				LoadFile(fname);
			}
			else {
				cout << "Шуканого студента не знайдено" << endl;
			}
			break;
		default:
			cout << "Помилка вводу! ";
		}
	} while (ch != '0');
	return 0;
}
void Create(char* fname)
{
	ofstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Помилка відкриття файлу '" << fname << "'" << endl;
		f.close();
		return;
	}
	int spec;
	Student student;
	char ch;
	int i = 0;
	do
	{
		cout << "Cтудент № " << i + 1 << ":" << endl; i++;
		cout << "прізвище: "; cin >> student.prizv;
		cout << "курс: "; cin >> student.kurs;
		if (student.kurs <= 0) {
			student.kurs = 1;
			cout << endl;
			cout << "Курс розпізнано, як перший!" << endl;
			cout << endl;
		}
		if (student.kurs > 6) {
			student.kurs = 6;
			cout << endl;
			cout << "Курс розпізнано, як \"6\"!" << endl;
			cout << endl;
		}
		cout << "оцінка з фізики: "; cin >> student.fiz;
		if (student.fiz > 5) {
			student.fiz = 5;
			cout << endl;
			cout << "Оцінка розпізнана, як максимальна!" << endl;
			cout << endl;
		}
		if (student.fiz < 0) {
			student.fiz = 0;
			cout << endl;
			cout << "Оцінка розпізнана, як мінімальна!" << endl;
			cout << endl;
		}
		cout << "оцінка з математики: "; cin >> student.mat;
		if (student.mat > 5) {
			student.mat = 5;
			cout << endl;
			cout << "Оцінка розпізнана, як максимальна!" << endl;
			cout << endl;
		}
		if (student.mat < 0) {
			student.mat = 0;
			cout << endl;
			cout << "Оцінка розпізнана, як мінімальна!" << endl;
			cout << endl;
		}
		cout << "cпеціальність (0 - комп. науки, 1 - мат і економ, 2 - інформ, 3 - фіз і інформ, 4 - труд. навч): ";  cin >> spec;
		if (spec > 4) {
			cout << endl;
			cout << "============================================================================================================" << endl;
			cout << endl;
			cout << "Схоже, ви ввели неправильне значення спеціальності!" << endl;
			cout << "Програма продовжить роботу з спеціальностю за замовчуванням - комп. науки!" << endl;
			cout << "Перезапустіть програму для введення правильного номера спеціальності." << endl;
			cout << endl;
			cout << "============================================================================================================" << endl;
			cout << endl;
			spec = 0;
		}
		student.spec = (Specialnist)spec; // присвоєння спеціальності, введенної користувачем через перелік
		switch (student.spec)
		{
		case KN:
			cout << "оцінка з програмування: "; cin >> student.prog;
			if (student.prog > 5) {
				student.prog = 5;
				cout << endl;
				cout << "Оцінка розпізнана, як максимальна!" << endl;
				cout << endl;
			}
			if (student.prog < 0) {
				student.prog = 0;
				cout << endl;
				cout << "Оцінка розпізнана, як мінімальна!" << endl;
				cout << endl;
			}
			student.avarage = (student.mat + student.fiz + student.prog) / 3.0;
			break;
		case ME:
			cout << "оцінка з педагогіки: "; cin >> student.pedagog;
			if (student.pedagog > 5) {
				student.pedagog = 5;
				cout << endl;
				cout << "Оцінка розпізнана, як максимальна!" << endl;
				cout << endl;
			}
			if (student.pedagog < 0) {
				student.pedagog = 0;
				cout << endl;
				cout << "Оцінка розпізнана, як мінімальна!" << endl;
				cout << endl;
			}
			student.avarage = (student.mat + student.fiz + student.pedagog) / 3.0;
			break;
		case IF:
			cout << "оцінка з чисельних методів: "; cin >> student.chis_metod;
			if (student.chis_metod > 5) {
				student.chis_metod = 5;
				cout << endl;
				cout << "Оцінка розпізнана, як максимальна!" << endl;
				cout << endl;
			}
			if (student.chis_metod < 0) {
				student.chis_metod = 0;
				cout << endl;
				cout << "Оцінка розпізнана, як мінімальна!" << endl;
				cout << endl;
			}
			student.avarage = (student.mat + student.fiz + student.chis_metod) / 3.0;
			break;
		case FI:
			cout << "оцінка з педагогіки: "; cin >> student.pedagog;
			if (student.pedagog > 5) {
				student.pedagog = 5;
				cout << endl;
				cout << "Оцінка розпізнана, як максимальна!" << endl;
				cout << endl;
			}
			if (student.pedagog < 0) {
				student.pedagog = 0;
				cout << endl;
				cout << "Оцінка розпізнана, як мінімальна!" << endl;
				cout << endl;
			}
			student.avarage = (student.mat + student.fiz + student.pedagog) / 3.0;
			break;
		case TN:
			cout << "оцінка з педагогіки: "; cin >> student.pedagog;
			if (student.pedagog > 5) {
				student.pedagog = 5;
				cout << endl;
				cout << "Оцінка розпізнана, як максимальна!" << endl;
				cout << endl;
			}
			if (student.pedagog < 0) {
				student.pedagog = 0;
				cout << endl;
				cout << "Оцінка розпізнана, як мінімальна!" << endl;
				cout << endl;
			}
			student.avarage = (student.mat + student.fiz + student.pedagog) / 3.0;
			break;
		}
		if (!f.write((char*)&student, sizeof(Student)))
		{
			cerr << "Помилка запису в файл." << endl;
			f.close();
		}
		cout << "Продовжити? (Y/N) "; cin >> ch;
	} while (ch == 'Y' || ch == 'y');
	f.close();
}
void LoadFile(char* fname)
{
	ifstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Помилка відкриття файлу '" << fname << "'" << endl;
		f.close();
		return;
	}
	Student student;
	cout << "============================================================================================================"
		<< endl;
	cout << "| № | Прізвище | Курс | Cпеціальність | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |"
		<< endl;
	cout << "------------------------------------------------------------------------------------------------------------"
		<< endl;
	int i = 0;
	while (f.read((char*)&student, sizeof(Student)))
	{
		cout << "|" << setw(2) << right << i + 1 << " "; i++;
		cout << "| " << setw(9) << left << student.prizv
			<< "| " << setw(2) << right << student.kurs << "  "
			<< " | " << setw(14) << left << specialnistList[student.spec]
			<< setw(4) << "| " << setw(3) << left << student.fiz << "  "
			<< setw(6) << "| " << setw(6) << left << student.mat << " ";
		switch (student.spec)
		{
		case KN:
			cout << setw(8) << "| " << setw(7) << left << student.prog << setw(19)
				<< " | " << setw(12) << left
				<< "| " << left << " |" << endl;
			break;
		case ME:
			cout << "" << setw(15) << "| " << " "
				<< "" << setw(18) << "| "
				<< setw(6) << "| " << setw(6) << left << student.pedagog << " |" << endl;
			break;
		case IF:
			cout << "" << setw(15) << "| " << setw(9) << " |" << " "
				<< setw(8) << student.chis_metod << " |" << " "
				<< setw(10) << "" << " |" << endl;
			break;
		case FI:
			cout << "" << setw(15) << "| " << " "
				<< "" << setw(18) << "| "
				<< setw(6) << "| " << setw(6) << left << student.pedagog << " |" << endl;
			break;
		case TN:
			cout << "" << setw(15) << "| " << " "
				<< "" << setw(18) << "| "
				<< setw(6) << "| " << setw(6) << left << student.pedagog << " |" << endl;
			break;
		}
	}
	cout << "============================================================================================================"
		<< endl;
	cout << endl;
	f.close();
}

int SearchOne(char* fname)
{
	ifstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Помилка вікриття файлу '" << fname << "'" << endl;
		f.close();
		return 0;
	}
	Student student;
	int k = 0;
	while (f.read((char*)&student, sizeof(Student)))
	{
		if (student.mat == 5) {
			if (student.fiz == 5) {
				k++;
			}
		}
	}
	return k;
	f.close();
}

int SearchTwo(char* fname)
{
	ifstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Помилка відкриття файлу '" << fname << "'" << endl;
		f.close();
		return 0;
	}
	Student student;
	int k = 0, n = 0;
	while (f.read((char*)&student, sizeof(Student)))
	{
		if (student.mat == 5) {
			k++;
			n++;
		}
		if (student.fiz == 5) {
			k++;
			n++;
		}
		switch (student.spec) {
		case KN:
			if (student.prog == 5) {
				k++;
				n++;
			}
			break;
		case ME:
			if (student.pedagog == 5) {
				k++;
				n++;
			}
			break;
		case IF:
			if (student.chis_metod == 5) {
				k++;
				n++;
			}
			break;
		case TN:
			if (student.pedagog == 5) {
				k++;
				n++;
			}
			break;
		case FI:
			if (student.pedagog == 5) {
				k++;
				n++;
			}
			break;
		}
		cout << "У студента " << student.prizv << " оцінок \"відмінно\": " << k << endl;
		k = 0;
	}
	cout << endl;
	f.close();
	return n;
}

void Sort(char* fname) {
	ifstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Помилка відкриття файлу '" << fname << "'" << endl;
		f.close();
		return;
	}
	f.seekg(0, ios::end); // курсор ставиться в кінець
	int size = f.tellg(); // вказує місце де зараз знаходиться курсор і цим самим визначає величину файлу
	size = size / sizeof(Student); // визначається кількість студентів
	f.seekg(0, ios::beg); // повернення курсору на початок
	Student* student = new Student[size];
	Student temp;
	f.read((char*)student, size * sizeof(Student)); // зчитуюються студенти з файлу 
	f.close();
	for (int i = 0; i < size - 1; i++) { // Сортування бульбашкою
		for (int j = size - 1; j > i; j--) {
			string prizvOne = student[j].prizv;
			string prizvTwo = student[j - 1].prizv;
			if ((student[j].spec < student[j - 1].spec)
				||
				(student[j].spec == student[j - 1].spec &&
					student[j].kurs < student[j - 1].kurs)
				||
				(student[j].spec == student[j - 1].spec &&
					student[j].kurs == student[j - 1].kurs &&
					prizvOne < prizvTwo))
			{
				temp = student[j];
				student[j] = student[j - 1];
				student[j - 1] = temp;
			}
		}
	}
	f.close();
	ofstream file(fname, ios::binary);
	file.write((char*)student, size * sizeof(Student));
	file.close();
}

void IndexSort(char* fname, char* gname) {
	ifstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Помилка відкриття файлу '" << fname << "'" << endl;
		f.close();
		return;
	}
	f.seekg(0, ios::end); // курсор ставиться в кінець
	int size = f.tellg(); // вказує місце де зараз знаходиться курсор і цим самим визначає величину файлу
	size = size / sizeof(Student); // визначається кількість студентів
	f.seekg(0, ios::beg); // повернення курсору на початок
	Student* student = new Student[size];
	Student temp;
	f.read((char*)student, size * sizeof(Student)); // зчитуюються студенти з файлу 
	for (int i = 0; i < size - 1; i++) { // Сортування бульбашкою
		for (int j = size - 1; j > i; j--) {
			string prizvOne = student[j].prizv;
			string prizvTwo = student[j - 1].prizv;
			if ((student[j].spec < student[j - 1].spec)
				||
				(student[j].spec == student[j - 1].spec &&
					student[j].kurs < student[j - 1].kurs)
				||
				(student[j].spec == student[j - 1].spec &&
					student[j].kurs == student[j - 1].kurs &&
					prizvOne < prizvTwo))
			{
				temp = student[j];
				student[j] = student[j - 1];
				student[j - 1] = temp;
			}
		}
	}
	f.close();
	ofstream file(gname, ios::binary);
	if (!file)
	{
		cerr << "Помилка відкриття файлу '" << gname << "'" << endl;
		f.close();
		return;
	}
	file.write((char*)student, size * sizeof(Student));
	file.close();
}

int Search(char* fname) {
	ifstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Помилка відкриття файлу '" << fname << "'" << endl;
		f.close();
		return -1;
	}
	Specialnist special;
	int kurs;
	int ispec;
	string prizv;
	cout << endl;
	cout << "Введіть ключі пошуку: " << endl << endl;
	cout << "cпеціальність (0 - комп. науки, 1 - мат і економ, 2 - інформ, 3 - фіз і інформ, 4 - труд. навч): ";
	cin >> ispec;
	special = (Specialnist)ispec;
	cout << " прізвище: "; cin >> prizv;
	cout << " курс: "; cin >> kurs;
	cout << endl;

	f.seekg(0, ios::end); // курсор ставиться в кінець
	int size = f.tellg(); // вказує місце де зараз знаходиться курсор і цим самим визначає величину файлу
	size = size / sizeof(Student); // визначається кількість студентів
	f.seekg(0, ios::beg); // повернення курсору на початок
	Student* student = new Student[size];
	f.read((char*)student, size * sizeof(Student));
	int L = 0, R = size, m;
	do { // Бінарний пошук
		m = (L + R) / 2;
		string OriginalPrizv = student[m].prizv;
		if (OriginalPrizv == prizv && student[m].spec == special && student[m].kurs == kurs) {
			return m;
		}
		if ((student[m].kurs < kurs)
			||
			(student[m].kurs == kurs &&
				student[m].spec < special)
			||
			(student[m].kurs == kurs &&
				student[m].spec == special &&
				student[m].prizv < prizv)) {
			L = m + 1;
		}
		else {
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}