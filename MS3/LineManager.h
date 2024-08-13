/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#ifndef SENECA_LINEMANAGER_H
#define SENECA_LINEMANAGER_H

#include <vector>
#include "Workstation.h"
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

namespace seneca{

    class LineManager {
        std::vector<Workstation*> m_activeLine;
        size_t m_cntCustomerOrder;
        Workstation* m_firstStation;

    public:

        LineManager(const std::string& file, const std::vector<Workstation*>& station);
        void reorderStations();
        bool run(std::ostream& os);
        void display(std::ostream& os) const;
    };

}
#endif // !SENECA_LINEMANAGER_H