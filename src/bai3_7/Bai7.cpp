#include "Bai7.h"
#include "Class.hpp"
#include "../../lib/nlohmann/json.hpp"
#include <set>
#include <random>

using namespace std;
using json = nlohmann::json;

json readInputData(const char *fileName)
{
    std::ifstream f(fileName);
    json data = json::parse(f);

    return data;
}

int randomInt(int from, int to)
{
    std::random_device rd;  // obtain a random number from hardware
    std::mt19937 gen(rd()); // seed the generator
    std::uniform_int_distribution<> dis(from, to);
    int value = dis(gen);
    return value;
}

vector<vector<double>> get_Impact(int numOfSamples, int numOfValues, double minValue, double maxValue)
{
    vector<vector<double>> getIm;
    getIm.resize(numOfSamples);
    set<double> unique_values;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(minValue, maxValue);

    while (unique_values.size() < numOfValues)
    {
        unique_values.insert(dis(gen));
    }

    vector<double> samples(unique_values.begin(), unique_values.end());

    for (int i = 0; i < getIm.size(); i++)
    {
        int index = randomInt(0, numOfValues - 1);
        int impact = samples[index];
        for (int j = 0; j < 6; j++)
        {
            getIm[i].push_back(impact);
        }
    }

    return getIm;
}

vector<vector<double>> getImpact_Negative(int numOfSamples, int numOfValues, double minValue, double maxValue)
{
    vector<vector<double>> getIm;
    getIm.resize(numOfSamples);
    set<double> unique_values;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(minValue, maxValue);

    while (unique_values.size() < numOfValues)
    {
        unique_values.insert(-dis(gen)); // Generate negative values directly
    }

    vector<double> samples(unique_values.begin(), unique_values.end());

    for (int i = 0; i < getIm.size(); i++)
    {
        int index = randomInt(0, numOfValues - 1);
        double impact = samples[index];
        for (int j = 0; j < 6; j++)
        {
            getIm[i].push_back(impact);
        }
    }
    return getIm;
}

