#include "movie.h"
#include "util.h"
#include <sstream>

Movie::Movie(const std:: string& name, double price, int qty, const std::string& genre, const std::string& rating)
:Product("movie", name, price, qty),genre_(genre), rating_(rating)
{

}

std::set<std::string> Movie::keywords() const
{
  std::set<std::string> namekeys = parseStringToWords(convToLower(getName()));
  std::set<std::string> genreKeys = parseStringToWords(convToLower(genre_));
  std::set<std::string> allkeys = setUnion(namekeys,genreKeys);

  return allkeys;

}
std::string Movie::displayString() const
{
  std::ostringstream oss;
  oss << getName() << std::endl;
  oss << "Genre: " << genre_ << " Rating: " << rating_ << std::endl;
  oss << getPrice() << " " << getQty() << " left.";
  return oss.str();
}
void Movie::dump(std::ostream& os) const
{
 os << "movie" << std::endl;
 os << getName() << std::endl;
 os << getPrice() << std::endl;
 os << getQty() << std::endl;
 os << genre_ << std::endl;
 os << rating_ << std::endl;
}


