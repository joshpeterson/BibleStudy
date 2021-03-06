#ifndef __BEHAVIOR_DRIVEN_DESIGN_H
#define __BEHAVIOR_DRIVEN_DESIGN_H

#include <vector>
#include <stdexcept>
#include <string>
#include <typeinfo>
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
    World() {}

    World(const World& other)
    {
        std::copy(other.m_givens.begin(), other.m_givens.end(), std::back_inserter(m_givens));
        std::copy(other.m_whens.begin(), other.m_whens.end(), std::back_inserter(m_whens));
    }

    template <typename GivenType>
    World& Given()
    {
        const GivenType* current_given = this->FindGiven<GivenType>();
        if (!current_given)
        {
            boost::shared_ptr<IGiven> given = boost::shared_ptr<IGiven>(new GivenType());
            given->setup(*this);
            m_givens.push_back(given);

            return *this;
        }

        GivenType given_error;
        std::stringstream error_message;
        error_message << "A given of type " << typeid(given_error).name() << "already exists";

        throw std::logic_error(error_message.str().c_str());
    }

    template <typename GivenType, typename GivenTypeConstructorArugmentType>
    World& Given(GivenTypeConstructorArugmentType argument)
    {
        const GivenType* current_given = this->FindGiven<GivenType>();
        if (!current_given)
        {
            boost::shared_ptr<IGiven> given = boost::shared_ptr<IGiven>(new GivenType(argument));
            given->setup(*this);
            m_givens.push_back(given);

            return *this;
        }

        GivenType given_error;
        std::stringstream error_message;
        error_message << "A given of type " << typeid(given_error).name() << "already exists";

        throw std::logic_error(error_message.str().c_str());
    }

    template <typename GivenType, typename GivenTypeConstructorArugmentType1, typename GivenTypeConstructorArugmentType2>
    World& Given(GivenTypeConstructorArugmentType1 argument1, GivenTypeConstructorArugmentType2 argument2)
    {
        const GivenType* current_given = this->FindGiven<GivenType>();
        if (!current_given)
        {
            boost::shared_ptr<IGiven> given = boost::shared_ptr<IGiven>(new GivenType(argument1, argument2));
            given->setup(*this);
            m_givens.push_back(given);

            return *this;
        }

        GivenType given_error;
        std::stringstream error_message;
        error_message << "A given of type " << typeid(given_error).name() << "already exists";

        throw std::logic_error(error_message.str().c_str());
    }

    template<typename GivenType>
    const GivenType* GetGiven() const
    {
        const GivenType* given = this->FindGiven<GivenType>();
        if (given)
        {
            return given;
        }

        GivenType given_error;
        std::stringstream error_message;
        error_message << "Unable to find a given of type " << typeid(given_error).name();

        throw std::logic_error(error_message.str().c_str());
    }

    template <typename WhenType>
    World& When()
    {
        const WhenType* current_when = this->FindWhen<WhenType>();
        if (!current_when)
        {
            boost::shared_ptr<IWhen> when = boost::shared_ptr<IWhen>(new WhenType());
            when->occurs(*this);
            m_whens.push_back(when);

            return *this;
        }

        WhenType when_error;
        std::stringstream error_message;
        error_message << "A when of type " << typeid(when_error).name() << "already exists";

        throw std::logic_error(error_message.str().c_str());
    }

    template <typename WhenType, typename WhenTypeConstructorArgumentType>
    World& When(WhenTypeConstructorArgumentType argument)
    {
        const WhenType* current_when = this->FindWhen<WhenType>();
        if (!current_when)
        {
            boost::shared_ptr<IWhen> when = boost::shared_ptr<IWhen>(new WhenType(argument));
            when->occurs(*this);
            m_whens.push_back(when);

            return *this;
        }

        WhenType when_error;
        std::stringstream error_message;
        error_message << "A when of type " << typeid(when_error).name() << "already exists";

        throw std::logic_error(error_message.str().c_str());
    }

    template <typename WhenType, typename WhenTypeConstructorArgumentType1, typename WhenTypeConstructorArgumentType2>
    World& When(WhenTypeConstructorArgumentType1 argument1, WhenTypeConstructorArgumentType2 argument2)
    {
        const WhenType* current_when = this->FindWhen<WhenType>();
        if (!current_when)
        {
            boost::shared_ptr<IWhen> when = boost::shared_ptr<IWhen>(new WhenType(argument1, argument2));
            when->occurs(*this);
            m_whens.push_back(when);

            return *this;
        }

        WhenType when_error;
        std::stringstream error_message;
        error_message << "A when of type " << typeid(when_error).name() << "already exists";

        throw std::logic_error(error_message.str().c_str());
    }

    template<typename WhenType>
    const WhenType* GetWhen() const
    {
        const WhenType* when = this->FindWhen<WhenType>();
        if (when)
        {
            return when;
        }

        WhenType when_error;
        std::stringstream error_message;
        error_message << "Unable to find a when of type " << typeid(when_error).name();

        throw std::logic_error(error_message.str().c_str());
    }

    template <typename ThenType>
    World& Then()
    {
        boost::shared_ptr<IThen> then = boost::shared_ptr<IThen>(new ThenType());
        then->ensure_that(*this);
        
        return *this;
    }

    template <typename ThenType, typename ThenTypeConstructorArgumentType>
    World& Then(ThenTypeConstructorArgumentType argument)
    {
        boost::shared_ptr<IThen> then = boost::shared_ptr<IThen>(new ThenType(argument));
        then->ensure_that(*this);
        
        return *this;
    }

    template <typename ThenType, typename ThenTypeConstructorArgumentType1, typename ThenTypeConstructorArgumentType2>
    World& Then(ThenTypeConstructorArgumentType1 argument1, ThenTypeConstructorArgumentType2 argument2)
    {
        boost::shared_ptr<IThen> then = boost::shared_ptr<IThen>(new ThenType(argument1, argument2));
        then->ensure_that(*this);
        
        return *this;
    }

private:
    std::vector<boost::shared_ptr<const IGiven> > m_givens;
    std::vector<boost::shared_ptr<const IWhen> > m_whens;

    template <typename GivenType>
    const GivenType* FindGiven() const
    {
        for (std::vector<boost::shared_ptr<const IGiven> >::const_iterator it = m_givens.begin(); it != m_givens.end(); ++it)
        {
            GivenType given;
            if (typeid(*(it->get())) == typeid(given))
            {
                return static_cast<const GivenType*>(it->get());
            }
        }

        return NULL;
    }

    template <typename WhenType>
    const WhenType* FindWhen() const
    {
        for (std::vector<boost::shared_ptr<const IWhen> >::const_iterator it = m_whens.begin(); it != m_whens.end(); ++it)
        {
            WhenType when;
            if (typeid(*(it->get())) == typeid(when))
            {
                return static_cast<const WhenType*>(it->get());
            }
        }

        return NULL;
    }
};

}

#endif // __BEHAVIOR_DRIVEN_DESIGN_H
