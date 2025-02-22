#ifndef BOOK_H
#define BOOK_H

#include "product.h"
#include "util.h"

class Book : public Product {
public:
    Book(const std::string& name, double price, int qty, const std::string& isbn, const std::string& author);

    std::set<std::string> keywords() const;
    std::string displayString() const;
    virtual void dump(std::ostream& os) const;

private:
    std::string isbn_;
    std::string author_;

};

#endif