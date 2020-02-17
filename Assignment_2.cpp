/*
Name : Osama Salah Abdelmoniem               ID : 20180039
Name : Marwan Galal Mohamed                  ID : 20180268
Name : Mahmoud Maarouf abdelhalim            ID : 20180264
*/


#include<iostream>
#include<vector>
#include<string>
#include <fstream>
#include <algorithm>
#include <time.h>
using namespace std;

int exit_prog();
//variable to store the index of the player to access his data from any array
int index_of_player;
//var to know what is ID of the next QS during loading
int ID;
//variable to know if there is QS loaded or not
bool loaded = false;
//array used during generating random choices
int visited_choices[4];
//this is a struct to store all information of the user
struct full_user_information
{
	string un, password, fname, Lname, role;
};
//this struct is a struct to store the username and password of the user to compare it with the stored one
struct check_struct
{
	string username, pass;
};
class USER
{
protected:
	full_user_information ui;
public:
	USER() {
		ui.fname = "user";
		ui.Lname = "user";
	}
	virtual void main_menu() {}

	void struct_assigning(full_user_information x)
	{
		ui.fname = x.fname;
		ui.Lname = x.Lname;
		ui.un = x.un;
		ui.password = x.password;
		ui.role = x.role;
	}

	bool checking_exist(check_struct i)
	{
		return(i.username == ui.un && i.pass == ui.password);
	}
	bool checking_exist(string str)
	{
		return(str == ui.un);
	}
	string role_check()
	{
		return ui.role;
	}
	void Update_firstname_lastname()
	{
		cout << "Enter your First name ";
		cin >> ui.fname;
		cout << "Enter your Last name  ";
		cin >> ui.Lname;
	}
	void print_info() {
		cout << ui.fname << "  " << ui.Lname << "  " << ui.un << "  " << ui.role << endl;
	}
};
void admin_main_menu(int no_of_user, vector<USER*>& user_information);
void player_main_menu(int no_of_user, vector<USER*>& user_information);
class ADMIN : public USER
{
public:
	void main_menu()
	{
		cout << "Welcome" << " " << ui.fname << " " << ui.Lname << " " << "(" << ui.role << ")" << ", please choose from the following options: " << endl;
		cout << "[1] Switch accounts." << endl;
		cout << "[2] Update your name." << endl;
		cout << "[3] View all users." << endl;
		cout << "[4] Add new user." << endl;
		cout << "[5] View all questions." << endl;
		cout << "[6] Add new question." << endl;
		cout << "[7] Load questions from file." << endl;
		cout << "[8] Exit the program." << endl;
		cout << "My choice :";
	}
};
class PLAYER : public USER
{
private:

public:
	void main_menu()
	{
		cout << "Welcome" << " " << ui.fname << " " << ui.Lname << " " << "(" << ui.role << ")" << ", please choose from the following options: " << endl;
		cout << "[1] Switch accounts." << endl;
		cout << "[2] Update your name." << endl;
		cout << "[3] Start a new quiz" << endl;
		cout << "[4] Display your scores statistics" << endl;
		cout << "[5] Display all your scores." << endl;
		cout << "[6] Display details of your last 2 quizzes." << endl;
		cout << "[7] Exit the program." << endl;
		cout << "My choice :";
	}

};
//this struct takes the username & password to assign it to the calss struct and compare with it
check_struct assigning_username_password()
{
	check_struct x;
	cout << "Please enter your username: ";
	cin >> x.username;
	cout << "Please enter your password: ";
	cin >> x.pass;
	return x;
}
/*
this function checks that the account is exist in our vector or not.
takes the struct and vector as parameters.
uses the boolean checking exist function that return the value of checking if the username and password is exist or not.
returns the value of existing.
*/
int check_account(check_struct user_and_pass, vector<USER*>user_information)
{
	bool find = false;
	int count = 0;
	for (auto i = user_information.begin(); i != user_information.end(); i++)
	{

		if ((*i)->checking_exist(user_and_pass))
		{
			find = true;
			break;
		}
		count++;
	}
	if (find == true)
		return count;
	else
		return -1;
}
/*
this function takes the vector of objects and the struct that was used to compare with as paramiters
this function takes the first name,
last name,
username,
and the password of the user to store it and make a account for him
*/
void Default_admin_player(vector<USER*>& user_information)
{
	USER* admin = new ADMIN;
	USER* player = new PLAYER;
	full_user_information u_information;
	u_information.fname = "user";
	u_information.Lname = "user";
	u_information.un = "admin";
	u_information.role = "admin";
	u_information.password = "admin";
	admin->struct_assigning(u_information);
	user_information.push_back(admin);
	u_information.fname = "user";
	u_information.Lname = "user";
	u_information.un = "player";
	u_information.role = "player";
	u_information.password = "player";
	player->struct_assigning(u_information);
	user_information.push_back(player);
}
int ADD_USER(vector<USER*>& user_information, check_struct user_and_pass = { "notempty","notempty" })
{
	full_user_information user_inform;
	cout << "Please enter your signing information: " << endl;
	cout << "Enter your First name: ";
	cin >> user_inform.fname;
	cout << "Enter your Last name: ";
	cin >> user_inform.Lname;
	cout << "Enter your Username: ";
	cin >> user_inform.un;
	while (true)
	{
		for (auto i = user_information.begin(); i != user_information.end(); i++)
		{
			if ((*i)->checking_exist(user_inform.un))
			{
				cout << "This username already taken, please enter another username : " << endl;
				cin >> user_inform.un;
				break;
			}
		}
		break;
	}
	cout << "Enter your Password: ";
	cin >> user_inform.password;

	USER* base;
	if (user_and_pass.username == "admin" && user_and_pass.pass == "admin")
	{
		user_inform.role = "admin";
		base = new ADMIN;
		base->struct_assigning(user_inform);
		user_information.push_back(base);
	}
	else if ((user_and_pass.username == "player" && user_and_pass.pass == "player"))
	{
		user_inform.role = "player";
		base = new PLAYER;
		base->struct_assigning(user_inform);
		user_information.push_back(base);
	}
	else {
		cout << "Enter the role (admin or player) : ";
		cin >> user_inform.role;
		while (true)
		{
			if (user_inform.role == "admin")
			{
				base = new ADMIN;
				break;
			}
			else if (user_inform.role == "player")
			{
				base = new PLAYER;
				break;
			}
			cout << "Invalid input, please enter a valid role (admin or player) : ";
			cin >> user_inform.role;
		}
		base->struct_assigning(user_inform);
		user_information.push_back(base);
	}
	return user_information.size() - 1;
}
int logining(check_struct user_and_pass, vector<USER*>& user_information)
{


	int counter;
	while (true)
	{
		counter = check_account(user_and_pass, user_information);
		if (counter == -1)
		{
			cout << "Username or Password isn't correct, please enter your username and password again." << endl;
			cout << "Enter your username :" << endl;
			cin >> user_and_pass.username;
			cout << "Enter your password :" << endl;
			cin >> user_and_pass.pass;
		}
		else
			break;
	}
	return counter;

}

