#ifndef Class
#define Class

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include "../../lib/nlohmann/json.hpp"
#include <fstream>
#include <set>

using namespace std;

using json = nlohmann::json;
string filename = "../../data/input.json";

json readjsondata(const char *fileName){
    std::ifstream f(fileName);
    json data = json::parse(f);
    return data;
}

string fname = "../../data/hospital.txt";
vector <pair<string, vector<float>>> readhospital(const string& fname){
    vector <pair<string, vector<float>>> hospital;
    hospital.clear();
    ifstream input(fname);
    if (!input.is_open()){
        cout << "Mo file khong thanh cong" << endl;
        return hospital;
    }
    string line;
    int n;
    input >> n;
    getline(input, line);
    for (int i = 0; i < n; i++){
        string line;
        getline(input, line);
        istringstream iss(line);

        vector <float> value(5);
        string wardID;
        iss >> value[0] >> value[1] >> value[2] >> value[3] >> value[4] >> wardID;
        
        hospital.push_back({wardID, value});
    }

    //Đọc thông tin khoa A
    vector <float> value(8);
    for (int i = 0; i < 8; i++){
        input >> value[i];
    }
    hospital.push_back({"A", value});
    return hospital;
}

vector<string> ward_options(){
    vector <string> ward_options;
    ward_options.clear();
    vector <pair<string, vector<float>>> hospital = readhospital(fname);
    for (int i = 0; i < (int)hospital.size(); i++){
        ward_options.push_back(hospital[i].first);
    }
    return ward_options;
}

