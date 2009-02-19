#ifndef KHELPER_H
#define KHELPER_H

#include <QRectF>

namespace kHelper
{
	/*
		give a rect and x, y position and it will return values translated for point 0, 0 being the center of the rect, and increment x, y
		This allow to easy do this kind of thing so rotation, and scale does not need translations :
		original rect: 0, 0 510x510
		original x, y: 100, 100
		
		translated rect: -255, -255 510x510
		translated x, y: 355, 355
	*/
	QRectF translatedRect( const QRectF& rect );
	void translatedXY( const QRectF& rect, qreal& x, qreal& y );
	QRectF translatedRectXY( const QRectF& rect, qreal& x, qreal& y );
};

#endif // KHELPER_H
