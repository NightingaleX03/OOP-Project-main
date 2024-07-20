/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#include "Utilities.h"

namespace seneca{
    char Utilities::m_delimiter = '\0';

    void Utilities::setFieldWidth(size_t newWidth) {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const {
        return m_widthField;
    }

    const std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
        std::string token;
        size_t pos = str.find(m_delimiter, next_pos);

        if(next_pos == std::string::npos && more){
            more = false;
            throw "No token";
        }

        if(str.at(next_pos) == m_delimiter && more){
            more = false;
            throw "next_pos is a delimiter";
        }

        if (pos != std::string::npos) {
            token = str.substr(next_pos, pos - next_pos);
            token.erase(0, token.find_first_not_of(" \t"));
            token.erase(token.find_last_not_of(" \t") + 1);
            next_pos = pos + 1;
            more = true;
        }
        else {
            token = str.substr(next_pos);
            token.erase(0, token.find_first_not_of(" \t"));
            token.erase(token.find_last_not_of(" \t") + 1);
            next_pos = std::string::npos;
            more = false;
        }

        if (token.length() > m_widthField) {
            m_widthField = token.length();
        }
        
        return token;
    }

    void Utilities::setDelimiter(const char newDelimiter) {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter(){
        return m_delimiter;
    }
        
}