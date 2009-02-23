#ifndef CARDLOADER_H
#define CARDLOADER_H

#include <QDomDocument>
#include <QString>

class Card;
class CardSet;

class CardLoader
 {
	public:
	
	CardLoader(CardSet* a_cardSet);
	bool load(const QString& a_filename);
	
	private:
	
	Card* parseCardElement(const QDomElement &a_element);

    QDomDocument m_domDocument;
	QString m_filename;
	CardSet* m_cardSet;
 };
#endif //CARDLOADER_H
