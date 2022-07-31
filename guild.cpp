#include<string>
#include<memory>
#include<vector>
#include<iostream>
#include<stdexcept>
#include<set>
#include<algorithm>
#include<map>
#include "guild.h"
#include "license.h"
#include "person.h"
using namespace std;

Guild::Guild(string name, unsigned fee, unsigned sal, const vector<shared_ptr<Person>>& players){
    if(name.size()==0 || fee == 0 || sal == 0){
        throw runtime_error("LeerQ");
    }
    set <string> check;
    for(shared_ptr<Person> p : players){
        check.insert(p->get_name());
    }
    if(check.size() != players.size()){
        throw runtime_error ("Mehr als 1");
    }

    this->name = name;
    this->fee = fee;
    this->salary = sal;
    for(shared_ptr<Person> p : players){
        add_member(p);
    }
};

bool Guild::add_member(shared_ptr<Person> p ){
    if(members.find(p->get_name()) == members.end()){
        members[p->get_name()] = p;
        return true;
    }
    return false;
};
bool Guild::remove_member(string n){
    if(members.find(n) != members.end()){
        members.erase(members.find(n));
        return true;
    }
    return false;
};

void Guild::grant_license(string n){
    for(auto const &m : members){
        if(members[m.first]->get_name() == n && members[m.first]->pay_fee(fee)){
          unique_ptr<License> v(new License(name, salary));
          members[m.first]->receive_license(move(v));
          return;
        }
      }
    throw runtime_error("Not Ready! License Error");
};

bool Guild::offer_job(shared_ptr<Person> p) const{
    if(members.find(p->get_name()) != members.end()){
        p->work(salary*2);
        return true;
    } else if(members.find(p->get_name()) == members.end() && p->eligible(name)){
        p->work(name);
        return true;
    }
    return false;
};

ostream& Guild::print(ostream& o) const{
    cout << "[" << name << ", License fee: " << fee << ", Job salary: " << salary << ", {";
    bool first = false;
    for(auto it = members.begin(); it != members.end(); it++){
        if(!first){
            first = true;
        } else {
            cout << ", ";
        }
        cout << (*it->second).get_name();
    }
    cout << "}]";
    return o;
};

ostream& operator<<(ostream& out, const Guild& l){
    return l.print(out);
}
