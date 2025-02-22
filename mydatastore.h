#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <map>
#include <queue>

class MyDataStore : public DataStore {
public:

    MyDataStore();
    ~MyDataStore();

    // derived class functions
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);

    // additional functions
    void addToCart(std::string username, Product *p);
    void viewCart(std::string username);
    void buyCart(std::string username);


private:

    std::vector<Product*> products_;
    std::map<std::string, User*> users_;
    std::map<std::string, std::set<Product*>> keywordMap_;
    std::map<std::string, std::queue<Product*>> carts_;

};


#endif