/****************************************************************************
**
** This file is part of the KD Chart library.
**
** SPDX-FileCopyrightText: 2001-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
**
** SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDAB-KDChart OR LicenseRef-KDAB-KDChart-US
**
** Licensees holding valid commercial KD Chart licenses may use this file in
** accordance with the KD Chart Commercial License Agreement provided with
** the Software.
**
** Contact info@kdab.com if any conditions of this licensing are not
** clear to you.
**
****************************************************************************/

#include "KDChartBackgroundAttributes.h"
#include <QPixmap>

#include <KDABLibFakes>

#define d d_func()

using namespace KDChart;

class BackgroundAttributes::Private
{
    friend class KDChart::BackgroundAttributes;

public:
    Private();

private:
    bool visible;
    QBrush brush;
    BackgroundPixmapMode pixmapMode;
    QPixmap pixmap;
};

BackgroundAttributes::Private::Private()
    : visible(false)
    , pixmapMode(BackgroundAttributes::BackgroundPixmapModeNone)
{
}

BackgroundAttributes::BackgroundAttributes()
    : _d(new Private())
{
}

BackgroundAttributes::BackgroundAttributes(const BackgroundAttributes &r)
    : _d(new Private(*r.d))
{
}

BackgroundAttributes &BackgroundAttributes::operator=(const BackgroundAttributes &r)
{
    if (this == &r)
        return *this;

    *d = *r.d;

    return *this;
}

bool BackgroundAttributes::operator==(const BackgroundAttributes &r) const
{
    return isEqualTo(r);
}

bool BackgroundAttributes::isEqualTo(
    const BackgroundAttributes &other, bool ignorePixmap) const
{
    /*
    qDebug() << "BackgroundAttributes::operator==";
    qDebug() << "isVisible" << (isVisible() == other.isVisible());
    qDebug() << "brush"     << (brush() == other.brush());
    qDebug() << "pixmapMode"<< (pixmapMode() == other.pixmapMode());
    qDebug() << "pixmap"    << (pixmap().serialNumber() == other.pixmap().serialNumber());
    */
    return (
        isVisible() == other.isVisible() && brush() == other.brush() && pixmapMode() == other.pixmapMode() && (ignorePixmap || pixmap().cacheKey() == other.pixmap().cacheKey()));
}

BackgroundAttributes::~BackgroundAttributes()
{
    delete _d;
    _d = nullptr;
}

void BackgroundAttributes::setVisible(bool visible)
{
    d->visible = visible;
}

bool BackgroundAttributes::isVisible() const
{
    return d->visible;
}

void BackgroundAttributes::setBrush(const QBrush &brush)
{
    d->brush = brush;
}

QBrush BackgroundAttributes::brush() const
{
    return d->brush;
}

void BackgroundAttributes::setPixmapMode(BackgroundPixmapMode mode)
{
    d->pixmapMode = mode;
}

BackgroundAttributes::BackgroundPixmapMode BackgroundAttributes::pixmapMode() const
{
    return d->pixmapMode;
}

void BackgroundAttributes::setPixmap(const QPixmap &backPixmap)
{
    d->pixmap = backPixmap;
}

QPixmap BackgroundAttributes::pixmap() const
{
    return d->pixmap;
}

#if !defined(QT_NO_DEBUG_STREAM)
QDebug operator<<(QDebug dbg, const KDChart::BackgroundAttributes &ba)
{
    dbg << "KDChart::BackgroundAttributes("
        << "visible=" << ba.isVisible()
        << "brush=" << ba.brush()
        << "pixmapmode=" << ba.pixmapMode()
        << "pixmap=" << ba.pixmap().cacheKey()
        << ")";
    return dbg;
}
#endif /* QT_NO_DEBUG_STREAM */