// Hàm gen ngẫu nhiên 2 giá trị 0 và 1 với xác suất 0.5 và sai số dưới 5%
int generateRandomNumber() {
    // Thiết lập random device và engine
    std::random_device rd;
    std::mt19937 gen(rd());

    // Tạo ra phân phối Bernoulli với xác suất p = 0.5
    std::bernoulli_distribution distrib(0.5);

    // Biến để đếm số lần xuất hiện của mỗi giá trị
    int count0 = 0;
    int count1 = 0;

    // Số lần thử
    int numTrials = 100000; // Số lần thử có thể điều chỉnh

    // Thực hiện thử nghiệm và đếm số lần xuất hiện của mỗi giá trị
    for (int i = 0; i < numTrials; ++i) {
        if (distrib(gen)) {
            count1++;
        } else {
            count0++;
        }
    }

    // Tính tỷ lệ thực tế của mỗi giá trị
    double ratio0 = static_cast<double>(count0) / numTrials;
    double ratio1 = static_cast<double>(count1) / numTrials;

    // Đảm bảo tỷ lệ thực tế không vượt quá 5% sai số so với 0.5
    while (std::abs(ratio0 - 0.5) > 0.05 || std::abs(ratio1 - 0.5) > 0.05) {
        // Đếm lại với số lần thử lớn hơn
        numTrials += 1000;
        count0 = 0;
        count1 = 0;

        for (int i = 0; i < numTrials; ++i) {
            if (distrib(gen)) {
                count1++;
            } else {
                count0++;
            }
        }

        // Tính lại tỷ lệ thực tế
        ratio0 = static_cast<double>(count0) / numTrials;
        ratio1 = static_cast<double>(count1) / numTrials;
    }

    // Trả về một giá trị ngẫu nhiên
    return distrib(gen);
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

class Point{
private:
    double x, y;
public:
    Point(double x, double y){
        this->x = x;
        this->y = y;
    }
    Point(){};
    double getX(){
        return this->x;
    }
    double getY(){
        return this->y;
    }
    void setX(double x){
        this->x = x;
    }
    void setY(double y){
        this->y = y;
    }
};

class Ward{
protected:
    //Ten khoa
    string WardID;
    //Toa do cong vao, cong ra
    Point entrance;
    Point exit;
    //Toa do cac buc tuong vien quanh
    vector <pair<Point,Point>> wallEdge;
    double width;
public:
    Ward(string WardID, Point entrance, Point exit, vector <pair<Point,Point>> wallEdge)
    {
        this->WardID = WardID;
        this->entrance = entrance;
        this->exit = exit;
        this->wallEdge = wallEdge;
    }
    Ward(){};

    string getID(){return this->WardID;}
    Point getEntrance(){return this->entrance;}
    Point getExit(){return this->exit;}
    double getWight(){return this->width;}
    vector<pair<Point,Point>> getWallEdge(){return this->wallEdge;}

    void setID(string ID){this->WardID = ID;}
    void setEntrance(Point entrance){this->entrance = entrance;}
    void setExit(Point exit){this->exit = exit;}
    void setWidth(double width){this->width = width;}
    void setWallEdge(vector<pair<Point,Point>>& wallEdge){this->wallEdge = wallEdge;}
};

class A : public Ward{
private:
    //2 diem vao
    vector<Point> entrance;
    //2 diem ra
    vector<Point> exit;
public:
    vector<Point> getEntrance(){return this->entrance;}
    vector<Point> getExit(){return this->exit;}

    void setEntrance(vector<Point>& entrance){this->entrance = entrance;}
    void setExit(vector<Point>& exit){this->exit = exit;}
};

class Personality{
private:
    double lambda;
    double positiveEmotionThreshold;
    double negativeEmotionThreshold;
public:
     Personality(double lambda,double positiveEmotionThreshold,double negativeEmotionThreshold)
        {
            this->lambda = lambda;
            this->positiveEmotionThreshold = positiveEmotionThreshold;
            this->negativeEmotionThreshold = negativeEmotionThreshold;
        }
        Personality(){}

        double getLambda(){return this->lambda;}
        double getPositiveEmotionThreshold(){return this->positiveEmotionThreshold;}
        double getNegativeEmotionThreshold(){return this->negativeEmotionThreshold;}

        void setLambda(double lambda){this->lambda = lambda;}
        void setPositiveEmotionThreshold(double positiveEmotionThreshold){this->positiveEmotionThreshold = positiveEmotionThreshold;}
        void setNegativeEmotionThreshold(double negativeEmotionThreshold){this->negativeEmotionThreshold = negativeEmotionThreshold;}
};

class Emotion{
private:
    double pleasure = 0.75;
    double surprise = 0.5;
    double anger = -0.2;
    double fear = -0.2;
    double hate = -0.4;
    double sad = -0.4;
public:
    Emotion(double pleasure,double surprise,double anger,double fear,double hate,double sad)
        {
            this->pleasure = pleasure;
            this->surprise = surprise;
            this->anger = anger;
            this->fear = fear;
            this->hate = hate;
            this->sad = sad;
        }
        Emotion(){}

        double getPleasure(){return this-> pleasure;}
        double getSurprise(){return this->surprise;}
        double getAnger(){return this->anger;}
        double getFear(){return this->fear;}
        double getHate(){return this->hate;}
        double getSad(){return this->sad;}

        void setPleasure(double pleasure){this-> pleasure = pleasure;}
        void settSurprise(double surprise){this->surprise = surprise;}
        void setAnger(double anger){this->anger = anger;}
        void setFear(double fear){this->fear = fear;}
        void setHate(double hate){this->hate = hate;}
        void setSad(double sad){this->sad= sad;}
};

class Event{
private:
    //intensity với giá trị bằng giá trị được sinh ra trong mã nguồn Python ở câu (i) bài 2
    vector <double> intensity;
    //thoi diem bat dau su kien
    double time;
public:
    Event(vector<double> intensity,double time)
        {
            this->intensity = intensity;
            this->time = time;
        }
        Event(){}

        vector<double> getIntensity(){return this->intensity;}
        double getTime(){return this->time;}

        void setIntensity(vector<double> intensity){this->intensity = intensity;}
        void addIntensity(double events){this->intensity.push_back(events);}
        void setTime(double time){this->time = time;}
};

class AGVEvent : public Event{

};

enum Walkability{
    noDisabilityNoOvertaking = 0,
    noDisabilityOvertaking = 1,
    crutches = 2,
    sticks = 3,
    wheelchairs = 4,
    blind = 5
};

class Pedestrian{
protected:
    int ID;
    Ward start;
    Ward end;
    vector <Ward> journey;
    double velocity;
    Personality personality;
    Emotion emotion;
    vector <Event> events;//cac su kien tac dong
    double walkingTime;
    int values; //so luong cac khoa/vien can den
    double distance;
    double age;
    AGVEvent impactOfAGV;
    Point tempPoints;
    int numOfWard;
    string type;
public:
    Pedestrian(int ID,Ward start,Ward end,vector<Ward> journey,double velocity,Personality personality,Emotion emotion,
        vector<Event> events,double walkingTime,int values,double distance,double age,AGVEvent impactOfAGV,Point tempPoints)
        {
            this->ID = ID;
            this->start = start;
            this->end = end;
            this->journey = journey;
            this->velocity = velocity;
            this->personality = personality;
            this->emotion = emotion;
            this->events = events;
            this->walkingTime = walkingTime;
            this->values = values;
            this->distance = distance;
            this->age = age;
            this-> impactOfAGV = impactOfAGV;
            this->tempPoints = tempPoints;

        }
        Pedestrian(){}

        //Hàm random đường đi: giá trị các khoa từ 1 đến 10, các khoa không trùng nhau.
        int convertToRange(double value) {
        int result = static_cast<int>(value);
        if (result < 1) result = 1;
        if (result > 10) result = 10;
        return result;
        }
        virtual Walkability getWalkability(){};
        string getType(){return this->type;}
        int getValues(){return this->values;}
        int getID() { return this->ID; }
        Ward getStart() { return this->start; }
        Ward getEnd() { return this->end; }
        vector<string> getJourney() { 
            std::random_device rd;
            std::mt19937 gen(rd());
            std::normal_distribution<> distrib(5.5, 2.5); // Mean 5.5, Standard deviation 2.5

            vector <pair<string, vector<float>>> hospital = readhospital(fname);
            vector <string> ans;
            ans.clear();
            ans.push_back(start.getID());
            std::set<int> uniqueValues;
            for (int i = 0; i < (int)hospital.size(); i++){
                if (hospital[i].first == start.getID()){
                    uniqueValues.insert(i + 1);
                    break;
                }
            }
            while (uniqueValues.size() < numOfWard) {
                double randomValue = distrib(gen);
                int value = convertToRange(randomValue);
                set <int> :: iterator it = uniqueValues.find(value);
                if (it == uniqueValues.end()){
                    pair<string, vector<float>> ward = hospital[value - 1];
                    ans.push_back(ward.first);
                    uniqueValues.insert(value);
                }
                // Ward department;
                // department.setID(ward.first);
            }
            ans.push_back(end.getID());
            return ans;
        }
        double getVelocity() { return this->velocity; }
        Personality getPersonality() { return this->personality; }
        Emotion getEmotion() { return this->emotion; }
        vector<vector<double>> getEvents(){
            vector<vector<double>> allEvents(6,vector<double>(20));
            for(int i=0;i<6;i++){
                for(int j=0;j<20;j++){
                    allEvents[i][j]=events.at(j).getIntensity().at(i);
                }
            }
            return allEvents;
        }
        double getWalkingTime() { return this->walkingTime; }
        double getDistance() { return this->distance; }
        double getAge() { return this->age; }
        Point getTempPoints() { return this->tempPoints; }
        
        vector<double> getImpactOfAGV(){
            return this->impactOfAGV.getIntensity();
        }
        void setType(string type){this->type = type;}
        void setValues(int values){this->values = values;}
        void setID(int ID) { this->ID = ID; }
        void setStart(Ward start) { this->start = start; }
        void setEnd(Ward end) { this->end = end; }
        void setJourney(vector<Ward>& journey) { this->journey = journey; }
        void setVelocity(double velocity) { this->velocity = velocity; }
        void setPersonality(Personality personality) { this->personality = personality; }
        void setEmotion(Emotion emotion) { this->emotion = emotion; }
        void setEvents(vector<Event>& events) { this->events = events; }
        void setWalkingTime(double walkingTime) { this->walkingTime = walkingTime; }
        void setDistance(double distance) { this->distance = distance; }
        void setAge(double age) { this->age = age; }
        void setImpactOfAGV(AGVEvent impactOfAGV) { this->impactOfAGV = impactOfAGV; }
        void setTempPoints(Point temPoints) { this->tempPoints = tempPoints; }
        void setNumOfWard(int numOfWard){
            this->numOfWard = numOfWard;
        }
};

class Patient : public Pedestrian{
private:
    enum Walkability walkability;
public:
    Walkability getWalkability(){
    // Thiết lập random device và engine
    std::random_device rd;
    std::mt19937 gen(rd());

    // Tạo ra phân phối với các giá trị từ 0 đến 5
    std::uniform_int_distribution<> distrib(0, 5);

    // Trả về giá trị ngẫu nhiên thuộc enum Walkability
    return static_cast<Walkability>(distrib(gen));
    }
    void setWalkability(Walkability walkability){this->walkability = walkability;}
    Patient(){}
};

class Visitor : public Pedestrian{
private:
    enum Walkability walkability;
public:
    Walkability getWalkability(){
    // Thiết lập random device và engine
    std::random_device rd;
    std::mt19937 gen(rd());

    // Tạo ra phân phối với các giá trị từ 0 đến 5
    std::uniform_int_distribution<> distrib(0, 5);

    // Trả về giá trị ngẫu nhiên thuộc enum Walkability
    return static_cast<Walkability>(distrib(gen));
    }
    void setWalkability(Walkability walkability){this->walkability = walkability;}
    Visitor(){}
};

class Personel : public Pedestrian{
private:
    enum Walkability walkability;
public:
    Walkability getWalkability(){
    // Thiết lập random device và engine
    std::random_device rd;
    std::mt19937 gen(rd());

    // Tạo ra phân phối với các giá trị từ 0 đến 1
    std::uniform_int_distribution<> distrib(0, 1);

    // Trả về giá trị ngẫu nhiên thuộc enum Walkability
    return static_cast<Walkability>(distrib(gen));
    }

    void setWalkability(Walkability walkability){this->walkability = walkability;}
    Personel(){}

    
};

class object{
    private:
        vector<Patient> patient;
        vector<Visitor> visitor;
        vector<Personel> personel;
    public:
        vector<Patient> getPatitent(){return this->patient;}
        vector<Visitor>  getVisitor(){return this->visitor;}
        vector<Personel> getPersonel(){return this->personel;}

        void setPatient(vector<Patient> patient){this->patient = patient;}
        void setVisitor(vector<Visitor> visitor){this->visitor = visitor;}
        void setPersonel(vector<Personel> personel){this->personel = personel;}
        
};
#endif