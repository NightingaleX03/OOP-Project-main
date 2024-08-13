/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#include "CustomerOrder.h"

namespace seneca{

    size_t CustomerOrder::m_widthField = 0;

    // default constructor
    CustomerOrder::CustomerOrder(): m_cntItem(0), m_lstItem(nullptr){}

    CustomerOrder::CustomerOrder(const std::string& str){
        Utilities util;
        size_t next_pos = 0;
        bool more = true;

        // extract the name and product
        m_name = util.extractToken(str, next_pos, more);
        m_product = util.extractToken(str,next_pos,more);

        // extract the items
        m_cntItem = 0;
        size_t pos_Start = next_pos;
        while(more){
            util.extractToken(str, pos_Start, more);
            m_cntItem++;
        }

        // allocate memory for the items
        m_lstItem = new Item*[m_cntItem];
        more = true;

        // extract the items
        for(size_t i = 0; i < m_cntItem; i++){
            m_lstItem[i] = new Item(util.extractToken(str, next_pos, more));
        }

        // update the widthField
        if(m_widthField < util.getFieldWidth()){
            m_widthField = util.getFieldWidth();
        }

    }

    CustomerOrder::CustomerOrder(const CustomerOrder& other){
        m_lstItem = nullptr;
        throw std::exception(); 
    }


    CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept{
        m_lstItem = nullptr;
        m_cntItem = 0;
        *this = std::move(other);
    }
    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept{
        // check if exist
        if(this != &other){
            
            // deallocate memory
            m_name = other.m_name;
            other.m_name.erase();
            m_product = other.m_product;
            other.m_product.erase();

            // deallocate memory
            for(size_t i = 0; i < m_cntItem; i++){
                delete m_lstItem[i];
            }
            delete[] m_lstItem;

            m_cntItem = other.m_cntItem;
            m_lstItem = other.m_lstItem;
            other.m_lstItem = nullptr;
            other.m_cntItem = 0u;
        }

        return *this;
    }

    CustomerOrder::~CustomerOrder(){
        // deallocate memory
        for(size_t i = 0; i < m_cntItem; i++){
            delete m_lstItem[i];
        }

        delete[] m_lstItem;
    }


    bool CustomerOrder::isOrderFilled() const{
        // flag
        bool filled = true;

        // check if all items are filled
        for(size_t i = 0; i < m_cntItem; i++){
            // if not filled return false
            if(!m_lstItem[i]->m_isFilled){
                filled = false;
            }
        }

        return filled;
    }

    bool CustomerOrder::isItemFilled(const std::string& itemName) const{
        // flag
        bool filled = true;
        // check if the item is filled
        for(size_t i = 0; i < m_cntItem; i++){
            // if the item is not filled and the name matches return false
            if(m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled){
                filled = false;
            }
        }

        return filled;
    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os){
        bool filled = false;
        // fill the item
        for(size_t i = 0; i < m_cntItem && !filled; i++){
            // if the item is not filled
            if(m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled){
                // check if the station has the item
                if(station.getQuantity() > 0){
                    // fill the item
                    station.updateQuantity();
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    filled = true;

                    // display the message
                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }else{
                    // display the message
                    os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                }
            }
        }
    }

    void CustomerOrder::display(std::ostream& os) const{
        // output name and product
        os << m_name << " - " << m_product << std::endl;
        // output the items
        for(size_t i = 0; i < m_cntItem; i++){
            os << "[" << std::setw(6) << std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber << "] "
           << std::setw(m_widthField) << std::setfill(' ') << std::left << m_lstItem[i]->m_itemName << " - "
           << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
        }
    }
}