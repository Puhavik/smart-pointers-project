#include<string>
#include<memory>
#include<vector>
#include<iostream>
#include<map>
#include "person.h"
#include "license.h"
using namespace std;

//PERSON CLASS METHODS IMPLEMENTATION
Person::Person(string name, unsigned int wealth){
    if(name.size() == 0){
        throw runtime_error("Leer!");
    }
    this->name = name;
    this->wealth = wealth;
};

void Person::work(string guild){
    for(auto const &l : licenses){
        if(l.first == guild && licenses[l.first]->valid()){
            licenses[l.first]->use();
            work(licenses[l.first]->get_salary());
            return;
        }
    }
    throw runtime_error("Keine Lizenz");
};

void Person::increase_wealth(unsigned int i){
    wealth+=i;
};

string Person::get_name() const {
    return name;
};

bool Person::pay_fee(unsigned int i){
    if(wealth == 0 || wealth < i){
        return false;
    }
    wealth-=i;
    return true;
};

void Person::receive_license(unique_ptr<License> l){
  if(licenses.find(l->get_guildname()) != licenses.end()){
    licenses.erase(l->get_guildname());
    licenses.insert(make_pair(l->get_guildname(), move(l)));
    return;
  }
  licenses[l->get_guildname()] = move(l);
};

void Person::transfer_license(string l, shared_ptr<Person> p){
    if(licenses.find(l) == licenses.end()){
        throw runtime_error("Not Found");
    }
    p->licenses.insert(make_pair(l, move(licenses[l])));
    this->licenses.erase(l);
};

bool Person::eligible(string l) const{
    if(licenses.find(l) != licenses.end() && licenses.at(l)->valid()){
        return true;
    }
    return false;
};

ostream& Person::print(ostream& o) const{
    cout << name << ", " << wealth << " Coins" << ", {";
    bool first =false;
    for(auto it = licenses.begin(); it != licenses.end(); it++){
        if(!first){
            first = true;
        } else {
            cout << ", ";
        }
        cout << *it->second;
    }
    cout << "}]";
    return o;
};

ostream& operator<<(ostream& out, const Person& p) {
    return p.print(out);
}

//WORKER CLASS METHODS IMPLEMENTATION
Worker::Worker(string name, unsigned int wealth) : Person(name, wealth){};

void Worker::work(unsigned int i) {
    increase_wealth(i);
}

ostream& Worker::print(ostream& o) const {
    o << "[Worker ";
    Person::print(o);
    return o;
}


//SUPERWORKER CLASS METHODS IMPLEMENTATION
Superworker::Superworker(unsigned int fee, string name, unsigned int wealth) : Person(name, wealth){
    this->fee = fee;
};

void Superworker::work(unsigned int i) {
    increase_wealth(i + fee);
}

ostream& Superworker::print(ostream& o) const {
    o << "[Superworker ";
    Person::print(o);
    return o;
}
