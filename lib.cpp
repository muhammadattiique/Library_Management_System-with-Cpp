#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<iomanip>
#include<chrono>
#include<thread>
using namespace std;
bool instruction_display = 0;
struct library
{
	int book_serial_number;
	string book_name;
	string author_name;
	int book_edition;
	int book_quantity;
	int book_rack;
	int student_id;
	string student_first_name;
	string student_second_name;
	string student_password;
};
void add_books();
bool serial_number_exist(int serial_number);
void display_books();
void student_signup();
void display_students();
void delete_students();
void borrow_books();
void display_borrow_book();
void display_borrow_book_to_student();
void return_book();
void book_feedback();
void display_book_feedback();
void admin_page();
void student_page();
void starline();
void instruction();
library Lib;
int main()
{
	if (!instruction_display)
	{
		instruction();
		instruction_display = 1;
	}
again_ask:
	system("cls");
    string admin_username, admin_password;
	int admin_login_count_pos = 0, admin_login_count_neg = 3;
	int student_login_count_pos = 0, student_login_count_neg = 3;
	string existing_password;
	int  existing_id;
	bool student_found = 0;
	ifstream students_file;
	starline();
	cout << "\t\t\t\t\t WELCOME TO LIBRARY MANAGEMENT SYSTEM" << endl;
	starline();
	int choice;
	cout << "\nPress 1 for admin login " << endl;
	cout << "Press 2 for student login " << endl;
	cout << "Press 3 for student signup " << endl;
	cout << "Press 0 to exit " << endl;
	cout << "\nEnter Your Choice : ";
	cin >> choice;
	switch (choice)
	{
	case 0:
		cout << "\t\t\t\t\t\tGOOD BYE !" << endl;
		starline();
		exit(0);
		break;
	case 1:
		system("cls");
		starline();
		cout << "\t\t\t\t\t\t\t ADMIN LOGIN " << endl;
		starline();
	admin_again:
		cout << "\nEnter Your Username : ";
		cin >> admin_username;
		cout << "Enter Your Password : ";
		cin >> admin_password;
		if ((admin_username == "admin") && (admin_password == "admin123"))
		{
			system("cls");
			starline();
			cout << "\t\t\t\t\t\tLOGIN SUCESSFULLY" << endl;
			starline();
			this_thread::sleep_for(chrono::seconds(1));
			system("cls");
			admin_page();
		}
		else
		{
			cout << "\t\t\t\t\t\tINCORRECT USERNAME OR PASSWORD" << endl;
			admin_login_count_pos++;
			cout << "\t\t\t\t\t\tYou have left " << --admin_login_count_neg << " login attempts" << endl;
			if (admin_login_count_pos == 3)
			{
				cout << "\t\t\t\t\t\tYOU HAVE DONE " << admin_login_count_pos << " LOGIN ATTEMPTS" << endl;
				system("pause");
				system("cls");
				goto again_ask;
			}
			goto admin_again;
		}
		break;
	case 2:
		system("cls");
		starline();
		cout << "\t\t\t\t\t\t STUDENT LOGIN" << endl;
		starline();
	student_again:
		cout << "\nEnter Your Student ID : ";
		cin.ignore();
		cin >> Lib.student_id;
		cin.ignore();
		cout << "Enter Your Password : ";
		cin >> Lib.student_password;
		students_file.open("Students Detail.txt");
		while (students_file >> existing_id >> Lib.student_first_name >> Lib.student_second_name >> existing_password)
		{
				if (existing_id == Lib.student_id && existing_password == Lib.student_password) 
			{
				student_found = 1;
				break;
			}
		}
		students_file.close();
		if (student_found)
		{
			system("cls");
			starline();
			cout << "\t\t\t\t\t\tLOGIN SUCESSFULLY" << endl;
			starline();
			this_thread::sleep_for(chrono::seconds(1));
			system("cls");
			student_page();
		}
		else
		{
			cout << "\t\t\t\t\t\tINVALID STUDENT ID OR PASSWORD" << endl;
			student_login_count_pos++;
			cout << "\t\t\t\t\t\tYou have left " << --student_login_count_neg << " login attempts" << endl;
			if (student_login_count_pos == 3)
			{
				cout << "\t\t\t\t\t\tYOU HAVE DONE " << student_login_count_pos << " LOGIN ATTEMPTS" << endl;
				system("pause");
				system("cls");
				goto again_ask;
			}
			goto student_again;
		}
		system("pause");
		break;
	case 3:
		system("cls");
		student_signup();
		break;
	default:
		starline();
		cout << "\t\t\t\t\t\tINVALID OPERATOR! TRY AGAIN " << endl;
		starline();
		system("pause");
		goto again_ask;
		break;
	}
}
void add_books()
{
	starline();
	cout << "\t\t\t\t\t\tMENU FOR ADDING BOOKS" << endl;
	starline();
	int n;
	cout << "\nEnter Number of Books You Want To Add : ";
	cin >> n;
	ofstream add_books_file;
	add_books_file.open("Book Detail.txt", ios::app);
	for (int i = 1; i <= n; i++)
	{
		cout << "BOOK NUMBER : " << i << endl;
		do
		{
			cout << "Enter Book Serial Number : ";
			cin >> Lib.book_serial_number;
			if (serial_number_exist(Lib.book_serial_number))
			{
				cout << "\t\t\t\t\t\tERROR: Book Serial Number already exists! Try again." << endl;
			}
			else
			{
				break;
			}
		} while (true);
		cout << "Enter Book Name : ";
		cin.ignore();
		getline(cin, Lib.book_name);
		cout << "Enter Author Name : ";
		getline(cin, Lib.author_name);
		cout << "Enter Book Edition : ";
		cin >> Lib.book_edition;
		cout << "Enter Book Quantity : ";
		cin >> Lib.book_quantity;
		cout << "Enter Book Rack : ";
		cin >> Lib.book_rack;
		cout << "\t\t\t\t\t\tThe " << i << " Book has been added sucessfully " << endl;
		add_books_file << Lib.book_serial_number << setw(30) << Lib.book_name << setw(20) << Lib.author_name << setw(20) << Lib.book_edition << setw(20) << Lib.book_quantity << setw(20) << Lib.book_rack << endl;
	}
	add_books_file.close();
	system("pause");
	system("cls");
	admin_page();
}
bool serial_number_exist(int serial_number)
{
	ifstream read_book;
	read_book.open("Book Detail.txt");
	if (!read_book.is_open())
	{
		cout << "\t\t\t\t\t\tError opening file for reading." << endl;
		return 0;
	}
	string content;
	while (getline(read_book, content))
	{
		stringstream book_info(content);
		int current_book_serial;
		book_info >> current_book_serial;
		if (current_book_serial == serial_number)
		{
			read_book.close();
			return 1;
		}
	}
	read_book.close();
	return 0;
}
void display_books()
{
	starline();
	cout << "\t\t\t\t\t\tBOOKS RECORD" << endl;
	starline();
	string content;
	cout <<"\nBook Sr. Number " << setw(20) << "Books Name " << setw(20) << "Author Name" << setw(20) << "Books Edition" << setw(20) << "Books Quantity" << setw(20) << "Books Rack" << endl;
	ifstream book_read;
	book_read.open("Book Detail.txt");
	if (!book_read.is_open())
	{
		cout << "\t\t\t\t\t\tError opening file for writing." << endl;
		return;
	}
	while (getline(book_read, content))
	{
		cout << content << endl;
	}
	book_read.close();
}
void student_signup()
{
	starline();
	cout << "\t\t\t\t\t\tCREATE YOUR ACCOUNT" << endl;
	starline();
	cout << "\nEnter Your Student ID (Only Last Digits) : ";
	cin >> Lib.student_id;
	cin.ignore(); 
	ifstream check_students_ids("Students Detail.txt");
	int existing_id;
	while (check_students_ids >> existing_id)
	{
		if (existing_id == Lib.student_id)
		{
			cout << "\t\t\t\t\t\tERROR: Student ID already exists!" << endl;
			check_students_ids.close();
			system("pause");
			main();
			return;
		}
		check_students_ids.ignore(INT_MAX, '\n');
	}
	check_students_ids.close();
	cout << "Enter Your First Name : ";
	getline(cin, Lib.student_first_name);
	cout << "Enter Your Last Name : ";
	getline(cin, Lib.student_second_name);
	cout << "Create Your Password (Don't Add Space) : ";
	getline(cin, Lib.student_password);
	ofstream signup_file("Students Detail.txt", ios::app);
	signup_file << Lib.student_id << "\t\t\t" << Lib.student_first_name << "\t\t\t"
	<< Lib.student_second_name << "\t\t\t" << Lib.student_password << endl;
	signup_file.close();
	cout << "\t\t\t\t\t\t Student sign up successfully \n";
	system("pause");
	main();
}
void display_students()
{
	starline();
	cout << "\t\t\t\t\t\tSTUDENTS RECORD" << endl;
	starline();
	string content;
	cout << "\nStudent ID" << "\t" << "Student First Name" << "\t" << "Student Last Name" << "\t" << "Student Password" << endl;
	ifstream show_students;
	show_students.open("Students Detail.txt");
	if (!show_students.is_open())
	{
		cout << "\t\t\t\t\t\tError opening file for Reading." << endl;
		return;
	}
	while (getline(show_students, content))
	{
		cout << content << endl;
	}
	show_students.close();
	system("pause");
	system("cls");
	admin_page();
}
void delete_students()
{
	starline();
	cout << "\t\t\t\t\t\t\DELETE STUDENT RECORD" << endl;
	starline();
	int student_id_to_delete;
	cout << "\nEnter Student ID to Delete : ";
	cin >> student_id_to_delete;
	ifstream student_detail("Students Detail.txt");
	ofstream temp_file("Temp file.txt");
	string content;
	if (!student_detail.is_open() || !temp_file.is_open())
	{
		cout << "Error opening files for reading or writing." << endl;
		return;
	}
	bool student_found = 0;
	while (getline(student_detail, content))
	{
		stringstream line(content);
		int current_student_id;
		line >> current_student_id;
		if (current_student_id!=student_id_to_delete)
		{
			temp_file << content << endl;
		}
		else
		{
			student_found = 1;
		}
	}
	student_detail.close();
	temp_file.close();
	remove("Students Detail.txt");
	rename("Temp file.txt", "Students Detail.txt");
	if (student_found == 1)
	{
		cout << "\t\t\t\t\tThe Student with ID " << student_id_to_delete << " has been deleted sucessfully" << endl;
	}
	else
	{
		cout << "\t\t\t\t\tThe Student with ID " << student_id_to_delete << " has not found" << endl;
	}
	system("pause");
	system("cls");
	admin_page();
}
void starline()
{
	for (int i = 1; i <= 120; i++)
	{
		cout << "*";
	}
	cout << endl;
}
void admin_page()
{
admin:
	starline();
	cout << "\t\t\t\t\t\tWELCOME, TO ADMIN PANEL!" << endl;
	starline();
	int choice2;
	cout << "Press 1 to add books " << endl;
	cout << "Press 2 to display all students" << endl;
	cout << "Press 3 to display all books that are available " << endl;
	cout << "Press 4 to delete Student" << endl;
	cout << "Press 5 to display borrowed books" << endl;
	cout << "Press 6 to display books feedback" << endl;
	cout << "Press 0 to sign out " << endl;
	cout << "\nEnter Your Choice : ";
	cin >> choice2;
	system("cls");
	switch (choice2)
	{
	case 0:
		main();
		break;
	case 1:
		add_books();
		break;
	case 2:
		display_students();
		break;
	case 3:
		display_books();
		system("pause");
		system("cls");
		goto admin;
		break;
	case 4:
		delete_students();
		break;
	case 5:
		display_borrow_book();
		break;
	case 6:
		display_book_feedback();
		goto admin;
		break;
	default:
		starline();
		cout << "\t\t\t\t\t\tINVALID OPERATOR! TRY AGAIN " << endl;
		starline();
		system("pause");
		system("cls");
		goto admin;
		break;
	}
}
void borrow_books()
{
	display_books();
	int book_serial_to_issue;
	cout << "\nEnter The Book Serial Number You Want To Issue : ";
	cin >> book_serial_to_issue;
	ifstream books_detail;
	books_detail.open("Book Detail.txt");
	ofstream borrow_books_detail;
	borrow_books_detail.open("Borrow Books.txt",ios::app);
	ofstream update_books_detail;
	update_books_detail.open("Updated Books Detail.txt");
	string content;
	bool book_found = 0;
	while (getline(books_detail, content))
	{
		stringstream books(content);
		int current_book_serial_name;
		string current_book_name, current_author_name;
		int current_book_edition, current_book_quantity, current_book_rack;
		books >> current_book_serial_name >> current_book_name >> current_author_name >> current_book_edition >> current_book_quantity >> current_book_rack;
		if (current_book_serial_name == book_serial_to_issue && current_book_quantity > 0)
		{
			current_book_quantity--;
			update_books_detail << current_book_serial_name << setw(30) << current_book_name << setw(20) << current_author_name << setw(20) << current_book_edition << setw(20) << current_book_quantity << setw(20) << current_book_rack << endl;
			borrow_books_detail << Lib.student_id << "\t\t"<<Lib.student_first_name << "\t\t\t" <<Lib.student_second_name<<"\t\t" << current_book_serial_name << "\t\t" << current_book_name << "\t\t" << current_author_name << "\t\t" << current_book_edition << endl;
			book_found = 1;
			cout << "\t\t\t\t\t\tBOOK ISSUED SUCESSFULLY" << endl;
		}
		else
		{
			update_books_detail << current_book_serial_name << setw(30) << current_book_name << setw(20) << current_author_name << setw(20) << current_book_edition << setw(20) << current_book_quantity << setw(20) << current_book_rack << endl;
		}
	}
	books_detail.close();
	borrow_books_detail.close();
	update_books_detail.close();
	remove("Book Detail.txt");
	rename("Updated Books Detail.txt", "Book Detail.txt");
	if (book_found==0)
	{
		cout << "\t\t\t\t\t\tBOOK IS NOT AVAILABLE FOR ISSUE" << endl;
	}
	system("pause");
	system("cls");
	student_page();
}
void display_borrow_book()
{
	starline();
	cout << "\t\t\t\t\t\tBORROWED BOOKS RECORD" << endl;
	starline();
	ifstream display_issued_books;
	display_issued_books.open("Borrow Books.txt");
	cout << "\nStudent ID" << "\t" << "Student First Name" << "\t" << "Last Name" << "\t" << "Book SR" << "\t\t" << "Book Name" << "\t" << "Author Name" << "\t" << "Book Edition" << endl;
	string content;
	if (!display_issued_books.is_open())
	{
		cout << "\t\t\t\t\t\tError opening file for Reading." << endl;
		return;
	}
	while (getline(display_issued_books, content))
	{

			cout << content << endl;
	}
	display_issued_books.close();
	system("pause");
	system("cls");
	admin_page();
}
void display_borrow_book_to_student()
{
	ifstream display_issued_books;
	display_issued_books.open("Borrow Books.txt");
	int student_id_to_check = Lib.student_id;
	cout << "Student ID" << "\t" << "Student First Name" << "\t" << "Last Name" << "\t" << "Book SR" << "\t\t" << "Book Name" << "\t" << "Author Name" << "\t" << "Book Edition" << endl;
	bool any_book_issued = 0;
	string content;
	if (!display_issued_books.is_open())
	{
		cout << "\t\t\t\t\t\tError opening file for Reading." << endl;
		return;
	}
	while (getline(display_issued_books, content))
	{
		stringstream book_info(content);
		int current_student_id;
		book_info >> current_student_id;
		if (current_student_id == student_id_to_check)
		{
			any_book_issued = 1;
			cout << content << endl;
		}
	}
	display_issued_books.close();
	if (!any_book_issued)
	{
		cout << "\t\t\t\t\t\tNO BOOKS BORROWED BY THE STUDENT." << endl;
		system("pause");
		system("cls");
		student_page();
	}
}
void return_book()
{
	starline();
	cout << "\t\t\t\t\t\tRETURN BOOK MENU" << endl;
	starline();
	display_borrow_book_to_student();
	int book_serial_no_to_return;
	cout << "\nEnter the Book Serial No You want to return : ";
	cin >> book_serial_no_to_return;
	ifstream borrowed_books;
	borrowed_books.open("Borrow Books.txt");
	ofstream update_borrowed_books;
	update_borrowed_books.open("Update Borrow Books.txt");
	string content;
	bool book_found = 0;
	while (getline(borrowed_books, content))
	{
		stringstream books_info(content);
		int current_student_id, current_book_serial;
		books_info >> current_student_id >> Lib.student_first_name >> Lib.student_second_name >> current_book_serial;
		if (current_student_id == Lib.student_id && current_book_serial == book_serial_no_to_return)
		{
			book_found = 1;
			cout << "\t\t\t\t\t\tBOOK RETURNED SUCCESSFULLY" << endl;
			char book_feedback_choice;
			cout << "Do You Want To Give Feedback ? (y/n) ";
			cin >> book_feedback_choice;
			if (book_feedback_choice == 'Y' || book_feedback_choice == 'y')
			{
				book_feedback();
			}
		}
		else
		{
			update_borrowed_books << content << endl;
		}
	}
		borrowed_books.close();
		update_borrowed_books.close();
		remove("Borrow Books.txt");
		rename("Update Borrow Books.txt", "Borrow Books.txt");
		if (!book_found)
		{
			cout << "\t\t\t\t\t\tBOOK NOT FOUND IN YOUR BORROWED LIST" << endl;
		}
		else
		{
			ifstream book_detail;
			book_detail.open("Book Detail.txt");
			ofstream update_book_detail;
			update_book_detail.open("Update Book Detail");
			while (getline(book_detail,content))
			{
				stringstream book_info(content);
				int current_book_serial;
				string current_book_name, current_author_name;
				int current_book_edition, current_book_quantity, current_book_rack;
				book_info >> current_book_serial >> current_book_name >> current_author_name >> current_book_edition >> current_book_quantity >> current_book_rack;
				if (current_book_serial == book_serial_no_to_return)
				{
					current_book_quantity++;
				}
				update_book_detail << current_book_serial << setw(30) << current_book_name << setw(20) << current_author_name << setw(20) << current_book_edition << setw(20) << current_book_quantity << setw(20) << current_book_rack << endl;
			}
			book_detail.close();
			update_book_detail.close();
			remove("Book Detail.txt");
			rename("Update Book Detail", "Book Detail.txt");
		}
		system("pause");
		system("cls");
		student_page();
}
void book_feedback()
{
	again:
	int feedback;
	cout << "Enter Your Feedback Numbers (1-5) : ";
	cin >> feedback;
	if (feedback >= 1 && feedback <= 5)
	{
		ofstream your_feedback;
		your_feedback.open("Books Feedback.txt", ios::app);
		ifstream borrowed_books;
		borrowed_books.open("Borrow Books.txt");
		string content;
		while (getline(borrowed_books, content))
		{
			stringstream book_feed(content);
			int current_book_serial;
			string current_book_name, current_author_name;
			book_feed >> Lib.student_id >> Lib.student_first_name >> Lib.student_second_name >> current_book_serial >> current_book_name >> current_author_name;
			your_feedback << Lib.student_id << "\t\t" << Lib.student_first_name << "\t\t\t" << Lib.student_second_name << "\t\t" << current_book_serial << "\t\t" << current_book_name << "\t\t" << current_author_name << "\t\t" << feedback << endl;
		}
		your_feedback.close();
		cout << "\t\t\t\t\t\tYOUR FEEDBACK SUBMITTED SUCESSFULLY" << endl;
	}
	else
	{
		cout << "\t\t\t\t\tERROR: Incorrect Number Please Try Again!" << endl;
		goto again;
	}
}
void display_book_feedback()
{
	starline();
	cout << "\t\t\t\t\t\tBOOKS FEEDBACK" <<  endl;
	starline();
	ifstream check_feedback;
	check_feedback.open("Books Feedback.txt");
	cout << "\nStudent ID" << "\t" << "Student First Name" << "\t" << "Last Name" << "\t" << "Book SR" << "\t\t" << "Book Name" << "\t" << "Author Name" << "\t" << "Ratings" << endl;
	if (!check_feedback.is_open())
	{
		cout << "\t\t\t\t\t\tError opening file for writing." << endl;
		return;
	}
	string content;
	while (getline(check_feedback,content))
	{
		cout << content << endl;
	}
	check_feedback.close();
	system("pause");
	system("cls");
}
void student_page()
{
	again_ask:
	starline();
	cout << "\t\t\t\t\t\tWELCOME, " << Lib.student_first_name << " " << Lib.student_second_name << "!" << endl;
	starline();
	int choice3;
	cout << "Press 1 to Borrow Book " << endl;
	cout << "Press 2 to See Borrowed Book " << endl;
	cout << "Press 3 to Return Book " << endl;
	cout << "Press 4 to See Books Feedback " << endl;
	cout << "Press 0 to Sign Out " << endl;
	cout << "\nEnter Your Choice : ";
	cin >> choice3;
	system("cls");
	switch (choice3)
	{
	case 0:
		main();
		break;
	case 1:
		borrow_books();
		break;
	case 2:
		starline();
		cout << "\t\t\t\t\tBORROWED BOOKS BY ID " << Lib.student_id << endl;
		starline();
		display_borrow_book_to_student();
		system("pause");
		system("cls");
		goto again_ask;
		break;
	case 3:
		return_book();
		break;
	case 4:
		display_book_feedback();
		goto again_ask;
		break;
	default:
		starline();
		cout << "\t\t\t\t\t\tINVALID OPERATOR! TRY AGAIN " << endl;
		starline();
		system("pause");
		system("cls");
		goto again_ask;
		break;
	}
}
void instruction()
{
	starline();
	cout << "\t\t\t\t\t\tPROJECT MADE BY " << endl;
	starline();
	cout << "\n\t\t\t\tSTUDENT ID\t\t\t\tSTUDENT NAME\n" << endl;
	cout << "\t\t\t\tXXXXXXXXXXX\t\t\t\tXXXXXXXXXXX\n" << endl;
	cout << "\t\t\t\tXXXXXXXXXXX\t\t\t\tXXXXXXXXXXX\n" << endl;
	cout << "\t\t\t\tXXXXXXXXXXX\t\t\t\tXXXXXXXXXXX\n" << endl;
	cout << "\t\t\t\tXXXXXXXXXXX\t\t\t\tXXXXXXXXXXX\n" << endl;
	starline();
	system("pause");
	system("cls");
	starline();
	cout << "\t\t\t\t\t\tLIBRARY MANAGEMENT SYSTEM FEATURES" << endl;
	starline();
	cout << "\n1. Admin Login: Use username and password to access the admin panel." << endl;
	cout << "2. Student Login: Enter your Student ID and Password to log in as a student." << endl;
	cout << "3. Student Signup: Create a new student account by providing required details." << endl;
	cout << "4. Borrow Book: Students can borrow books available in the library." << endl;
	cout << "5. Return Book: Students can return borrowed books and provide feedback." << endl;
	cout << "6. Admin Features: Add books, display students, delete student records, etc." << endl;
	cout << "7. Feedback: Students can provide feedback for the borrowed books." << endl;
	cout << "8. Display Borrowed Books: View the list of books borrowed by a student." << endl;
	cout << "9. Display Books Feedback: Admin and Student can view feedback provided by students." << endl;
	cout << "10. Sign Out: Log out from the system.\n" << endl;
	starline();
	cout << "Note: Follow the on-screen instructions for a smooth experience." << endl;
	starline();
	system("pause");
	system("cls");
}