//Project for Shopping management System in C++ using OOPs
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
using namespace std;

class earn //base class
{
public:
  //constructor
  earn()
  {
    cout << "\n Object of Earn class created ";
  }
  ~earn()
  {
    cout << "\nObject of Earn class destructed  ";
  }
  //profit
  double profit;
  void show() //display profit
  {
    ifstream x("profit.txt");
    if (!x)
      cout << "PROFIT = 0 ";
    else
    {
      x >> profit;
      cout << "\nTOTAL STARTING PROFIT:  " << profit << endl;
      x.close();
    }
  }
};
//virtual base class

//class product for storing details of products
class product : public virtual earn //derived class
{

protected:
  static int count_product;
  int quan;
  char name[20];
  char id[20];
  double percost;
  double persell;
  double cost;
  double sell;

public:
  //constructor
  product()
  {
    cout << "\n Object of product class created";
  }
  ~product()
  {
    cout << "\n Object of product class destructed ";
  }

  //to calculate profit
  void call_profit()
  {
    cost = percost * quan;
    sell = persell * quan;
    profit = profit + (sell - cost) * 365;
    ofstream fout("ooo.txt");
    fout << profit;
    fout.close();
  }
  static void update_count_product(int s)
  {
    count_product += s;
  }
  void file();
  void get();
};
int product::count_product;
//top input details from the user
void product::get()
{
  int s;
  cout << "\nnumber of products produced?\n";
  cin >> s;
  for (int i = 0; i < s; i++)
  {
    cout << "\nInput product name: \n";
    cin >> name;
    fflush(stdin);
    cout << "\nInput product id: \n";
    cin >> id;
    cout << "\nInput cost price of product: \n";
    cin >> percost;
    cout << "\nInput selling price of product: \n";
    cin >> persell;
    cout << "\nTotal product quantity: \n";
    cin >> quan;
    product::update_count_product(quan);
    call_profit();
    file();
  }
}
//into file contents
void product::file()
{
  char file[20];
  strcpy(file, id);
  strcat(file, ".txt");
  ofstream f(file);
  f << "\nProduct name: " << name << "\nproduct id: " << id << "\ncost price of product: " << percost << "\nselling price of product: " << persell << "\nquantity: " << quan << "\n total cost: " << cost << "\nsell: " << sell;
  f.close();
}
//class staff to store employees details
class staff : public virtual earn
{
protected:
  double salary;
  char post[12];
  char empid[10];
  int postquan;
  void call_profit()
  {
    profit = (profit - salary * postquan) * 12;
  }
  void getstaff();
  void file();
  static int count_employee;
  static void update_count_employee(int s)
  {
    count_employee += s;
  }

public:
  //constructor
  staff()
  {
    cout << "\n Object of staff class created";
  }
  ~staff()
  {
    cout << "\n Object of staff class destructed ";
  }
};
int staff::count_employee;
//to get employee details
void staff::getstaff()
{
  cout << "\nInput salary: \n";
  cin >> salary;
  cout << "\nInput number of employees: \n";
  cin >> postquan;
  staff::update_count_employee(postquan);
  for (int i = 0; i < postquan; i++)
  {
    cout << "Input employee name\n";
    cin >> post;
    fflush(stdin);
    cout << "\nInput employee ID\n";
    cin >> empid;

    call_profit();
    file();
  }
}
//file to input the contents into the file
void staff::file()
{
  char file[20];
  strcpy(file, empid);
  strcat(file, ".txt");
  ofstream f(file);
  f << "\nNumber of working employees: " << postquan << "\nemployee salary: " << salary << "\nemployee name :" << post << "\nemployee id: " << empid;
  f.close();
}
//this class is inherited from 2 classes which are in turn inherited by other two classes
class modify : public staff, public product
{
  string update_id_2;
  string update_id_1;

public:
  //default and parametrized constructor
  modify()
  {
    cout << "\n Object of modify class created  ";
    update_id_2 = "";
    update_id_1 = "";
  }
  ~modify()
  {
    cout << "\n Object of modify class destructed ";
  }
  //modify the string
  modify(string s1, string s2)
  {
    update_id_2 = "s1";
    update_id_1 = "s2";
  }
  //friend function
  friend void display_update_id(modify m1);
  void enter_update_id(string s1, string s2)
  {
    update_id_1 = s1;
    update_id_2 = s2;
  }

  void add();
  void update_item();
  void update_emp();
  //new operator overload
  void *operator new(size_t size)
  {
    cout << " Object Created using 'new' operator overloading ";
    void *p = ::operator new(size);
    //void * p = malloc(size); will also work fine

    return p;
  }
};

void display_update_id(modify m1)
{
  cout << "\n Update Id 1 : " << m1.update_id_1;
  cout << "\n Update Id 2 : " << m1.update_id_2;
}

