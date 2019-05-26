#include <string>

using namespace std;

class Account
{
private:
	int account_number_; // So tai khoan
	char name_[100]; // Ho ten chu tai khoan
	int balance_; // So du tai khoan
	char type_; // Kieu tai khoan. N: binh thuong. V: tai khoan Vip
public:
	void CreateAccount(); 
	void Modify();		
	void Deposit(int);	
	void Withdraw(int);	
	void PrintAccount() const;	// In thong tin tai khoan
	void PrintAccountInFormat() const;
	int GetAccountNumber() const;	// Tra ve so tai khoan
	int GetBalance() const;			// Tra ve so du
	char GetType() const;			// Tra ve loai tai khoan

	void Write(ofstream& ofs); // Ham ghi file account.dat
	void Read(ifstream& ifs);  // Ham doc file account.dat

	void SetName(char* name ); 
	void SetAccountNumber(int set_acc_number);
	void SetBalance(int set_balance);
	void SetType(char set_type);
};

void Account::SetName(char* name)
{
	snprintf(name_, sizeof(name_), name);
}

void Account::SetAccountNumber(int set_acc_number)
{
	account_number_= set_acc_number;
}

void Account::SetBalance(int set_balance)
{
	balance_ = set_balance;
}

void Account::SetType(char set_type)
{
	type_ = set_type;
}
