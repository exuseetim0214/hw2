#include "clothing.h"
#include "util.h"
#include <sstream>

Clothing::Clothing(const std:: string& name, double price, int qty, const std::string& size, const std::string& brand)
:Product("clothing", name, price, qty), size_(size), brand_(brand)
{

}


std::set<std::string> Clothing::keywords() const
{
  std::set<std::string> namekeys = parseStringToWords(convToLower(getName()));
  std::set<std::string> brandKeys = parseStringToWords(convToLower(brand_));
  std::set<std::string> allkeys = setUnion(namekeys,brandKeys);
  return allkeys;

}

std::string Clothing::displayString() const
{
  std::ostringstream oss;
  oss << getName() << std::endl;
  oss << "Size: " << size_ << " Brand: " << brand_ << std::endl;
  oss << getPrice() << " " << getQty() << " left.";
  return oss.str();
}

void Clothing::dump(std::ostream& os) const
{
 os << "clothing" << std::endl;
 os << getName() << std::endl;
 os << getPrice() << std::endl;
 os << getQty() << std::endl;
 os << size_ << std::endl;
 os << brand_ << std::endl;
}



