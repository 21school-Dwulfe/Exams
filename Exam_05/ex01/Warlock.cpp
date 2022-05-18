#include "Warlock.hpp"

Warlock::Warlock(const std::string& name, const std::string& title) : _name(name), _title(title)
{
    std::cout << this->_name << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock()
{
    std::map<std::string, ASpell*>::iterator be = _spells.begin();
    std::map<std::string, ASpell*>::iterator it = _spells.end();
    
    while (be != it)
    {
        delete be->second;
        be++;
    }
    _spells.clear();
    std::cout << this->_name << ": My job here is done!" <<std::endl;
}

const std::string& Warlock::getName() const
{
    return (this->_name);
}

const std::string& Warlock::getTitle() const
{
    return (this->_title);
}

void    Warlock::setTitle(const std::string& title)
{
    const std::string *t = &title;

    if (t)
        _title = title;
}

void    Warlock::introduce() const
{
    std::cout << this->_name << ": I am " << this->_name << ", " << this->_title << "!"<<std::endl;
}

void    Warlock::learnSpell(const ASpell* spell)
{
    if (spell)
        _spells.insert(std::pair<std::string, ASpell*>(spell->getName(), spell->clone()));
}

void    Warlock::forgetSpell(const std::string& spellName)
{
    std::map<std::string, ASpell*>::iterator it = this->_spells.find(spellName);

    if (it != _spells.end())
    {
        delete it.second;
        this->_spells.erase(it);
    }
}

void    Warlock::launchSpell(const std::string& spellName, const ATarget& target)
{
    std::map<std::string, ASpell*>::iterator it = this->_spells.find(spellName);
    const ATarget* p = &target;

    if (it != _spells.end() && p)
        this->_spells[spellName]->launch(target);
}
