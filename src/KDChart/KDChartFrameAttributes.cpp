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

#include "KDChartFrameAttributes.h"

#include <KDABLibFakes>

#define d d_func()

using namespace KDChart;

class FrameAttributes::Private
{
    friend class FrameAttributes;

public:
    Private();

private:
    bool visible;
    QPen pen;
    qreal cornerRadius;
    int padding;
};

FrameAttributes::Private::Private()
    : visible(false)
    , cornerRadius(0)
    , padding(0)
{
}

FrameAttributes::FrameAttributes()
    : _d(new Private())
{
}

FrameAttributes::FrameAttributes(const FrameAttributes &r)
    : _d(new Private(*r.d))
{
}

FrameAttributes &FrameAttributes::operator=(const FrameAttributes &r)
{
    if (this == &r)
        return *this;

    *d = *r.d;

    return *this;
}

FrameAttributes::~FrameAttributes()
{
    delete _d;
    _d = nullptr;
}

bool FrameAttributes::operator==(const FrameAttributes &r) const
{
    return (isVisible() == r.isVisible() && pen() == r.pen() && cornerRadius() == r.cornerRadius() && padding() == r.padding());
}

void FrameAttributes::setVisible(bool visible)
{
    d->visible = visible;
}

bool FrameAttributes::isVisible() const
{
    return d->visible;
}

void FrameAttributes::setPen(const QPen &pen)
{
    d->pen = pen;
}

QPen FrameAttributes::pen() const
{
    return d->pen;
}

void FrameAttributes::setCornerRadius(qreal radius)
{
    d->cornerRadius = radius;
}

qreal FrameAttributes::cornerRadius() const
{
    return d->cornerRadius;
}

void FrameAttributes::setPadding(int padding)
{
    d->padding = padding;
}

int FrameAttributes::padding() const
{
    return d->padding;
}

#if !defined(QT_NO_DEBUG_STREAM)
QDebug operator<<(QDebug dbg, const KDChart::FrameAttributes &fa)
{
    dbg << "KDChart::FrameAttributes("
        << "visible=" << fa.isVisible()
        << "pen=" << fa.pen()
        << "cornerRadius=" << fa.cornerRadius()
        << "padding=" << fa.padding()
        << ")";
    return dbg;
}
#endif /* QT_NO_DEBUG_STREAM */
