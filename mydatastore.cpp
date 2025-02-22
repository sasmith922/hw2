#include "mydatastore.h"
#include "util.h"

MyDataStore::MyDataStore()
{
    // empty constructor, no initialization needed
}
MyDataStore::~MyDataStore()
{
    for(size_t i = 0; i < products_.size(); i++)
    {
        delete products_[i]; // deletes product pointers
    }

    std::map<std::string, User*>::iterator iter;
    for(iter = users_.begin(); iter != users_.end(); ++iter)
    {
        delete iter->second; // deletes user pointers in map
    }
}



void MyDataStore::addProduct(Product* p)
{
    std::set<std::string> keywords = p->keywords(); // get keywords from product

    std::set<std::string>::iterator iter;
    for(iter = keywords.begin(); iter != keywords.end(); ++iter)
    {
        keywordMap_[*iter].insert(p); // add keywords from product to map
    }

    products_.push_back(p); // add product to products
}

void MyDataStore::addUser(User* u)
{
    users_[convToLower(u->getName())] = u;
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    std::set<Product*> results;

    if (type == 0) // AND search
    {
        if (keywordMap_.find(terms[0]) == keywordMap_.end()) 
        {
            return {}; // first term not found
        }
        results = keywordMap_[terms[0]]; // initialize with first term products

        for (size_t i = 1; i < terms.size(); i++) 
        {
            if (keywordMap_.find(terms[i]) == keywordMap_.end()) 
            {
                return {}; // term is missing, no intersection
            }
            results = setIntersection(results, keywordMap_[terms[i]]);
        }
    }
    else // OR search
    {
        for(std::string term : terms)
        {
            if(keywordMap_.find(term) != keywordMap_.end()) // term exists
            {
                results = setUnion(results, keywordMap_[term]);
            }
        }
    }

    return std::vector<Product*>(results.begin(), results.end());
}

void MyDataStore::dump(std::ostream& ofile)
{
    ofile << "<products>" << std::endl;
    for (size_t i = 0; i < products_.size(); i++) {
        products_[i]->dump(ofile); // uses dump member function for product
    }
    ofile << "</products>" << std::endl;

    ofile << "<users>" << std::endl;
    std::map<std::string, User*>::iterator iter;
    for (iter = users_.begin(); iter != users_.end(); ++iter) {
        iter->second->dump(ofile); // gets user from iter and uses dump member function
    }
    ofile << "</users>" << std::endl;
}


void MyDataStore::addToCart(std::string username, Product *p)
{
    if(users_.find(username) == users_.end()) // username is not in users
    {
        std::cout << "Invalid request" << std::endl;
        return;
    }
    carts_[username].push(p);
}

void MyDataStore::viewCart(std::string username)
{
    username = convToLower(username);

    if(users_.find(username) == users_.end()) // username is not in users
    {
        std::cout << "Invalid request, invalid username" << std::endl;
        return;
    }
    
    std::queue<Product*> temp = carts_[username]; // carts keys are queues so this works

    int index = 1;

    while(!temp.empty())
    {
        Product* p = temp.front();
        temp.pop();
        std::cout << "Index " << index << ":" << std::endl;
        std::cout << p->displayString() << std::endl;
        index++;
    }
}

void MyDataStore::buyCart(std::string username)
{
    username = convToLower(username);
    std::cout << "Buying cart!" << std::endl; // debug
    if(users_.find(username) == users_.end()) // username is not in users
    {
        std::cout << "Invalid request, invalid username" << std::endl;
        return;
    }

    User* user = users_[username];
    std::queue<Product*> temp = carts_[username]; // using queue cus we need FIFO functionality
    Product* lastProduct = temp.back();

    while(!temp.empty())
    {
        Product* p = temp.front();
        temp.pop();

        if (p->getQty() > 0 && user->getBalance() >= p->getPrice()) // item is purchased
        {
            p->subtractQty(1);
            std::cout << "Decremented!" << std::endl; // debug
            user->deductAmount(p->getPrice());
            std::cout << "Deducted amount!" << std::endl; // debug
        }
        else // item not purchased
        {
            std::cout << "Item not purchased!" << std::endl; // debug
            
            temp.push(p); // item added back to queue
            if(p == lastProduct && user->getBalance() < p->getPrice()) // check for insufficient funds
            {
                std::cout << "Insufficient funds check" << std::endl;
                break;
            }
            if(p->getQty() <= 0) // out of stock check
            {
                std::cout << "Out of stock!" << std::endl; // debug
                break;
            }
        }

    }

    carts_[username] = temp;
}

