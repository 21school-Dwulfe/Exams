#ifndef SPELLBOOK_HPP
#define SPELLBOOK_HPP

#include "ASpell.hpp"
#include <map>

class SpellBook
{
private:
    std::map<std::string, ASpell*> _spells;
    SpellBook(const SpellBook& copy);
    SpellBook&    operator=(const SpellBook& copy);
public:
    SpellBook();
    ~SpellBook();

    void    learnSpell(ASpell *spell);
    void    forgetSpell(std::string const &spell);
    ASpell* createSpell(std::string const& spell);
};

#endif
