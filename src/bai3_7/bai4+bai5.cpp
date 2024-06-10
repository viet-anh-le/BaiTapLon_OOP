#include<bits/stdc++.h>
#include "../../lib/nlohmann/json.hpp"
#include"class.hpp"
using namespace std;
using json = nlohmann::json;

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
// string find1max(vector<pair<Ward,int>> &ans){
//     pair<Ward,int> max = ans[0];
//     for(int i = 1; i< ans.size(); i++){
//         if(ans[i].second > max.second) max = ans[i];
//     }
    
// }
bool cmp(pair<Ward,int> &a, pair<Ward,int> &b){
    return a.second > b.second;
}

 int main(){

   int triple = 30;
   int single = 20;
   ifstream file("../../data/input.json");
   if (!file.is_open()) {
        cout << "Khong mo duoc file" << endl;
        return 1;
   }
    json j;
    file >> j;
    file.close();
    vector<Ward> wards;
    for (auto& element : j["wardDistribution"]["distribution"].items()) {
        string key = element.key();
        // Check if the key is an uppercase letter
        if (key.size() == 1 && isupper(key[0])) {
            Ward ward;
            ward.setID(key);
            wards.push_back(ward);
        }
    }
    int numOfAgents = j["numOfAgents"]["value"];
    if(triple+single != numOfAgents){
        cout <<"ERROR";
        return 0;
    }
   vector<pair<Ward,int>> ans;
   ans = generatePair(wards,triple,single);
    for(int i = 0; i<10;i++){
    cout <<ans[i].first.getID() << ":"<< ans[i].second << " "  ;
   }

   //Bai 5
   ifstream input("../../data/pedestrian.txt");
   if (!input.is_open()) {
        cout << "Khong mo duoc file" << endl;
        return 1;
   }
 
    string line;
    vector<json> jsonObject;
    while(getline(input,line)){
        json j = json::parse(line);
        if(j.contains("journey")){
            auto &journey = j["journey"];
            if(journey.size() == 5){
                sort(ans.begin(),ans.end(),cmp);
                for(int i = 0;i < 3; i++){
                    journey[i+1] = ans[i].first.getID();
                    ans[i].second--;
                }
            }
            if(journey.size() == 3){
                sort(ans.begin(),ans.end(),cmp);
                journey[1] = ans[0].first.getID();
            }
            jsonObject.push_back(j);
        }
    }
    input.close();

    ofstream output("../../data/pedestrian.txt");
       if (!output.is_open()) {
        cout << "Khong mo duoc file" << endl;
        return 1;
   }
   for(const auto &j : jsonObject){
    output << j << endl;
   }
   //output << js;
   output.close();
   return 0;
 }
