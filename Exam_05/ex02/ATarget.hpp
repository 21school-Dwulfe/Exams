#ifndef ATARGET_HPP
#define ATARGET_HPP

#include <iostream>
#include "ASpell.hpp"

class ASpell;

class ATarget
{
private:
    std::string _type;
    ATarget();
public:
    ATarget(const std::string& type);
    ATarget(const ATarget& target);
    virtual ~ATarget();
    const std::string& getType()const;

    ATarget& operator=(const ATarget& target);

    void                getHitBySpell(const ASpell& spell) const;
    virtual ATarget*    clone() const = 0;
};

#endif
