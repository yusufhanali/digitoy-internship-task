#include <iostream>
#include <time.h>
#include <list>
#include <vector>
#include <array>
#include <utility>
using namespace std;

class Table
{
    public:
        Table(int num, int betAmt, char spec) {tableNum=num;bet=betAmt;specs=spec;}
        int getName(){return tableNum;}
        int getBet(){return bet;}
        char getSpecs(){return specs;}
        
    private:
        int tableNum;
        int bet;
        char specs;
};

Table randomTableGen()
{
    static int num=0;
    int bet = (rand()%4801)+200;
    int spec = rand()%8;
    num++;
    //cout<<num<<"-"<<bet<<"-"<<spec<<endl;
    return Table(num, bet, spec);
}

void emplace(vector<pair<int,array<list<Table>,8> > >& tableList, Table newTable)
{
    if(tableList.size()<1)
    {
        array<list<Table>,8> arr;
        arr.fill(list<Table>());
        tableList.push_back(make_pair(newTable.getBet(), arr));
        tableList.at(0).second.at(newTable.getSpecs()).push_front(newTable);
        return;
    }
    
    int min=0, max=tableList.size()-1, bet=newTable.getBet();
    bool found=false;
    
    if(tableList.at(min).first>bet)
    {
        array<list<Table>,8> arr;
        arr.fill(list<Table>());
        tableList.insert(tableList.begin(),make_pair(newTable.getBet(), arr));
        tableList.at(0).second.at(newTable.getSpecs()).push_front(newTable);
        return;
    } else if(tableList.at(max).first<bet)
    {
        array<list<Table>,8> arr;
        arr.fill(list<Table>());
        tableList.push_back(make_pair(newTable.getBet(), arr));
        tableList.at(max+1).second.at(newTable.getSpecs()).push_front(newTable);
        return;
    } else if(tableList.at(min).first==bet)
    {
        tableList.at(min).second.at(newTable.getSpecs()).push_front(newTable);
        return;
    } else if(tableList.at(max).first==bet)
    {
        tableList.at(max).second.at(newTable.getSpecs()).push_front(newTable);
        return;
    }
    
    while((min+1)<max)
    {  
        int mean=tableList.at((min+max)/2).first;
        
        if(mean==bet)
        {
            found=true;
            break;
        }
        
        if(mean<bet)
        {
            min=(min+max)/2;
        }else
        {
            max=(min+max)/2;
        }
    }
    
    if(found)
    {
        tableList.at((min+max)/2).second.at(newTable.getSpecs()).push_front(newTable);
        return;
    }else
    {
        array<list<Table>,8> arr;
        arr.fill(list<Table>());
        tableList.insert(tableList.begin()+max,make_pair(newTable.getBet(), arr));
        tableList.at(max).second.at(newTable.getSpecs()).push_front(newTable);
        return;
    }
    
}

void printTables(list<Table> tables)
{
    if(!tables.empty())
    {
        cout<<"İşte uygun masalar:"<<endl;
        for(auto i:tables)
        {
            cout<<"Masa no:"<<i.getName()<<endl;
        }
    }
    else
    {
        cout<<"Maalesef bu kriterlerde aktif masa bulunmamaktadır."<<endl;
        return;
    }
}

void findTables(vector<pair<int,array<list<Table>,8> > >& tableList, int bet, char spec)
{
    if(tableList.size()<1)
    {
        cout<<"Maalesef aktif masa bulunmamaktadır."<<endl;
        return;
    }
    
    int min=0, max=tableList.size()-1;
    bool found=false;
    
    if(tableList.at(min).first==bet)
    {
        printTables(tableList.at(min).second.at(spec));
        return;
    } else if(tableList.at(max).first==bet)
    {
        printTables(tableList.at(max).second.at(spec));
        return;
    }
    
    while((min+1)<max)
    {  
        int mean=tableList.at((min+max)/2).first;
        
        if(mean==bet)
        {
            found=true;
            break;
        }
        
        if(mean<bet)
        {
            min=(min+max)/2;
        }else
        {
            max=(min+max)/2;
        }
    }
    
    if(found)
    {
        printTables(tableList.at((min+max)/2).second.at(spec));
        return;
    }else
    {
        cout<<"Maalesef bu kriterlerde aktif masa bulunmamaktadır."<<endl;
        return;
    }
}

int main()
{
    srand(time(NULL));
    
    int amtBet;
    char hiz, tek, rov;
    
    vector<pair<int,array<list<Table>,8> > > tableList;
    
    for(int i=0; i<1000000; i++)
    {
        emplace(tableList, randomTableGen());
    }
    
    cout << "Hoş Geldiniz! Ne kadar bahis koymak istersiniz? Lütfen 200-5000 arası bir miktar girip enter tuşuna basınız: ";
    cin >> amtBet;
    
    while(amtBet<200 || amtBet>5000)
    {
        cout << "Lütfen 200 ve 5000 arasında bir miktar girip enter tuşuna basınız: ";
        cin >> amtBet;
    }
    
    cout << "Masanız hızlı olsun mu? Olması için Y, olmaması için N yazıp enter tuşuna basınız: ";
    cin >> hiz;

    while(hiz!='Y' && hiz!='N')
    {
        cout << "Lütfen Y ya da N yazıp enter tuşuna basınız: ";
        cin >> hiz;
    }
    
    cout << "Masanız teke tek olsun mu? Olması için Y, olmaması için N yazıp enter tuşuna basınız: ";
    cin >> tek;

    while(tek!='Y' && tek!='N')
    {
        cout << "Lütfen Y ya da N yazıp enter tuşuna basınız: ";
        cin >> tek;
    }
    
    cout << "Masanız rövanşlı olsun mu? Olması için Y, olmaması için N yazıp enter tuşuna basınız: ";
    cin >> rov;

    while(rov!='Y' && rov!='N')
    {
        cout << "Lütfen Y ya da N yazıp enter tuşuna basınız: ";
        cin >> rov;
    }

    hiz = 4*(hiz/89);
    tek = 2*(tek/89);
    rov = 1*(rov/89);
    
    findTables(tableList, amtBet, hiz+tek+rov);

    return 0;
}




