#include "clothing.h"
#include <sstream>

Clothing::Clothing(const std::string& name, double price, int qty, const std::string& size, const std::string& brand) 
        : Product("clothing", name, price, qty), size_(size), brand_(brand)
{
    // empty bc using constructor initialization list
}

std::set<std::string> Clothing::keywords() const
{
    std::set<std::string> keys;

    std::set<std::string> brandKeys = parseStringToWords(convToLower(brand_));
    keys.insert(brandKeys.begin(), brandKeys.end());

    std::set<std::string> nameKeys = parseStringToWords(convToLower(name_));
    keys.insert(nameKeys.begin(), nameKeys.end());

    return keys;
}
std::string Clothing::displayString() const
{
    std::ostringstream oss;
    oss << name_ << std::endl;
    oss << "Size: " << size_ << " Brand: " << brand_ << std::endl;
    oss << price_ << " " << qty_ << " left.";
    return oss.str();
}
void Clothing::dump(std::ostream& os) const
{
    os << "clothing" << std::endl;
    os << name_ << std::endl;
    os << price_ << std::endl;
    os << qty_ << std::endl;
    os << size_ << std::endl;
    os << brand_ << std::endl;
}