void run_program(vector<USER*>& user_information); //declaration

//fun to convert int to string
int str_To_Int(string s)
{
	int num = 0, digit = s.length(), multiplier = 1, temp;
	for (int i = 1; i < digit; i++) { multiplier *= 10; }
	for (int i = 0; i < s.length(); i++)
	{
		switch (int(s[i]))
		{
		case((int)'0'):
		{
			temp = 0;
			break;
		}
		case((int)'1'):
		{
			temp = 1;
			break;
		}
		case((int)'2'):
		{
			temp = 2;
			break;
		}
		case((int)'3'):
		{
			temp = 3;
			break;
		}
		case((int)'4'):
		{
			temp = 4;
			break;
		}
		case((int)'5'):
		{
			temp = 5;
			break;
		}
		case((int)'6'):
		{
			temp = 6;
			break;
		}
		case((int)'7'):
		{
			temp = 7;
			break;
		}
		case((int)'8'):
		{
			temp = 8;
			break;
		}
		case((int)'9'):
		{
			temp = 9;
			break;
		}
		}
		temp *= multiplier;
		num += temp;
		multiplier /= 10;
	}
	return num;
}
class question
{
public:
	virtual void readQuestionFromFile(string arr[6]) {}
	virtual void print_with_ans() {}
	virtual void store_details_of_qs(string arr[8]) {}
	virtual void printing_for_last_two() {}
};
class mcq : public question
{
	string qs;
	string right_ans;
	string answers[4];
	string player_ans;
public:
	mcq() {}
	mcq(string arr[6])
	{
		qs = arr[0];
		right_ans = arr[1];
		answers[0] = arr[1];
		answers[1] = arr[3];
		answers[2] = arr[4];
		answers[3] = arr[5];
	}
	void readQuestionFromFile(string arr[6])
	{
		qs = arr[0];
		right_ans = arr[1];
		answers[0] = arr[1];
		answers[1] = arr[2];
		answers[2] = arr[3];
		answers[3] = arr[4];
	}
	bool operator==(mcq added)
	{
		return qs == added.qs && right_ans == added.right_ans;
	}
	void set_visited_choices_def()
	{
		visited_choices[0] = 132456;
		visited_choices[1] = 132456;
		visited_choices[2] = 123456;
		visited_choices[3] = 123456;
	}
	bool if_visited_choices(int target)
	{
		for (int i = 0; i < 4; i++)
		{
			if (visited_choices[i] == target)
				return true;
		}
		return false;
	}
	int random(int limit, int ind)
	{
		//rand()%((max+1)-min+1)+min			rand_equ
		int target;
		target = rand() % limit;
		while (if_visited_choices(target))
		{
			target = rand() % limit;
		}
		visited_choices[ind] = target;
		return target;
	}
	void print_with_ans()
	{
		cout << qs << endl;
		set_visited_choices_def();
		for (int r = 0; r < 4; r++)
		{
			int rand = random(4, r);
			char c = 97 + r;
			if (answers[rand] == right_ans)
				cout << "     " << "*[" << c << "] " << answers[rand];
			else
				cout << "     " << "[" << c << "] " << answers[rand];
		}
		cout << endl << endl;

	}
	//used in last 2 quizzes
	void store_details_of_qs(string arr[8])
	{
		qs = arr[1];
		right_ans = arr[2];
		answers[0] = arr[3];
		answers[1] = arr[4];
		answers[2] = arr[5];
		answers[3] = arr[6];
		player_ans = arr[7];
	}
	void printing_for_last_two()
	{
		cout << "[1] " << qs << endl;
		for (int r = 0; r < 4; r++)
		{
			int c = 97;
			cout << "        " << '[' << (char)(c + r) << "] " << answers[r];
		}
		cout << endl;
		cout << "Player answer: " << player_ans << "        ";
		if (player_ans == right_ans)
			cout << "( right answer )" << endl;
		else
			cout << "( wrong answer )" << endl;
		cout << "Right answer: " << right_ans << endl;
		cout << endl;
	}
	//to store qs in arrays of last two quizzes when rand_fun generate a random index of QS
	string get_qs()
	{
		return qs;
	}
	string get_right_ans()
	{
		return right_ans;
	}
	string get_ith_choice(int ind)
	{
		return answers[ind];
	}
};
//array to store mcq QS
mcq mcq_qs[1000];
//var to know how many mcq we have
int num_mcq_qs = 0;
//array to store the id of every QS
int mcq_ids[1000];
//fun to know if the structure of mcq qs valid or not
bool valid_mcq(string arr[6], int cnt)
{
	if (cnt == 5)
	{
		for (int i = 0; i < 5; i++)
		{
			if ((arr[i] != "MCQ" && arr[i] != "COMPELETE" && arr[i] != "TF" && arr[i] != "")) {}
			else
				return false;
		}
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			if ((arr[i] != "MCQ" && arr[i] != "COMPELETE" && arr[i] != "TF" && arr[i] != "") && (arr[5] == "COMPLETE" || arr[5] == "MCQ" || arr[5] == "TF")) {}
			else
				return false;
		}
	}
	return true;
}
class complete : public question
{
	string qs;
	string ans;
	string player_ans;
public:
	complete() {}
	//fun to store data of QS
	complete(string arr[6])
	{
		qs = arr[0];
		ans = arr[1];
	}
	void readQuestionFromFile(string arr[6])
	{
		qs = arr[0];
		ans = arr[1];
	}
	bool operator==(complete added)
	{
		return added.qs == qs && added.ans == ans;
	}
	void print_with_ans()
	{
		cout << qs << " (Answer: " << ans << ")" << endl << endl;
	}
	void store_details_of_qs(string arr[8])
	{
		qs = arr[1];
		ans = arr[2];
		player_ans = arr[3];
	}
	string get_qs()
	{
		return qs;
	}
	string get_ans()
	{
		return ans;
	}
	void printing_for_last_two()
	{
		cout << "[1] " << qs << endl;
		cout << endl;
		cout << "Player answer: " << player_ans << "        ";
		if (player_ans == ans)
			cout << "( right answer )" << endl;
		else
			cout << "( wrong answer )" << endl;
		cout << "Right answer: " << ans << endl;
		cout << endl;
	}
};
complete com_qs[1000];
int num_com_qs = 0;
int com_ids[1000];
bool valid_com(string arr[6], int cnt)
{
	int dots = 0;
	for (int i = 0; i < arr[0].length(); i++)
	{
		if (arr[0][i] == '.' && arr[0][i + 1] == '.' && i < arr[0].length())
		{
			dots++;
			int cnt = 0;
			for (int r = i; r < arr[0].length(); r++)
				cnt++;
			i += cnt;
		}
	}
	if (dots != 1)
		return false;
	if (cnt == 2)
	{
		if (arr[0] != "MCQ" && arr[0] != "COMPLETE" && arr[0] != "" && arr[1] != "" && arr[0] != "TF" && arr[1] != "MCQ" && arr[1] != "COMPLETE" && arr[1] != "TF") {}
		else
			return false;
	}
	else
	{
		if ((arr[2] == "COMPLETE" || arr[2] == "MCQ" || arr[2] == "TF") && arr[0] != "" && arr[1] != "" && arr[0] != "MCQ" && arr[0] != "COMPLETE" && arr[0] != "TF" && arr[1] != "MCQ" && arr[1] != "COMPLETE" && arr[1] != "TF") {}
		else
			return false;
	}
	return true;
}
class tf : public question
{
	string qs;
	string ans;
	string player_ans;
	string id;
public:
	tf() {}
	tf(string arr[6])
	{
		qs = arr[0];
		ans = arr[1];
	}
	void readQuestionFromFile(string arr[6])
	{
		qs = arr[0];
		ans = arr[1];
	}
	bool operator==(tf added)
	{
		return added.qs == qs && added.ans == ans;
	}
	void print_with_ans()
	{
		cout << qs << " (Answer: " << (char)toupper(ans[0]) << ")" << endl << endl;
	}
	void print()
	{
		cout << qs << endl << ans << endl;
	}
	void store_details_of_qs(string arr[8])
	{
		id = arr[0];
		qs = arr[1];
		ans = arr[2];
		player_ans = arr[3];
	}
	string get_qs()
	{
		return qs;
	}
	string get_ans()
	{
		return ans;
	}
	void printing_for_last_two()
	{
		cout << "[1] " << qs << endl;
		cout << endl;
		cout << "Player answer: " << player_ans << "        ";
		if (player_ans == ans)
			cout << "( right answer )" << endl;
		else
			cout << "( wrong answer )" << endl;
		cout << "Right answer: " << ans << endl;
		cout << endl;
	}
};
tf tf_qs[1000];
int num_tf_qs = 0;
int tf_ids[1000];
bool valid_tf(string arr[6], int cnt)
{
	if (cnt == 2)
	{
		if (arr[0] != "MCQ" && arr[0] != "COMPLETE" && arr[0] != "TF" && arr[0] != "" && arr[1] != "" && (arr[1] == "true" || arr[1] == "false")) {}
		else
			return false;
	}
	else
	{
		if (arr[0] != "MCQ" && arr[0] != "COMPLETE" && arr[0] != "TF" && (arr[1] == "true" || arr[1] == "false") && (arr[2] == "MCQ" || arr[2] == "COMPLETE" || arr[2] == "TF")) {}
		else
			return false;
	}
	return true;
}
//fun to know how many line in file
int num_lines_of_file()
{
	fstream file;
	file.open("exam2_questions.txt", ios::in);
	string s;
	int cnt = 0;
	while (!file.eof())
	{
		getline(file, s);
		cnt++;
	}
	file.close();
	return cnt;
}
bool if_file_found(string name)
{
	fstream file;
	file.open(name, ios::in);
	int i = 0;
	bool cond = false;
	while (!file.eof() && i <= 30)
	{
		string s;
		getline(file, s);
		i++;
		if (!cond && s != "\0")
			cond = true;
	}
	return cond;
}
void loading()
{
	string str;
	cin.ignore();
	cout << "Please add \".txt\" at the end of the file name" << endl << "The file name: ";
	getline(cin, str);
	while (!if_file_found(str))
	{
		cout << "This file is not found, Please enter a valid name of file" << endl << "The file name: ";
		getline(cin, str);
	}
	loaded = true;
	fstream file;
	file.open(str, ios::in);
	int cnt = 0;
	bool m = false, c = false, t = false;
	string arr[6];
	int lines = 0;
	while (!file.eof())
	{
		string s;
		getline(file, s);
		lines++;
		if (m)
		{
			arr[cnt] = s;
			cnt++;
			if (cnt == 6 || (cnt == 5 && lines == num_lines_of_file()))
			{
				m = false;
				if (!valid_mcq(arr, cnt))
				{
					cout << "The structure of a question is wrong, the process of loading has stopped." << endl;
					break;
				}
				else
				{
					mcq added(arr);
					bool flag = false;
					for (int r = 0; r < num_mcq_qs; r++)
					{
						if (added == mcq_qs[r])
						{
							flag = true;
							break;
						}
					}
					if (!flag)
					{
						question* ptr;
						ptr = &mcq_qs[num_mcq_qs];
						ptr->readQuestionFromFile(arr);
						mcq_ids[num_mcq_qs] = ++ID;
						num_mcq_qs++;
					}
				}
				cnt = 0;
			}
		}
		else if (c)
		{
			arr[cnt] = s;
			cnt++;
			if (cnt == 3 || (cnt == 2 && lines == num_lines_of_file()))
			{
				c = false;
				for (int i = 0; i < arr[0].length(); i++)
				{
					if ((int)arr[0][i] >= 32 && (int)arr[0][i] <= 125) {}
					else
						arr[0][i] = '.';
				}
				if (!valid_com(arr, cnt))
				{
					cout << "The structure of a question is wrong, the process of loading has stopped." << endl;
					break;
				}
				else
				{
					complete added(arr);
					bool flag = false;
					for (int r = 0; r < num_com_qs; r++)
					{
						if (added == com_qs[r])
						{
							flag = true;
							break;
						}
					}
					if (!flag)
					{
						question* ptr;
						ptr = &com_qs[num_com_qs];
						ptr->readQuestionFromFile(arr);
						com_ids[num_com_qs] = ++ID;
						num_com_qs++;
					}
				}
				cnt = 0;
			}
		}
		else if (t)
		{
			arr[cnt] = s;
			cnt++;
			bool cond = true;
			if (cnt == 3 || (cnt == 2 && lines == num_lines_of_file()))
			{
				t = false;

				if (!valid_tf(arr, cnt))
				{
					cout << "The structure of a question is wrong, the process of loading has stopped." << endl;
					break;
				}
				else
				{
					tf added(arr);
					bool flag = false;
					for (int r = 0; r < num_tf_qs; r++)
					{
						if (added == tf_qs[r])
						{
							flag = true;
							break;
						}
					}
					if (!flag)
					{
						question* ptr;
						ptr = &tf_qs[num_tf_qs];
						ptr->readQuestionFromFile(arr);
						tf_ids[num_tf_qs] = ++ID;
						num_tf_qs++;
					}
				}
				cnt = 0;
			}
		}
		if (s == "MCQ" && !m && !c && !t)
			m = true;
		else if (s == "COMPLETE" && !m && !c && !t)
			c = true;
		else if (s == "TF" && !m && !c && !t)
			t = true;
	}
}
bool check_int(string ele) {
	for (int i = 0; i < ele.length(); i++) {
		if ((int)ele[i]<(int)'1' || (int)ele[i] > (int)'9')
			return false;
	}
	return true;
}
void view_all_qs(int no_of_user, vector<USER*>& user_information)
{
	cout << "Number of questions available: " << num_mcq_qs + num_com_qs + num_tf_qs << endl << endl;
	cout << "---------------------------------------------------" << endl << endl;
	cout << "MC Questions list (Total: " << num_mcq_qs << " Questions)" << endl << endl;
	cout << "---------------------------------------------------" << endl << endl;
	for (int i = 0; i < num_mcq_qs; i++)
	{
		cout << '[' << i + 1 << "] (ID: " << mcq_ids[i] << ") ";
		mcq_qs[i].print_with_ans();
	}
	cout << "----------------------------------------------------" << endl << endl;
	cout << "TF Questions list (Total: " << num_tf_qs << " Questions)" << endl << endl;
	cout << "----------------------------------------------------" << endl << endl;
	for (int i = 0; i < num_tf_qs; i++)
	{
		cout << '[' << i + 1 << "] (ID: " << tf_ids[i] << ") ";
		tf_qs[i].print_with_ans();
	}
	cout << "----------------------------------------------------" << endl << endl;
	cout << "COMPLETE Questions list (Total: " << num_com_qs << " Questions)" << endl << endl;
	cout << "----------------------------------------------------" << endl << endl;
	for (int i = 0; i < num_com_qs; i++)
	{
		cout << '[' << i + 1 << "] (ID: " << com_ids[i] << ") ";
		com_qs[i].print_with_ans();
	}
	cout << endl << "----------------------------------------------------" << endl << endl;
	cout << "Press [d] and the question ID if you want to delete a question (Example: d 2)" << endl;
	cout << "Press [b] if you want to go back to the main menu " << endl << endl;
	char charac;
	string num;
	cout << "Your choice: ";
	cin >> charac;
	while ((charac != 'b' && charac != 'd'))
	{
		cin >> charac;
	}
	if (charac == 'b')
		admin_main_menu(no_of_user, user_information);
	else
	{
		cin >> num;
		while (!check_int(num))
		{
			cout << "Please enter a valid ID of question: ";
			cin >> num;
		}
		bool flag = false;
		while (!flag)
		{
			int n = str_To_Int(num);
			for (int i = 0; i < num_mcq_qs; i++)
			{
				if (n == mcq_ids[i])
				{
					swap(mcq_ids[i], mcq_ids[num_mcq_qs - 1]);
					swap(mcq_qs[i], mcq_qs[num_mcq_qs - 1]);
					num_mcq_qs--;
					flag = true;
					break;
				}
			}
			if (!flag)
			{
				for (int i = 0; i < num_com_qs; i++)
				{
					if (n == com_ids[i])
					{
						swap(com_ids[i], com_ids[num_com_qs - 1]);
						swap(com_qs[i], com_qs[num_com_qs - 1]);
						num_com_qs--;
						flag = true;
						break;
					}
				}
			}
			if (!flag)
			{
				for (int i = 0; i < num_tf_qs; i++)
				{
					if (n == tf_ids[i])
					{
						swap(tf_ids[i], tf_ids[num_tf_qs - 1]);
						swap(tf_qs[i], tf_qs[num_tf_qs - 1]);
						num_tf_qs--;
						flag = true;
						break;
					}
				}
			}
			if (!flag)
			{
				cout << "There is no question found with that ID, please enter a valid ID." << endl;
				cout << "ID: ";
				cin >> num;
			}
		}
		view_all_qs(no_of_user, user_information);
	}
}
void add_new_qs(int no_of_user, vector<USER*>& user_information)
{
	string cont = "yes";
	while (cont == "yes" || cont == "YES" || cont == "YES")
	{
		char choice;
		cout << "What is the type of the question that you want to add?" << endl;
		cout << "[a] MCQ     [b] COMPLETE     [c]TF" << endl;
		cout << "My choice: ";
		cin >> choice;
		while (choice != 'a' && choice != 'b' && choice != 'c')
		{
			cout << "Please enter a valid choice." << endl;
			cout << "My choice: ";
			cin >> choice;
		}
		if (choice == 'a')
		{
			cin.ignore();
			string arr[6];
			cout << "Please enter the question: ";
			getline(cin, arr[0]);
			while (arr[0] == "")
			{
				cout << "Please enter a valid question: ";
				getline(cin, arr[0]);
			}
			cout << "Please enter 4 choices which include the right choice as a first choice" << endl;
			cout << "first choice: ";
			getline(cin, arr[1]);
			while (arr[1] == "")
			{
				cout << "Please enter a valid choice: ";
				getline(cin, arr[1]);
			}
			cout << "second choice: ";
			getline(cin, arr[2]);
			while (arr[2] == "")
			{
				cout << "Please enter a valid choice: ";
				getline(cin, arr[2]);
			}
			cout << "third choice: ";
			getline(cin, arr[3]);
			while (arr[3] == "")
			{
				cout << "Please enter a valid choice: ";
				getline(cin, arr[3]);
			}
			cout << "fourth choice: ";
			getline(cin, arr[4]);
			while (arr[4] == "")
			{
				cout << "Please enter a valid choice: ";
				getline(cin, arr[4]);
			}
			mcq added(arr);
			bool flag = false;
			for (int r = 0; r < num_mcq_qs; r++)
			{
				if (added == mcq_qs[r])
				{
					flag = true;
					cout << "Sorry, This question has already been added";
					break;
				}
			}
			if (!flag)
			{
				question* ptr;
				ptr = &mcq_qs[num_mcq_qs];
				ptr->readQuestionFromFile(arr);
				mcq_ids[num_mcq_qs] = ++ID;
				num_mcq_qs++;
				cout << "The question has been added" << endl;
			}
		}
		else if (choice == 'b')
		{
			cin.ignore();
			string arr[6];
			cout << "Please enter the question: ";
			getline(cin, arr[0]);
			while (arr[0] == "")
			{
				cout << "Please enter a valid question: ";
				getline(cin, arr[0]);
			}
			cout << "Please enter the answer: ";
			getline(cin, arr[1]);
			while (arr[1] == "")
			{
				cout << "Please enter a valid answer: ";
				getline(cin, arr[1]);
			}
			if (!valid_com(arr, 2))
				cout << "The structure of the question is not valid" << endl;
			else
			{
				complete added(arr);
				bool flag = false;
				for (int r = 0; r < num_com_qs; r++)
				{
					if (added == com_qs[r])
					{
						flag = true;
						cout << "Sorry, This question has already been added";
						break;
					}
				}
				if (!flag)
				{
					question* ptr;
					ptr = &com_qs[num_com_qs];
					ptr->readQuestionFromFile(arr);
					com_ids[num_com_qs] = ++ID;
					num_com_qs++;
				}
			}
		}
		else if (choice == 'c')
		{
			cin.ignore();
			string arr[6];
			cout << "Please enter the question: ";
			getline(cin, arr[0]);
			while (arr[0] == "")
			{
				cout << "Please enter a valid question: ";
				getline(cin, arr[0]);
			}
			cout << "Please enter the answer: ";
			getline(cin, arr[1]);
			while (arr[1] == "")
			{
				cout << "Please enter a valid answer: ";
				getline(cin, arr[1]);
			}
			if (!valid_tf(arr, 2))
				cout << "The structure of the question is not valid" << endl;
			else
			{
				tf added(arr);
				bool flag = false;
				for (int r = 0; r < num_tf_qs; r++)
				{
					if (added == tf_qs[r])
					{
						flag = true;
						cout << "Sorry, This question has already been added";
						break;
					}
				}
				if (!flag)
				{
					question* ptr;
					ptr = &tf_qs[num_tf_qs];
					ptr->readQuestionFromFile(arr);
					tf_ids[num_tf_qs] = ++ID;
					num_tf_qs++;
				}
			}
		}
		cout << "Do you want to add another question? " << endl;
		cout << "My answer: ";
		cin >> cont;
		while (cont != "YES" && cont != "Yes" && cont != "yes" && cont != "NO" && cont != "no")
		{
			cout << "Please enter a valid choice: ";
			cin >> cont;
		}
	}
	cout << "Press [b] if you want to go back to the main menu or [e] to exit" << endl;
	char choice;
	cout << "My choice: ";
	cin >> choice;
	while (choice != 'e' && choice != 'b')
	{
		cout << "Please enter a valid choice: ";
		cin >> choice;
	}
	if (choice == 'b')
		admin_main_menu(no_of_user, user_information);
	else
		exit_prog();
}
class details
{
protected:
	int scores[1000];
	float mcq_right[1000];
	float com_right[1000];
	float tf_right[1000];
public:
	int num_of_quizes;
	details()
	{
		num_of_quizes = 0;
		for (int i = 0; i < 1000; i++)
		{
			scores[i] = 0;
			mcq_right[i] = 0;
			com_right[i] = 0;
			tf_right[i] = 0;
		}
	}
	void inc_num_of_quizes_taken()
	{
		num_of_quizes++;
	}
	void inc_mcq_right()
	{
		mcq_right[num_of_quizes]++;
	}
	void inc_com_right()
	{
		com_right[num_of_quizes]++;
	}
	void inc_tf_right()
	{
		tf_right[num_of_quizes]++;
	}
	void store_score(int s)
	{
		scores[num_of_quizes] = s;
	}
	void print_num_of_quizes_taken()
	{
		cout << "        " << "- Number of Quizzes taken: " << num_of_quizes << endl;
	}
	void highest_score()
	{
		int Max = 0;
		for (int i = 0; i < num_of_quizes; i++)
			Max = max(Max, scores[i]);
		cout << "        " << "- highst quiz score: " << *max_element(scores, scores + num_of_quizes) << "/10" << endl;
	}
	void lowest_score()
	{
		cout << "        " << "- lowest quiz score: " << *min_element(scores, scores + num_of_quizes) << "/10" << endl;
	}
	void avg_score()
	{
		float sum = 0;
		for (int i = 0; i < num_of_quizes; i++)
			sum += scores[i];
		float res = sum / num_of_quizes;
		cout << "        " << "- Average quiz score: " << res << "/10" << endl;
	}
	void num_of_mcq()
	{
		cout << "        " << "- Number of MC questions: " << num_of_quizes * 3 * 2 << endl;
	}
	void num_of_com()
	{
		cout << "        " << "- Number of COMPLETE questions: " << num_of_quizes * 1 * 3 << endl;
	}
	void num_of_tf()
	{
		cout << "        " << "- Number of T/F questions: " << num_of_quizes * 2 * 1 << endl;
	}
	void avg_mcq()
	{
		float sum = 0;
		for (int i = 0; i < num_of_quizes; i++)
			sum += mcq_right[i];
		cout << "        " << "- Average grade for MC questions: " << (sum * 1) / (num_of_quizes * 3) << "/1" << endl;
	}
	void avg_com()
	{
		float sum = 0;
		for (int i = 0; i < num_of_quizes; i++)
			sum += mcq_right[i];
		cout << "        " << "- Average grade for COMPLETE questions: " << (sum * 3) / (num_of_quizes * 1) << "/3" << endl;
	}
	void avg_tf()
	{
		float sum = 0;
		for (int i = 0; i < num_of_quizes; i++)
			sum += mcq_right[i];
		cout << "        " << "- Average grade for T/F questions: " << (sum * 2) / (num_of_quizes * 2) << "/2" << endl;
	}
	void print_mcq_details_ans(int ith_quiz)
	{
		cout << "        " << "- MC Questions' right answers: " << mcq_right[ith_quiz] << endl;
		cout << "        " << "- MC Questions' wrong answers: " << 3 - mcq_right[ith_quiz] << endl;
	}
	void print_com_details_ans(int ith_quiz)
	{
		cout << "        " << "- COMPLETE Questions' right answers: " << com_right[ith_quiz] << endl;
		cout << "        " << "- COMPLETE Questions' wrong answers: " << 1 - com_right[ith_quiz] << endl;
	}
	void print_tf_details_ans(int ith_quiz)
	{
		cout << "        " << "- T/F Questions' right answers: " << tf_right[ith_quiz] << endl;
		cout << "        " << "- T/F Questions' wrong answers: " << 2 - tf_right[ith_quiz] << endl;
	}
	void print_quiz_details_ans()
	{
		for (int i = 0; i < num_of_quizes; i++)
		{
			if (i == 0)
				cout << "The 1st quiz: " << endl;
			else if (i == 1)
				cout << "The 2nd quiz: " << endl;
			else if (i == 2)
				cout << "The 3rd quiz: " << endl;
			else
				cout << "The " << i + 1 << "th quiz: " << endl;
			print_mcq_details_ans(i);
			print_com_details_ans(i);
			print_tf_details_ans(i);
			cout << endl;
		}
	}
};
class last
{
	mcq mcq_ques[3];
	complete com_ques[1];
	tf tf_ques[2];
	int right_mcq;
	int right_tf;
	int right_com;
public:
	void store_right_qs(int m, int c, int t)
	{
		right_mcq = m;
		right_com = c;
		right_tf = t;
	}
	void store_mcq(string arr[8], int ind)
	{
		mcq_ques[ind].store_details_of_qs(arr);
	}
	void store_com(string arr[8], int ind)
	{
		com_ques[ind].store_details_of_qs(arr);
	}
	void store_tf(string arr[8], int ind)
	{
		tf_ques[ind].store_details_of_qs(arr);
	}
	void display_all_mcq()
	{
		cout << "---------------------------------------------------" << endl << endl;
		cout << "MC Questions list: (Total: 3 questions)" << endl << endl;
		cout << "---------------------------------------------------" << endl << endl;
		for (int i = 0; i < 3; i++)
			mcq_ques[i].printing_for_last_two();
		cout << "Score of the player in MC Questions: " << right_mcq << "/3" << endl << endl;
	}
	void display_all_tf()
	{
		cout << "---------------------------------------------------" << endl << endl;
		cout << "T/F Questions list: (Total: 2 questions)" << endl << endl;
		cout << "---------------------------------------------------" << endl << endl;
		for (int i = 0; i < 2; i++)
			tf_ques[i].printing_for_last_two();
		cout << "Score of the player in T/F Questions: " << right_tf * 2 << "/4" << endl << endl;
	}
	void display_all_com()
	{
		cout << "---------------------------------------------------" << endl << endl;
		cout << "COMPLETE Questions list: (Total: 1 question)" << endl << endl;
		cout << "---------------------------------------------------" << endl << endl;
		for (int i = 0; i < 1; i++)
			com_ques[i].printing_for_last_two();
		cout << "Score of the player in COMPLETE Questions: " << right_com * 3 << "/3" << endl << endl;
	}
	void display_score()
	{
		cout << "Player score in this quiz: " << right_com + right_mcq + right_tf << endl << endl;
	}
};
int exit_prog()
{
	return 0;
}
//array to store details of every quiz for every player
details for_all_players[1000];
//dun to display stats of every player in previous quizzes
void statistics_for_player(int no_of_user, vector<USER*>& user_information)
{
	if (for_all_players[index_of_player].num_of_quizes < 1)
	{
		cout << "------------------------------------------------------------------------------------------------------" << endl << endl;
		cout << "This player did not take any quizzes to show" << endl << endl;
		cout << "Press [b] if you want to go back to the main menu or [e] to exit" << endl;
		char choice;
		cout << "My choice: ";
		cin >> choice;
		while (choice != 'e' && choice != 'b')
		{
			cout << "Please enter a valid choice: ";
			cin >> choice;
		}
		if (choice == 'b')
			player_main_menu(no_of_user, user_information);
		else
			exit_prog();
	}
	else
	{
		cout << "------------------------------------------------------------------------------------------------------" << endl << endl;
		cout << "Your score statistics per quiz:" << endl;
		for_all_players[index_of_player].print_num_of_quizes_taken();
		for_all_players[index_of_player].highest_score();
		for_all_players[index_of_player].lowest_score();
		for_all_players[index_of_player].avg_score();
		cout << "Your score statistics per question type:" << endl;
		for_all_players[index_of_player].num_of_mcq();
		for_all_players[index_of_player].num_of_com();
		for_all_players[index_of_player].num_of_tf();
		for_all_players[index_of_player].avg_mcq();
		for_all_players[index_of_player].avg_com();
		for_all_players[index_of_player].avg_tf();
		cout << "Press [b] if you want to go back to the main menu or [e] to exit" << endl;
		char choice;
		cout << "My choice: ";
		cin >> choice;
		while (choice != 'e' && choice != 'b')
		{
			cout << "Please enter a valid choice: ";
			cin >> choice;
		}
		if (choice == 'b')
			admin_main_menu(no_of_user, user_information);
		else
			exit_prog();
	}
}
void display_all_scores(int no_of_user, vector<USER*>& user_information)
{
	if (for_all_players[index_of_player].num_of_quizes < 1)
	{
		cout << "------------------------------------------------------------------------------------------------------" << endl << endl;
		cout << "This player did not take any quizzes to show" << endl << endl;
		cout << "Press [b] if you want to go back to the main menu or [e] to exit" << endl;
		char choice;
		cout << "My choice: ";
		cin >> choice;
		while (choice != 'e' && choice != 'b')
		{
			cout << "Please enter a valid choice: ";
			cin >> choice;
		}
		if (choice == 'b')
			player_main_menu(no_of_user, user_information);
		else
			exit_prog();
	}
	else
	{
		cout << "------------------------------------------------------------------------------------------------------" << endl << endl;
		for_all_players[index_of_player].print_num_of_quizes_taken();
		cout << endl;
		for_all_players[index_of_player].print_quiz_details_ans();
		char choice;
		cout << "My choice: ";
		cin >> choice;
		while (choice != 'e' && choice != 'b')
		{
			cout << "Please enter a valid choice: ";
			cin >> choice;
		}
		if (choice == 'b')
			player_main_menu(no_of_user, user_information);
		else
			exit_prog();
	}
}
last last_one[1000];
bool bool_last_one[1000];
last pre_last_one[1000];
bool bool_pre_last_one[1000];
void display_details_for_last_2_quizzes(int no_of_user, vector<USER*>& user_information)
{
	cout << "------------------------------------------------------------------------------------------------------" << endl << endl;
	if (!bool_last_one[index_of_player] && !bool_pre_last_one[index_of_player])
		cout << "The player did not take any quizzes" << endl << endl;
	else if (!bool_pre_last_one[index_of_player])
	{
		cout << "The player took just 1 quiz" << endl << endl;
		cout << "Details of the quiz:" << endl << endl;
		last_one[index_of_player].display_all_mcq();
		last_one[index_of_player].display_all_tf();
		last_one[index_of_player].display_all_com();
	}
	else
	{
		cout << "Details of the before last quiz" << endl << endl;
		pre_last_one[index_of_player].display_all_mcq();
		pre_last_one[index_of_player].display_all_tf();
		pre_last_one[index_of_player].display_all_com();
		cout << "Details of the last quiz" << endl << endl;
		last_one[index_of_player].display_all_mcq();
		last_one[index_of_player].display_all_tf();
		last_one[index_of_player].display_all_com();
	}
	cout << "Press [b] if you want to go back to the main menu or [e] to exit" << endl;
	char choice;
	cout << "My choice: ";
	cin >> choice;
	while (choice != 'e' && choice != 'b')
	{
		cout << "Please enter a valid choice: ";
		cin >> choice;
	}
	if (choice == 'b')
		player_main_menu(no_of_user, user_information);
	else
		exit_prog();

}
int visited_qs[3];
void set_visited_qs_def()
{
	visited_qs[0] = 132456;
	visited_qs[1] = 132456;
	visited_qs[2] = 123456;
}
bool if_visited_qs(int target, int limit)
{
	for (int i = 0; i < limit; i++)
	{
		if (visited_qs[i] == target)
			return true;
	}
	return false;
}
int random_qs(int ind, int num_qs)
{
	//rand()%((max+1)-min+1)+min			rand_equ
	int target;
	target = rand() % num_qs;
	while (if_visited_qs(target, num_qs))
		target = rand() % num_qs;
	visited_qs[ind] = target;
	return target;
}
void set_visited_choices_def()
{
	visited_choices[0] = 132456;
	visited_choices[1] = 132456;
	visited_choices[2] = 123456;
	visited_choices[3] = 123456;
}
bool if_visited_choices(int target)
{
	for (int i = 0; i < 4; i++)
	{
		if (visited_choices[i] == target)
			return true;
	}
	return false;
}
int random(int ind)
{
	//rand()%((max+1)-min+1)+min			rand_equ
	int target;
	target = rand() % 4;
	while (if_visited_choices(target))
	{
		target = rand() % 4;
	}
	visited_choices[ind] = target;
	return target;
}
void start_new_quiz(int no_of_user, vector<USER*>& user_information)
{
	if (!loaded)
	{
		cout << "There are no enough questions to start quiz" << endl << endl;
		cout << "Press [b] if you want to go back to the main menu or [e] to exit" << endl;
		char choice;
		cout << "My choice: ";
		cin >> choice;
		while (choice != 'e' && choice != 'b')
		{
			cout << "Please enter a valid choice: ";
			cin >> choice;
		}
		if (choice == 'b')
			player_main_menu(no_of_user, user_information);
		else if (choice == 'e')
			exit_prog();
	}
	else if ((num_mcq_qs < 3 && num_com_qs < 1 && num_tf_qs < 2))
	{
		cout << "There are no enough questions to start quiz" << endl << endl;
		cout << "Press [b] if you want to go back to the main menu or [e] to exit" << endl;
		char choice;
		cout << "My choice: ";
		cin >> choice;
		while (choice != 'e' && choice != 'b')
		{
			cout << "Please enter a valid choice: ";
			cin >> choice;
		}
		if (choice == 'b')
			player_main_menu(no_of_user, user_information);
		else if (choice == 'e')
			exit_prog();
	}
	else
	{
		cout << "------------------------------------------------------------------------------------------------------" << endl;
		int mcq_right = 0;
		int com_right = 0;
		int tf_right = 0;
		if (!bool_last_one[index_of_player] && !bool_pre_last_one[index_of_player])
			bool_last_one[index_of_player] = true;
		else
		{
			bool_last_one[index_of_player] = true;
			bool_pre_last_one[index_of_player] = true;
			swap(last_one[index_of_player], pre_last_one[index_of_player]);
		}
		// ----------------------------- MCQ --------------------
		cout << "Number of questions in quiz: " << 6 << endl << endl;
		cout << "---------------------------------------------------" << endl << endl;
		cout << "MC Questions (list: 3 Questions)" << endl << endl;
		cout << "---------------------------------------------------" << endl << endl;
		int rand1;
		string mcq_data[8];
		set_visited_qs_def();
		for (int i = 0; i < 3; i++)
		{
			set_visited_choices_def();
			rand1 = random_qs(i, num_mcq_qs);
			cout << '[' << i + 1 << "] " << "( ID: " << mcq_ids[rand1] << " )" << mcq_qs[rand1].get_qs() << endl;
			mcq_data[0] = mcq_ids[rand1];
			mcq_data[1] = mcq_qs[rand1].get_qs();
			mcq_data[2] = mcq_qs[rand1].get_right_ans();
			for (int r = 0; r < 4; r++)
			{
				int rand2 = random(r);
				mcq_data[3 + r] = mcq_qs[rand1].get_ith_choice(rand2);
				int c = 97;
				cout << "        " << '[' << (char)(c + r) << "] " << mcq_qs[rand1].get_ith_choice(rand2);
			}
			cout << endl << endl;
			char choice;
			cout << "My choice: ";
			cin >> choice;
			while ((int)choice < 97 || (int)choice>100)
			{
				cout << "Please enter a valid choice: ";
				cin >> choice;
			}
			mcq_data[7] = mcq_data[(int)choice - 97 + 3];
			if (mcq_data[2] == mcq_data[7])
			{
				for_all_players[index_of_player].inc_mcq_right();
				mcq_right++;
			}
			cout << endl << endl << endl;
			last_one[index_of_player].store_mcq(mcq_data, i);
		}
		//---------------------------------------- T/F -----------------------
		cout << "---------------------------------------------------" << endl << endl;
		cout << "T/F Questions (list: 2 Questions)" << endl << endl;
		cout << "---------------------------------------------------" << endl << endl;
		string tf_data[8];
		set_visited_qs_def();
		for (int i = 0; i < 2; i++)
		{
			set_visited_choices_def();
			rand1 = random_qs(i, num_tf_qs);
			cout << '[' << i + 1 << "] " << "( ID: " << tf_ids[rand1] << " )" << tf_qs[rand1].get_qs() << endl;
			tf_data[0] = tf_ids[rand1];
			tf_data[1] = tf_qs[rand1].get_qs();
			tf_data[2] = tf_qs[rand1].get_ans();
			cout << endl << endl;
			string choice;
			cout << "My choice: ";
			cin >> choice
				;        while (choice != "true" && choice != "false")
			{
				cout << "please enter a valid answer: ";
				cin >> choice;
			}
			tf_data[3] = choice;
			if (tf_data[2] == tf_data[3])
			{
				for_all_players[index_of_player].inc_tf_right();
				tf_right++;
			}
			last_one[index_of_player].store_tf(tf_data, i);
			cout << endl << endl << endl;
		}
		//---------------------------------------- COMPLETE -----------------------
		cout << "---------------------------------------------------" << endl << endl;
		cout << "COMPLETE Questions (list: 2 Questions)" << endl << endl;
		cout << "---------------------------------------------------" << endl << endl;
		string com_data[4];
		set_visited_qs_def();
		for (int i = 0; i < 1; i++)
		{
			set_visited_choices_def();
			rand1 = random_qs(i, num_com_qs);
			cout << '[' << i + 1 << "] " << "( ID: " << com_ids[rand1] << " )" << com_qs[rand1].get_qs() << endl;
			com_data[0] = com_ids[rand1];
			com_data[1] = com_qs[rand1].get_qs();
			com_data[2] = com_qs[rand1].get_ans();
			cout << endl << endl;
			string choice;
			cout << "My choice: ";
			cin.ignore();
			getline(cin, choice);
			com_data[3] = choice;
			if (com_data[2] == com_data[3])
			{
				for_all_players[index_of_player].inc_com_right();
				com_right++;
			}
			cout << endl << endl << endl;
			last_one[index_of_player].store_com(com_data, i);
		}
		last_one[index_of_player].store_right_qs(mcq_right, com_right, tf_right);
		cout << endl << "---------------------------------------------------" << endl << endl;
		cout << "Report of the quiz: " << endl << endl;
		cout << endl << "---------------------------------------------------" << endl << endl;
		cout << "Score: " << (mcq_right * 1) + (com_right * 3) + (tf_right * 2) << "/10" << endl << endl;
		for_all_players[index_of_player].store_score((mcq_right * 1) + (com_right * 3) + (tf_right * 2));
		cout << "Number of right answer in MC Questions: " << mcq_right << endl << endl;
		cout << "Number of wrong answer in MC Questions: " << 3 - mcq_right << endl << endl;
		cout << "Number of right answer in T/F Questions: " << tf_right << endl << endl;
		cout << "Number of wrong answer in T/F Questions: " << 2 - tf_right << endl << endl;
		cout << "Number of right answer in COMPLETE Questions: " << com_right << endl << endl;
		cout << "Number of wrong answer in COMPLETE Questions: " << 1 - com_right << endl << endl;
		cout << endl << endl;
		for_all_players[index_of_player].inc_num_of_quizes_taken();
		player_main_menu(no_of_user, user_information);
	}
}
void player_main_menu(int no_of_user, vector<USER*>& user_information) {
	char choice;
	user_information[no_of_user]->main_menu();
	cin >> choice;
	while ((int)choice<(int)'1' || (int)choice>(int)'8')
	{
		cout << "Please enter a valid choice:";
		cin >> choice;
	}
	if (choice == '1') {
		run_program(user_information);
	}
	else if (choice == '2') {
		user_information[no_of_user]->Update_firstname_lastname();
		player_main_menu(no_of_user, user_information);
	}
	else if (choice == '3')
		start_new_quiz(no_of_user, user_information);
	else if (choice == '4')
		statistics_for_player(no_of_user, user_information);
	else if (choice == '5')
		display_all_scores(no_of_user, user_information);
	else if (choice == '6')
		display_details_for_last_2_quizzes(no_of_user, user_information);
	else if (choice == '7') {
		exit_prog();
	}
}

