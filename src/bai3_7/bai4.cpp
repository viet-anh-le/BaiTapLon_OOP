#include<bits/stdc++.h>
#include "../../lib/nlohmann/json.hpp"
using namespace std;
using json = nlohmann::json;
class Ward{
    private:
    string ten;
    public:
    void setName(string name){
        this->ten = name;
    }
    // pair<double,double> congvao;
    // pair<double,double> congra;
    // vector<pair<double,double> > canh;
    // public:
    // Ward(){
    //     canh.resize(4);
    // }
};
vector<pair<Ward,int>> generatePair(vector<Ward> &wards, int triple ,int single){
  vector<pair<Ward,int>> result;
  int total = triple*3 + single;
  double mean = total / wards.size();
  double stddev = mean / 3;
  random_device genarate;
  normal_distribution<>  distribution(mean,stddev);
   //Tạo các mẫu ngẫu nhiên
   vector<double> tmp;
   for (const auto& ward : wards) {
        double tmp1 = distribution(genarate);
        tmp.push_back(tmp1);
        result.push_back(make_pair(ward,tmp1));
    }
    //Chuẩn hóa các mẫu ngẫu nhiên
    double sum = 0 ;
    for (int i = 0; i < tmp.size() ;i++) {
       sum+=tmp[i];
    }
    for (int i = 0; i < tmp.size() ;i++) {
       tmp[i] *= total / sum;
    }
    //Làm tròn
    vector<int> intValue(tmp.size());
    int sumIntValue = 0;
    for (int i = 0; i < tmp.size() ;i++) {
        intValue[i] = static_cast<int>(round(tmp[i]));
        sumIntValue += intValue[i];
    }
    while(sumIntValue != total){
         for (int i = 0; i < tmp.size() && sumIntValue != total ;i++){
            if(sumIntValue < total) {
                intValue[i]++;
                sumIntValue++;
            } else if(sumIntValue > total) {
                intValue[i]--;
                sumIntValue--;
            }
         }
    }
    for (int i = 0; i < tmp.size() ;i++) {
        result[i].second = intValue[i];
    }
    return result;
 }
 int main(){
   vector<Ward> wards(5);
   cout <<"nhap ward:";
   for(int i = 0; i<5;i++){
    string name;
    cin >> name;
    wards[i].setName(name);
   }
   int triple = 30;
   int single = 20;
   ifstream file("input.json");
   if (!file.is_open()) {
        cout << "ERROR" << endl;
        return 1;
   }
    json j;
    file >> j;
    file.close();
    int numOfAgents = j["numOfAgents"]["value"];
    if(triple+single != numOfAgents){
        cout <<"ERROR";
        return 0;
    }
   vector<pair<Ward,int>> ans;
   ans = generatePair(wards,triple,single);
    for(int i = 0; i<5;i++){
    cout << ans[i].second << " " ;
   }
   return 0;
 }
