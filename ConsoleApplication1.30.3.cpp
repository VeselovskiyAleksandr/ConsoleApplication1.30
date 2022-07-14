// ConsoleApplication1.30.3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Задача 3. Симуляция работы компании.

#include <iostream>
#include <locale.h>
#include <ctime>
#include <string>
#include <cassert>
using namespace std;

class Directorate;
class MiddleLink;

class BasicWorkers {
	string workerName = "";
	int numberTask=0;
public:
	void setWorkerName(string wN) {
		workerName = wN;
	}

	string getWorkerName() {
		return workerName;
	}

	void setNumberTask(int numTask) {
		numberTask = numTask;
	}

	int getNumberTask() {
		return numberTask;
	}

	BasicWorkers(string inworkerName, int innumberTask):workerName(inworkerName), numberTask(innumberTask){};
};

class MiddleLink {
	string managerName = "";
	int quantityWorkers= 0, order=0, initialTask=0;//initialTask - начальная задача отдела
   
public:

	void setQuantityWorkers(int numW) {
		quantityWorkers = numW;
	}

	int getQuantityWorkers() {
		return quantityWorkers;
	}
	void setManagerName(string manName) {
		managerName = manName;
	}

	string getManagerName() {
		return managerName;
	}

	void setOrders(int ord) {
		order = ord;
	}

	int getOrders() {
		return order;
	}

	void setInitialTask(int ntTask) {
		initialTask = ntTask;
	}

	int getInitialTask() {
		return initialTask;
	}
private:
	BasicWorkers** worker = nullptr;
public:
	BasicWorkers* getWorker(int index) {
		if (index < 0 || index >= quantityWorkers) {
			return nullptr;
		}
		return  worker[index];
	}

		MiddleLink(int inOrders, int inquantityWorkers, string inworkerName, int innumberTask, int ininitialTask) :quantityWorkers(inquantityWorkers), initialTask(ininitialTask), order(inOrders) {
		assert(inquantityWorkers >= 0);
		int countTask = 0;
		cout << "\nКоличество задач, которые должен решить отдел: " << getOrders();
		 worker = new BasicWorkers * [inquantityWorkers];
		for (int i = 0; i < inquantityWorkers; ++i) {
           worker[i] = new BasicWorkers(inworkerName, innumberTask);
				string nameW = "";
				int tType = 0;
				if (getOrders() < getQuantityWorkers()) {
					cout << "\nОтделу требуется дополнительно "<<getQuantityWorkers()-getOrders()<<" задач";
					time_t t = time(0);
					time_t completion = t + 5;
					int interval = 0;
					do {
						time_t  start = time(nullptr);
						interval = (int)difftime(completion, start);
						if (completion == start) {
							break;
						}
					} while (completion);
					cout << "\nОтделу дополнительно поставлено " << getQuantityWorkers()-getOrders() << " задач";
					setOrders(getOrders() + getQuantityWorkers() - getOrders());
				}
				cout << "\n Рабочий: ";
				cin >> nameW;
				worker[i]->setWorkerName(nameW);
					tType = rand() % 3;
					cout << " выполняет задачу: " << getInitialTask() + countTask << " тип ";
					if (tType == 0) cout << " A";
					else if (tType == 1) cout << " B";
					else if (tType == 2) cout << " C";
					worker[i]->setNumberTask(getInitialTask() + countTask);
					countTask++;
		}
		for (int j = 0; j < getQuantityWorkers(); j++) {
				delete worker[j];
			}
	}
};

class Directorate {

	string  directorName = "";
	int  quantityDivisions=0, directives = 0 ;
public:

	void setQuantityDivisions(int qDiv) {
		quantityDivisions = qDiv;
	}

	void setDirectives(int direct) {
		directives = direct;
	}

	void setDirectorName(string dirName) {
		directorName = dirName;
	}

	int getQuantityDivisions() {
		return quantityDivisions;
}

	int getDirectives() {
		return directives;
	}
private:
	MiddleLink** manager = nullptr;
public:
	MiddleLink* getManager(int index) {
		if (index < 0 || index >= quantityDivisions) {
			return nullptr;
		}
		return manager[index];
	}
	Directorate( int inDirectives, int inOrder, int inquantityDivisions, string  indirectorName, int inquantityWorkers, string inworkerName, int innumberTask, int ininitialTask) :  directives(inDirectives), quantityDivisions(inquantityDivisions), directorName(indirectorName) {
		assert(quantityDivisions >= 0);
		cout << "\nУкажите имя директора: ";
		cin >> indirectorName;
        cout << "\nВведите указания главы компании: ";
        cin >> inDirectives;
		cout << "\nУкажите количество подразделений в компании: ";
		cin >> inquantityDivisions;
		setQuantityDivisions(inquantityDivisions);
		manager = new MiddleLink*[inquantityDivisions];
		for (int i = 0; i < inquantityDivisions; ++i) {
        if (i == 0) {
				ininitialTask = 1;
			}
			else {
				ininitialTask = manager[i - 1]->getInitialTask()+ manager[i - 1]->getQuantityWorkers();
			}
                cout << "\nУкажите имя руководителя отдела: ";
			string mN = "";
			cin >> mN;
				cout << "\nУкажите количество рабочих в отделе: ";
				cin >> inquantityWorkers;
			inOrder = rand() % (inDirectives + i);
			    manager[i] = new MiddleLink( inOrder, inquantityWorkers, inworkerName, innumberTask, ininitialTask);
				manager[i]->setInitialTask(ininitialTask);
				manager[i]->setManagerName(mN);
				manager[i]->setOrders(inOrder);
				manager[i]->setQuantityWorkers(inquantityWorkers);
		}
		for (int i = 0; i < getQuantityDivisions(); ++i) {
				delete  manager[i];
			}
	}
};

int main()
 {
	setlocale(LC_ALL, "Russian");
	srand(time(nullptr));
	int directive=0, orders=0, quantityDivision=0,  quantityWorker=0,  numberTask=0, initialTask=0;
	string directorName = "", workerName = "";
	Directorate* directorate = new Directorate(directive, orders, quantityDivision,  directorName, quantityWorker, workerName, numberTask, initialTask);
	delete  directorate;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
