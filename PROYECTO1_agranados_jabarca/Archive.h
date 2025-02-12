#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <fstream>
#include <sstream>
#include "ConfigEvent.h"
#include "Segment.h"
#include <iostream>
using namespace std;
using namespace sf;


inline void saveReservedSeat(int segmentIndex, const string& seatCode) {
    ofstream file("reserved_seats.txt", ios::app);
    if (file.is_open()) {
        file << segmentIndex << " " << seatCode << "\n";
        file.close();
    }
}

inline void loadReservedSeats(ConfigEvent& configEvent) {
    ifstream file("reserved_seats.txt");
    if (!file.is_open())
        return;

    string line;
    while (getline(file, line)) {
        if(line.empty())
            continue;
        istringstream iss(line);
        int segmentIndex;
        string seatCode;
        if (iss >> segmentIndex >> seatCode) {
            if(segmentIndex < configEvent.getSizeSegmentsSpace()){
                Segment* seg = configEvent.getSegment(segmentIndex);
                if (seg != nullptr) {
                    seg->reserveSeat(seatCode);
                }
            }
            else {
                cerr << "Segment index " << segmentIndex << " está fuera de rango (evento actual tiene " 
                          << configEvent.getSizeSegmentsSpace() << " segmentos)." << endl;
            }
        }
    }
    file.close();
    cout << "Asientos reservados cargados correctamente desde 'reserved_seats.txt'." << endl;
}
#endif