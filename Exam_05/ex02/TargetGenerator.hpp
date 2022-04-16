#ifndef TARGETGENERATOR_HPP
#define TARGETGENERATOR_HPP

#include "ATarget.hpp"
#include <map>

class   TargetGenerator
{
private:
    std::map<std::string, ATarget*> _targets; 
    TargetGenerator(const TargetGenerator& copy);
    TargetGenerator&    operator=(const TargetGenerator& copy);
public:
    TargetGenerator();
    virtual ~TargetGenerator();
    void    learnTargetType(ATarget* targetType);
    void    forgetTargetType(std::string const & targetType);
    ATarget* createTarget(std::string const &target);
};

#endif
