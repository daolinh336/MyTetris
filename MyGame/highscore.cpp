#include<bits/stdc++.h>
using namespace std;


string a[5];
vector<string>dc;
vector<int>adu;

#include "highscore.h"
#include "Number.h"

void InHighScore()
{
    int cnt = 0;
    for(int i = 0; i < 5; i++)
    {
        string s;
        cin >> s;
        a[cnt] = s;
        cnt++;
    }
}

int getnumreal(string s)
{
    int l = s.size();
    int res = 0;

    res = int(s[0] - '0');

    for(int i = 1; i <= l - 1; i++)
    {
        res = res*10 + (s[i] - '0');
    }
    return res;
}
string getxau(int a)
{
    string res = "";
    if(a == 0)return "0";
    while(a!=0)
    {
        res = char(a%10 + '0') + res;
        a = a/10;
    }
    return res;
}
void preHighScore()
{
    for(int i = 0; i <= 4; i++)
    {
        string s = a[i];
        adu.push_back(getnumreal(s));
    }
    sort(adu.begin(),adu.end());

    dc.push_back(getxau(adu[4]));
    dc.push_back(getxau(adu[3]));
    dc.push_back(getxau(adu[2]));
    dc.push_back(getxau(adu[1]));
    dc.push_back(getxau(adu[0]));

}

