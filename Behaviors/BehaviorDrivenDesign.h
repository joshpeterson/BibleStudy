#ifndef __BEHAVIOR_DRIVEN_DESIGN_H
#define __BEHAVIOR_DRIVEN_DESIGN_H

#include <vector>
#include <stdexcept>
#include <string>
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
        boost::shared_ptr<const IGiven> current_given = this->FindGiven<GivenType>();
        if (!current_given)
        {
            boost::shared_ptr<IGiven> given = boost::shared_ptr<IGiven>(new GivenType());
            given->setup(*this);
            m_givens.push_pack(given);

            return;
        }

        GivenType given;
        std::stringstream error_message;
        error_message << "A given of type " << typeid(given).name() << "already exists";

        throw std::logic_error(error_message.str().c_str());
    }

    template<typename GivenType>
    boost::shared_ptr<const IGiven> GetGiven() const
    {
        boost::shared_ptr<const IGiven> given = this->FindGiven<GivenType>();
        if (given)
        {
            return given;
        }

        GivenType given;
        std::stringstream error_message;
        error_message << "Unable to find a given of type " << typeid(given).name();

        throw std::logic_error(error_message.str().c_str());
    }

    template <typename WhenType>
    void When()
    {
        boost::shared_ptr<const IWhen> current_when = this->FindWhen<WhenType>();
        if (!current_when)
        {
            boost::shared_ptr<IWhen> when = boost::shared_ptr<IWhen>(new WhenType());
            when->occurs(*this);
            m_whens.push_pack(when);
        }

        WhenType when;
        std::stringstream error_message;
        error_message << "A when of type " << typeid(when).name() << "already exists";

        throw std::logic_error(error_message.str().c_str());
    }

    template<typename WhenType>
    boost::shared_ptr<const IWhen> GetWhen() const
    {
        boost::shared_ptr<const IWhen> when = this->FindWhen<WhenType>();
        if (when)
        {
            return when;
        }

        WhenType when;
        std::stringstream error_message;
        error_message << "Unable to find a when of type " << typeid(when).name();

        throw std::logic_error(error_message.str().c_str());
    }

    template <typename ThenType>
    void Then()
    {
        boost::shared_ptr<IThen> then = boost::shared_ptr<IThen>(new ThenType());
        then->ensure_that(*this);
    }

private:
    std::vector<boost::shared_ptr<const IGiven> > m_givens;
    std::vector<boost::shared_ptr<const IWhen> > m_whens;

    template <typename GivenType>
    boost::shared_ptr<const IGiven> FindGiven()
    {
        for (std::vector<boost::shared_ptr<const IGiven> >::iterator it = m_givens.begin(); it != m_givens.end(); ++it)
        {
            GivenType given;
            if (typeid(*it) == typeid(given))
            {
                return *it;
            }
        }

        return NULL;
    }

    template <typename WhenType>
    boost::shared_ptr<const IWhen> FindWhen()
    {
        for (std::vector<boost::shared_ptr<const IWhen> >::iterator it = m_whens.begin(); it != m_whens.end(); ++it)
        {
            WhenType when;
            if (typeid(*it) == typeid(when))
            {
                return *it;
            }
        }

        return NULL;
    }
};

}

#endif // __BEHAVIOR_DRIVEN_DESIGN_H
