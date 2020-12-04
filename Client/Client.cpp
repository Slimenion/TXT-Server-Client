#include <fstream>
#include <iostream>
#include "Windows.h"
#include <string>
#include "..//Functions/Func.h"
#define DATA "..//ServerData//config.txt" // Config.txt
#define PDATA "..//PersonalData//"+nick
using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	string command, nick;
	fstream CON;

	CON.open(DATA, ios::app); // открыт файл для записи и вывода информации
	cout << "Для старта пропишите nick START\n";
	getline(cin, command);
	CON << "\n" << command;
	CON.close();

	long size, filesize;

	size = Find_Size(DATA); // Поиск размера файла

	nick = command;
	nick.erase(Find_Split(nick), nick.size() + 1); // Разделил на имя и команду
	command.erase(0, Find_Split(command) + 1);

	ofstream PFile(PDATA);
	PFile.close();

	long adsize, adfsize;
	adsize = Find_Size(DATA);

	cout << "Ожидание ответа от сервера\n";
	while (true) {

		filesize = Find_Size(DATA); // Размер файла
		if (filesize > size) {
			CON.open(DATA);
			while (!CON.eof()) { getline(CON, command); }
			CON.close();

			nick = command;
			nick.erase(Find_Split(nick), nick.size()); // Разделил на имя и команду
			command.erase(0, Find_Split(command));

			if (nick == "admin") {
				if (command == " PASS") {
					CON.open(DATA, ios::app);
					cout << "Server: Введите пароль\n";
					cin >> command;
					CON << "\n" + nick + " " + command;
					CON.close();
					Sleep(2000);
					CON.open(DATA);
					while (!CON.eof()) { getline(CON, command); }
					command.erase(0, Find_Split(command));
					if (command == " ACCESS") {
						cout << "Server: Добро пожаловать в админ-панель\n";
						break;
					}
					CON.close();
				}
			}

			else if (command == " GOOD") {
				cout << "Server: Вы успешно вошли в систему.\n";//Вошел в систему
				break;
			}
			else if (command == " BAD") {
				cout << "\aServer: Такой пользователь уже есть в сети\n";//Такой пользователь есть
				Sleep(2000);
				cout << "Потеря соединения с сервером...\n";
				break;
			}
		}
	}
	if (command == " GOOD") {
		Sleep(2000);
		cout << "Ожидается ввод команды\n";
		Sleep(1000);
		cout << "/help - чтобы узнать о всех командах сервера.\n\n";
		string text;
		while (text != "/stop") {//ожидаем команд от пользователя
			getline(cin, text);
			command = text;
			command.erase(0, Find_Split(command) + 1);

			if (command == "KUBSU") {
				CON.open(DATA, ios::app);
				CON << "\n" << text;
				CON.close();
				cout << "Введите свои оценки за сессию.\n";
				cout << "Пример: 4554 \n";
				cout << "Оценки: ";
				int otmetki = 0;
				cin >> otmetki;
				PFile.open(PDATA, ios::app);
				PFile << "\n" << otmetki;
				PFile.close();
				size = Find_Size(PDATA);
				while (true) {
					filesize = Find_Size(PDATA);
					if (filesize > size) {
						fstream file;
						file.open(PDATA);
						while (!file.eof()) getline(file, text);
						cout << text << endl;
						file.close();
						break;
					}
				}
			}
			else if (text == "/help") {
				cout << "nick+KUBSU - для того, чтобы узнать размер своей стипендии.\n";
				cout << "nick+DISCONNECT - для того чтобы отключится от сервера.\n";
				cout << "/cmd- для введения команды.\n";
				cout << "admin STOP - для принудительного закрытия сервера\n";
			}
			else if (text == "/cmd") {
				cout << "Введите команду.\n";
				getline(cin, text);

				CON.open(DATA, ios::app);
				CON << "\n" << text;
				CON.close();

				text.erase(0, Find_Split(text) + 1);
				if (text == "DISCONNECT")
				{
					size = Find_Size(DATA);
					while (true)
					{
						filesize = Find_Size(DATA);
						if (filesize > size)
						{
							CON.open(DATA);
							while (!CON.eof()) getline(CON, text);
							cout << "Server: " << text;
							CON.close();

							break;
						}
					}
				}
			}
		}
	}
	else if (command == " ACCESS") {//отладка при помощи администратора
		CON.close();
		Sleep(1000);
		cout << "Ожидается ввод админ - команды\n";
		Sleep(1000);
		cout << "/help - чтобы узнать о функциях админ панели.\n";
		string text;
		while (text != "/stop") {
			getline(cin, text);
			command = text;
			command.erase(0, Find_Split(command) + 1);
			if (text == "/help") {
				cout << "nick+KUBSU - для того, чтобы узнать размер своей стипендии.\n";
				cout << "nick+DISCONNECT - для того чтобы отключится от сервера.\n";
				cout << "/cmd- для введения команды.\n";
				cout << "admin STOP - для принудительного закрытия сервера\n";
			}
			else if (command == "STOP") {
				CON.open(DATA, ios::app);
				CON << "\nadmin STOP";
				CON.close();
				cout << "Сервер был закрыт вами.\n";
				system("pause");
				break;
			}
			else if (text == "/cmd") {
				cout << "Введите команду.\n";
				getline(cin, text);

				CON.open(DATA, ios::app);
				CON << "\n" << text;
				CON.close();

				text.erase(0, Find_Split(text) + 1);
				if (text == "DISCONNECT")
				{
					size = Find_Size(DATA);
					while (true)
					{
						filesize = Find_Size(DATA);
						if (filesize > size)
						{
							CON.open(DATA);
							while (!CON.eof()) getline(CON, text);
							cout << "Server: " << text;
							CON.close();

							break;
						}
					}
				}
			}
		}
	}
}
