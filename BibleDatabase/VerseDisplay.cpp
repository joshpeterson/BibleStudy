#include <vector>
#include <stdexcept>
#include <sstream>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/lexical_cast.hpp>
#include "VerseDisplay.h"    

using namespace BibleDatabase;

VerseDisplay::VerseDisplay(std::string translation, int verse_id, int num_verses_context) :
    m_translation(translation),
    m_verse_id(verse_id),
    m_num_verses_context(num_verses_context)
{
}

VerseDisplay::VerseDisplay(std::string serailized_verse_display)
{
	std::vector<std::string> parts;
	boost::algorithm::split(parts, serailized_verse_display, boost::algorithm::is_any_of(":"));

	if (parts.size() != 3)
	{
		throw std::invalid_argument(serailized_verse_display);
	}

	m_translation = parts[0];
	m_verse_id = boost::lexical_cast<int>(parts[1]);
	m_num_verses_context = boost::lexical_cast<int>(parts[2]);
}

std::string VerseDisplay::get_translation() const
{
    return m_translation;
}

int VerseDisplay::get_verse_id() const
{
    return m_verse_id;
}

int VerseDisplay::get_num_verses_context() const
{
    return m_num_verses_context;
}

bool VerseDisplay::operator==(const VerseDisplay& other) const
{
    return m_verse_id == other.get_verse_id() && m_translation == other.get_translation();
}

std::string VerseDisplay::serialize() const
{
	std::stringstream stream;
	stream << m_translation << ":" << m_verse_id << ":" << m_num_verses_context;

	return stream.str();
}

