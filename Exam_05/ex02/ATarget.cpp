#include "ATarget.hpp"

ATarget::ATarget(const std::string& type): _type(type)
{

}

ATarget::ATarget(const ATarget& target)
{
    *this = target;
}

ATarget& ATarget::operator=(const ATarget& target)
{
    const ATarget* p = &target;

    if (!p)
        return (*this);
    if (this != &target)
    {
        this->_type = target._type;
    }
    return (*this);
}

ATarget::~ATarget()
{

}

const std::string& ATarget::getType()const
{
    return (this->_type);
}

void    ATarget::getHitBySpell(const ASpell& spell) const
{
    std::cout << this->_type << " has been "<< spell.getEffects() << "!" << std::endl;
}
