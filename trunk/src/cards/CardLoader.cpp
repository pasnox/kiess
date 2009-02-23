#include "CardLoader.h" 

#include "Card.h" 
#include "CardProperties.h" 
#include "CardSet.h" 

#include <QFile>
#include <QDebug>

CardLoader::CardLoader(CardSet* a_cardSet)
{
	m_cardSet=a_cardSet;
}

 
bool CardLoader::load(const QString& a_filename)
{
   QFile l_file(a_filename);
    if (!l_file.open(QFile::ReadOnly | QFile::Text)) 
	{
		qWarning() << l_file.errorString();
        return false ;
    }
	
    QString l_errorMsg;
    int l_errorLine, l_errorColumn;
    if (!m_domDocument.setContent(&l_file, true, &l_errorMsg, &l_errorLine, &l_errorColumn)) 
	{
        qWarning() <<__LINE__
			<<(m_filename)
			<<(l_errorLine)
			<<(l_errorColumn)
			<<(l_errorMsg);
        return false;
    }

    QDomElement l_root = m_domDocument.documentElement();
    if (l_root.tagName() != "KiessCardSet") 
	{
		qWarning()<<"Not a KiessCardSet file";
        return false;
    } 
	else 
	if (l_root.hasAttribute("version") && l_root.attribute("version") != "1.0") {
        qWarning()<<"Not a KiessCardSet version 1.0 file";
        return false;
    }

    QDomElement l_child = l_root.firstChildElement("card");
    while (!l_child.isNull()) 
	{
        Card *l_card = parseCardElement(l_child);
		m_cardSet->addCard(*l_card);
        l_child = l_child.nextSiblingElement("card");
    }
    return true;
}

Card* CardLoader::parseCardElement(const QDomElement &a_element)
{
    QString l_name = a_element.firstChildElement("name").text();
	
    QDomElement l_child = a_element.firstChildElement();
	CardProperties cp;	
	while (!l_child.isNull()) 
	{
		if(l_child.tagName()=="hair")
		{
			cp.setHairProperties(CardProperties::string2HairProp(l_child.attribute("color")), CardProperties::HAIR_PROP_COLOR);
			cp.setHairProperties(CardProperties::string2HairProp(l_child.attribute("shape")), CardProperties::HAIR_PROP_SHAPE);
		}
		else
		if(l_child.tagName()=="eyes")
		{
			cp.setEyesProperties(CardProperties::string2EyesProp(l_child.attribute("color")), CardProperties::EYES_PROP_COLOR);
			cp.setEyesProperties(CardProperties::string2EyesProp(l_child.attribute("eyebrows")), CardProperties::EYES_PROP_EYEBROWS);
		}
		else
		if(l_child.tagName()=="nose")
		{
		cp.setNoseProperties(CardProperties::string2NoseProp(l_child.attribute("size")), CardProperties::NOSE_PROP_SIZE);
		}
		else
		if(l_child.tagName()=="mouth")
		{
			cp.setMouthProperties(CardProperties::string2MouthProp(l_child.attribute("size")), CardProperties::MOUTH_PROP_SIZE);
			cp.setMouthProperties(CardProperties::string2MouthProp(l_child.attribute("expr")), CardProperties::MOUTH_PROP_EXPR);
		}
		else
		if(l_child.tagName()=="skin")
		{
			cp.setSkinProperties(CardProperties::string2SkinProp(l_child.attribute("color")), CardProperties::SKIN_PROP_COLOR);
		}
		else
		if(l_child.tagName()=="sex")
		{
			cp.setSex(CardProperties::string2SexProp(l_child.attribute("gender")));
		}
		else
		if(l_child.tagName()=="other")
		{
			cp.setOtherProperties(CardProperties::string2OtherProp(l_child.attribute("value")));
		}
		
        l_child = l_child.nextSiblingElement();
	}
    Card * l_card = new Card(l_name);
	l_card->setProperties((const CardProperties &)cp);
	return l_card;
}
