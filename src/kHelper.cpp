#include "kHelper.h"

QRectF kHelper::translatedRect( const QRectF& rect )
{
	QSizeF size = rect.size() /2;
	QRectF r = rect;
	r.moveTopLeft( QPointF( -size.width(), -size.height() ) );
	return r;
}

void kHelper::translatedXY( const QRectF& rect, qreal& x, qreal& y )
{
	QSizeF size = rect.size() /2;
	x += size.width();
	y += size.height();
}

QRectF kHelper::translatedRectXY( const QRectF& rect, qreal& x, qreal& y )
{
	QSizeF size = rect.size() /2;
	QRectF r = rect;
	r.moveTopLeft( QPointF( -size.width(), -size.height() ) );
	x += size.width();
	y += size.height();
	return r;
}
