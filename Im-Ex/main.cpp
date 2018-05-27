//
//  main.cpp
//  Im-Ex
//
//  Created by Rohit  on 27/05/2018.
//  Copyright © 2018 Rohit . All rights reserved.
//

#include<conio.h>
#include<iostream.h>
#include<fstream.h>
#include<string.h>
#include<stdio.h>
#include<time.h>

class item
{
    char item_code[10],item_name[20];
    float rate;
    int qty;
public:
    void in()
    {
        cout<<"enter the item code:";
        gets(item_code);
        cout<<"enter the item name:";
        gets(item_name);
        cout<<"enter the rate:";
        cin>>rate;
        cout<<"enter the quantity:";
        cin>>qty;
    }
    void out()
    {
        cout<<"the item code:";
        puts(item_code);
        cout<<"the item name:";
        puts(item_name);
        cout<<"the rate:";
        cout<<rate;
        cout<<"the quantity:";
        cout<<qty;
    }
    int get_qty()
    {
        return qty;
    }
    char* get_item_code()
    {
        return item_code;
    }
    char* get_item_name()
    {
        return item_name;
    }
    void change_item_code(char *item_code1)
    {
        strcpy(item_code,item_code1);
    }
    void change_item_name(char *item_name1)
    {
        strcpy(item_name,item_name1);
    }
    void change_rate(float rate1)
    {
        rate=rate1;
    }
    void import(int amt)
    {
        qty+=amt;
    }
    void export(int amt)
    {
        qty-=amt;
    }
    void view_qty()
    {
        cout<<"item code:"<<item_code<<endl;
        cout<<"item quantity:"<<qty<<endl;
    }
    void import_report()
    {
        cout<<"item code:"<<item_code<<endl;
        cout<<"item name:"<<item_name<<endl;
        cout<<"item quantity:"<<qty<<endl;
    }
    void export_report()
    {
        cout<<"item code:"<<item_code<<endl;
        cout<<"item name:"<<item_name<<endl;
        cout<<"item quantity:"<<qty<<endl;
    }
};
void new_entry()
{
    int f=0;
    item i1,i2;
    i1.in();
    ifstream it("item.dat",ios::binary);
    if(it)
    {
        while(!it.eof())
        {
            it.read((char*)&i2,sizeof(i2));
            if(it.eof())
                break;
            if(strcmpi(i2.get_item_code(),i1.get_item_code())==0)
            {
                cout<<"item already exist";
                f=1;
                break;
            }
        }
    }
    it.close();
    if(f==0)
    {
        ofstream it1("item.dat",ios::binary|ios::app);
        it1.write((char*)&i1,sizeof(i1));
        it1.close();
    }
}
void view_quantity()
{
    item i1;
    ifstream it("item.dat",ios::binary);
    if(!it)
    {
        cout<<"item.dat not found";
        getch();
        return;
    }
    while(!it.eof())
    {
        it.read((char*)&i1,sizeof(i1));
        if(it.eof())
            break;
        i1.view_qty();
    }
    it.close();
}
void update_item()
{
    item i1;
    char item_code[10];
    int f=0,switch1;
    ifstream it("item.dat",ios::binary);
    ofstream tmp("tmp.dat",ios::binary);
    if(!it)
    {
        cout<<"item.dat not found";
        getch();
        return;
    }
    cout<<"enter the item code:";
    gets(item_code);
    while(!it.eof())
    {
        it.read((char*)&i1,sizeof(i1));
        if(it.eof())
            break;
        if(strcmpi(i1.get_item_code(),item_code)==0)
        {
            f=1;
            i1.out();
            cout<<"which one do you want to update";
            cout<<"1.item code";
            cout<<"2.item name";
            cout<<"3.rate";
            cin>>switch1;
            switch(switch1)
            {
                case 1:
                    char item_code[10];
                    cout<<"enter the item code:";
                    gets(item_code);
                    i1.change_item_code(item_code);
                    break;
                case 2:
                    char item_name[20];
                    cout<<"enter the item name:";
                    gets(item_name);
                    i1.change_item_name(item_name);
                    break;
                case 3:
                    float rate;
                    cout<<"enter the rate:";
                    cin>>rate;
                    i1.change_rate(rate);
                    break;
                default:
                    cout<<"choose the option correctly";
                    break;
            }
        }
        tmp.write((char*)&i1,sizeof(i1));
    }
    it.close();
    tmp.close();
    remove("item.dat");
    rename("tmp.dat","item.dat");
    if(f==0)
        cout<<"the item code did not match please try agian";
}
void daily_report()
{
    char e;
    time_t now = time(0);
    struct tm *systime=localtime(&now);
    int amt,date,month,year,k;
    item i1;
    ifstream r("report.dat",ios::binary);
    if(!r)
    {
        cout<<"report not found";
        getch();
        return;
    }
    while(!r.eof())
    {
        r.read((char*)&date,2);
        r.read((char*)&month,2);
        r.read((char*)&year,2);
        if((date!=systime->tm_mday)||(month!=systime->tm_mon+1)||(year!=systime->tm_year+1900))
        {
            cout<<"no import or export today";
            break;
        }
        else
        {
            r.read((char*)&e,sizeof(e));
            r.read((char*)&i1,sizeof(i1));
            r.read((char*)&amt,sizeof(amt));
            if(r.eof())
                break;
            cout<<endl<<date<<"/"<<month<<"/"<<year<<endl;
            if(e=='e')
            {
                i1.export_report();
                cout<<"quantity exported:"<<amt;
                k++;
                getch();
            }
            else if(e=='i')
            {
                i1.import_report();
                cout<<"quantity imported:"<<amt;
                k++;
                getch();
            }
        }
    }
    if(k==0)
    {
        cout<<"no import or export today";
    }
    r.close();
}
void search_report()
{
    int amt,date1,date2,month1,month2,year1,year2,k;
    item i1;
    char e;
    cout<<"enter the date:";
    cin>>date1;
    cout<<"enter the month:";
    cin>>month1;
    cout<<"enter the year:";
    cin>>year1;
    ifstream r("report.dat",ios::binary);
    if(!r)
    {
        cout<<"report.dat not found";
        getch();
        return;
    }
    while(!r.eof())
    {
        r.read((char*)&date2,sizeof(date1));
        r.read((char*)&month2,sizeof(date1));
        r.read((char*)&year2,sizeof(date1));
        if((date2==date1)&&(month2==month1)&&(year1==year2))
        {
            r.read((char*)&e,sizeof(e));
            r.read((char*)&i1,sizeof(i1));
            r.read((char*)&amt,sizeof(amt));
            if(r.eof())
                break;
            cout<<endl<<date1<<"/"<<month1<<"/"<<year1<<endl;
            if(e=='e')
            {
                i1.export_report();
                cout<<"quantity exported"<<amt;
            }
            else if(e=='i')
            {
                i1.import_report();
                cout<<"quantity imported"<<amt;
            }
            k++;
            getch();
        }
    }
    if(k==0)
    {
        cout<<"no report found on the date"<<date1<<"/"<<month1<<"/"<<year1<<endl;;
        cout<<"please try again";
    }
    r.close();
}
void inventory()
{
    char rep='y';
    int switch1;
    while(rep=='y')
    {
        cout<<"1.new item entry"<<endl;
        cout<<"2.item quantity"<<endl;
        cout<<"3.update item"<<endl;
        cout<<"4.daily report"<<endl;
        cout<<"5.search report for a given date"<<endl;
        cin>>switch1;
        switch(switch1)
        {
            case 1:
                new_entry();
                break;
            case 2:
                view_quantity();
                break;
            case 3:
                update_item();
                break;
            case 4:
                daily_report();
                break;
            case 5:
                search_report();
                break;
            default:
                cout<<"choose a proper option";
                break;
        }
        cout<<"do you want to continue:";
        cin>>rep;
    }
}