void admin_main_menu(int no_of_user, vector<USER*>& user_information)
{

	char choice;
	user_information[no_of_user]->main_menu();
	cin >> choice;
	while ((int)choice<(int)'1' || (int)choice>(int)'8')
	{
		cout << "Please enter a valid choice:";
		cin >> choice;
	}
	if (choice == '1') {
		run_program(user_information);
	}
	else if (choice == '2') {
		user_information[no_of_user]->Update_firstname_lastname();
		admin_main_menu(no_of_user, user_information);
	}
	else if (choice == '3') {
		for (auto i = user_information.begin(); i != user_information.end(); i++)
		{
			(*i)->print_info();
		}
		admin_main_menu(no_of_user, user_information);
	}
	else if (choice == '4') {
		ADD_USER(user_information);
		admin_main_menu(no_of_user, user_information);
	}
	else if (choice == '5')
		view_all_qs(no_of_user, user_information);
	else if (choice == '6')
		add_new_qs(no_of_user, user_information);
	else if (choice == '7') {
		loading();
		admin_main_menu(no_of_user, user_information);
	}
	else if (choice == '8') {
		exit_prog();
	}

}

void run_program(vector<USER*>& user_information)
{
	int user_index;
	check_struct ass_struct;
	ass_struct = assigning_username_password();
	user_index = logining(ass_struct, user_information);
	if (user_information[user_index]->role_check() == "admin")
	{
		admin_main_menu(user_index, user_information);
	}
	else
	{
		player_main_menu(user_index, user_information);
		index_of_player = user_index;
	}
}
int main()
{
	srand(time(0));
	vector<USER*>user_information;
	cout << "***************************************************************************" << endl;
	cout << "\t\tWelcome to the Quiz game program V2.0! " << endl;
	cout << "***************************************************************************" << endl;
	Default_admin_player(user_information);
	run_program(user_information);
	return 0;
}
