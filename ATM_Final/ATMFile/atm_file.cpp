// Project 4 - CPP101x
// IDE: Microsoft Visual Studio 2019
// Version 16.1.0 Preview 2.0
// Date : May 26 2019

#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include "account.h"

using namespace std;

void CreateAccount();
void SearchAndPrintAccount(int);
void SearchAndModifyAccount(int);
void DeleteAccount(int);
void PrintAllAccountInFormat();
void DepositOrWithdraw(int, int);

int NumberInput();


int balance_max = INT_MAX; // So du toi da, bang voi kieu du lieu dang khai bao
streampos posistion_cur;   // Vi tri con tro trong file


// Tao moi tai khoan:
// Nhap so tai khoan, ten chu tai khoan, loai tai khoan
// va so du ban dau tu ban phim
void Account::CreateAccount()
{
	Account account;
	ifstream in_file;	
	bool exist = true;	// Dat bien de kiem tra su ton tai cua tai khoan
	
	while(exist)		// Neu so tai khoan da ton tai, yeu cau nhap so tai khoan khac	
	{
		exist = false;
		in_file.open("account.dat", ios::binary);
		cout << "\n\nNhap so tai khoan: ";
		account_number_ = NumberInput();

		while (in_file.read(reinterpret_cast<char*> (&account), sizeof(Account)))
		{
			if (account.GetAccountNumber() == account_number_)
			{								
				cout << "So tai khoan da ton tai, vui long nhap lai" <<endl;
				exist = true;
			}
		}	
		in_file.close();
	}

	cout << "Nhap ten chu tai khoan: ";
	cin.getline(name_, 100);

	// Loai tai khoan chi nhap duoc 1 ky tu bao gom: N, V
	do {

		cout << "Nhap loai tai khoan: ";		
		cin >> type_;
		if (!cin.fail())
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	} while (type_ != 'V' && type_ != 'N');
	cout << "Nhap so du ban dau: ";
	balance_  = NumberInput();
	cout << "\n\n\nTai khoan da duoc tao thanh cong" << endl;
}

// Sua doi tai khoan:
// Nhap moi ten chu tai khoan, loai tai khoan va so du
void Account::Modify()
{
	Account account;
	ofstream file;
	cout << "\nNhap thong tin de thay doi:";
	cout << "\nTen chu tai khoan: ";
	cin.getline(name_, 100);
	
	// Loai tai khoan chi nhap duoc 1 ky tu bao gom: N, V
	do {
		cout << "\Loai tai khoan: ";
		cin >> type_;
		cin.ignore(INT_MAX, '\n');
	} while (type_ != 'V' && type_ != 'N');
	
	cout << "\So du: ";
	balance_ = NumberInput();	//So nhap vao phai la so nguyen > 0

	account.SetName(name_);
	account.SetType(type_);
	account.SetBalance(balance_);
	account.SetAccountNumber(account_number_);

	file.open("account.dat", ios_base::binary | ios_base::in | ios_base::out);
	
	// di chuyen con tro den vi tri can sua
	file.seekp(posistion_cur);
	int x = sizeof(account);
	file.seekp(-x, ios_base::cur);

	account.Write(file);
	file.close();
}

// Nap them tien vao tai khoan
void Account::Deposit(int amount)
{		
	Account account;
	ofstream out_file;

	// Neu so tien lon hon kieu du lieu hien tai, yeu cau nhap lai
	while ((balance_ + amount) > balance_max)
	{
		cout << "\nSo du qua lon, moi nhap lai: ";
		amount = NumberInput();		
	}

	balance_ += amount;  // so du sau khi nap

	account.SetAccountNumber(account_number_);
	account.SetName(name_);							
	account.SetType(type_);
	account.SetBalance(balance_);

	out_file.open("account.dat", ios_base::binary | ios_base::in | ios_base::out);
		
	out_file.seekp(posistion_cur);					
	int x = sizeof(account);
	out_file.seekp(-x, ios_base::cur);	

	account.Write(out_file);		
}