void item_list_export()
{
    item i1;
    ifstream it("item.dat",ios::binary);
    if(!it)
    {
        cout<<"item.dat file not found";
        getch();
        return;
    }
    while(!it.eof())
    {
        it.read((char*)&i1,sizeof(i1));
        if(it.eof())
            break;
        if(i1.get_qty()>20)
        {
            cout<<"item code:"<<i1.get_item_code()<<endl;
            cout<<"item name:"<<i1.get_item_name()<<endl;
            cout<<"item quantity:"<<i1.get_qty()<<endl;
            getch();
        }
    }
    it.close();
}
void export_item()
{
    time_t now = time(0);
    struct tm *systime=localtime(&now);
    item i1;
    char item_code[10];
    int amt,d,m,y;
    ifstream it("item.dat",ios::binary);
    ofstream tmp("tmp.dat",ios::binary);
    ofstream r("report.dat",ios::binary|ios::app);
    if(!it)
    {
        cout<<"item.dat not found";
        getch();
        return;
    }
    cout<<"enter the item code:";
    gets(item_code);
    while(!it.eof())
    {
        it.read((char*)&i1,sizeof(i1));
        if(it.eof())
            break;
        if(strcmpi(i1.get_item_code(),item_code)==0)
        {
            if(i1.get_qty()<20)
            {
                cout<<"the item can not be exported";
                getch();
                return;
            }
            cout<<"enter the quantity to be exported:";
            cin>>amt;
            if(amt>i1.get_qty())
            {
                cout<<"can not export as quantity is less";
                return;
            }
            i1.export(amt);
            d=(systime->tm_mday);
            m=(systime->tm_mon)+1;
            y=(systime->tm_year)+1900;
            char a='e';
            r.write((char*)&d,sizeof(int));
            r.write((char*)&m,sizeof(int));
            r.write((char*)&y,sizeof(int));
            r.write((char*)&a,1);
            r.write((char*)&i1,sizeof(i1));
            r.write((char*)&amt,sizeof(amt));
        }
        tmp.write((char*)&i1,sizeof(i1));
    }
    r.close();
    it.close();
    tmp.close();
    remove("item.dat");
    rename("tmp.dat","item.dat");
}
void export_report()
{
    char e;
    clrscr();
    time_t now = time(0);
    struct tm *systime=localtime(&now);
    int date,month,year,k,amt;
    item i1;
    ifstream r("report.dat",ios::binary);
    if(!r)
    {
        cout<<"report not found";
        getch();
        return;
    }
    while(!r.eof())
    {
        r.read((char*)&date,sizeof(int));
        r.read((char*)&month,sizeof(int));
        r.read((char*)&year,sizeof(int));
        if((date!=systime->tm_mday)||(month!=systime->tm_mon+1)||(year!=systime->tm_year+1900))
        {
            cout<<"no import or export today";
            break;
        }
        else
        {
            r.read((char*)&e,sizeof(e));
            r.read((char*)&i1,sizeof(i1));
            r.read((char*)&amt,sizeof(amt));
            if(r.eof())
                break;
            if(e=='e')
            {
                cout<<date<<"/"<<month<<"/"<<year<<endl;
                i1.export_report();
                cout<<"quantity exported:"<<amt;
                k++;
                getch();
            }
        }
    }
    if(k==0)
    {
        cout<<"no export today";
    }
    r.close();
}
void search_export_report()
{
    int amt,date1,month1,year1,month2,year2,date2,k;
    item i1;
    char e;
    cout<<"enter the date:";
    cin>>date1;
    cout<<"enter the month:";
    cin>>month1;
    cout<<"enter the year:";
    cin>>year1;
    ifstream r("report.dat",ios::binary);
    if(!r)
    {
        cout<<"report.dat not found";
        getch();
        return;
    }
    while(!r.eof())
    {
        r.read((char*)&date2,sizeof(date1));
        r.read((char*)&month2,sizeof(date1));
        r.read((char*)&year2,sizeof(date1));
        if((date2==date1)&&(month2==month1)&&(year1==year2))
        {
            r.read((char*)&e,sizeof(e));
            r.read((char*)&i1,sizeof(i1));
            r.read((char*)&amt,sizeof(amt));
            if(r.eof())
                break;
            
            if(e=='e')
            {
                cout<<date1<<"/"<<month1<<"/"<<year1<<endl;
                i1.export_report();
                cout<<"quantity exported"<<amt;
                k++;
                getch();
            }
        }
    }
    if(k==0)
    {
        cout<<"no report found on the date"<<date1<<"/"<<month1<<"/"<<year1<<endl;;
        cout<<"please try again";
    }
    r.close();
}

