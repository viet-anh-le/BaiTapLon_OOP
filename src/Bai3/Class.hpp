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
};

class Personality{
protected:
    double lambda;
    double positiveEmotionThreshold;
    double negativeEmotionThreshold;
};

class Emotion{
protected:
    double pleasure = 0.75;
    double surprise = 0.5;
    double anger = -0.2;
    double fear = -0.2;
    double hate = -0.4;
    double sad = -0.4;
};

class Event{
protected:
    //intensity với giá trị bằng giá trị được sinh ra trong mã nguồn Python ở câu (i) bài 2
    vector <double> intensity;
    //thoi diem bat dau su kien
    double time;
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
    vector <Event> events;
    double walkingTime;
    double distance;
    double age;
    AGVEvent impactOfAGV;
    Point tempPoints;
};

class Patient : public Pedestrian{
protected:
    enum Walkability walkability;
};

class Visitor : public Pedestrian{
protected:
    enum Walkability walkability;
};

class Personal : public Pedestrian{
    
};
#endif