void createImpactForPedestrians(vector<Pedestrian> &p)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Mo file khong thanh cong" << endl;
        return;
    }

    json data;
    file >> data;
    file.close();
    int nChildren = 0, nPersonnelOfALKW = 0, nPersonnelOfBGFMEN = 0, nElder = 0, nBlinder = 0, nOther = 0;
    for (int i = 0; i < p.size(); i++)
    {
        if ((double)p[i].getAge() < (double)12)
        {
            nChildren++;
        }
        else if ((double)p[i].getAge() > (double)60)
        {
            nElder++;
        }
        else
        {
            if (p[i].getType() == "Personel")
            {
                if (p[i].getStart().getID() == "A" || p[i].getStart().getID() == "L" || p[i].getStart().getID() == "K" || p[i].getStart().getID() == "W")
                    nPersonnelOfALKW++;
                else
                    nPersonnelOfBGFMEN++;
            }
            else if (p[i].getType() == "Patient")
            {
                if (p[i].getWalkability() == 5)
                    nBlinder++;
                else
                    nOther++;
            }
            else
            {
                if (p[i].getWalkability() == 5)
                    nBlinder++;
                else
                    nOther++;
            }
        }
    }
    // cout << "hello";
    // return;
    // cout << "nChildren = " << nChildren << '\n';
    // cout << "nPersonnelOfALKW = " << nPersonnelOfALKW << '\n';
    // cout << "nPersonnelOfBGFMEN = " << nPersonnelOfBGFMEN << '\n';
    // cout << "nElder = " << nElder << '\n';
    // cout << "nBlinder = " << nBlinder << '\n';
    // cout << "nOther = " << nOther << '\n';
    // return;
    vector<vector<double>> impactToChildren;
    vector<vector<double>> impactToALKW;
    vector<vector<double>> impactToBFGMEN;
    vector<vector<double>> impactToElder;
    vector<vector<double>> impactToBlinder;
    vector<vector<double>> impactToOther;

    if (nChildren != 0)
        impactToChildren = get_Impact(nChildren, (int)data["impactOfAGV"]["distribution"]["children"]["numberOfValues"], (double)data["impactOfAGV"]["distribution"]["children"]["minValue"], (double)data["impactOfAGV"]["distribution"]["children"]["maxValue"]);
    if (nPersonnelOfALKW != 0)
        impactToALKW = get_Impact(nPersonnelOfALKW, (int)data["impactOfAGV"]["distribution"]["ALKW"]["numberOfValues"], (double)data["impactOfAGV"]["distribution"]["ALKW"]["minValue"], (double)data["impactOfAGV"]["distribution"]["ALKW"]["maxValue"]);
    if (nPersonnelOfBGFMEN != 0)
        impactToBFGMEN = getImpact_Negative(nPersonnelOfBGFMEN, (int)data["impactOfAGV"]["distribution"]["BFGMEN"]["numberOfValues"], (double)data["impactOfAGV"]["distribution"]["BFGMEN"]["minValue"], (double)data["impactOfAGV"]["distribution"]["BFGMEN"]["maxValue"]);
    if (nBlinder != 0)
        impactToBlinder = getImpact_Negative(nBlinder, (int)data["impactOfAGV"]["distribution"]["Blinder"]["numberOfValues"], (double)data["impactOfAGV"]["distribution"]["Blinder"]["minValue"], (double)data["impactOfAGV"]["distribution"]["Blinder"]["maxValue"]);
    if (nOther != 0)
        impactToOther = get_Impact(nOther, (int)data["impactOfAGV"]["distribution"]["Other"]["numberOfValues"], (double)data["impactOfAGV"]["distribution"]["Other"]["minValue"], (double)data["impactOfAGV"]["distribution"]["Other"]["maxValue"]);
    if (nElder != 0)
        impactToElder = getImpact_Negative(nElder, (int)data["impactOfAGV"]["distribution"]["Elder"]["numberOfValues"], (double)data["impactOfAGV"]["distribution"]["Elder"]["minValue"], (double)data["impactOfAGV"]["distribution"]["Elder"]["maxValue"]);

    for (int i = 0; i < p.size(); i++)
    {

        if ((double)p[i].getAge() < (double)12)
        {
            AGVEvent impact;
            if (impactToChildren.empty() == false)
            {
                impact.setIntensity(impactToChildren.back());
                p[i].setImpactOfAGV(impact);
                impactToChildren.pop_back();
            }
        }
        else if ((double)p[i].getAge() > (double)60)
        {
            AGVEvent impact;
            if (impactToElder.empty() == false)
            {
                impact.setIntensity(impactToElder.back());
                p[i].setImpactOfAGV(impact);
                impactToElder.pop_back();
            }
        }
        else
        {
            if (p[i].getType() == "Personel")
            {
                if (p[i].getStart().getID() == "A" || p[i].getStart().getID() == "L" || p[i].getStart().getID() == "K" || p[i].getStart().getID() == "W")
                {
                    AGVEvent impact;
                    if (impactToALKW.empty() == false)
                    {
                        impact.setIntensity(impactToALKW.back());
                        p[i].setImpactOfAGV(impact);
                        impactToALKW.pop_back();
                    }
                }
                else
                {
                    AGVEvent impact;
                    if (impactToBFGMEN.empty() == false)
                    {
                        impact.setIntensity(impactToBFGMEN.back());
                        p[i].setImpactOfAGV(impact);
                        impactToBFGMEN.pop_back();
                    }
                }
            }
            else if (p[i].getType() == "Patient")
            {
                if (p[i].getWalkability() == 5)
                {
                    AGVEvent impact;
                    if (impactToBlinder.empty() == false)
                    {
                        impact.setIntensity(impactToBlinder.back());
                        p[i].setImpactOfAGV(impact);
                        impactToBlinder.pop_back();
                    }
                }
                else
                {
                    AGVEvent impact;
                    if (impactToOther.empty() == false)
                    {
                        impact.setIntensity(impactToOther.back());
                        p[i].setImpactOfAGV(impact);
                        impactToOther.pop_back();
                    }
                }
            }
            else
            {
                if (p[i].getWalkability() == 5)
                {
                    AGVEvent impact;
                    if (impactToBlinder.empty() == false)
                    {
                        impact.setIntensity(impactToBlinder.back());
                        p[i].setImpactOfAGV(impact);
                        impactToBlinder.pop_back();
                    }
                }
                else
                {
                    AGVEvent impact;
                    if (impactToOther.empty() == false)
                    {
                        impact.setIntensity(impactToOther.back());
                        p[i].setImpactOfAGV(impact);
                        impactToOther.pop_back();
                    }
                }
            }
        }
    }
    return;
}
