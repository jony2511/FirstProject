#include<iostream>
#include<string>
#include<vector>
using namespace std;
const int x=101;
class Customer;

class Menu
{
    vector<int>code;
    vector<string>name;
    vector<float>price;
public:
    int total_item;
    Menu()
    {
        total_item=5;
    }
    void show()
    {
        cout<<"Code   Price    Name"<<endl;
        for(int i=0; i<total_item; i++)
        {
            cout<<code[i]<<"    "<<price[i]<<"       "<<name[i]<<endl;
        }
        cout<<endl;
    }
    friend class Customer;
    friend class Item;
};
class Item
{
    int c;
    string s;
    float p;

public:
    Menu menuObj;
    Item() {}
    void intial_item()
    {
        menuObj.code.push_back(101),menuObj.price.push_back(80.0),menuObj.name.push_back("Burger");
        menuObj.code.push_back(102),menuObj.price.push_back(10.0),menuObj.name.push_back("Bread");
        menuObj.code.push_back(103),menuObj.price.push_back(15.0),menuObj.name.push_back("Rice");
        menuObj.code.push_back(104),menuObj.price.push_back(20.0),menuObj.name.push_back("Egg");
        menuObj.code.push_back(105),menuObj.price.push_back(90.0),menuObj.name.push_back("Biriyani");
    }
    vector<int> send_code()
    {
        return menuObj.code;
    }
    vector<float> send_price()
    {
        return menuObj.price;
    }
    vector<string> send_name()
    {
        return menuObj.name;
    }

    void display_item()
    {
        cout<<"Here is total item of our Restaurent:"<<endl;
        menuObj.show();
    }
};
class Customer
{
    Menu menuObj;
    int order_count;
    float cost;
    int feedback;
public:
    int cd,cnt;
    Customer()
    {
        cost=0.0;
        feedback=0;
        order_count=0;
    }
    int tot_order()
    {
        order_count+=cnt;
        return order_count;
    }
    float order(vector<int> v1, vector<float> v2, vector<string> v3)
    {

        cout<<"You can buy a product more than once"<<endl;
        cout<<"How many products do you want: ";
        cin>>cnt;
        tot_order();
        for(int i=0; i<cnt; i++)
        {
            cout<<"Please enter item code to make a order: ";
            cin>>cd;

            int index=cd-101;
            if((cd>=101)&&((index)<menuObj.total_item))
            {
                cout<<"Order done!!"<<endl;
                cost=cost+v2[index];
            }
            else
            {
                cout<<"Please enter correct code"<<endl;
                i=i-1;
            }
        }
        cout<<"your total cost is= "<<cost<<endl;
        return cost;
    }

    int Customer_feedback()
    {
        cout<<"Please give a feedback from 0 to 5: ";
        cin>>feedback;
        cout<<"Thank You!"<<endl<<endl;
        return feedback;
    }
    friend void waiter_earning(Customer& ob,float total,float cfd,int odr);   //friend function
    friend void managing(Customer& ob1,float total,float cfd,int odr);        //friend function
};
class Waiter
{
public:
    Waiter() {}
    friend void waiter_earning(Customer& ob,float total,float cfd,int odr);
};
void waiter_earning(Customer& ob,float total,float cfd,int odr)
{
    float earnings=50.0;
    earnings=50+(total*5)/100;
    if(cfd>=3.00)
        earnings+=10.00;
    cout<<"Total order taken today: "<<odr/2<<endl;
    cout<<"My earnings today= "<<earnings<<endl<<endl;
}

class Manager
{
    Item itemObj;
public:
    friend void managing(Customer& ob1,float total,float cfd,int odr);
    Manager() {}
};
void managing(Customer& ob1,float total,float cfd,int odr)
{
    float profit=(total*40)/100;
    cout<<"Today's total order: "<<odr/2<<endl;
    cout<<"Total sells: "<<total<<" Taka"<<endl;
    cout<<"Today's profit: "<<profit<<endl;
    cout<<"Customer Rating: "<<cfd<<endl;
    float w_earn=50+(total*5)/100;
    if(cfd>=3.00)
        w_earn+=10.00;
    cout<<"Waiter's salary: "<<w_earn<<endl<<endl;
}

int main()
{
    int option,fd,tot_order_cnt=0,od,tot_fd=0,call=0;
    float cst,tot_cst=0.0,av_fd=0.0;
    cout<<"\a*************WELCOME TO OUR RESTAURANT!**********"<<endl<<endl;
    do
    {
        string password;
        cout<<"Please select an appropriate option for you:"<<endl;
        cout<<"1.Manager"<<endl;
        cout<<"2.Waiter"<<endl;
        cout<<"3.Customer"<<endl;
        cout<<"Enter 0 to quit"<<endl;
        cout<<"Enter your option: ";
        cin>>option;
        cout<<endl;
        if(option==1)
        {
checking:
            cout<<"Please enter password: ";
            cin>>password;
            if(password=="manager")
            {
                cout<<"Welcome dear manager"<<endl;
                Item obj3;
                obj3.intial_item();
                obj3.display_item();
                cout<<"Here is the today's all details\n"<<endl;
                Customer o2;
                managing(o2,tot_cst,av_fd,tot_order_cnt);
            }
            else
            {
                cout<<"Password doesn't match,please enter correct password!"<<endl;
                goto checking;
            }
        }
        else if(option==2)
        {
check_pass:
            cout<<"Enter your password: ";
            cin>>password;
            if(password=="waiter"){
                cout<<"Welcome dear waiter,you can see this details\n"<<endl;
                Customer o1;
                waiter_earning(o1,tot_cst,av_fd,tot_order_cnt);}
            else
            {                cout<<"Password doesn't match,please enter correct password!"<<endl;
                goto check_pass;
            }
        }
        else if(option==3)
        {
            call++;
            cout<<"Welcome dear customer,you can buy our products!"<<endl;
            Item obj;
            vector<int>v1;
            vector<float>v2;
            vector<string>v3;
            obj.intial_item();
            obj.display_item();
            v1 = obj.send_code();
            v2 = obj.send_price();
            v3 = obj.send_name();
            Customer obj1;
            cst=obj1.order(v1, v2, v3);
            od =obj1.tot_order();
            fd=obj1.Customer_feedback();
            tot_cst=tot_cst+cst;
            tot_fd=tot_fd+fd;
            av_fd=(float)(tot_fd)/call;
            tot_order_cnt=tot_order_cnt+od;
        }
        else if(option==0)
            cout<<"Thank You!\nSee you again"<<endl;
        else
            cout<<"Incorrect option,Please try again\n"<<endl;
    }
    while(option!=0);
    return 0;
}
