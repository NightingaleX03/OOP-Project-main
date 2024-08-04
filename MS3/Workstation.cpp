/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#include "Workstation.h"

namespace seneca{

    std::deque<CustomerOrder> pending;
    std::deque<CustomerOrder> completed;
    std::deque<CustomerOrder> incomplete;

    Workstation::Workstation(const std::string& str) {

    }

    void Workstation::fill(std::ostream& os){

    }
    bool Workstation::attemptToMoveOrder(){

    }
    void Workstation::setNextStation(Workstation* station){

    }
    Workstation* Workstation::getNextStation() const{

    }
    void Workstation::display(std::ostream& os) const{

    }
    Workstation& Workstation::operator+=(CustomerOrder&& newOrder){

    }
}