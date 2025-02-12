#pragma once
#ifndef INVOICE_H
#define INVOICE_H

#include <string>

struct PurchasedSeat {
    int segmentIndex;         
    string seatCode;          
    float basePrice;          
    bool discountApplied;     
    float discountAmount;    
    float finalPrice;         
};

#endif