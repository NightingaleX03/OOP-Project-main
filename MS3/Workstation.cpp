/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#include <iostream>
#include "Workstation.h"

namespace seneca{

    //initialize the deques
    std::deque<CustomerOrder> g_pending;
    std::deque<CustomerOrder> g_completed;
    std::deque<CustomerOrder> g_incomplete;

    void Workstation::fill(std::ostream& os){
        //if the order is not empty
        if(!m_orders.empty()){
            //fill the item in the order
            m_orders.front().fillItem(*this,os);
        }
    }

    bool Workstation::attemptToMoveOrder(){
        bool flag = false;

        // check if the order is not empty and if the front order is filled or the quantity is zero
        if (!m_orders.empty() && (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0)) {

            // if the next station
            if (m_pNextStation) {
                // move the order to next station's orders
                m_pNextStation->m_orders.push_back(std::move(m_orders.front()));
            }
            // if the next station is empty
            else {
                // if the order is filled
                if (m_orders.front().isOrderFilled()) {
                    // Move the order to the global completed deque
                    g_completed.push_back(std::move(m_orders.front()));
                }
                // if the order is not filled
                else {
                    // Move the order to deque
                    g_incomplete.push_back(std::move(m_orders.front()));
                }
            }

            // Remove the order from the deque
            m_orders.pop_front();
            flag = true;
        }   

        // Return the flag
        return flag;
    }

    void Workstation::setNextStation(Workstation* station){
        //set the next station
        m_pNextStation = station;
    }

    Workstation* Workstation::getNextStation() const{
        //return the next station
        return m_pNextStation;
    }

    void Workstation::display(std::ostream& os) const{
        //display the next station
        if (m_pNextStation) {
			os << getItemName() << " --> " << m_pNextStation->getItemName();
			
		}
        //display the end of line
		else {
			os << getItemName() << " --> End of Line";
		}
		os << std::endl;
    }

    Workstation& Workstation::operator+=(CustomerOrder&& newOrder){
        //add the order to the deque
        m_orders.push_back(std::move(newOrder));
        return *this;
    }

    bool Workstation::isEmpty(){
        //check if the order is empty
        return m_orders.empty();
    }
}