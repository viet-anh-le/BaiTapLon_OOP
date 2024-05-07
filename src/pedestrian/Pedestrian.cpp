#include "Class.hpp"
#include "read_txtFile.hpp"
#include <random>

using namespace std;
using json = nlohmann::json;

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

json readInputData(const char *fileName){
    std::ifstream f(fileName);
    json data = json::parse(f);

    return data;
}

int randomNumber(int min_value, int max_value){
    // Khởi tạo một generator ngẫu nhiên
    std::random_device rd;  // Thiết bị ngẫu nhiên
    std::mt19937 gen(rd()); // Mersenne Twister engine, seed từ random_device

    // Tạo một phân phối ngẫu nhiên từ 0 đến 42 (bao gồm cả 0 và 42)
    std::uniform_int_distribution<> dis(min_value, max_value);

    // Tạo số nguyên ngẫu nhiên và in ra
    int randomNumber = dis(gen);
    return randomNumber;
}

void generatePedestrian(){
    json inputData = readInputData("../../data/input.json");    

    int numPedestrian[] = {20, 20, 40};
    int ID = 0;
    vector<Pedestrian> pedestrians;
    vector<Event> allEvents = generateEvents();
    vector<vector<double>> allTimeDistances = generateTimeDistances();
    vector<double> allAges = generateAges();
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < numPedestrian[i]; j++){
            ID++;
            //personality
            Personality open, neurotic;
            open.setPositiveEmotionThreshold(double(inputData["personalityDistribution"]["distribution"]["open"]["positiveEmotionThreshold"]));
            open.setNegativeEmotionThreshold(double(inputData["personalityDistribution"]["distribution"]["open"]["negativeEmotionThreshold"]));
            open.setLambda(double(inputData["personalityDistribution"]["distribution"]["open"]["lambda"]));

            neurotic.setPositiveEmotionThreshold(double(inputData["personalityDistribution"]["distribution"]["neurotic"]["positiveEmotionThreshold"]));
            neurotic.setNegativeEmotionThreshold(double(inputData["personalityDistribution"]["distribution"]["neurotic"]["negativeEmotionThreshold"]));
            neurotic.setLambda(double(inputData["personalityDistribution"]["distribution"]["neurotic"]["lambda"]));

            //velocity
            double noDisabilityNoOvertaking =
                double(inputData["walkability"]["distribution"]["noDisabilityNoOvertaking"]["velocity"]);
            double noDisabilityOvertaking =
                double(inputData["walkability"]["distribution"]["noDisabilityOvertaking"]["velocity"]);
            double crutches =
                double(inputData["walkability"]["distribution"]["crutches"]["velocity"]);
            double sticks =
                double(inputData["walkability"]["distribution"]["sticks"]["velocity"]);
            double wheelchairs =
                double(inputData["walkability"]["distribution"]["wheelchairs"]["velocity"]);
            double blind =
                double(inputData["walkability"]["distribution"]["blind"]["velocity"]);
            if (i == 0){
                Personel personel;
                vector <Event> events;
                personel.setID(ID);
                personel.setAge(allAges[ID - 1]);
                personel.setPersonality(open);
                personel.setVelocity(noDisabilityOvertaking);
                for (int i = 0; i < 20; i++){
                    int x = randomNumber(0, 42);
                    Event event = allEvents[x];
                    vector<double> timeBetweenEventsDistribution = allTimeDistances[i];
                    event.setTime(allTimeDistances[i][x]);
                    events.push_back(event);
                }
                personel.setEvents(events);
                pedestrians.push_back(personel);   
            }
            else if (i == 1){
                Visitor visitor;
                vector <Event> events;
                visitor.setID(ID);
                visitor.setAge(allAges[ID - 1]);
                visitor.setPersonality(open);
                visitor.setVelocity(noDisabilityOvertaking);
                for (int i = 0; i < 20; i++){
                    int x = randomNumber(0, 42);
                    Event event = allEvents[x];
                    vector<double> timeBetweenEventsDistribution = allTimeDistances[i];
                    event.setTime(allTimeDistances[i][x]);
                    events.push_back(event);
                }
                visitor.setEvents(events);
                pedestrians.push_back(visitor); 
            }
            else if (i == 2){
                Patient patient;
                vector <Event> events;
                patient.setID(ID);
                patient.setAge(allAges[ID - 1]);
                patient.setPersonality(open);
                patient.setVelocity(noDisabilityOvertaking);
                for (int i = 0; i < 20; i++){
                    int x = randomNumber(0, 42);
                    Event event = allEvents[x];
                    vector<double> timeBetweenEventsDistribution = allTimeDistances[i];
                    event.setTime(allTimeDistances[i][x]);
                    events.push_back(event);
                }
                patient.setEvents(events);
                pedestrians.push_back(patient); 
            }
        }
    }

    //Ghi ket qua
    ofstream output("../../data/pedestrian.txt");
    if (!output.is_open()){
        cout << "Mo file khong thanh cong" << '\n';
        return;
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
        jsonObject["personality"]["name"] = pedestrian.getPersonality().getLambda() == 1 ? "Open" : "Neurotic";
        jsonObject["personality"]["positiveEmotionThreshold"] = pedestrian.getPersonality().getPositiveEmotionThreshold();
        jsonObject["personality"]["negativeEmotionThreshold"] = pedestrian.getPersonality().getNegativeEmotionThreshold();
        jsonObject["personality"]["lambda"] = pedestrian.getPersonality().getLambda();
        jsonObject["events"] = pedestrian.getEvents();
        output << jsonObject << '\n';
    }
    output.close();
    cout << "Ghi file thanh cong" << '\n';
    return;
}

int main(){
    generatePedestrian();
    return 0;
}
