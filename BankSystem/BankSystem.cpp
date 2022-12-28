

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
struct Data {
	int month;
	int day;
	int week;
};

struct Сost_categories {

	string name_categories;
	float spend_count_categories = 0;              //общая сумма покупок в данной категории
	int count_categories = 0;                     //колличество покупок в данной категории
	Data data_pay;

	void set_data_pay() {

		int _month;
		int _week;
		int _day;
		cout << "when the transaction was made?" << endl;

		cout << "month" << endl;
		cin >> _month;

		cout << "week" << endl;
		cin >> _week;

		cout << "day" << endl;
		cin >> _day;


		data_pay.month = _month;
		data_pay.week = _week;
		data_pay.day = _day;

	}
	int GetDay() { return data_pay.day; }
	int GetMohnt() { return data_pay.month; }
	int GetWeek() { return data_pay.week; }

	int GetCount() { return count_categories; }

	string GetName_categorie() { return name_categories; }
	Сost_categories() {
		name_categories = "name";
		spend_count_categories = 0;
		count_categories = 0;
	}
	Сost_categories(string name, float spend_count_categories, int count_categories) {
		name_categories = name;
		this->spend_count_categories = spend_count_categories;
		this->count_categories = count_categories;
	}
	friend bool operator<(const Сost_categories& c1, const Сost_categories& c2);


};


bool operator<(const Сost_categories& c1, const Сost_categories& c2)
{
	return c1.count_categories < c2.count_categories;
}


class Card
{
private:
	Сost_categories cost_categiries;
	string type;
	string number;
	string CVV;
	string date;
	string owner;
	int credit_limit;
	int balance;



public:
	vector<Сost_categories> mas_cost_categiries;
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
		this->balance = 0;
		this->type = "type";
		this->number = "number";
		this->CVV = "CVV";
		this->date = "date";
		this->owner = "owner";
		this->credit_limit = 0;

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

