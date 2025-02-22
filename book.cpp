#include "book.h"
#include <sstream>

Book::Book(const std::string& name, double price, int qty, const std::string& isbn, const std::string& author) 
        : Product("book", name, price, qty), isbn_(isbn), author_(author)
{
    // empty bc using constructor initialization list
}

std::set<std::string> Book::keywords() const
{
    std::set<std::string> keys;

    keys.insert(isbn_);

    std::set<std::string> authorKeys = parseStringToWords(convToLower(author_));
    keys.insert(authorKeys.begin(), authorKeys.end());
    
    std::set<std::string> nameKeys = parseStringToWords(convToLower(name_));
    keys.insert(nameKeys.begin(), nameKeys.end());

    return keys;
}
std::string Book::displayString() const
{
    std::ostringstream oss;
    oss << name_ << std::endl;
    oss << "Author: " << author_ <<  " ISBN: " << isbn_ << std::endl; // isbn and author are flipped need to change
    oss << price_ << " " << qty_ << " left.";
    return oss.str();
}
void Book::dump(std::ostream& os) const
{
    os << "book" << std::endl;
    os << name_ << std::endl;
    os << price_ << std::endl;
    os << qty_ << std::endl;
    os << isbn_ << std::endl;
    os << author_ << std::endl;
}