// Rut tien tu tai khoan
void Account::Withdraw(int amount)
{
	Account account;
	ofstream out_file;	

	// Neu so tien rut lon hon so du, yeu cau nhap lai
	while(balance_ < amount)
	{
		cout << "\nSo du khong du, moi nhap lai: ";
		amount = NumberInput();
	}

	balance_ -= amount;  // so du sau khi rut

	account.SetAccountNumber(account_number_);
	account.SetName(name_);
	account.SetType(type_);
	account.SetBalance(balance_);

	out_file.open("account.dat", ios_base::binary | ios_base::in | ios_base::out);
	
	out_file.seekp(posistion_cur);						
	int x = sizeof(account);
	out_file.seekp(-x, ios_base::cur);	
	account.Write(out_file);
}


//// Hien thi thong tin tai khoan (khong in theo dinh dang)
//// Thong tin hien thi tren 4 dong:
//// Dong 1: So tai khoan
//// Dong 2: Ten chu tai khoan
//// Dong 3: Loai tai khoan
//// Dong 4: So du tai khoan
void Account::PrintAccount() const
{
	cout << "\nSo tai khoan: " << account_number_;
	cout << "\nTen chu tai khoan: ";
	cout << name_;						
	cout << "\nLoai tai khoan: " << type_;
	cout << "\nSo du: " << balance_ << endl;
}


//// In ra thong tin tai khoan tren mot dong theo dinh dang
//// So tai khoan: do rong 11 ky tu, can le trai
//// Ten chu tai khoan: do rong 19 ky tu, can le trai
//// Loai tai khoan: do rong 8 ky tu, can le trai
//// So du tai khoan: do rong 14 ky tu, can le trai
void Account::PrintAccountInFormat() const
{
	cout << left << setw(11) << account_number_ << setw(19) << name_ << setw(8) << type_ << setw(14) << balance_ << endl;
}

// Lay ra so tai khoan
int Account::GetAccountNumber() const
{
	return account_number_;
}

// Lay ra so du
int Account::GetBalance() const
{
	return balance_;
}

// Lay ra kieu tai khoan
char Account::GetType() const
{
	return type_;
}


int main()
{
	char menu_option;
	int account_number = 0; // Nhap tu ban phim
	do
	{
		system("cls");
		cout << "\n\n\n\tMenu";
		cout << "\n\n\t1. Tao tai khoan";
		cout << "\n\n\t2. Nop tien";
		cout << "\n\n\t3. Rut tien";
		cout << "\n\n\t4. Tra cuu tai khoan";
		cout << "\n\n\t5. Danh sach tai khoan";
		cout << "\n\n\t6. Xoa tai khoan";
		cout << "\n\n\t7. Sua tai khoan";
		cout << "\n\n\t8. Thoat";
		cout << "\n\n\tChon menu (so tu 1 den 8) ";

		cin >> menu_option;// menu_option nhan vao 1 ky tu, neu nguoi dung nhap vao 1 day so/ ky tu thi se loi
		cin.ignore(INT_MAX,'\n'); // xoa bo tat ca ky tu du thua (neu co) cho den khi gap enter
		system("cls");
		switch (menu_option)
		{
			case '1':
				cout << "\n\n\tTao tai khoan: ";
				CreateAccount();
				break;
			case '2':
				cout << "\n\n\tChon so tai khoan: ";
				DepositOrWithdraw(NumberInput(), 1); // 1: Nap tien
				break;
			case '3':
				cout << "\n\n\tChon so tai khoan: ";
				DepositOrWithdraw(NumberInput(), 2); // 2: Rut tien
				break;
			case '4':
				cout << "\n\n\tNhap so tai khoan: ";				
				// Tim va in thong tin tai khoan
				SearchAndPrintAccount(NumberInput());
				break;
			case '5':
				// In danh sach toan bo tai khoan
				PrintAllAccountInFormat();
				break;
			case '6':
				// Xoa tai khoan
				cout << "\n\n\tNhap so tai khoan muon xoa: ";
				DeleteAccount(NumberInput());
				break;
			case '7':
				// Sua tai khoan
				cout << "\n\n\tNhap so tai khoan: ";				
				SearchAndModifyAccount(NumberInput());
				break;
			case '8':
				cout << "\n\n\n\tCam on ban da su dung dich vu, hen gap lai";
				break;
			default: 
				cout << "\a\n\n\n\tVui long nhap lai"; // a: beep; t: tab
				break;
		}
		cin.get();
	} while (menu_option != '8');
	return 0;
}

