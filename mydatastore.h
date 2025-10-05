#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include "util.h"
#include <map>
#include <set>
#include <vector>
#include <iostream>
#include <string>


class MyDataStore : public DataStore {
public:
     MyDataStore();
     ~MyDataStore();

    // copying datastore functions
    /**
     * Adds a product to the data store
     */
     void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
     void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
     std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
     void dump(std::ostream& ofile);


     bool add(const std::string& username, Product* prod);
     void viewCart(const std::string& username, std::ostream& os);
     void buyCart(const std::string& username);

private:
    std::vector<Product*> products_;
    std::vector<User*> users_;
    std::map<std::string, User*> usersByName_;
    std::map<std::string, std::set<Product*> > index_;
    std::map<std::string, std::vector<Product*> > carts_;
};

#endif

