#pragma once
#include <iostream>
#include "Segment.h"
#include "List.h"
#include "Client.h"
#include "DateProcessorTool.h"
#include "InputUtils.h"

using namespace std;

class ConfigEvent {
private:
    string nameEvent;
    string dateEvent;
    int sizeSegmentsSpace;
    int acountWithDiscount;
    int discount;
    int freeSeats;
    List<Segment> segmentsList;
    List<string> discountCodesList;
    List<string> temporalCodesList;
    Client client;
    DateProcessorTool dateProcessorTool;

public:
    ConfigEvent();
    ~ConfigEvent();
    string getNameEvent();
    string getDateEvent();
    int getSizeSegmentsSpace();
    void setNameEvent(string _nameEvent);
    void setDateEvent(string _dateEvent);
    void setSegmentSpace(int _segmentSpace);
    void setCodeDiscount(int codeDiscount);
    void setDiscount(int _discount);
    void addSegment(Segment* segment);
    void removeSegment(int pos);
    void deleteEvent();
    void generateDiscountCodes();
    void printCodes();
    void deleteCode(string aCode);
    bool isSegmentExists();
    bool isDiscountNumExist();
    bool isCodeExist(string code);
    void showStatusOfEvent(RenderWindow& window);
    void deleteSegment(int index);
    Segment* getSegment(int pos);
    List<string>& getDiscountCodes();
    int getDiscount();
    void addDiscountCode( string &code);
    int getCodeDiscount();

};