// Tao mot tai khoan bang cach nhap tu ban phim
// roi luu tai khoan vua tao vao file "account.dat"
void CreateAccount()
{	
	Account account;
	ofstream out_file;
	out_file.open("account.dat", ios_base::binary | ios_base::app);
	if (out_file)
	{	
		account.CreateAccount();
		account.Write(out_file);		
	}
	out_file.close(); // dong file
}


// Tim va in tai khoan co so tai khoan la account_number (khong in theo dinh dang)
// Tim tai khoan trong file "account.dat"
void SearchAndPrintAccount(int account_number)
{
	Account account;
	bool found = false;
	ifstream in_file;

	in_file.open("account.dat", ios::binary);
	if (!in_file)
	{
		cout << "\n\nKhong mo duoc file, hay an phim enter de quay lai menu chinh" << endl;
		return;
	}
	cout << "\nKet qua tim kiem:\n";

	while (in_file.read(reinterpret_cast<char *> (&account), sizeof(Account)))
	{
		if (account.GetAccountNumber() == account_number)
		{
			account.PrintAccount();
			found = true;
		}
	}

	in_file.close();
	if (found == false)
		cout << "\n\n\tKhong tim thay tai khoan";
}


// Tim tai khoan co so tai khoan la account_number (khong in theo dinh dang)
// trong file "account.dat"
// Sau do cho phep nguoi dung sua doi tai khoan nay
// bang cach thay doi ten chu tai khoan, loai tai khoan va so du
// Cuoi cung, luu thay doi vao file "account.dat"
void SearchAndModifyAccount(int account_number)
{	
	Account account;     
	fstream in_file;
	bool found = false;	

	in_file.open("account.dat", ios::binary | ios::in | ios::out);
	if (!in_file)
	{
		cout << "\n\nKhong mo duoc file, hay an phim enter de quay lai menu chinh" << endl;
		return;
	}
	cout << "\nKet qua tim kiem:\n" << endl;
	
	while (in_file.read(reinterpret_cast<char*> (&account), sizeof(Account)))
	{
		if (account_number == account.GetAccountNumber())	// goi ham modify neu tim thay tai khoan trong data
		{
			account.PrintAccount();
			posistion_cur = in_file.tellp();
			account.Modify();			
			found = true;
			cout << "\n\n\tTai khoan da sua thanh cong" << endl;
		}				
	}

	in_file.close();
	if (found == false)
		cout << "\n\n\tKhong tim thay tai khoan";
}


// Tim tai khoan co so tai khoan la account_number
// trong file "account.dat"
// Sau do xoa tai khoan nay trong file "account.dat"
void DeleteAccount(int account_number)
{
	Account account;
	ifstream in_file;
	ofstream out_file;
	in_file.open("account.dat", ios::binary);
	if (!in_file)
	{
		cout << "\n\nKhong mo duoc file, hay an phim enter de quay lai menu chinh" << endl;
		return;
	}

	// Luu tat ca cac tai khoan trong file "account.dat", tru tai khoan muon xoa vao file "temp.dat"
	out_file.open("temp.dat", ios::binary);
	in_file.seekg(0, ios::beg);
	bool search = false;
	while (in_file.read(reinterpret_cast<char *> (&account), sizeof(Account)))
	{
		if (account_number != account.GetAccountNumber()) // 
		{
			account.Write(out_file);
		}

		if (account_number == account.GetAccountNumber()) 
		{
			search = true; // Tra ve gia tri true khi phat hien tai khoan da ton tai
		}
	}

	in_file.close();
	out_file.close();

	// Neu khong tim thay tai khoan can xoa, thuc hien xoa file file "temp.dat", file "account.dat" giu nguyen
	if (!search)
	{
		cout << "\n\n\tKhong tim thay tai khoan, hay an phim enter de quay lai menu chinh" << endl;
		remove("temp.dat"); 
		return;
	}

	else {
		int result1 = rename("account_temp.dat", "account.dat");
		remove("account.dat");
		int result2 = rename("temp.dat", "account.dat"); // rename: thanh cong thi tra ve 0, that bai tra ve gia tri 1
		// Doi ten thanh cong thi xoa file "account_temp.dat"
		if (result2 == 0)
		{
			cout << "\n\n\tTai khoan da xoa thanh cong";
			remove("account_temp.dat");
		}

		// Neu that bai thi xoa file "temp.dat" va doi ten "account_temp.dat" thanh "account.dat" nhu ban dau
		else {
			cout << "\n\n\tthao tac that bai" << endl;
			remove("temp.dat");
			result1 = rename("account.dat", "account_temp.dat");
		}			
	}
}


