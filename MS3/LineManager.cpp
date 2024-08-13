/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#include "LineManager.h"

namespace seneca{

    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations){
        
        std::vector<Workstation*> tempVec(stations);
        m_cntCustomerOrder = g_pending.size();

        std::string line, station, nextStation;
        std::vector<Workstation*>::iterator it, it2, it3;
        std::ifstream fileObj(file);

        while (std::getline(fileObj, line)) {
            size_t i = line.find('|');
            station = line.substr(0, i);
            nextStation = (i != std::string::npos) ? line.substr(i + 1) : "";

            // Find workstation by name
            it = std::find_if(tempVec.begin(), tempVec.end(),
                [&station](const Workstation* wk) {
                    return wk->getItemName() == station;
                });

            if (nextStation.empty()) {
                (*it)->setNextStation(nullptr);
                it3 = it; // Store the iterator pointing to the last station
            } else {
                it2 = std::find_if(tempVec.begin(), tempVec.end(),
                    [&nextStation](const Workstation* wk) {
                        return wk->getItemName() == nextStation;
                    });
                (*it)->setNextStation(*it2);
            }

            m_activeLine.push_back(*it);
        }

        // Find the first station directly within the constructor
        it = it3;
        std::vector<Workstation*>::iterator itFirst;
        while (true) {
            itFirst = std::find_if(m_activeLine.begin(), m_activeLine.end(),
                [&it](const Workstation* wk) {
                    return wk->getNextStation() && wk->getNextStation()->getItemName() == (*it)->getItemName();
                });

            if (itFirst == m_activeLine.end()) {
                m_firstStation = *it;
                break;
            }
            it = itFirst;
        }

    }


    void LineManager::reorderStations(){
        
        std::vector<Workstation*> order;
        order.push_back(m_firstStation);

        // move the stations to the order vector
        for(size_t i = 0; i < order.size(); i++){
            if(order[i]->getNextStation() != nullptr){
                order.push_back(order[i]->getNextStation());
            }
        }

        //move the order to the active line
        m_activeLine = order;
    }

    bool LineManager::run(std::ostream& os){
        static size_t count = 0;
        count++;
        os << "Line Manager Iteration: " << count << std::endl;

        //if the pending deque is not empty
        if(!g_pending.empty()){
            //move the order to the first station
            *(m_firstStation) += std::move(g_pending.front());
            //remove the order from the pending deque
            g_pending.pop_front();
        };

        //fill the order
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&os](Workstation*& ws) {
			ws->fill(os);
			});

        //move the order
		std::for_each(m_activeLine.begin(), m_activeLine.end(),[&os](Workstation*& ws) {
			ws->attemptToMoveOrder();
			});

        //check if the line is empty
		return std::all_of(m_activeLine.begin(), m_activeLine.end(), [](Workstation*& ws) {
			return ws->isEmpty();
			});
		
    }

    void LineManager::display(std::ostream& os) const{
        //display the order
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&os](const Workstation* ws) {
			ws->display(os);
		});
    }
}