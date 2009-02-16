#include "CardProperties.h" 

CardProperties::CardProperties()
{
}


CardProperties::HAIR_PROP_VALUES CardProperties::getHairProperties(CardProperties::HAIR_PROP a_prop)
{
	switch (a_prop)
	{
		case CardProperties::HAIR_PROP_COLOR : return m_hair_prop_color;break;
		case CardProperties::HAIR_PROP_SHAPE : return m_hair_prop_shape;break;		
	}
}

void CardProperties::setHairProperties(CardProperties::HAIR_PROP_VALUES a_val, CardProperties::HAIR_PROP a_prop)
{
	switch (a_prop)
	{
		case CardProperties::HAIR_PROP_COLOR : m_hair_prop_color=a_val;break;
		case CardProperties::HAIR_PROP_SHAPE : m_hair_prop_shape=a_val;break;		
	}
}

CardProperties::EYES_PROP_VALUES 
CardProperties::getEyesProperties(CardProperties::EYES_PROP a_prop)
{
	switch (a_prop)
	{
		case CardProperties::EYES_PROP_COLOR    : return m_eyes_prop_color;   break;
		case CardProperties::EYES_PROP_EYEBROWS : return m_eyes_prop_eyebrows;break;		
	}
}

void 
CardProperties::setEyesProperties(CardProperties::EYES_PROP_VALUES a_val, CardProperties::EYES_PROP a_prop)
{
	switch (a_prop)
	{
		case CardProperties::EYES_PROP_COLOR : m_eyes_prop_color=a_val;break;
		case CardProperties::EYES_PROP_EYEBROWS : m_eyes_prop_eyebrows=a_val;break;		
	}
}

CardProperties::NOSE_PROP_VALUES 
CardProperties::getNoseProperties(CardProperties::NOSE_PROP a_prop)
{
	switch (a_prop)
	{
		case CardProperties::NOSE_PROP_SIZE    : return m_nose_prop_size;   break;
	}
}	

void 
CardProperties::setNoseProperties(CardProperties::NOSE_PROP_VALUES a_val, CardProperties::NOSE_PROP a_prop )
{
	switch (a_prop)
	{
		case CardProperties::NOSE_PROP_SIZE    : m_nose_prop_size = a_val;   break;
	}
}

CardProperties::MOUTH_PROP_VALUES 
		CardProperties::getMouthProperties(CardProperties::MOUTH_PROP a_prop)
{
	switch (a_prop)
	{
		case CardProperties::MOUTH_PROP_SIZE : return m_mouth_prop_size; break;
		case CardProperties::MOUTH_PROP_EXPR : return m_mouth_prop_expr; break;		
	}
}

void 
CardProperties::setMouthProperties(CardProperties::MOUTH_PROP_VALUES a_val, CardProperties::MOUTH_PROP a_prop)
{
	switch (a_prop)
	{
		case CardProperties::MOUTH_PROP_SIZE : m_mouth_prop_size=a_val;break;
		case CardProperties::MOUTH_PROP_EXPR : m_mouth_prop_expr=a_val;break;		
	}
}

CardProperties::SKIN_PROP_VALUES 
CardProperties::getNoseProperties(CardProperties::SKIN_PROP a_prop)
{
	switch (a_prop)
	{
		case CardProperties::SKIN_PROP_COLOR    : return m_skin_prop_color;   break;
	}
}	

void 
CardProperties::setNoseProperties(CardProperties::SKIN_PROP_VALUES a_val, CardProperties::SKIN_PROP a_prop )
{
	switch (a_prop)
	{
		case CardProperties::SKIN_PROP_COLOR    : m_skin_prop_color = a_val;   break;
	}
}

CardProperties::SEX_PROP_VALUES
CardProperties::getSex()
{
	return m_sex;
}

void 
CardProperties::setSex(CardProperties::SEX_PROP_VALUES a_val)
{
	m_sex = a_val;
}	


CardProperties::OTHER_PROP_VALUES 
CardProperties::getOtherProperties()
{
	return m_other_prop;
}

void 
CardProperties::setOtherProperties(CardProperties::OTHER_PROP_VALUES a_val)
{
	m_other_prop = a_val;
}

bool CardProperties::hasOtherProperties(CardProperties::OTHER_PROP_VALUES a_val)
{
	return ( (getOtherProperties() & a_val) != 0);
}

