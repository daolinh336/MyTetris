#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include "Number.h"

using namespace std;

string LineScore;

Number::Number(butve *pIO) : Line(0), Score(0), Level(1), Ve(pIO)
{

}

string getnum(int a)
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

void Number::UpdateLevel(int score)
{
    Level = (score/336) + 1;
}
void Number::PlusScore(int num)
{
    Score += num;
}
void Number::PlusLine()
{
    Line++;
}
void Number::ResetLine()
{
    Line = 0;
}
void Number::DrawLineScore(int line)
{
    LTexture ad(Ve);
    LineScore = getnum(line);

    ad.loadFromRenderedText(LineScore);

    if(line < 10)ad.render(193, 330);
    else if(line < 100)ad.render(180, 330);
    else if(line < 1000)ad.render(170, 330);
    else if(line < 10000)ad.render(160, 330);
    else ad.render(150, 330);

    ad.free();
}


void Number::DrawScore(int score)
{
    LTexture ad(Ve);
    LineScore = getnum(score);

    ad.loadFromRenderedText(LineScore);

    if(score < 10)ad.render(193, 495);
    else if(score < 100)ad.render(180, 495);
    else if(score < 1000)ad.render(170, 495);
    else if(score < 10000)ad.render(160, 495);
    else ad.render(150, 330);

    ad.free();
}

void Number::DrawLevel(int level)
{
    LTexture ad(Ve);
    LineScore = getnum(level);
    ad.loadFromRenderedText(LineScore);

    if(level < 10)ad.render(193, 170);
    else if(level < 100)ad.render(180, 170);
    else if(level < 1000)ad.render(170, 170);
    else if(level < 10000)ad.render(160, 170);
    else ad.render(150, 330);

    ad.free();
}

void Number :: DrawNumber()
{
    DrawLevel(Level);
    DrawScore(Score);
    DrawLineScore(Line);
}
string Number :: getScore()
{
    return getnum(Score);
}
string Number :: getLine()
{
    return getnum(Line);
}
string Number :: getLevel()
{
    return getnum(Level);
}

