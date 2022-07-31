#include<string>
#include<memory>
#include<vector>
#include<iostream>
#include<map>
#include "license.h"

License::License(string name, unsigned int salary) {
    if(name.size()==0 || salary == 0){
        throw runtime_error ("Leer");
    }
    counter = 0;
    this->name = name;
    this->salary = salary;
};

License::~License() {}

string License::get_guildname() const{
    return name;
};

unsigned int License::get_salary() const{
    return salary;
};

bool License::valid() const{
    return counter <= 3;
};

bool License::use() {
    if(valid()){
        counter++;
        return true;
    }
    return false;
};

ostream& License::print(ostream& o) const{
    o << "[License for " << name << ", Salary: " << salary << ", Used: " << counter << "]";
    return o;
};

ostream& operator<<(ostream& out, const License& l){
    return l.print(out);
}
