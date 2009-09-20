#ifndef __ICOMMAND_H
#define __ICOMMAND_H

//! This class represents a generic command interface.
class ICommand
{
    //! Execute the command.
    virtual void Execute() = 0;
};

#endif // __ICOMMAND_H
