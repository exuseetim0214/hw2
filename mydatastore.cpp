#include "mydatastore.h"
#include "util.h"
#include <sstream>
#include <iomanip>

// constructor

MyDataStore::MyDataStore()
{

}

//Destructor

MyDataStore::~MyDataStore()
{
  for(std::size_t i = 0; i < products_.size(); i++){
    delete products_[i];
  }

  for(std::size_t i = 0; i < users_.size(); i++){
    delete users_[i];
  }

  carts_.clear();
}

// add product to the cart

void MyDataStore::addProduct(Product* p)
{
  if(p ==NULL){
    return;
  }

  products_.push_back(p);

  std::set<std::string> keys = p-> keywords();
  std::set<std::string>:: iterator it;
  for(it = keys.begin(); it != keys.end(); it++){
    std::string out = convToLower(*it);
    index_[out].insert(p);
  }
}

//add user

void MyDataStore::addUser(User* u)
{
  if(u ==NULL){
    return;
  }

  users_.push_back(u);

  std::string username =convToLower(u->getName());
  usersByName_[username] = u;
}

//search
std::vector<Product*>MyDataStore::search(std::vector<std::string>& terms, int type)
{
  std::vector<Product*> out;
  //nothing to search
  if(terms.size() == 0){
    return std::vector<Product*>();
  }

  std::set<Product*> process;
  bool firstTerm = true;

  for(std:: size_t i =0; i< terms.size(); i++){
    std::string key = convToLower(terms[i]);
    
    std::map<std::string, std::set<Product*>>::iterator it = index_.find(key);
    
    std::set<Product*> found;
    if(it != index_.end()){
      found = it->second;
    }

    if(firstTerm){
      process = found;
      firstTerm = false;
    }
    else{
      if(type == 0){
        process = setIntersection(process, found);
      }
      
      else{
        process = setUnion(process, found);
      }
    }
  }

  for(std::set<Product*>::iterator it = process.begin(); it != process.end(); it++){
    out.push_back(*it);
  }

  return out;
}

//add
bool MyDataStore::add(const std::string& username, Product* prod)
{
  if(prod == nullptr){
    return false;
  }

  std::string uname = convToLower(username);

  if(usersByName_.find(uname) == usersByName_.end()){
    return false;
  }

  carts_[uname].push_back(prod);
  return true;
}


//viewcart
void MyDataStore::viewCart(const std::string& username, std::ostream& os)
{
  std::string lower_case_uname = convToLower(username);

  std::map<std::string, User*>::iterator it = usersByName_.find(lower_case_uname);
  if(it == usersByName_.end()){
    std::cout << "Invalid username" << std::endl;
    return;
  }

  if(carts_.find(lower_case_uname) == carts_.end()){
    return;
  }
  std::vector<Product*>& userCart = carts_[lower_case_uname];
  std::size_t num = userCart.size();

  for(std::size_t i = 0; i <num; i++){
    os << "Item " << (i + 1)<< std::endl;
    os << userCart[i]->displayString() <<std::endl;
    os << std::endl;
  }
}
//buycart
void MyDataStore::buyCart(const std::string& username)
{
  std::string lower_case_uname = convToLower(username);

  std::map<std::string, User*>::iterator it = usersByName_.find(lower_case_uname);
  if(it == usersByName_.end()){
    std::cout << "Invalid username" << std::endl;
    return;
  }
  if(carts_.find(lower_case_uname) == carts_.end()){
    return;
  }
  User* buyer = it->second;
  std::vector<Product*>& shoppingCart = carts_[lower_case_uname];

  // item can't buy
  std::vector<Product*> item_left;
  
  for(std::size_t idx = 0; idx < shoppingCart.size(); idx++){
    Product* item = shoppingCart[idx];
    double cost = item->getPrice();
    int available = item->getQty();

    bool inStock = (available > 0);
    bool canAfford = (buyer->getBalance() >= cost);

    if(inStock && canAfford){
      item->subtractQty(1);
      buyer->deductAmount(cost);
    }
    else{
      item_left.push_back(item);
    }
  }
  shoppingCart = item_left;
}
//dump
void MyDataStore::dump(std::ostream& ofile){
  ofile << "<products>" << std::endl;

  std::size_t count = products_.size();
  for (std::size_t idx =0; idx < count; idx++){
    Product* current = products_[idx];
    current->dump(ofile);
  }

  ofile << "</products>" << std::endl;

  ofile << "<users>"<< std::endl;

  std::size_t user_count = users_.size();
  for(std::size_t idx = 0; idx < user_count; idx++){
    User* current_user = users_[idx];
    current_user->dump(ofile);
  }
  ofile << "</users>" << std::endl;
}