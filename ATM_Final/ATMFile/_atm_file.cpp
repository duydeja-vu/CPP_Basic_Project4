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

// Tao moi tai khoan:
// Nhap so tai khoan, ten chu tai khoan, loai tai khoan
// va so du ban dau tu ban phim
void Account::CreateAccount()
{
	cout << "Nhap so tai khoan: ";
	cin >> account_number_;
	cout << "Nhap ten chu tai khoan: ";
	cin.ignore();
	cin.getline(name_, 100);
	cout << "Nhap loai tai khoan: ";
	cin >> type_;
	cout << "Nhap so du ban dau: ";
	cin >> balance_;

	cin.ignore();
	cout << "\n\n\nTai khoan da duoc tao thanh cong" << endl;
}

// Sua doi tai khoan:
// Nhap moi ten chu tai khoan, loai tai khoan va so du
void Account::Modify()
{
	cout << "\nNhap thong tin de thay doi:";
	cout << "\nTen chu tai khoan: ";
	//your code here
}

// Nap them tien vao tai khoan
void Account::Deposit(int amount)
{
	//your code here
}

// Rut tien tu tai khoan
void Account::Withdraw(int amount)
{
	//your code here
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


	cout << name_;  // chu y ten=====================
	cout << "\nLoai tai khoan: " << type_;
	cout << "\nSo du tai khoan: " << balance_ << endl;
}

//// In ra thong tin tai khoan tren mot dong theo dinh dang
//// So tai khoan: do rong 11 ky tu, can le trai
//// Ten chu tai khoan: do rong 19 ky tu, can le trai
//// Loai tai khoan: do rong 8 ky tu, can le trai
//// So du tai khoan: do rong 14 ky tu, can le trai
void Account::PrintAccountInFormat() const
{
	//your code here
}

//// Lay ra so tai khoan
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


//===== viet them ======
// Lay ra kieu tai khoan
char Account::GetName() const
{
	return name_[99];
}





int main()
{
	char menu_option;

	int account_number = 0; // Nhap tu ban phim



	// tao file database: account.dat
	fstream account;
	account.open("account.dat", ios_base::in | ios_base::out | ios_base::binary);

	if (!(account.is_open())) // neu file chua ton tai thi tao moi
	{
		ifstream datoteka("account.dat");
		account.open("account.dat", ios_base::in | ios_base::out | ios_base::binary);
		cout << "Tao moi file." << endl;
	}
	account.close();

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

		std::cin >> menu_option;
		system("cls");
		switch (menu_option)
		{
			case '1':
				CreateAccount();
				break;
			case '2':
				cout << "\n\n\tChon so tai khoan: ";
				//your code here
				break;
			case '3':
				cout << "\n\n\tChon tai khoan: ";
				//your code here
				break;
			case '4':
				cout << "\n\n\tNhap so tai khoan: ";
				//your code here
				break;
			case '5':
				//your code here
				break;
			case '6':
				//your code here
				break;
			case '7':
				cout << "\n\n\tNhap so tai khoan: ";
				//your code here
				break;
			case '8':
				//your code here
				break;
			default:cout << "\a";
		}
 		std::cin.ignore();
		std::cin.get();
	} while (menu_option != '8');
	return 0;
}

// Tao mot tai khoan bang cach nhap tu ban phim
// roi luu tai khoan vua tao vao file "account.dat"
void CreateAccount()
{	
	//Account account;
	Account ac[50];
	//account.CreateAccount();
	ofstream out_file;

	out_file.open("account.dat", ios_base::binary);
	if (out_file.is_open())
	{	
		int soluong = 1;
		cout << "Nhap so luong muon tao: ";
		cin >> soluong;

		for (int i = 0; i < soluong; i++) {

			ac[soluong].CreateAccount();
			ac[soluong].Write(out_file);
			cout << "Gia tri cua i: " << i << endl;
		}
		//account.Write(out_file);		
	}
	else
	{
		std::cerr << "Couldn't open account.dat for writing." << std::endl;
	}

	out_file.close(); // dong file

	//===================================================================
	//					Test doc file account.bin
	//===================================================================
	ifstream in_file;
	in_file.open("account.dat", ios_base::binary); // mo file
	if (in_file.is_open())
	{
		int n = 0;
		Account bc[10];
		//account.Read(in_file); // ham doc file account.bin
		//account.PrintAccount(); // ham in ra thong tin tai khoan


		while (!in_file.eof()) {
			bc[n].Read(in_file);
			bc[n].PrintAccount();

			if (!in_file.eof()) n++;
		}




		system("pause");

	}
	else
	{
		std::cerr << "Couldn't open account.dat for writing." << std::endl;
	}
	in_file.close(); // dong file
}

