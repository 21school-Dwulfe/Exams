#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator()
{

}

TargetGenerator::~TargetGenerator()
{

}

void    TargetGenerator::learnTargetType(ATarget* targetType)
{
    if (targetType)
        _targets[targetType->getType()] = targetType;
}

void    TargetGenerator::forgetTargetType(std::string const & targetType)
{
    std::map<std::string, ATarget*>::iterator it =  _targets.find(targetType);

    if (it != _targets.end())
    {
        _targets.erase(it);
    }
}

ATarget* TargetGenerator::createTarget(std::string const &target)
{
    std::map<std::string, ATarget*>::iterator it =  _targets.find(target);

    if (it != _targets.end())
    {
        return (it->second);
    }
    return (0);
}
