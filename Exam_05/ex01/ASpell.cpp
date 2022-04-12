#include "ASpell.hpp"

ASpell::ASpell(const std::string& name, const std::string& effects): _name(name), _effects(effects)
{

}

ASpell::ASpell(const ASpell& copy)
{
    *this = copy;
}

ASpell::~ASpell()
{

}

const std::string& ASpell::getName()const
{
    return (this->_name);
}

const std::string& ASpell::getEffects()const
{
    return (this->_effects);
}

ASpell&   ASpell::operator=(const ASpell& spell)
{
    const ASpell* p = &spell;

    if (!p)
        return (*this);
    if (this != &spell)
    {
        this->_name = spell._name;
        this->_effects = spell._effects;
    }
    return (*this);
}

void    ASpell::launch(const ATarget& target)
{
    const ATarget *p = &target;
    if (p)
        target.getHitBySpell(*this);
}
