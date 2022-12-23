﻿#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
using namespace std;


class Card
{
public:

	Card(int balance,
		string type,
		string number,
		string CVV,
		string date,
		string owner,
		int credit_limit)

	{

		this->balance = balance;
		this->type = type;
		this->number = number;
		this->CVV = CVV;
		this->date = date;
		this->owner = owner;
		this->credit_limit = credit_limit;

	};

	Card() {


	}

	void set_number() {
		cout << "type number" << endl;
		cin >> number;
	}

	string get_number() {
		return number;
	}


	void set_CVV() {
	Error_cvv:

		cout << "type CVV" << endl;
		cin >> CVV;

		if (CVV.size() != 3)
		{
			cout << "wrong CVV" << endl;
			goto Error_cvv;
		}

	}

	string get_CVV() {
		return CVV;
	}


	void set_date() {
		cout << "type date" << endl;
		cin >> date;
	}

	string get_date() {
		return date;
	}



	void set_owner() {
		cout << "type owner" << endl;
		getline(cin, owner);
	}

	string get_owner() {
		return owner;
	}


	void set_type(string type) {
		/*cout << "type type" << endl;*/
		/*cin >> type;*/
		this->type = type;
	}

	string get_type() {
		return type;
	}

	void set_balance(int balance) {
		this->balance = balance;
	}

	int get_balance() {
		return balance;
	}

	void set_limit(int credit_limit) {
		this->credit_limit = credit_limit;
	}

	int get_limit() {
		return credit_limit;
	}


	//вывод объекта Card на экран

	void Show() {
		cout << endl;

		cout << "type of card : " << type << endl;
		cout << "number  : " << number << endl;
		cout << "balance : " << balance << endl;
		cout << "credit limit : " << credit_limit << endl;
		cout << "CVV : " << CVV << endl;
		cout << "date : " << date << endl;
		cout << "owner : " << owner << endl;

		cout << endl;
	}

	//сохраняет карты в файл

	void Save(vector<Card> pocket) {

		ofstream out;

		out.open("bank_system.txt");

		if (out.is_open()) {

			for (size_t i = 0; i < pocket.size(); i++)
			{
				out << pocket[i].balance << " ";
				out << pocket[i].type << " ";
				out << pocket[i].number << " ";
				out << pocket[i].CVV << " ";
				out << pocket[i].date << " ";
				out << pocket[i].owner << " ";
				out << pocket[i].credit_limit << " ";
			}

		}

		out.close();

	}

	//считывает данные карт с файла

	void Read(vector<Card> pocket) {

		ifstream in("bank_system.txt");



		if (in.is_open()) {



			while (in >> balance >> type >> number >> CVV >> date >> owner >> credit_limit >> balance) {

				pocket.push_back(Card(balance, type, number, CVV, date, owner, credit_limit));

			}

		}

		in.close();

	}


	void credit_spend() {

	}

	void debit_spend() {

	}

	//пополняет карту

	void top_up() {
		int top_up;
		int tmp_balance = balance;

		cout << "how much u wanna add?" << endl;
		cin >> top_up;

		if (top_up < 0)
		{
			cout << "top up can't be bellow than 0";
		}
		else
		{
			tmp_balance += top_up;

			balance = tmp_balance;
		}

	}


	//создает карту

	Card create() {

		Card* card = new Card;
	tryAgain:


		cout << "Enter card type: 1 - debet / 2 - credit" << endl;
		int choose;
		cin >> choose;


		if (choose == 1) {
			card->set_type("debet");
			card->set_limit(0);
			card->set_number();
			card->set_CVV();
			card->set_date();
			cin.ignore();
			card->set_owner();
			card->set_balance(0);
		}


		else if (choose == 2) {
			card->set_type("credit");
			card->set_limit(10000);
			card->set_number();
			card->set_CVV();
			card->set_date();
			cin.ignore();
			card->set_owner();
			card->set_balance(0);
		}
		else
		{
			cout << "Wrong choice!" << endl;
			goto tryAgain;
		}



		return *card;
	}

private:

	string type;
	string number;
	string CVV;
	string date;
	string owner;
	int credit_limit;
	int balance;

};







int main()
{
	vector<Card> pocket;


	//временный объект Card для вызова методов
	Card tmp_card;


	int choose;
	bool No_exit = true;


	//чтение из файла
	tmp_card.Read(pocket);

Start_Menu:

	string tmp_number;

	while (No_exit) {

		cout << "1 add card\n";
		cout << "2 top up card\n";
		cout << "3 show pocket\n";
		cout << "4 clear console\n";
		cout << "5 save & exit\n";



		cin >> choose;
		switch (choose)
		{

			//создаёт объект Card и записывет в vector
		case 1:

			pocket.push_back(tmp_card.create());

			system("cls");

			break;


			//ищет в vectore объект Card с подходящим номером
		case 2:

			cout << "type nomber of card for top up \n";
			cin >> tmp_number;
			for (size_t i = 0; i < pocket.size(); i++)
			{
				if (pocket[i].get_number() == tmp_number)
				{
					pocket[i].top_up();
					goto Start_Menu;
				}

			}
			break;

			//вывод vectora объектов Card на экран
		case 3:

			for (size_t i = 0; i < pocket.size(); i++)
			{
				pocket[i].Show();
			}
			break;

			//очистка консоли и показ стартового меню
		case 4:

			system("cls");

			break;

			//сохранение в файл
		case 5:
			tmp_card.Save(pocket);
			No_exit = false;

			//выход из меню

			break;
		default:
			cout << "error\n";

			goto Start_Menu;

			//если ввел несуществующий нукт в меню правильно

			break;
		}


	}


}

