#ifndef BAI7_H
#define BAI7_H


#include "Class.hpp"
#include "../../lib/nlohmann/json.hpp"
#include<set>
#include<random>
#include<sstream>
#include<fstream>

using namespace std;
using json = nlohmann::json;


json readInputData(const char *fileName);
int randomInt(int from, int to);
vector<vector<int> >  getImpact(int numOfSamples,int numOfValues,int minValue,int maxValue);
vector<vector<int> > getImpactNegative(int numOfSamples,int numOfValues,int minValue,int maxValue);
void createImpactForPedestrians(vector<Pedestrian> &p);

#endif