// In ra tat ca cac tai khoan luu trong file "account.dat" theo dinh dang
// Moi tai khoan in tren mot dong
void PrintAllAccountInFormat() 
{
	Account account;
	ifstream in_file;
	in_file.open("account.dat", ios::binary);
	if (!in_file)
	{
		cout << "\n\nKhong mo duoc file, hay an phim enter de quay lai menu chinh" << endl;
		return;
	}
	cout << "\n\n\t\tDanh sach tai khoan:\n\n";
	cout << "====================================================\n";
	cout << "So TK      Chu TK             Loai    So du\n";
	cout << "====================================================\n";
	while (in_file.read(reinterpret_cast<char *> (&account), sizeof(Account)))
	{
		account.PrintAccountInFormat();
	}
	in_file.close();
}



// Tim tai khoan co so tai khoan la account_number trong file "account.dat"
// Roi nop hoac rut tien vao tai khoan tim duoc
// option = 1: nop tien
// option = 2: rut tien
// So tien nop hoac rut duoc nhap tu ban phim
// Sau cung, luu tai khoan vua sua doi vao file "account.dat"
void DepositOrWithdraw(int account_number, int option)
{	
	int amount = 0; // So tien muon rut/nop duoc nhap tu ban phim	
	bool found = false;
	Account account;
	fstream file;

	file.open("account.dat", ios::binary | ios::in | ios::out);

	if (!file) // khong mo duoc file
	{		
		cout << "\n\nKhong mo duoc file, hay an phim enter de quay lai menu chinh";
		return;
	}

	while (!file.eof() && found == false)
	{
		file.read(reinterpret_cast<char *> (&account), sizeof(Account));
		if (account.GetAccountNumber() == account_number)  
		{			
			posistion_cur = file.tellp(); // vi tri hien tai trng file
			account.PrintAccount(); 			

			if (option == 1)
			{								
				cout << "\n\n\tNop tien ";
				cout << "\n\nNhap so tien nop: "; 
				account.Deposit(NumberInput());	// thuc hien nop tien		
			}
			else if (option == 2)
			{
				// neu so du khong du, tro ve man hinh chinh
				if (account.GetBalance() <= 50000)
				{
					cout << "\n\nSo du khong du de thuc hien";
					return;
				}
				cout << "\n\n\tRut tien ";
				cout << "\n\nNhap so tien rut: ";
				account.Withdraw(NumberInput()); // thuc hien rut tien	
			}
			cout << "\n\n\t Giao dich thuc hien thanh cong";
			found = true;
		}
	}

	file.close();
	if (found == false)
		cout << "\n\n\tKhong tim thay tai khoan";
}


void Account::Write(ofstream& ofs) {
	ofs.write(reinterpret_cast<const char*> (this), sizeof(Account));
}

void Account::Read(ifstream& ifs) {
	ifs.read(reinterpret_cast<char*>(this), sizeof(Account));
}



// Ham kiem tra du lieu nhap vao la so nguyen
int NumberInput()
{	
	int number = 0;
	do
	{		
		cin >> number;
		if (cin.fail() || number <= 0 || number >= balance_max)
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Vui long nhap lai: ";
		}
	} while (cin.fail() || number <= 0 || number >= balance_max);
	cin.ignore(INT_MAX, '\n');
	return number;
}
