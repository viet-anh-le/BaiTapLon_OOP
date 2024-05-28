#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include "Class.hpp"
#include "../../lib/nlohmann/json.hpp"
#include "Bai7.cpp"
#include <random>

using namespace std;

vector<Event> generateEvents(){
    vector<Event> events;
    ifstream file("../../data/outputEventDistribution.txt");
    string line;

    if(!file.is_open()){
        cout << "Mo file khong thanh cong" << '\n';
        return events;
    }

    while(getline(file, line)){
        Event event;
        stringstream ss(line);
        double value;
        vector<double> intensity;

        while (ss >> value){
            intensity.push_back(value);
        }
        cout << '\n';
        event.setIntensity(intensity);
        event.setTime(0);
        events.push_back(event);
    }
    file.close();
    return events;
}

vector<vector<double>> generateTimeDistances(){
    vector<vector<double>> allTimeDistances;
    ifstream file("../../data/outputTimeDistribution.txt");
    string line;

    if(!file.is_open()){
        cout << "Mo file khong thanh cong" << '\n';
        return allTimeDistances;
    }

    while(getline(file, line)){
        vector<double> time;
        stringstream ss(line);
        double value;

        while (ss >> value){
            time.push_back(value);
        }
        allTimeDistances.push_back(time);
    }
    file.close();
    return allTimeDistances;
}

vector<double> generateAges(){
    vector<double> allAges;
    ifstream file("../../data/outputAge.txt");
    string line;

    if(!file.is_open()){
        cout << "Mo file khong thanh cong" << '\n';
        return allAges;
    }

    while(getline(file, line)){
        stringstream ss(line);
        double value;
        if (ss >> value)
        allAges.push_back(value);
    }
    file.close();
    return allAges;
}

