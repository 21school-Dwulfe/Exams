#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include <iostream>

class Warlock
{
private:
    std::string _name;
    std::string _title;
public:
    Warlock(const std::string& name, const std::string& title);
    virtual ~Warlock();


    const std::string& getName() const;
    const std::string& getTitle() const;

    void    setTitle(const std::string& title);
    void    introduce() const;
};

#endif
