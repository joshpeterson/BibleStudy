#ifndef _ISERIALIZEABLE_H
#define _ISERIALIZEABLE_H

#include <QString>

namespace BibleStudyGui
{

//! This interface is used to serialize project data from objects to string.
class ISerializable
{
public:
	//! Write the project data of an object to a string.  The string should not end with a newline.
	virtual QString serialize() const = 0;
};

}

#endif // _ISERIALIZEABLE_H
