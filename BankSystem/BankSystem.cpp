

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
using namespace std;
struct Data {
	int month;
	int day;
	int week;
};
struct Сost_categories {
	string food = "Food";
	string entertaiment = "Entertaiment";
	string communal_payments = "Communal_payments";
	string subscriptions = "Subscriptions";
	string other = "Other";
	float spend_countFood = 0;              //общая сумма покупок в данной категории
	float spend_countEntertaiment = 0;  
	float spend_countCom_payments = 0;
	float spend_countSubscript = 0;
	float spend_countOther = 0;
	int countFood = 0;                     //колличество покупок в данной категории
	int countEntertaiment = 0;
	int countCom_payments = 0;
	int countSubscript = 0;
	int countOther = 0;
};

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

		out.open("bank_system.txt", ios::out  | ios::binary);

		if (out.is_open()) {
			out << pocket.size() << " ";
			for (size_t i = 0; i < pocket.size(); i++)
			{
				out << pocket[i].balance<<" ";
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

	void Read(vector<Card> &pocket) {

		ifstream in("bank_system.txt",ios::in | ios::binary);



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
	void Card_selection(vector<Card>& pocket,int summ) {
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
				
				cout << "enter the amount to replenish the account\n";
				
				if (summ <= pocket[i].get_balance()) {
                   pocket[i].set_balance(pocket[i].get_balance()-summ);
					
				   pocket[i].set_data_pay();
				
				}
				
			}
		}





	}
	void Categori_Menu(vector<Card>& pocket) {

		int categori;
		int sum=0;
		cout << "what categori u wanna use?" << endl;
		cout << "1 " << cost_categiries.food << endl;
		cout << "2 " << cost_categiries.entertaiment << endl;
		cout << "3 " << cost_categiries.communal_payments << endl;
		cout << "4 " << cost_categiries.subscriptions << endl;
		cout << "5 " << cost_categiries.other << endl;


	Start:
		cin >> categori;

		switch (categori)
		{

		case 1:
			cout << "enter the purchase amount in this category: " << endl;
			
			cin >> sum;
			cost_categiries.spend_countFood+=sum;
			cost_categiries.countFood++;
			Card_selection(pocket,sum);
			
			

			break;

		case 2:
			cout << "enter the purchase amount in this category: " << endl;
			
			cin >> sum;
			cost_categiries.spend_countEntertaiment += sum;
			cost_categiries.countEntertaiment++;
			Card_selection(pocket, sum);
			break;

		case 3:
			cout << "enter the purchase amount in this category: " << endl;
			
			cin >> sum;
			cost_categiries.spend_countCom_payments += sum;
			cost_categiries.countCom_payments++;
			Card_selection(pocket, sum);
			break;

		case 4:
			cout << "enter the purchase amount in this category: " << endl;
			
			cin >> sum;
			cost_categiries.spend_countSubscript += sum;
			cost_categiries.countSubscript++;
			Card_selection(pocket, sum);
			break;

		case 5:
			cout << "enter the purchase amount in this category: " << endl;
			
			cin >> sum;
			cost_categiries.spend_countOther += sum;
			cost_categiries.countOther++;
			Card_selection(pocket, sum);
			break;

		default:

			cout << "Wrong categori";
			goto Start;

			break;
		}
	}
private:
	Сost_categories cost_categiries;
	Data data_pay;
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

	string number_card;
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
		cout << "5 card replenishment\n";
		cout << "6 card replenishment\n";
		cout << "7 save & exit\n";



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
					int sum=0;
					cout << "enter the amount to replenish the account\n";
					cin >> sum;
					pocket[i].set_balance(sum);
				}
			}
			
			break;

			//сохранение в файл выход из меню
		case 6:
			tmp_card.Categori_Menu(pocket);
			
						
			break;
			//сохранение в файл выход из меню
		case 7:
			tmp_card.Save(pocket);
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



