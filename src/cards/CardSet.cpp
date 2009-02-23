#include "CardSet.h"

#include <QDebug>

#include "CardLoader.h"

CardSet::CardSet(const QString &a_filename)
{
	CardLoader l_cl(this);
	l_cl.load(a_filename);
}

void CardSet::addCard(const Card &a_card)
{
	m_cards.append(a_card);
}

const QList<Card>& CardSet::getCards() const
{
	return m_cards;
}

	
void CardSet::print() const
{
	QListIterator<Card> i(m_cards);
	while (i.hasNext())
		qDebug() << i.next().toString();
}
