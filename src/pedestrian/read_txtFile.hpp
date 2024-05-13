#ifndef read_txtFile
#define read_txtFile
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Class.hpp"
#include "read_json.hpp"

using namespace std;

vector <int> get_numOfPedestrian(){
    string file_name = "../../data/outputNumOfPedestrian.txt";
    ifstream file(file_name);
    vector <int> soLuong;

    if (!file.is_open()){
        cout << "Mo file txt khong thanh cong" << '\n';
        return soLuong;
    }

    int total;
    string line;
    getline(file,line);
    stringstream ss(line);
    ss >> total;

    if (total != get_numOfAgents()){
        cout << "Du lieu khong thoa man" << '\n';
        return soLuong;
    }

    while (getline(file,line)){
        stringstream ss(line);
        int num;
        while (ss >> num){
            soLuong.push_back(num);
        }
    }
    file.close();
    cout << "Goi thanh cong get_numOfPedestrian()" << '\n';
    return soLuong;
}

vector<double> get_age()
{
    vector<double> age;
    string filename = "../../data/outputAge.txt";
    ifstream file(filename);
    if(!file.is_open())
    {
        cout << "Khong mo duoc file" << '\n';
        return age;
    }
    string line;
    while(getline(file, line))
    {
        double num = stod(line);
        age.push_back(num);
    }
    file.close();
    cout << "Goi thanh cong get_age()" << '\n';
    return age;
}
#endif
