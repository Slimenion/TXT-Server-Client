#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>
#include "..//Functions/Func.h"
#include "../date-master/include/date/date.h"
#include <chrono>
#define _CRT_SECURE_NO_WARNINGS
#define DATA "..//ServerData/config.txt"
#define PDATA "..//PersonalData//"+nick
using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");

	long size, filesize;

	vector<string> CONNECTIONS = { "test" };

	string cmd, nick;
	fstream CON;
	ofstream config(DATA);
	namespace cr = std::chrono;
	config << date::format("%F %T", cr::floor<cr::seconds>(cr::system_clock::now()));;
	config.close();

	size = Find_Size(DATA);
	while (true) {

		filesize = Find_Size(DATA);

		if (filesize > size) {
			CON.open(DATA);
			while (!CON.eof()) { getline(CON, cmd); }
			CON.close();

			nick = cmd;
			nick.erase(Find_Split(nick), nick.size() + 1);
			cmd.erase(0, Find_Split(cmd));
			if (cmd == " START")
			{
				if (nick == "admin") {
					string command, admin;
					CON.open(DATA, ios::app);
					CON << "\n" + nick + " PASS";
					CON.close();
					long adsize, adfsize;
					adsize = Find_Size(DATA);
					while (true) {
						adfsize = Find_Size(DATA);
						if (adfsize > adsize) {
							CON.open(DATA);
							while (!CON.eof()) { getline(CON, command); }
							CON.close();
							command.erase(0, Find_Split(command));
							if (command == " admin")
							{
								CON.open(DATA, ios::app);
								CON << "\n" << nick << " ACCESS";
								CON.close();
								CONNECTIONS.push_back(nick);
								cout << date::format("%F %T", cr::floor<cr::seconds>(cr::system_clock::now()));
								cout << ": Пользователь " << nick << " был успешно подключён в систему.\n";
								break;
							}
							else {
								CON.open(DATA, ios::app);
								CON << "\n" << nick + " BAD";
								CON.close();
								cout << date::format("%F %T", cr::floor<cr::seconds>(cr::system_clock::now()));
								cout << ": Неудачная попытка входа в " << nick << ".Система заблокировала попытку взлома .\n";
								break;
							}
							adsize = adfsize;
						}

					}
				}
				else if (find(CONNECTIONS.begin(), CONNECTIONS.end(), nick) != CONNECTIONS.end())
				{
					CON.open(DATA, ios::app);
					CON << "\n" << nick + " BAD";
					CON.close();
					cout << date::format("%F %T", cr::floor<cr::seconds>(cr::system_clock::now()));
					cout << ": Файл пользователя " << nick << " был удалён с персональной системы.\n";
				}
				else
				{
					CON.open(DATA, ios::app);
					CON << "\n" << nick + " GOOD";
					CONNECTIONS.push_back(nick);
					CON.close();
					cout << date::format("%F %T", cr::floor<cr::seconds>(cr::system_clock::now()));
					cout << ": Пользователь " << nick << " был успешно подключён в систему.\n";

					size = Find_Size(PDATA);
				}
			}

			else if (cmd == " DISCONNECT") {
				if (find(CONNECTIONS.begin(), CONNECTIONS.end(), nick) != CONNECTIONS.end())
				{
					CONNECTIONS.erase(find(CONNECTIONS.begin(), CONNECTIONS.end(), nick));
					CON.open(DATA, ios::app);
					CON << "\n" << nick + " GOODBYE";
					CON.close();


					cout << date::format("%F %T", cr::floor<cr::seconds>(cr::system_clock::now()));
					cout << ": Пользователь " << nick << " успешно отключён от сервера.\n";
				}
			}

			else if (cmd == " KUBSU") {
				long size_nick, filesize_nick;
				size_nick = Find_Size(PDATA);
				while (true) {
					filesize_nick = Find_Size(PDATA);
					if (filesize_nick > size_nick) {
						fstream  PFile;
						int otm, five = 0, four = 0, three = 0;
						PFile.open(PDATA);
						PFile.seekg(-5, ios::end);
						PFile >> otm;
						PFile.close();
						cout << date::format("%F %T", cr::floor<cr::seconds>(cr::system_clock::now()));
						cout << ": " + nick + " input: " << otm << endl;
						for (int i = 0; i < 5; i++) {
							if (otm % 10 == 5) {
								five++;
							}
							else if (otm % 10 == 4) {
								four++;
							}
							else if (otm % 10 == 3) {
								three++;
							}
							else if (otm % 10 == 2) {
								break;
							}
							otm /= 10;
						}
						if (three > 0) {
							PFile.open(PDATA, ios::app);
							PFile << "\nВ этом полугодии вы не получаете стипендию. Задумайтесь о своей учёбе!";
							PFile.close();
						}
						else if (four > 0) {
							PFile.open(PDATA, ios::app);
							PFile << "\nНеплохо! Размер вашей стипендии составляет 1730 рублей.";
							PFile.close();
						}
						else if (five > 0) {
							PFile.open(PDATA, ios::app);
							PFile << "\nДа вы молодец! Размер вашей стипендии составляет 2530 рублей.";
							PFile.close();
						}
						else {
							PFile.open(PDATA, ios::app);
							PFile << "\nУ вас имеется задолженность.";
							PFile.close();
						}
						size_nick = filesize_nick;
						break;
					}
				}
			}

			else if (nick == "admin" && cmd == " STOP")
			{ // Условие закрытие сервера со стороны клиента
				cout << date::format("%F %T", cr::floor<cr::seconds>(cr::system_clock::now()));
				cout << "Сервер был закрыт администратором.\n";
				break;
			}

			size = filesize;
		}
	}
}