	vector<Сost_categories> get_mas()const {

		return this->mas_cost_categiries;

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


	//выводит топ трат (категории)
	void Show_top(vector<Сost_categories>& mas_cost) {

		vector<Сost_categories> tmp_cost;
		tmp_cost = mas_cost;
		sort(tmp_cost.begin(), tmp_cost.end());

		reverse(tmp_cost.begin(), tmp_cost.end());

		for (size_t i = 0; i < 3; i++)
		{
			cout << tmp_cost[i].name_categories;
			cout << "-";
			cout << tmp_cost[i].count_categories;
			cout << endl;
		}
		cout << endl;
	}



	//выводит топ трат
	void Show_top_spend(vector<Сost_categories>& mas_cost) {

		vector<int> tmp_cost;

		for (size_t i = 0; i < mas_cost.size(); i++)
		{
			tmp_cost.push_back(mas_cost[i].spend_count_categories);
		}

		sort(tmp_cost.begin(), tmp_cost.end());

		reverse(tmp_cost.begin(), tmp_cost.end());

		for (size_t i = 0; i < 3; i++)
		{
			cout << tmp_cost[i];
			cout << endl;
		}
		cout << endl;
	}

	//сохраняет карты в файл

	void Save(vector<Card> pocket) {

		ofstream out;


		out.open("bank_system.txt", ios::out | ios::binary);


		if (out.is_open()) {
			out << pocket.size() << " ";
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

	void Save_top(vector<Сost_categories> mas_cost) {

		ofstream out_top;

		out_top.open("top_payments.txt", ios::out | ios::binary);

		if (out_top.is_open()) {
			/*out_top << mas_cost_categiries.size() << " ";*/
			for (size_t i = 0; i < mas_cost.size(); i++)
			{

				out_top << mas_cost[i].name_categories << " ";
				out_top << mas_cost[i].spend_count_categories << " ";
				out_top << mas_cost[i].count_categories << " ";


			}

		}

		out_top.close();



	}

	//считывает данные карт с файла


	void Read(vector<Card>& pocket) {

		ifstream in("bank_system.txt", ios::in | ios::binary);


		if (in.is_open()) {

			int tmp_size;
			in >> tmp_size;

			Card* tmp = new Card();
			while (in >> tmp->balance >> tmp->type >> tmp->number >> tmp->CVV >> tmp->date >> tmp->owner >> tmp->credit_limit) {

				pocket.push_back(*tmp);

			}

		}

		in.close();


	}

	void Read_top(vector<Сost_categories> mas_cost_categiries, vector<Сost_categories>& mas_cost) {

		ifstream in_top("top_payments.txt", ios::in | ios::binary);


		if (in_top.is_open()) {

			/*int tmp_size;
			in_top >> tmp_size;*/
			Сost_categories* tmp_struct = new Сost_categories();
			while (in_top >> tmp_struct->name_categories >> tmp_struct->spend_count_categories >> tmp_struct->count_categories) {


				mas_cost_categiries.push_back(*tmp_struct);

			}
			mas_cost = mas_cost_categiries;
		}

		in_top.close();


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

	void Card_selection(vector<Card>& pocket, int summ) {
		string _numbCard;
		for (size_t i = 0; i < pocket.size(); i++)
		{
			pocket[i].Show();
		}

		cout << "Enter nunber card: \n";
		cin >> _numbCard;
		for (size_t i = 0; i < pocket.size(); i++)
		{
			if (_numbCard == pocket[i].get_number()) {



				if (pocket[i].get_type() == "credit")
				{
					if (summ <= pocket[i].get_balance()) {
						pocket[i].set_balance(pocket[i].get_balance() - summ);
					}
					else if (summ <= pocket[i].get_limit())
					{
						pocket[i].set_limit(pocket[i].get_limit() - summ);
					}
					else
					{
						cout << "Not enough money";
					}

				}

				if (pocket[i].get_type() == "debet")
				{
					if (summ <= pocket[i].get_balance()) {
						pocket[i].set_balance(pocket[i].get_balance() - summ);
					}
				}
				else
				{
					cout << "Not enough money";
				}

			}

		}
	}

	void cost_report(vector<Card>& pocket, vector<Сost_categories>& mas_cost) {
	Begin:
		cout << "\tReport categories: " << endl;
		cout << "   daily report   - eneter '1' " << endl;
		cout << "   weekly report  - eneter '2' " << endl;
		cout << "   monthly report - eneter '3' " << endl;
		int numb;
		int count = 0;
		cin >> numb;
		if (numb > 0 && numb < 4) {
			if (numb == 1) {
				cout << "enter the day for the report " << endl;
				int _day;

				cin >> _day;

				for (int i = 0; i < mas_cost.size(); i++)
				{
					if (_day == mas_cost[i].GetDay()) {
						count++;
						cout << "On this day there were expenses by category: " << mas_cost[i].GetName_categorie() << endl;
					}

				}
				if (count == 0) {
					cout << "there were no charges that day! " << endl;
				}

			}
			if (numb == 2) {
				cout << "enter the week for the report " << endl;
				int _week;
				cin >> _week;
				for (int i = 0; i < mas_cost.size(); i++)
				{
					if (_week == mas_cost[i].GetWeek()) {
						count++;
						cout << "This week's expenses by category: " << mas_cost[i].GetName_categorie() << endl;
					}
				}
				if (count == 0) {
					cout << "no expenses this week! " << endl;
				}
			}
			if (numb == 3) {
				cout << "enter the week for the report " << endl;
				int _mohnt;
				cin >> _mohnt;
				for (int i = 0; i < mas_cost.size(); i++)
				{
					if (_mohnt == mas_cost[i].GetMohnt()) {
						count++;
						cout << "This month's expenses by category: " << mas_cost[i].GetName_categorie();
					}
				}
				if (count == 0) {
					cout << "no expenses this month! " << endl;
				}
			}
		}
		else {
			cout << "Wrong categori";
			goto Begin;
		}

	}
	void Categori_Menu(vector<Card>& pocket, vector<Сost_categories>& mas_cost) {

		int categori;
		int sum = 0;

		cout << "what categori u wanna use?" << endl;
		cout << "1 - Food" << endl;
		cout << "2 - Entertaiment " << endl;
		cout << "3 - Communal_payments " << endl;
		cout << "4 - Subscriptions " << endl;
		cout << "5 - Other" << endl;


	Start:
		cin >> categori;

		switch (categori)
		{

		case 1:
			cout << "enter the purchase amount in this category: " << endl;

			cin >> sum;
			Card_selection(pocket, sum);
			mas_cost[0].spend_count_categories += sum;
			mas_cost[0].count_categories++;
			mas_cost[0].set_data_pay();




			break;

		case 2:
			cout << "enter the purchase amount in this category: " << endl;

			cin >> sum;
			Card_selection(pocket, sum);
			mas_cost[1].spend_count_categories += sum;
			mas_cost[1].count_categories++;
			mas_cost[1].set_data_pay();

			break;

		case 3:
			cout << "enter the purchase amount in this category: " << endl;

			cin >> sum;
			Card_selection(pocket, sum);
			mas_cost[2].spend_count_categories += sum;
			mas_cost[2].count_categories++;
			mas_cost[2].set_data_pay();

			break;

		case 4:
			cout << "enter the purchase amount in this category: " << endl;

			cin >> sum;
			Card_selection(pocket, sum);
			mas_cost[3].spend_count_categories += sum;
			mas_cost[3].count_categories++;
			mas_cost[3].set_data_pay();

			break;

		case 5:
			cout << "enter the purchase amount in this category: " << endl;

			cin >> sum;
			Card_selection(pocket, sum);
			mas_cost[4].spend_count_categories += sum;
			mas_cost[4].count_categories++;
			mas_cost[4].set_data_pay();

			break;

		default:

			cout << "Wrong categori";
			goto Start;

			break;
		}
	}


};








int main()
{
	vector<Card> pocket;

	vector<Сost_categories> mas_cost;
	Сost_categories categories("Food", 0, 0);
	Сost_categories categories1("Entertaiment", 0, 0);
	Сost_categories categories2("Communal_payments", 0, 0);
	Сost_categories categories3("Subscriptions", 0, 0);
	Сost_categories categories4("Other", 0, 0);
	mas_cost.push_back(categories);
	mas_cost.push_back(categories1);
	mas_cost.push_back(categories2);
	mas_cost.push_back(categories3);
	mas_cost.push_back(categories4);
	//временный объект Card для вызова методов
	Card tmp_card;


	string number_card;
	int choose;
	bool No_exit = true;


	//чтение из файла
	tmp_card.Read(pocket);
	tmp_card.Read_top(tmp_card.get_mas(), mas_cost);
	

Start_Menu:

	string tmp_number;

	while (No_exit) {

		cout << "1 add card\n";
		cout << "2 top up card\n";
		cout << "3 show pocket\n";
		cout << "4 clear console\n";
		cout << "5 card replenishment\n";
		cout << "6 costs by category\n";
		cout << "7 cost and category report\n";
		cout << "8 Show top by catigories\n";
		cout << "9 Show top by summ\n";
		cout << "10 save & exit\n";



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
			//пополнение карт
		case 5:
			cout << "choose a card to replenish your account" << endl;
			for (size_t i = 0; i < pocket.size(); i++)
			{
				pocket[i].Show();
			}

			cout << "Enter nunber card: \n";
			cin >> number_card;
			for (size_t i = 0; i < pocket.size(); i++)
			{
				if (number_card == pocket[i].get_number()) {
					int sum = 0;
					cout << "enter the amount to replenish the account\n";
					cin >> sum;
					pocket[i].set_balance(sum);
				}
			}

			break;

			//сохранение в файл выход из меню
		case 6:
			tmp_card.Categori_Menu(pocket, mas_cost);


			break;
			//отчет по затратам и категориям
		case 7:
			tmp_card.cost_report(pocket, mas_cost);


			break;

		case 8:
			tmp_card.Show_top(mas_cost);


			break;


		case 9:
			tmp_card.Show_top_spend(mas_cost);


			break;


			//сохранение в файл выход из меню
		case 10:
			tmp_card.Save(pocket);
			tmp_card.Save_top(mas_cost);
			No_exit = false;

			break;
		default:
			cout << "error\n";

			goto Start_Menu;

			//если ввел несуществующий нукт в меню правильно

			break;
		}


	}


}



