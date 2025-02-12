/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#include "Station.h"

namespace seneca {

    // Static member initialization
    size_t Station::m_widthField = 0;
    size_t Station::id_generator = 0;

    // Custom constructor
    Station::Station(const std::string& str) {
        Utilities util;
        size_t next_pos = 0;
        bool more = false;

        m_id = ++id_generator;

        // Extract tokens
        m_name = util.extractToken(str, next_pos, more);
        // Convert to int
        m_serial = std::stoi(util.extractToken(str, next_pos, more));
        m_qty = std::stoi(util.extractToken(str, next_pos, more));

        // Set the width of the field
        if(m_widthField < util.getFieldWidth()){
            m_widthField = util.getFieldWidth();
        }

        m_desc = util.extractToken(str, next_pos, more);        
    }

    // get item names
    const std::string& Station::getItemName() const {
        return m_name;
    }

    // get next serial number
    size_t Station::getNextSerialNumber() {
        return m_serial++;
    }

    // get quantity
    size_t Station::getQuantity() const {
        return m_qty;
    }

    // update quantity
    void Station::updateQuantity() {
        if (m_qty > 0) {
            m_qty--;
        }
    }

    // display function
    void Station::display(std::ostream& os, bool full) const {

        // Display the item
        os << std::setw(3) << std::setfill('0') << std::right << m_id << " | " <<
        std::setw(m_widthField) << std::left << std::setfill(' ') << m_name << " | " <<
        std::setw(6) << std::setfill('0') << std::right << m_serial << " | ";

        // Display the item description and quantity
        if (full) {
            if(m_id < 5){
                os << std::setw(4) << std::setfill(' ')<< std::right << m_qty << " | " << std::left << m_desc.substr(0);
            }
            else{
                os << std::setw(4) << std::setfill(' ')<< std::right << m_qty << " | " << std::left << m_desc;
            }
        }

        os << std::endl;
    }
}