#include <iostream>
#include <fstream>
#include <map>

using namespace std;

struct CInfo
{
    int days;
    long long money = 0;
};

struct PInfo
{
    string location;
    long long money;
};

map<string, CInfo> cities;
map<string, PInfo> persons;

string richcity;
bool nobodyWins = false;
int exday = 0;

//void parseBillionersAndPopulateCities(ifstream &fin)
void parseBillionersAndPopulateCities(istream &fin)
{
    int n;
    fin >> n;

    for (int i = 0; i < n; i++)
    {
        string name;
        string city;
        long long cash = 0;
        fin >> name >> city >> cash;


        PInfo &pers = persons[name];
        pers.money = cash;
        pers.location = city;

        cities[city].money += pers.money;

        if (richcity.empty())
        {
            richcity = city;
        }
    }

    CInfo *rich = &cities[richcity];
    for(map<string,CInfo>::iterator it = cities.begin(); it != cities.end(); ++it)
    {

        if(it->first == richcity)
        {
            continue;
        }

        if (it->second.money > rich->money)
        {
            rich = &it->second;
            richcity = it->first;
            nobodyWins = false;
        }
        else if(it->second.money == rich->money)
        {
            nobodyWins = true;
        }
    }
}

//void processMoves(ifstream &fin)
void processMoves(istream &fin)
{
    int m; // сколько дней всего
    int k; // сколько переездов
    fin >> m >> k;

    for (int i = 0; i < k; i++)
    {

        string name;
        int day;
        string city;
        fin >> day >> name >> city;

        if (!nobodyWins)
        {
          cities[richcity].days+=(day - exday);
        }

        PInfo &pers = persons[name];
        cities[pers.location].money -= pers.money;
        pers.location = city;
        cities[pers.location].money += pers.money;

        nobodyWins = false;
        CInfo *rich = &cities[richcity];
        for(map<string,CInfo>::iterator it = cities.begin(); it != cities.end(); ++it)
        {

            if(it->first == richcity)
            {
                continue;
            }

            if (it->second.money > rich->money)
            {
                rich = &it->second;
                richcity = it->first;
                nobodyWins = false;
            }
            else if(it->second.money == rich->money)
            {
                nobodyWins = true;
            }
        }

        exday = day;
    }

    if (!nobodyWins)
    {
        cities[richcity].days+=(m - exday);
    }
}

void printOutput()
{
    for(map<string,CInfo>::iterator it = cities.begin(); it != cities.end(); ++it)
    {
        if (it->second.days == 0)
        {
            continue;
        }
        cout << it->first << " " << it->second.days << endl;
    }
}


int main()
{
//    ifstream fin("input.txt");


//    parseBillionersAndPopulateCities(fin);
    parseBillionersAndPopulateCities(cin);

//    processMoves(fin);
    processMoves(cin);

    printOutput();

//    fin.close();
    return 0;
}
