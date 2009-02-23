#include "CardProperties.h" 

CardProperties::CardProperties()
{
}


CardProperties::HAIR_PROP_VALUES CardProperties::getHairProperties(CardProperties::HAIR_PROP a_prop) const
{
	switch (a_prop)
	{
		case CardProperties::HAIR_PROP_COLOR : return m_hair_prop_color;break;
		case CardProperties::HAIR_PROP_SHAPE : return m_hair_prop_shape;break;		
	}
	return (CardProperties::HAIR_PROP_VALUES)0;
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
CardProperties::getEyesProperties(CardProperties::EYES_PROP a_prop) const
{
	switch (a_prop)
	{
		case CardProperties::EYES_PROP_COLOR    : return m_eyes_prop_color;   break;
		case CardProperties::EYES_PROP_EYEBROWS : return m_eyes_prop_eyebrows;break;		
	}
	return (CardProperties::EYES_PROP_VALUES)0;
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
CardProperties::getNoseProperties(CardProperties::NOSE_PROP a_prop) const
{
	switch (a_prop)
	{
		case CardProperties::NOSE_PROP_SIZE    : return m_nose_prop_size;   break;
	}
	return (CardProperties::NOSE_PROP_VALUES)0;
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
		CardProperties::getMouthProperties(CardProperties::MOUTH_PROP a_prop) const
{
	switch (a_prop)
	{
		case CardProperties::MOUTH_PROP_SIZE : return m_mouth_prop_size; break;
		case CardProperties::MOUTH_PROP_EXPR : return m_mouth_prop_expr; break;		
	}
	return (CardProperties::MOUTH_PROP_VALUES)0;
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
CardProperties::getSkinProperties(CardProperties::SKIN_PROP a_prop) const
{
	switch (a_prop)
	{
		case CardProperties::SKIN_PROP_COLOR    : return m_skin_prop_color;   break;
	}
	return (CardProperties::SKIN_PROP_VALUES)0;
}	

void 
CardProperties::setSkinProperties(CardProperties::SKIN_PROP_VALUES a_val, CardProperties::SKIN_PROP a_prop )
{
	switch (a_prop)
	{
		case CardProperties::SKIN_PROP_COLOR    : m_skin_prop_color = a_val;   break;
	}
}

CardProperties::SEX_PROP_VALUES
CardProperties::getSex() const
{
	return m_sex;
}

void 
CardProperties::setSex(CardProperties::SEX_PROP_VALUES a_val)
{
	m_sex = a_val;
}	


CardProperties::OTHER_PROP_VALUES 
CardProperties::getOtherProperties() const
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
 CardProperties::HAIR_PROP_VALUES CardProperties::string2HairProp(const QString& a_string)
{
	if(a_string == "BLONDE")
		return CardProperties::HAIR_PROP_COLOR_BLONDE;
	else
	if(a_string == "BROWN")
		return CardProperties::HAIR_PROP_COLOR_BROWN ;
	else
	if(a_string == "BLACK")
		return CardProperties::HAIR_PROP_COLOR_BLACK;
	else
	if(a_string == "RED")
		return CardProperties::HAIR_PROP_COLOR_RED;
		
	else
	if(a_string == "STRAIGHT")
		return CardProperties::HAIR_PROP_SHAPE_STRAIGHT;
	else
	if(a_string == "WAVY")
		return CardProperties::HAIR_PROP_SHAPE_WAVY;
	else
	if(a_string == "FRIZZY")
		return CardProperties::HAIR_PROP_SHAPE_FRIZZY;
	else
	if(a_string == "LONG")
		return CardProperties::HAIR_PROP_SHAPE_LONG;
	else
	if(a_string == "SHORT")
		return CardProperties::HAIR_PROP_SHAPE_SHORT;
}

CardProperties::EYES_PROP_VALUES CardProperties::string2EyesProp(const QString& a_string)
{
	if(a_string == "BROWN")
		return CardProperties::EYES_PROP_COLOR_BROWN;
	else
	if(a_string == "GREEN")
		return CardProperties::EYES_PROP_COLOR_GREEN;
	else
	if(a_string == "BLUE")
		return CardProperties::EYES_PROP_COLOR_BLUE;
		
	else
	if(a_string == "THIN")
		return CardProperties::EYES_PROP_EYEBROWS_THIN;
	else
	if(a_string == "NORMAL")
		return CardProperties::EYES_PROP_EYEBROWS_NORMAL;
	else
	if(a_string == "HUGE")
		return CardProperties::EYES_PROP_EYEBROWS_HUGE;
}
		 
CardProperties::NOSE_PROP_VALUES CardProperties::string2NoseProp(const QString& a_string)
{
	if(a_string == "SMALL")
		return CardProperties::NOSE_PROP_SIZE_SMALL;
	else
	if(a_string == "MEDIUM")
		NOSE_PROP_SIZE_MEDIUM;
	else
	if(a_string == "BIG")
		NOSE_PROP_SIZE_BIG;
}
		 
CardProperties::MOUTH_PROP_VALUES CardProperties::string2MouthProp(const QString& a_string)
{
	if(a_string == "SMALL")
		return CardProperties::MOUTH_PROP_SIZE_SMALL;
	else
	if(a_string == "MEDIUM")
		return CardProperties::MOUTH_PROP_SIZE_MEDIUM;
	else
	if(a_string == "BIG")
		return CardProperties::MOUTH_PROP_SIZE_BIG;
		
	else
	if(a_string == "SMILE")
		return CardProperties::MOUTH_PROP_EXPR_SMILE;
	else
	if(a_string == "NONE")
		return CardProperties::MOUTH_PROP_EXPR_NONE;
	else
	if(a_string == "SAD")
		return CardProperties::MOUTH_PROP_EXPR_SAD;
}
		 
CardProperties::SKIN_PROP_VALUES CardProperties::string2SkinProp(const QString& a_string)
{
	if(a_string == "WHITE")
		return CardProperties::SKIN_PROP_COLOR_WHITE;
	else
	if(a_string == "BLACK")
		return CardProperties::SKIN_PROP_COLOR_BLACK;
	else
	if(a_string == "YELLOW")
		return CardProperties::SKIN_PROP_COLOR_YELLOW;
}
		 
CardProperties::SEX_PROP_VALUES CardProperties::string2SexProp(const QString& a_string)
{
	if(a_string == "FEMALE")
		return CardProperties::SEX_PROP_FEMALE;
	else
	if(a_string == "MALE")
		return CardProperties::SEX_PROP_MALE;
}
		 
CardProperties::OTHER_PROP_VALUES CardProperties::string2OtherProp(const QString& a_string)
{
	if(a_string == "MUSTACHE")
		return CardProperties::OTHER_PROP_MUSTACHE;
	else
	if(a_string == "BEARD")
		return CardProperties::OTHER_PROP_BEARD;
	else
	if(a_string == "GLASSES")
		return CardProperties::OTHER_PROP_GLASSES;
	else
	if(a_string == "HAT")
		return CardProperties::OTHER_PROP_HAT;
	else
	if(a_string == "NECKLACE")
		return CardProperties::OTHER_PROP_NECKLACE;
}
		 
//-----------------------------------------------------------------------------
QString CardProperties::toString() const
{
	return QString(
		" hair  : %1 %2,\n"
		" Eyes  : %3 %4,\n"
		" Nose  : %5,\n"
		" Mouth : %6 %7,\n"
		" Skin  : %8 ,\n"
		" Sex   : %9 ,\n"
		" Other : %10 \n"
	)
		.arg((int)getHairProperties(HAIR_PROP_COLOR), 2, 16)
		.arg((int)getHairProperties(HAIR_PROP_SHAPE), 2, 16)
		
		.arg((int)getEyesProperties(EYES_PROP_COLOR), 2, 16)
		.arg((int)getEyesProperties(EYES_PROP_EYEBROWS), 2, 16)
		
		.arg((int)getNoseProperties(NOSE_PROP_SIZE), 2, 16)
		
		.arg((int)getMouthProperties(MOUTH_PROP_SIZE), 2, 16)
		.arg((int)getMouthProperties(MOUTH_PROP_EXPR), 2, 16)
		
		.arg((int)getSkinProperties(), 2, 16)
		
		.arg((int)getSex(), 2, 16)
		
		.arg((int)getOtherProperties(), 2, 16)
		;
}