// Tim va in tai khoan co so tai khoan la account_number (không in theo dinh dang)
// Tim tai khoan trong file "account.dat"
//void SearchAndPrintAccount(int account_number)
//{
//	Account account;
//	bool found = false;
//	ifstream in_file;
//
//	in_file.open("account.dat", ios::binary);
//	if (!in_file)
//	{
//		//your code here
//		return;
//	}
//	cout << "\nKet qua tim kiem:\n";
//
//	while (in_file.read(reinterpret_cast<char *> (&account), sizeof(Account)))
//	{
//		//your code here
//	}
//
//	in_file.close();
//	if (found == false)
//		cout << "\n\nKhong tim thay tai khoan";
//}

// Tim tai khoan co so tai khoan la account_number (khong in theo dinh dang)
// trong file "account.dat"
// Sau do cho phep nguoi dung sua doi tai khoan nay
// bang cach thay doi ten chu tai khoan, loai tai khoan va so du
// Cuoi cung, luu thay doi vao file "account.dat"
//void SearchAndModifyAccount(int account_number)
//{
//	bool found = false;
//	//Account account;
//	fstream file;
//
//	file.open("account.dat", ios::binary | ios::in | ios::out);
//	if (!file)
//	{
//		//your code here
//		return;
//	}
//
//	while (!file.eof() && found == false)
//	{
//		//your code here
//	}
//
//	file.close();
//	if (found == false)
//		cout << "\n\nKhong tim thay tai khoan";
//}

// Tim tai khoan co so tai khoan la account_number
// trong file "account.dat"
// Sau do xoa tai khoan nay trong file "account.dat"
//void DeleteAccount(int account_number)
//{
//	Account account;
//	ifstream in_file;
//	ofstream out_file;
//	in_file.open("account.dat", ios::binary);
//
//	if (!in_file)
//	{
//		//your code here
//		return;
//	}
//
//	// Luu tat ca cac tai khoan trong file "account.dat", tru tai khoan muon xoa vao file "temp.dat"
//	out_file.open("temp.dat", ios::binary);
//	in_file.seekg(0, ios::beg);
//	while (in_file.read(reinterpret_cast<char *> (&account), sizeof(Account)))
//	{
//		//your code here
//	}
//
//	// Dong cac file da mo, xoa file "account.dat", doi ten file "temp.dat" thanh "account.dat"
//	//your code here
//	cout << "\n\n\tTai khoan da xoa thanh cong";
//}

// In ra tat ca cac tai khoan luu trong file "account.dat" theo dinh dang
// Moi tai khoan in tren mot dong
//void PrintAllAccountInFormat() 
//{
//	Account account;
//	ifstream in_file;
//	in_file.open("account.dat", ios::binary);
//	if (!in_file)
//	{
//		//your code here
//		return;
//	}
//	cout << "\n\n\t\tDanh sach tai khoan:\n\n";
//	cout << "====================================================\n";
//	cout << "So TK      Chu TK             Loai    So du\n";
//	cout << "====================================================\n";
//	while (in_file.read(reinterpret_cast<char *> (&account), sizeof(Account)))
//	{
//		//your code here
//	}
//	in_file.close();
//}

// Tim tai khoan co so tai khoan la account_number trong file "account.dat"
// Roi nop hoac rut tien vao tai khoan tim duoc
// option = 1: nop tien
// option = 2: rut tien
// So tien nop hoac rut duoc nhap tu ban phim
// Sau cung, luu tai khoan vua sua doi vao file "account.dat"
//void DepositOrWithdraw(int account_number, int option)
//{
//	int amount = 0; // So tien muon rut/nop duoc nhap tu ban phim
//	bool found = false;
//	Account account;
//	fstream file;
//
//	file.open("account.dat", ios::binary | ios::in | ios::out);
//	if (!file)
//	{
//		//your code here
//		return;
//	}
//
//	while (!file.eof() && found == false)
//	{
//		//file.read(reinterpret_cast<char *> (&account), sizeof(Account));
//		//if (account.GetAccountNumber() == account_number)  // ham GetAccountNumber chua viet====================== =
//		//{
//		//	//account.PrintAccount(); // ham PrintAccount chua viet=======================
//		//	if (option == 1)
//		//	{
//		//		cout << "\n\n\tNop tien ";
//		//		cout << "\n\nNhap so tien nop: ";
//		//		//your code here
//		//	}
//		//	else if (option == 2)
//		//	{
//		//		cout << "\n\n\tRut tien ";
//		//		cout << "\n\nNhap so tien rut: ";
//		//		//your code here
//		//	}
//
//		//	//your code here
//		//	cout << "\n\n\t Giao dich thuc hien thanh cong";
//		//	found = true;
//		//}
//	}
//
//	file.close();
//	if (found == false)
//		cout << "\n\nKhong tim thay tai khoan";
//}


void Account::Write(ofstream& ofs) {
	ofs.write(reinterpret_cast<const char*> (this), sizeof(Account));
}

void Account::Read(ifstream& ifs) {
	ifs.read(reinterpret_cast<char*>(this), sizeof(Account));
}

