/*
I declare that this submission is the result of my own work and I only copied the code that 
my professor provided to complete my workshops and assignments. This submitted piece of work 
has not been shared with any other student or 3rd party content provider.

Sarah Mathew
smathew32@myseneca.ca
140903238
*/

#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

#include <string>
#include <stdexcept>

namespace seneca{
    class Utilities {
        size_t m_widthField = 1;
        static char m_delimiter;

    public:
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        const std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
        static void setDelimiter(const char newDelimiter);
        static char getDelimiter();
    };
}

#endif // !SENECA_UTILITIES_H