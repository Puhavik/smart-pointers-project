#ifndef LICENSE_H
#define LICENSE_H
#include<string>
#include<memory>
#include<vector>
#include<iostream>
#include<map>
using namespace std;

class License {
    string name;
    unsigned int salary;
    unsigned int counter;

public:
    License(string name, unsigned int salary);
    ~License();
    string get_guildname() const;
    unsigned int get_salary() const;
    bool valid() const;
    bool use();
    ostream& print(ostream&) const;
};

ostream& operator<<(ostream&, const License&);

#endif