int main(){
    ifstream file(filename);
    if (!file.is_open()){
        cout << "Mo file khong thanh cong" << endl;
        return -1;
    }

    json jsondata;
    file >> jsondata;
    file.close();

    int nums_of_agents = jsondata["numOfAgents"]["value"];
    vector <Pedestrian> pedestrians;
    vector<Event> allEvents = generateEvents();
    vector<vector<double>> allTimeDistances = generateTimeDistances();
    vector<double> allAges = generateAges();

    //Khoi tao Pedestrian
    int numPedestrian[] = {20, 20, 10};
    int ID = 0;
        for (int i = 0; i < 3; i++){
        for (int j = 0; j < numPedestrian[i]; j++){
            ID++;
            //personality
            Personality open, neurotic;
            open.setPositiveEmotionThreshold(double(jsondata["personalityDistribution"]["distribution"]["open"]["positiveEmotionThreshold"]));
            open.setNegativeEmotionThreshold(double(jsondata["personalityDistribution"]["distribution"]["open"]["negativeEmotionThreshold"]));
            open.setLambda(double(jsondata["personalityDistribution"]["distribution"]["open"]["lambda"]));

            neurotic.setPositiveEmotionThreshold(double(jsondata["personalityDistribution"]["distribution"]["neurotic"]["positiveEmotionThreshold"]));
            neurotic.setNegativeEmotionThreshold(double(jsondata["personalityDistribution"]["distribution"]["neurotic"]["negativeEmotionThreshold"]));
            neurotic.setLambda(double(jsondata["personalityDistribution"]["distribution"]["neurotic"]["lambda"]));


            //velocity
            double noDisabilityNoOvertaking =
                double(jsondata["walkability"]["distribution"]["noDisabilityNoOvertaking"]["velocity"]);
            double noDisabilityOvertaking =
                double(jsondata["walkability"]["distribution"]["noDisabilityOvertaking"]["velocity"]);
            double crutches =
                double(jsondata["walkability"]["distribution"]["crutches"]["velocity"]);
            double sticks =
                double(jsondata["walkability"]["distribution"]["sticks"]["velocity"]);
            double wheelchairs =
                double(jsondata["walkability"]["distribution"]["wheelchairs"]["velocity"]);
            double blind =
                double(jsondata["walkability"]["distribution"]["blind"]["velocity"]);
            if (i == 0){
                Personel personel;
                vector <Event> events;
                personel.setID(ID);
                personel.setAge(allAges[ID - 1]);
                while ((double)personel.getAge() < (double)23 || (double)personel.getAge() > (double)61){
                    personel.setAge((double)allAges[randomNumber(0, (int)allAges.size() - 1)]);
                }
                int rd;
                if (personel.getAge() < (double)11) rd = 0;
                else{
                    rd = generateRandomNumber();
                }
                if (rd == 0) personel.setPersonality(open);
                else personel.setPersonality(neurotic);
                personel.setVelocity(noDisabilityOvertaking);
                for (int i = 0; i < 20; i++){
                    int x = randomNumber(0, 42);
                    Event event = allEvents[x];
                    vector<double> timeBetweenEventsDistribution = allTimeDistances[i];
                    event.setTime(allTimeDistances[i][x]);
                    events.push_back(event);
                }
                personel.setEvents(events);

                Walkability random = personel.getWalkability();
                personel.setWalkability(random);
                personel.setNumOfWard((int)jsondata["journeyDistribution"]["distribution"]["forPersonel"]["value"] + 1);
                
                Ward start;
                
                int index = randomNumber(0, ward_options().size() - 1);
                vector <string> ward_opt = ward_options();
                start.setID(ward_opt[randomNumber(0,9)]);
                personel.setStart(start);

                personel.setEnd(start);
                personel.setType("Personel");
                //cout <<personel.getWalkability() << '\n';
                pedestrians.push_back(personel);   
            }
            else if (i == 1){
                Visitor visitor;
                vector <Event> events;
                visitor.setID(ID);
                visitor.setAge(allAges[ID - 1]);
                
                visitor.setVelocity(noDisabilityOvertaking);
                for (int i = 0; i < 20; i++){
                    int x = randomNumber(0, 42);
                    Event event = allEvents[x];
                    vector<double> timeBetweenEventsDistribution = allTimeDistances[i];
                    event.setTime(allTimeDistances[i][x]);
                    events.push_back(event);
                }
                visitor.setEvents(events);
                int rd;
                if ((double)visitor.getAge() < (double)11) rd = 0;
                else{
                    rd = generateRandomNumber();
                }
                if (rd == 0) visitor.setPersonality(open);
                else visitor.setPersonality(neurotic);
                Walkability random = visitor.getWalkability();
                visitor.setWalkability(random);
                visitor.setNumOfWard((int)jsondata["journeyDistribution"]["distribution"]["forVisitor"]["value"] + 1);
                Ward start;
                start.setID(jsondata["journeyDistribution"]["distribution"]["forVisitor"]["start"]);
                visitor.setStart(start);

                Ward end;
                end.setID(jsondata["journeyDistribution"]["distribution"]["forVisitor"]["end"]);
                visitor.setEnd(end);
                visitor.setType("Visitor");
                //cout <<visitor.getWalkability() << '\n';
                pedestrians.push_back(visitor); 
            }
            else if (i == 2){
                Patient patient;
                vector <Event> events;
                patient.setID(ID);
                patient.setAge(allAges[ID - 1]);
                int rd;
                if ((double)patient.getAge() < (double)11) rd = 0;
                else{
                    rd = generateRandomNumber();
                }
                if (rd == 0) patient.setPersonality(open);
                else patient.setPersonality(neurotic);
                Walkability random = patient.getWalkability();
                patient.setWalkability(random);
                patient.setVelocity(noDisabilityOvertaking);
                for (int i = 0; i < 20; i++){
                    int x = randomNumber(0, 42);
                    Event event = allEvents[x];
                    vector<double> timeBetweenEventsDistribution = allTimeDistances[i];
                    event.setTime(allTimeDistances[i][x]);
                    events.push_back(event);
                }
                patient.setEvents(events);
                patient.setNumOfWard((int)jsondata["journeyDistribution"]["distribution"]["forPatient"]["value"] + 1);
                Ward start;
                start.setID(jsondata["journeyDistribution"]["distribution"]["forPatient"]["start"]);
                patient.setStart(start);

                Ward end;
                end.setID(jsondata["journeyDistribution"]["distribution"]["forPatient"]["end"]);
                patient.setEnd(end);
                patient.setType("Patient");
                //cout <<patient.getWalkability() << '\n';
                pedestrians.push_back(patient); 
            }
        }
    }
    
    //Bai 7
    createImpactForPedestrians(pedestrians);
    ofstream output("../../data/pedestrian.txt");
    if (!output.is_open()){
        cout << "Mo file khong thanh cong" << '\n';
        return -1;
    }
    for (auto& pedestrian : pedestrians){
        json jsonObject;
        jsonObject["ID"] = pedestrian.getID();
        jsonObject["velocity"] = pedestrian.getVelocity();
        jsonObject["emotion"]["pleasure"] = pedestrian.getEmotion().getPleasure();
        jsonObject["emotion"]["surprise"] = pedestrian.getEmotion().getSurprise();
        jsonObject["emotion"]["anger"] = pedestrian.getEmotion().getAnger();
        jsonObject["emotion"]["fear"] = pedestrian.getEmotion().getFear();
        jsonObject["emotion"]["hate"] = pedestrian.getEmotion().getHate();
        jsonObject["emotion"]["sad"] = pedestrian.getEmotion().getSad();
        jsonObject["age"] = pedestrian.getAge();
        jsonObject["personality"]["name"] = (pedestrian.getPersonality().getLambda() == 1) ? "Open" : "Neurotic";
        jsonObject["personality"]["positiveEmotionThreshold"] = pedestrian.getPersonality().getPositiveEmotionThreshold();
        jsonObject["personality"]["negativeEmotionThreshold"] = pedestrian.getPersonality().getNegativeEmotionThreshold();
        jsonObject["personality"]["lambda"] = pedestrian.getPersonality().getLambda();
        jsonObject["events"] = pedestrian.getEvents();
        jsonObject["journey"] = pedestrian.getJourney();
        jsonObject["impactOfAGV"] = pedestrian.getImpactOfAGV();
        output << jsonObject << '\n';
    }
    output.close();
    cout << "Ghi file thanh cong" << '\n';
    return 0;
    
    //a.Số lượng M bằng đúng giá trị của trường value trong tùy chọn numOfAgents
    // int check = 0;
    // for (int i = 0; i < 3; i++){
    //     check += numPedestrian[i];
    // }
    // if (check == nums_of_agents){
    //     cout << "Số lượng người đi bộ đã tạo đúng bằng giá trị của trường numOfAgents" << endl;
    // }
    // else{
    //     cout << "Số lượng người đi bộ đã tạo không đúng bằng giá trị của trường numOfAgents" << endl;
    //     return -1;
    // }

    //b.số nhân viên y tế (tức đối tượng của lớp Personel) phải bé hơn số người noDisability
    // int noDisabilityNoOvertaking = jsondata["walkability"]["distribution"]["noDisabilityNoOvertaking"]["value"];
    // int noDisabilityOvertaking = jsondata["walkability"]["distribution"]["noDisabilityOvertaking"]["value"];
    // int noDisability = noDisabilityNoOvertaking + noDisabilityOvertaking;
    // //thu kiem tra = instance?
    // if (numPedestrian[0] < noDisability){
    //     cout << "Số lượng nhân viên y tế nhỏ hơn số người noDisability" << endl;
    // }
    // else{
    //     cout << "Số lượng nhân viên y tế nhỏ hơn số người noDisability" << endl;
    //     return -1;
    // }
    // cout << noDisability << '\n';

    //c) Không có đối tượng nào của lớp Personel lại thuộc nhóm crutches, sticks, wheelchairs hay blind

    //d. Các đối tượng đều có số lượng các khoa Viện cần đến (không tính khoa viện đầu tiên và kết thúc) bằng đúng số lượng khoa viện trong tùy chọn journeyDistribution. Tất cả các khoa viện đều xuất hiện ít nhất một lần trong danh sách các khoa viện cần đến của người đi bộ

    //e) tỉ lệ người có tính cách open hay neurotic là xấp xỉ (sai số dưới 5%) 50%

    //f) Không có người nào dưới 11 tuổi lại có tính cách neurotic 

    //g) không có nhân viên y tế nào có tuổi dưới 23 và không có nhân viên y tế nào có tuổi trên 61

    
    return 0;
}