void export()
{
    char rep='y';
    int switch1;
    while(rep=='y')
    {
        cout<<"1.items available for export"<<endl;
        cout<<"2.export items"<<endl;
        cout<<"3.daily export report"<<endl;
        cout<<"4.search export report"<<endl;
        cin>>switch1;
        switch(switch1)
        {
            case 1:
                item_list_export();
                break;
            case 2:
                export_item();
                break;
            case 3:
                export_report();
                break;
            case 4:
                search_export_report();
            default:
                cout<<"choose a correct option";
                break;
        }
        cout<<"do you want to continue:";
        cin>>rep;
        }
        }
        
        void item_list_import()
        {
            item i1;
            ifstream it("item.dat",ios::binary);
            if(!it)
            {
                cout<<"item.dat file not found";
                getch();
                return;
            }
            while(!it.eof())
            {
                it.read((char*)&i1,sizeof(i1));
                if(it.eof())
                    break;
                cout<<"item code:"<<i1.get_item_code()<<endl;
                cout<<"item name:"<<i1.get_item_name()<<endl;
                cout<<"item quantity:"<<i1.get_qty()<<endl;
                getch();
            }
            it.close();
        }
        void import_item()
        {
            time_t now = time(0);
            struct tm *systime=localtime(&now);
            item i1;
            char item_code[10];
            int amt,d,m,y;
            ifstream it("item.dat",ios::binary);
            ofstream tmp("tmp.dat",ios::binary);
            ofstream r("report.dat",ios::binary|ios::app);
            if(!it)
            {
                cout<<"item.dat not found";
                getch();
                return;
            }
            cout<<"enter the item code:";
            gets(item_code);
            while(!it.eof())
            {
                it.read((char*)&i1,sizeof(i1));
                if(it.eof())
                    break;
                if(strcmpi(i1.get_item_code(),item_code)==0)
                {
                    cout<<"enter the quantity to be imported:";
                    cin>>amt;
                    i1.import(amt);
                    d=(systime->tm_mday);
                    m=(systime->tm_mon)+1;
                    y=(systime->tm_year)+1900;
                    char a='i';
                    r.write((char*)&d,sizeof(int));
                    r.write((char*)&m,sizeof(int));
                    r.write((char*)&y,sizeof(int));
                    r.write((char*)&a,1);
                    r.write((char*)&i1,sizeof(i1));
                    r.write((char*)&amt,sizeof(amt));
                }
                tmp.write((char*)&i1,sizeof(i1));
            }
            r.close();
            it.close();
            tmp.close();
            remove("item.dat");
            rename("tmp.dat","item.dat");
        }
        
        void import_report()
        {
            char e;
            time_t now = time(0);
            struct tm *systime=localtime(&now);
            int date,month,year,k,amt;
            item i1;
            ifstream r("report.dat",ios::binary);
            if(!r)
            {
                cout<<"report not found";
                getch();
                return;
            }
            while(!r.eof())
            {
                r.read((char*)&date,sizeof(int));
                r.read((char*)&month,sizeof(int));
                r.read((char*)&year,sizeof(int));
                if((date!=systime->tm_mday)||(month!=systime->tm_mon+1)||(year!=systime->tm_year+1900))
                {
                    cout<<"no import or export today";
                }
                else
                {
                    r.read((char*)&e,sizeof(e));
                    r.read((char*)&i1,sizeof(i1));
                    r.read((char*)&amt,sizeof(amt));
                    if(r.eof())
                        break;
                    if(e=='i')
                    {
                        cout<<date<<"/"<<month<<"/"<<year<<endl;
                        i1.import_report();
                        cout<<"quantity imported:"<<amt<<endl;
                        k++;
                        getch();
                    }
                }
            }
            if(k==0)
            {
                cout<<"no import today";
            }
            r.close();
        }
        void search_import_report()
        {
            int amt,date1,month1,year1,month2,year2,date2,k;
            item i1;
            char e;
            cout<<"enter the date:";
            cin>>date1;
            cout<<"enter the month:";
            cin>>month1;
            cout<<"enter the year:";
            cin>>year1;
            ifstream r("report.dat",ios::binary);
            if(!r)
            {
                cout<<"report.dat not found";
                getch();
                return;
            }
            while(!r.eof())
            {
                r.read((char*)&date2,sizeof(date1));
                r.read((char*)&month2,sizeof(date1));
                r.read((char*)&year2,sizeof(date1));
                if((date2==date1)&&(month2==month1)&&(year1==year2))
                {
                    r.read((char*)&e,sizeof(e));
                    r.read((char*)&i1,sizeof(i1));
                    r.read((char*)&amt,sizeof(amt));
                    if(r.eof())
                        break;
                    cout<<date1<<"/"<<month1<<"/"<<year1<<endl;
                    if(e=='i')
                    {
                        i1.import_report();
                        cout<<"quantity imported"<<amt;
                    }
                    k++;
                    getch();
                }
            }
            if(k==0)
            {
                cout<<"no report found on the date"<<date1<<"/"<<month1<<"/"<<year1<<endl;
                cout<<"please try again";
            }
            r.close();
        }
        void import()
        {
            char rep='y';
            int switch1;
            while(rep=='y')
            {
                cout<<"1.items available for import"<<endl;
                cout<<"2.import items"<<endl;
                cout<<"3.daily import report"<<endl;
                cout<<"4.search import report"<<endl;
                cin>>switch1;
                switch(switch1)
                {
                    case 1:
                        item_list_import();
                        break;
                    case 2:
                        import_item();
                        break;
                    case 3:
                        import_report();
                        break;
                    case 4:
                        search_import_report();
                        break;
                    default:
                        cout<<"choose a correct option";
                        break;
                }
                cout<<"do you want to continue:";
                cin>>rep;
            }
        }
        
        void main()
        {
            clrscr();
            char rep='y';
            int switch1;
            while(rep=='y')
            {
                cout<<"1.inventory"<<endl;
                cout<<"2.import"<<endl;
                cout<<"3.export"<<endl;
                cin>>switch1;
                switch(switch1)
                {
                    case 1:
                        inventory();
                        break;
                    case 2:
                        import();
                        break;
                    case 3:
                        export();
                        break;
                    default:
                        cout<<"choose a proper option";
                        break;
                }
                cout<<"do you want to continue:";
                cin>>rep;
            }
            getch();
        }
