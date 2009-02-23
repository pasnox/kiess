#ifndef CARDSET_H
#define CARDSET_H

#include <QString>
#include <QList>

#include "Card.h"

class CardSet
 {
public:
	CardSet(const QString &a_filename);
	
	void addCard(const Card &a_card);
	
	const QList<Card>& getCards() const;
	
	void print() const;

private:
    QList<Card> m_cards;
 };

#endif //CARDSET_H
