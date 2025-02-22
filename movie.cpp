#include "movie.h"
#include <sstream>

Movie::Movie(const std::string& name, double price, int qty, const std::string& genre, const std::string& rating) 
        : Product("movie", name, price, qty), genre_(genre), rating_(rating)
{
    // empty bc using constructor initialization list
}

std::set<std::string> Movie::keywords() const
{
    std::set<std::string> keys;
    
    keys.insert(convToLower(genre_));

    std::set<std::string> nameKeys = parseStringToWords(convToLower(name_));
    keys.insert(nameKeys.begin(), nameKeys.end());

    return keys;
}
std::string Movie::displayString() const
{
    std::ostringstream oss;
    oss << name_ << std::endl;
    oss << "Genre: " << genre_ << " Rating: " << rating_ << std::endl;
    oss << price_ << " " << qty_ << " left.";
    return oss.str();
}
void Movie::dump(std::ostream& os) const
{
    os << "movie" << std::endl;
    os << name_ << std::endl;
    os << price_ << std::endl;
    os << qty_ << std::endl;
    os << genre_ << std::endl;
    os << rating_ << std::endl;
}