#include "Card.h"

Card::Card(QString a_name)
{
	setName(a_name);
}

void Card::setProperties(const CardProperties &a_properties)
{
	m_properties=a_properties;
}
const CardProperties & Card::getProperties() const
{
	return m_properties;
}

void Card::setName(const QString &a_name)
{
	m_name=a_name;
}

QString Card::toString() const
{
	return m_name + "->\n" + m_properties.toString();
}
