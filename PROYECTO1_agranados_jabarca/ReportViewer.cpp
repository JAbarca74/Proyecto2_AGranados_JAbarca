#include "ReportViewer.h"

void ReportViewer::displayReport(string& fileName) {
    ifstream inFile(fileName);
    if (!inFile.is_open()) {
        cerr << "Error al abrir el archivo " << fileName << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        cout << line << endl;
    }

    inFile.close();
}