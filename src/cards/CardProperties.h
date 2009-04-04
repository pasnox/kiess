#ifndef CARDPROPERTIES_H
#define CARDPROPERTIES_H

#include <QString>
class CardProperties
{
	public:
	
	enum HAIR_PROP 
	{
		HAIR_PROP_COLOR, 
		HAIR_PROP_SHAPE
	};
	enum HAIR_PROP_VALUES 
	{
		HAIR_PROP_COLOR_NONE     = 0x00000000, 
		HAIR_PROP_COLOR_BLONDE   = 0x00000001, 
		HAIR_PROP_COLOR_BROWN    = 0x00000002,
		HAIR_PROP_COLOR_BLACK    = 0x00000004, 
		HAIR_PROP_COLOR_RED      = 0x00000008,
		
		HAIR_PROP_SHAPE_STRAIGHT = 0x00000010, 
		HAIR_PROP_SHAPE_WAVY     = 0x00000020, 
		HAIR_PROP_SHAPE_CURLY    = 0x00000040, 
		HAIR_PROP_SHAPE_LONG     = 0x00000080, 
		HAIR_PROP_SHAPE_SHORT    = 0x00000100
	};
	//------------------------------------------------------------------------
	enum EYES_PROP 
	{
		EYES_PROP_COLOR,
		EYES_PROP_EYEBROWS
	};
	
	enum EYES_PROP_VALUES
	{
		EYES_PROP_COLOR_BROWN     = 0x00000001, 
		EYES_PROP_COLOR_GREEN     = 0x00000002, 
		EYES_PROP_COLOR_BLUE      = 0x00000004,
		
		EYES_PROP_EYEBROWS_THIN   = 0x00000008,
		EYES_PROP_EYEBROWS_NORMAL = 0x00000010,
		EYES_PROP_EYEBROWS_HUGE   = 0x00000020
	};
	//------------------------------------------------------------------------
	enum NOSE_PROP
	{
		NOSE_PROP_SIZE
	};
	
	enum NOSE_PROP_VALUES
	{
		NOSE_PROP_SIZE_SMALL = 0x00000001,
		NOSE_PROP_SIZE_MEDIUM,
		NOSE_PROP_SIZE_BIG
	};
	
	//------------------------------------------------------------------------
	enum MOUTH_PROP
	{
		MOUTH_PROP_SIZE,
		MOUTH_PROP_EXPR
	};
	
	enum MOUTH_PROP_VALUES
	{
		MOUTH_PROP_SIZE_SMALL   = 0x00000001,
		MOUTH_PROP_SIZE_MEDIUM  = 0x00000002,
		MOUTH_PROP_SIZE_BIG     = 0x00000004,
		
		MOUTH_PROP_EXPR_SMILE   = 0x00000008,
		MOUTH_PROP_EXPR_NONE    = 0x00000010,
		MOUTH_PROP_EXPR_SAD     = 0x00000020
	};

	
	//------------------------------------------------------------------------
	enum SKIN_PROP
	{
		SKIN_PROP_COLOR
	};
	
	enum SKIN_PROP_VALUES
	{
		SKIN_PROP_COLOR_WHITE = 0x00000001,
		SKIN_PROP_COLOR_BLACK,
		SKIN_PROP_COLOR_YELLOW
	};

	//------------------------------------------------------------------------
	enum SEX_PROP_VALUES
	{
		SEX_PROP_FEMALE = 0x00000001,
		SEX_PROP_MALE
	};
	
	//------------------------------------------------------------------------
	enum OTHER_PROP_VALUES
	{
		OTHER_PROP_MUSTACHE = 0x00000001,
		OTHER_PROP_BEARD    = 0x00000002,
		OTHER_PROP_GLASSES  = 0x00000004,
		OTHER_PROP_HAT      = 0x00000008,
		OTHER_PROP_NECKLACE = 0x00000010,
		OTHER_PROP_EARRING  = 0x00000020
	};
	
	//------------------------------------------------------------------------
	public :
		CardProperties();
		
		HAIR_PROP_VALUES getHairProperties(HAIR_PROP a_prop) const;
		void setHairProperties(HAIR_PROP_VALUES a_val, HAIR_PROP a_prop);
		
		EYES_PROP_VALUES getEyesProperties(EYES_PROP a_prop) const;
		void setEyesProperties(EYES_PROP_VALUES a_val, EYES_PROP a_prop);
	
		NOSE_PROP_VALUES getNoseProperties(NOSE_PROP a_prop = NOSE_PROP_SIZE) const;
		void setNoseProperties(NOSE_PROP_VALUES a_val, NOSE_PROP a_prop = NOSE_PROP_SIZE);
	
		MOUTH_PROP_VALUES getMouthProperties(MOUTH_PROP a_prop) const;
		void setMouthProperties(MOUTH_PROP_VALUES a_val, MOUTH_PROP a_prop);
	
		SKIN_PROP_VALUES getSkinProperties(SKIN_PROP a_prop = SKIN_PROP_COLOR) const;
		void setSkinProperties(SKIN_PROP_VALUES a_val, SKIN_PROP a_prop = SKIN_PROP_COLOR);
	
		SEX_PROP_VALUES getSex() const;
		void setSex(SEX_PROP_VALUES a_val);
	
		OTHER_PROP_VALUES getOtherProperties() const;
		void setOtherProperties(OTHER_PROP_VALUES a_val);
		bool hasOtherProperties(OTHER_PROP_VALUES a_val);
		
		//---------------------------------------------------------------------
		static HAIR_PROP_VALUES string2HairProp(const QString& a_string);
		static EYES_PROP_VALUES string2EyesProp(const QString& a_string);
		static NOSE_PROP_VALUES string2NoseProp(const QString& a_string);
		static MOUTH_PROP_VALUES string2MouthProp(const QString& a_string);
		static SKIN_PROP_VALUES string2SkinProp(const QString& a_string);
		static SEX_PROP_VALUES string2SexProp(const QString& a_string);
		static OTHER_PROP_VALUES string2OtherProp(const QString& a_string);

		//---------------------------------------------------------------------
		QString toString() const;

		
	private:
		HAIR_PROP_VALUES 
				m_hair_prop_color,
				m_hair_prop_shape;
			
		EYES_PROP_VALUES
				m_eyes_prop_color,
				m_eyes_prop_eyebrows;
				
		NOSE_PROP_VALUES 
				m_nose_prop_size;
		
		MOUTH_PROP_VALUES
				m_mouth_prop_size,
				m_mouth_prop_expr;
				
		SKIN_PROP_VALUES
				m_skin_prop_color;
	
		SEX_PROP_VALUES
				m_sex;
		
		OTHER_PROP_VALUES
				m_other_prop;
};
#endif // CARDPROPERTIES_H
