#ifndef Class
#define Class

#include <vector>
#include <string>

using namespace std;

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

        int getValues(){return this->values;}
        int getID() { return this->ID; }
        Ward getStart() { return this->start; }
        Ward getEnd() { return this->end; }
        vector<Ward> getJourney() { return this->journey; }
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
        AGVEvent getImpactOfAGV() { return this->impactOfAGV; }
        Point getTempPoints() { return this->tempPoints; }

        void setValues(int values){this->values = values;}
        void setID(int ID) { this->ID = ID; }
        void setStart(Ward start) { this->start = start; }
        void setEnd(Ward end) { this->end = end; }
        void setJourney(vector<Ward>& journey) { this->journey = journey; }
        void setVelocity(double velocity) { this->velocity = velocity; }
        void setPersonality(Personality Personality) { this->personality = personality; }
        void setEmotion(Emotion emotion) { this->emotion = emotion; }
        void setEvents(vector<Event>& events) { this->events = events; }
        void setWalkingTime(double walkingTime) { this->walkingTime = walkingTime; }
        void setDistance(double distance) { this->distance = distance; }
        void setAge(double age) { this->age = age; }
        void setImpactOfAGV(AGVEvent impactOfAGV) { this->impactOfAGV = impactOfAGV; }
        void setTempPoints(Point temPoints) { this->tempPoints = tempPoints; }
};

class Patient : public Pedestrian{
private:
    enum Walkability walkability;
public:
    Walkability getWalkability(){return this->walkability;}
    void setWalkability(Walkability walkability){this->walkability = walkability;}
    Patient(){}
};

class Visitor : public Pedestrian{
private:
    enum Walkability walkability;
public:
    Walkability getWalkability(){return this->walkability;}
    void setWalkability(Walkability walkability){this->walkability = walkability;}
    Visitor(){}
};

class Personel : public Pedestrian{
    
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