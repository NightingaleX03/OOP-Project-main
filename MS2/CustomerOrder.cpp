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

    size_t CustomerOrder::m_widthField = 1;

    // default constructor
    CustomerOrder::CustomerOrder(): m_name(""), m_product(""), m_cntItem(0), m_lstItem(nullptr){}

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
            util.extractToken(str, next_pos, more);
            m_cntItem++;
        }

        // allocate memory for the items
        m_lstItem = new Item*[m_cntItem];
        next_pos = pos_Start;
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
        // throw an exception
        throw std::runtime_error("CustomerOrders::CustomerOrders(&): ----> ERROR: Cannot make copies.");
    }
    
    CustomerOrder& CustomerOrder::operator=(const CustomerOrder& other){
        // throw an exception
        throw std::runtime_error("CustomerOrders::CustomerOrders(&): ----> ERROR: Cannot make copies.");
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& other) noexcept: m_name(""), m_product(""), m_cntItem(0), m_lstItem(nullptr){
        // call the move assignment operator
        *this = std::move(other);
    }
    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& other) noexcept{
        // check if exist
        if(this != &other){
            // deallocate memory
            for(auto i = 0u; i < m_cntItem; ++i){
                delete m_lstItem[i];
            }
            delete[] m_lstItem;

            // move the data
            m_name = other.m_name;  
            m_product = other.m_product;
            m_cntItem = other.m_cntItem;
            m_lstItem = other.m_lstItem;

            // set the other item to null
            other.m_name = "";
            other.m_product = "";
            other.m_lstItem = nullptr;
            other.m_cntItem = 0u;
        }

        return *this;
    }

    CustomerOrder::~CustomerOrder(){
        // deallocate memory
        for(size_t i = 0; i < m_cntItem; ++i){
            delete m_lstItem[i];
        }

        delete[] m_lstItem;
    }


    bool CustomerOrder::isOrderFilled() const{
        // check if all items are filled
        for(size_t i = 0; i < m_cntItem; i++){
            // if not filled return false
            if(!m_lstItem[i]->m_isFilled){
                return false;
            }
        }

        return true;
    }

    bool CustomerOrder::isItemFilled(const std::string& itemName) const{
        // check if the item is filled
        for(size_t i = 0; i < m_cntItem; i++){
            // if the item is not filled and the name matches return false
            if(m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled){
                return false;
            }
        }

        return true;
    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os){
        // fill the item
        for(size_t i = 0; i < m_cntItem; i++){
            // if the item is not filled
            if(m_lstItem[i]->m_itemName == station.getItemName()){
                // check if the station has the item
                if(station.getQuantity() > 0){
                    // fill the item
                    station.updateQuantity();
                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;

                    // display the message
                    os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
                    break;
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
            os << "[" << std::setw(6) << std::setfill('0') << m_lstItem[i]->m_serialNumber << "] "
           << std::setw(m_widthField) << std::setfill(' ') << m_lstItem[i]->m_itemName << " - "
           << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << std::endl;
        }
    }
}