#ifndef read_json
#define read_json
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../../lib/nlohmann/json.hpp"
#include "Class.hpp"

using namespace std;

using json = nlohmann::json;
string name_file = "../../data/input.json";

int get_numOfAgents(){
    ifstream file(name_file);
    if(!file.is_open()){
        cout << "Mo file json khong thanh cong." << '\n';
        return -1;
    }

    json jsondata;
    file >> jsondata;
    file.close();

    int numOfAgents = jsondata["numOfAgents"]["value"];
    cout << "numOfAgents: " << numOfAgents << ".\n";

    return numOfAgents;
}

#endif