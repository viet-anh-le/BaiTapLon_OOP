#include"Bai7.h"

#include <lib/nlohmann/json.hpp>

using namespace std;
using namespace Utility;
using json = nlohmann::json;



void createImpactForPedestrians(vector <Pedestrian> p)
{
    json inputData;
    inputData = Utility::readInputData("data/input.json");
    int nChildren = 0, nPersonnelOfALKW = 0,nPersonnelOfBGFMEN = 0,nElder = 0,nBlinder = 0,nOther = 0;
    for(int i = 0;i<p.size();i++)
    {
        if(p[i].getAge() < 12)
        {
            nChildren++;
        } else if(p[i].getStart() == "A" || p[i].getStart() == "L"||p[i].getStart() == "K"||p[i].getStart() == "W")
        {
            nPersonnelOfALKW++;
        } else if(p[i].getStart() == "B" || p[i].getStart() == "F"||p[i].getStart() == "G"||p[i].getStart() == "M"||p[i].getStart() == "E"||p[i].getStart() == "N")
        {
           nPersonnelOfBGFMEN++; 
        } else if(p[i].getAge() > 60)
        {
            nElder++;
        } else if()
    }
}