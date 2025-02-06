#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Segment.h"
#include "ConfigEvent.h"
#include "List.h"

using namespace std;

class Archive
{
private:
    //List<Segment> segments;
    ConfigEvent configEvent;
    Segment segment;

public:
   // void generateReport();
    void loadFromFile();
};