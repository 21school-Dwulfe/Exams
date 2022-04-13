#ifndef TARGETGENERATOR_HPP
#define TARGETGENERATOR_HPP

#include "ATarget.hpp"
#include <map>

class   TargetGenerator
{
private:
    std::map<std::string, ATarget*> _targets; 
public:
    TargetGenerator();
    virtual ~TargetGenerator();
    void    learnTargetType(ATarget* targetType);
    void    forgetTargetType(std::string const & targetType);
    ATarget* createTarget(std::string const &target);
};

#endif
