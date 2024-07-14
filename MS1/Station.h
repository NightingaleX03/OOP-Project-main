/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#ifndef SENECA_STATION_H
#define SENECA_STATION_H

#include <iostream>
#include <string>
#include <iomanip>
#include "Utilities.h"

namespace seneca{
    class Station {
        int m_id;
        std::string m_name;
        std::string m_desc;
        unsigned int m_serial;
        unsigned int m_qty;
        static size_t m_widthField;
        static int id_generator;

    public:

    Station(const std::string& str);
    const std::string& getItemName() const;
    size_t getNextSerialNumber();
    size_t getQuantity() const;
    void updateQuantity();
    void display(std::ostream& os, bool full) const;
    };
}
#endif // !SENECA_STATION_H