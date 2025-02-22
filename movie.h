#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"
#include "util.h"

class Movie : public Product {
public:
    Movie(const std::string& name, double price, int qty,const std::string& genre, const std::string& rating);

    std::set<std::string> keywords() const;
    std::string displayString() const;
    virtual void dump(std::ostream& os) const;

private:
    std::string genre_;
    std::string rating_;
};

#endif