void modify::add()
{
  int ch;
  char name[20];
  while (1)
  {
    cout << "\n1.)Input for product\n2.)Input for employee\n3.)Exit\n";
    cout << "Enter choice\n";
    cin >> ch;
    if (ch == 1)
    {
      get();
      ofstream x("ooo.txt");
      x << profit;
      x.close();
    }
    else if (ch == 2)
    {
      getstaff();
      ofstream x("ooo.txt");
      x << profit;
      x.close();
    }
    else if (ch == 3)
      break;
    else
      cout << "Invaid Option. Please re-enter\n";
  }
}
//function to update the item
void modify::update_item()
{
  char id[20];
  char pid[20];
  char c;
  cout << "\nINPUT product ID to modify\n";
  cin >> id;
  fflush(stdin);
  char file[20];
  char file2[20];
  strcpy(file, id);
  strcat(file, ".txt");
  fstream fout(file, ios::in | ios::out);
  if (!fout)
  {
    cout << "file couldn't be opened. product ID not found. \n";
  }
  else
  {
    cout << "file found! \n";
    cout << "\nUpdate product name: \n";
    cin >> name;
    fflush(stdin);
    cout << "\nUpdate percost of product: \n";
    cin >> percost;
    cout << "\nUpdate persell of product: \n";
    cin >> persell;
    cout << "\nUpdate total product quantity: \n";
    cin >> quan;
    cost = percost * quan;
    sell = persell * quan;
    profit = profit + (sell - cost) * 365;
    fout << "\nProduct name: " << name << "\nproduct id: " << id << "\npercost ofproduct: " << percost << "\npersell of product: " << persell << "\nquantity: " << quan << "\n total cost: " << cost << "\nsell: " << sell;
    fout.close();
  }
}

//Function to update the
void modify::update_emp()
{
  char id[20];
  char c;
  cout << "\nINPUT employee ID to modify: ";
  cin >> id;
  fflush(stdin);
  char file[20];
  strcpy(file, id);
  strcat(file, ".txt");
  fstream fout(file, ios::in | ios::out);
  if (!fout)
  {
    cout << "File couldn't be opened. product ID not found. \n";
  }
  cout << "Modify employee name: \n";
  cin >> post;
  fflush(stdin);
  fout << "\nnumber of working employees: " << postquan << "\nemployee salary: " << salary << "\nemployee name :" << post << "\nemployee id: " << empid;
  fout.close();
}

void admin()
{
  while (1)
  {
    cout << "\n==============================\n";
    cout << "\n    WELCOME TO THE SHOP  \n";
    cout << "\n==============================\n\n";
    cout << "\n* * * * * * * * * * * * * * * *\n";
    cout << "\n1. Add Entries\n2. Show profit\n3. Search Product Details\n4. Search Employee Details\n5. Modify Product Details\n6. Modify Employee Details\n7. Exit\n";
    cout << "\nSelect your choice -> ";
    // Refund
    int u;
    cin >> u;
    if (u == 1)
    {
      modify *p = new modify();
      // p->show();
      p->add();
      delete (p);
    }
    else if (u == 2)
    {
      modify *d = new modify("101", "201");
      d->show();
      delete (d);
    }
    else if (u == 3)
    {
      char id[20];
      char c;
      cout << "\nINPUT ID to search\n";
      cin >> id;
      fflush(stdin);
      char file[20];
      strcpy(file, id);
      strcat(file, ".txt");
      ifstream x(file);
      if (!x)
      {
        cout << "file couldn't be opened. product ID not found. \n";
      }
      while (x)
      {
        x.get(c);
        cout << c;
      }

      x.close();
    }

    else if (u == 4)
    {
      char eid[20];
      char d;
      cout << "\nINPUT employee ID to search\n";
      cin >> eid;
      fflush(stdin);
      char file[20];
      strcpy(file, eid);
      strcat(file, ".txt");
      ifstream y(file);
      if (!y)
      {
        cout << "file couldn't be opened. employee ID not found. \n";
      }
      while (y)
      {
        y.get(d);
        cout << d;
      }

      y.close();
    }
    else if (u == 5)
    {
      modify *u = new modify();
      u->update_item();
      string s;
      string s1;
      cout << "\n Enter the update id's\t";
      cin >> s;
      cin >> s1;
      u->enter_update_id(s, s1);
      display_update_id(*u);
      delete (u);
    }
    else if (u == 6)
    {
      modify *v = new modify();
      v->update_emp();
      delete (v);
    }
    else if (u == 7)
    {
      break;
    }
    else
      //in case of incorrect choice
      cout << "Invalid option. Please select one of the available options\n";
  }
}
//main
int main()
{
  int ch;
  char username[20];
  char password[20];
  char pwd[20];
  while (1)
  {
    cout << "\n =========================\n";
    cout << "\n WELCOME TO MY SHOP  \n";
    cout << "\n =========================\n\n";
    cout << "\n * * * * * * * * * * * * ";
    cout << "\n 1. ENTER SYSTEM";
    cout << "\n 2. EXIT";
    cout << "\n * * * * * * * * * * * *\n";
    cout << "\n Enter Your choice: ";
    cin >> ch;
    switch (ch)
    {
    case 1:
      admin();
      break;
    case 2:
      exit(0);
      break;
    default:
      cout << "Enter valid choice\n";
      break;
    }
  }

  return 0;
}