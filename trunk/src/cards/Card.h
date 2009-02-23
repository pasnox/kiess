#ifndef CARD_H
#define CARD_H

#include <QString>
#include <QDataStream>

#include "CardProperties.h"

class Card
 {
public:
	Card(QString a_name);
	
	void setProperties(const CardProperties &a_properties);
	const CardProperties & getProperties() const;
	
	void setName(const QString &a_name);

	QString toString() const;

private:
    CardProperties m_properties;
	QString m_name;
 };

#endif //CARD_H
