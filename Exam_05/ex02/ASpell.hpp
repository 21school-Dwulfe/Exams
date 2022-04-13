#ifndef SPELL_HPP
#define SPELL_HPP

#include <iostream>
#include "ATarget.hpp"

class ATarget;

class ASpell
{
private:
    std::string _name;
    std::string _effects;
public:
    ASpell(const std::string& name, const std::string& title);
    ASpell(const ASpell& copy);
    virtual ~ASpell();
    const std::string& getName()const;
    const std::string& getEffects()const;

    ASpell&   operator=(const ASpell& spell);
    void    launch(const ATarget& target);
    virtual ASpell* clone()const = 0;
};

#endif
