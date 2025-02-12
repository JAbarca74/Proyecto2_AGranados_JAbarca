#include "ConfigEvent.h"

ConfigEvent::ConfigEvent() {
    nameEvent = "";
    dateEvent = "";
    sizeSegmentsSpace = 0;
    acountWithDiscount = 0;
    discount = 0;
    freeSeats = 0;
}

ConfigEvent::~ConfigEvent() {}

string ConfigEvent::getNameEvent() {
    return nameEvent;
}

string ConfigEvent::getDateEvent() {
    return dateEvent;
}

int ConfigEvent::getSizeSegmentsSpace() {
    return sizeSegmentsSpace;
}

void ConfigEvent::setNameEvent(string _nameEvent) {
    nameEvent = _nameEvent;
}

void ConfigEvent::setDateEvent(string _dateEvent) {
    dateEvent = _dateEvent;
}

void ConfigEvent::setSegmentSpace(int _segmentSpace) {
    sizeSegmentsSpace = _segmentSpace;
}

void ConfigEvent::setCodeDiscount(int codeDiscount) {
    acountWithDiscount = codeDiscount;
}

void ConfigEvent::setDiscount(int _discount) {
    discount = _discount;
}

void ConfigEvent::addSegment(Segment* segment) {
    segmentsList.insertAtTheEnd(*segment);
    sizeSegmentsSpace++;
}

void ConfigEvent::removeSegment(int pos) {
    segmentsList.eliminateNode(pos);
    sizeSegmentsSpace--;
}

void ConfigEvent::deleteEvent() {
    segmentsList = List<Segment>();
    discountCodesList = List<string>();
    temporalCodesList = List<string>();
    nameEvent = "";
    dateEvent = "";
    sizeSegmentsSpace = 0;
    acountWithDiscount = 0;
    discount = 0;
    freeSeats = 0;
}

void ConfigEvent::generateDiscountCodes() {
    char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < acountWithDiscount; i++) {
        string code = "";
        for (int j = 0; j < 6; j++) {
            int randomIndex = rand() % 36;
            code += alphanum[randomIndex];
        }
        discountCodesList.insertAtTheEnd(code);
    }
}

void ConfigEvent::printCodes() {
    List<string>::Node* codesOfList = discountCodesList.getHead();
    while (codesOfList != nullptr) {
        cout << codesOfList->data << " ";
        codesOfList = codesOfList->next;
    }
    cout << endl;
}

void ConfigEvent::deleteCode(string aCode) {
    List<string>::Node* temp = discountCodesList.getHead();
    while (temp != nullptr) {
        if (temp->data == aCode) {
            discountCodesList.deleteNode(temp);
            return;
        }
        temp = temp->next;
    }
}

bool ConfigEvent::isSegmentExists() {
    return segmentsList.getSize() > 0;
}

bool ConfigEvent::isDiscountNumExist() {
    return acountWithDiscount > 0;
}

bool ConfigEvent::isCodeExist(string code) {
    List<string>::Node* temp = discountCodesList.getHead();
    while (temp != nullptr) {
        if (temp->data == code) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

void ConfigEvent::showStatusOfEvent(sf::RenderWindow& window) {
    for (int i = 0; i < segmentsList.getSize(); i++) {
        segmentsList.getAt(i).drawSeats(window);
    }
}

Segment* ConfigEvent::getSegment(int pos)
{
    typename List<Segment>::Node* currentNode = segmentsList.getHead();
    for (int i = 0; i < pos; ++i)
    {
        currentNode = currentNode->next;
        if (currentNode == nullptr)
        {
            cout << "Posición fuera de rango." << endl;
            return nullptr;
        }
    }
    return &currentNode->data;
}

List<string>& ConfigEvent::getDiscountCodes() {
    return discountCodesList;
}

int ConfigEvent::getDiscount()
{
    return discount;
}

void ConfigEvent::addDiscountCode( string& code) {
    
    discountCodesList.insertAtTheEnd(code);
}

int ConfigEvent::getCodeDiscount()
{
    return acountWithDiscount;
}

void ConfigEvent::deleteSegment(int index) {

    if (index < 0 || index >= segmentsList.getSize()) {
        cerr << "Índice de segmento fuera de rango." << endl;
        return;
    }
    Segment seg = segmentsList.getAt(index);

    if (seg.hasPurchasedSeats()) {
        cerr << "No se puede eliminar un segmento en el que ya se han vendido entradas." << endl;
        return;
    }
    segmentsList.deleteNodeWithData(index);
    sizeSegmentsSpace = segmentsList.getSize();
    cout << "Segmento " << (index + 1) << " eliminado correctamente." << endl;
}

