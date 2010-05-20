#ifndef __BEHAVIOR_DRIVEN_DESIGN_H
#define __BEHAVIOR_DRIVEN_DESIGN_H

#include <vector>
#include <boost/shared_ptr.hpp>

namespace BehaviorDrivenDesign
{
class World;

class IGiven
{
public:
    virtual void setup(const World&) = 0;
};

class IWhen
{
public:
    virtual void occurs(const World&) = 0;
};

class IThen
{
public:
    virtual void ensure_that(const World&) = 0;
};

class World
{
public:
    template <typename GivenType>
    void Given()
    {
        boost::shared_ptr<IGiven> given = boost::shared_ptr<IGiven>(new GivenType());
        given->setup(*this);
        m_givens.push_pack(given);
    }

    template <typename WhenType>
    void When()
    {
        boost::shared_ptr<IWhen> when = boost::shared_ptr<IWhen>(new WhenType());
        when->occurs(*this);
        m_whens.push_pack(when);
    }

    template <typename ThenType>
    void Then()
    {
        boost::shared_ptr<IThen> then = boost::shared_ptr<IThen>(new ThenType());
        then->ensure_that(*this);
    }

private:
    std::vector<boost::shared_ptr<IGiven> > m_givens;
    std::vector<boost::shared_ptr<IWhen> > m_whens;
};

}

#endif // __BEHAVIOR_DRIVEN_DESIGN_H
