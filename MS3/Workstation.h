/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H

#include <deque>
#include "CustomerOrder.h"
#include "Station.h"

namespace seneca{

    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;

    class Workstation : public Station {
        std::deque<CustomerOrder> m_orders;
        Workstation* m_pNextStation;

    public:

        Workstation(const std::string& str) : Station(str), m_pNextStation(nullptr) {};
        Workstation(const Workstation&) = delete;
        Workstation& operator=(const Workstation&) = delete;
        Workstation(Workstation&&) = delete;
        Workstation& operator=(Workstation&&) = delete;

        void fill(std::ostream& os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station = nullptr);
        bool isEmpty();
        Workstation* getNextStation() const;
        void display(std::ostream& os) const;
        Workstation& operator+=(CustomerOrder&& newOrder);
    };
}
#endif // !SENECA_WORKSTATION_H