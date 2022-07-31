#ifndef GUILD_H
#define GUILD_H
#include<string>
#include<memory>
#include<vector>
#include<iostream>
#include<map>
using namespace std;
class Person;
class Guild{
  string name;
    unsigned int fee;
    unsigned int salary;
 protected:
    map<string,shared_ptr<Person>> members;

public:
    Guild(string name, unsigned fee, unsigned sal, const vector<shared_ptr<Person>>& players = {});
  	virtual ~Guild() = default;
    bool add_member(shared_ptr<Person> p );
    bool remove_member(string n);
    void grant_license(string n);
    bool offer_job(shared_ptr<Person> p) const;
    ostream& print(ostream& o) const;
};

ostream& operator<<(ostream& out, const Guild& l);

#endif
