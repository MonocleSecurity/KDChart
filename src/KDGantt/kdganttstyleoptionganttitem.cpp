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

#include "kdganttstyleoptionganttitem.h"

using namespace KDGantt;

/*!\class KDGantt::StyleOptionGanttItem kdganttstyleoptionganttitem.h KDGanttStyleOptionGanttItem
 * \ingroup KDGantt
 * \brief QStyleOption subclass for gantt items.
 */

typedef QStyleOptionViewItem BASE;

/*! Constructor. Sets grid to 0. */
StyleOptionGanttItem::StyleOptionGanttItem()
    : BASE()
    , displayPosition(Left)
    , grid(nullptr)
{
    type = QStyleOption::SO_CustomBase + 89;
    version = 1;
}

/*! Copy constructor. Creates a copy of \a other */
StyleOptionGanttItem::StyleOptionGanttItem(const StyleOptionGanttItem &other)
    : BASE(other)
{
    operator=(other);
}

/*! Assignment operator */
StyleOptionGanttItem &StyleOptionGanttItem::operator=(const StyleOptionGanttItem &other)
{
    BASE::operator=(other);
    boundingRect = other.boundingRect;
    itemRect = other.itemRect;
    displayPosition = other.displayPosition;
    grid = other.grid;
    text = other.text;
    return *this;
}

#ifndef QT_NO_DEBUG_STREAM
QDebug operator<<(QDebug dbg, KDGantt::StyleOptionGanttItem::Position p)
{
    switch (p) {
    case KDGantt::StyleOptionGanttItem::Left:
        dbg << "KDGantt::StyleOptionGanttItem::Left";
        break;
    case KDGantt::StyleOptionGanttItem::Right:
        dbg << "KDGantt::StyleOptionGanttItem::Right";
        break;
    case KDGantt::StyleOptionGanttItem::Center:
        dbg << "KDGantt::StyleOptionGanttItem::Center";
        break;
    case KDGantt::StyleOptionGanttItem::Hidden:
        dbg << "KDGantt::StyleOptionGanttItem::Hidden";
        break;
    default:
        dbg << static_cast<int>(p);
    }
    return dbg;
}

QDebug operator<<(QDebug dbg, const KDGantt::StyleOptionGanttItem &s)
{
    dbg << "KDGantt::StyleOptionGanttItem[ boundingRect=" << s.boundingRect
        << ", itemRect=" << s.itemRect
        << ", displayPosition=" << s.displayPosition
        << ", grid=" << s.grid
        << ", text=" << s.text
        << "]";
    return dbg;
}

#endif /* QT_NO_DEBUG_STREAM */

/*!\enum KDGantt::StyleOptionGanttItem::Position
 * This enum is used to describe where the Qt::DisplayRole
 * (the label) should be located relative to the item itself.
 */

/*!\var StyleOptionGanttItem::boundingRect
 * Contains the bounding rectangle for the item
 */

/*!\var StyleOptionGanttItem::itemRect
 * Contains the "active" item rectangle that corresponds
 * to the values from the model.
 */

/*!\var StyleOptionGanttItem::displayPosition
 * \see StyleOptionGanttItem::Position.
 */

/*!\var StyleOptionGanttItem::grid
 * Contains a pointer to the AbstractGrid used by the view
 */

/*!\var StyleOptionGanttItem::text
 * Contains a string printed to the item
 */
