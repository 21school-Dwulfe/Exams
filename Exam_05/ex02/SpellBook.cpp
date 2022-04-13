#include "SpellBook.hpp"

SpellBook::SpellBook()
{
    
}

SpellBook::~SpellBook()
{
    std::map<std::string, ASpell*>::iterator be = _spells.begin();
    std::map<std::string, ASpell*>::iterator it = _spells.end();
    
    while (be != it)
    {
        delete be->second;
        be++;
    }
   _spells.clear();
}


void   SpellBook::learnSpell(ASpell *spell)
{
    if (spell)
        _spells.insert(std::pair<std::string, ASpell*>(spell->getName(), spell->clone()));
}

void    SpellBook::forgetSpell(std::string const &spell)
{
    std::map<std::string, ASpell*>::iterator it = this->_spells.find(spell);

    if (it != _spells.end())
    {
        delete it->second;
        this->_spells.erase(it);
    }
}

ASpell* SpellBook::createSpell(std::string const& spell)
{
    std::map<std::string, ASpell*>::iterator it = this->_spells.find(spell);

    if (it != _spells.end())
        return (_spells[spell]);
    return (0);
}