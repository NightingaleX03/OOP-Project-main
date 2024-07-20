/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#ifndef SENECA_CUSTOMER_ORDER_H
#define SENECA_CUSTOMER_ORDER_H

#include <string>
#include <stdexcept>
#include "Station.h"
#include "Utilities.h"

namespace seneca{
    class CustomerOrder {

        struct Item{
            std::string m_itemName;
            size_t m_serialNumber{0};
            bool m_isFilled{false};

            Item(const std::string& src) : m_itemName(src) {};
        };

    private:

        std::string m_name;
        std::string m_product;
        size_t m_cntItem;
        Item** m_lstItem;
        static size_t m_widthField;

    public:
        CustomerOrder();
        CustomerOrder(const std::string& str);
        
        // no copy constructor
        CustomerOrder(const CustomerOrder& other) = delete;
        CustomerOrder& operator=(const CustomerOrder& other) = delete;
        // move constructor
        CustomerOrder(CustomerOrder&& other) noexcept;
        CustomerOrder& operator=(CustomerOrder&& other) noexcept;

        ~CustomerOrder();

        bool isOrderFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os);
        void display(std::ostream& os) const;
    };
}

#endif // !SENECA_CUSTOMER_ORDER_H