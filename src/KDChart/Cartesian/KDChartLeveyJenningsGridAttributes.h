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

#ifndef KDCHARTLEVEYJENNINGSGRIDATTRIBUTES_H
#define KDCHARTLEVEYJENNINGSGRIDATTRIBUTES_H

#include <QMetaType>
#include "KDChartGlobal.h"
#include "KDChartEnums.h"

QT_BEGIN_NAMESPACE
class QPen;
QT_END_NAMESPACE

namespace KDChart {

/**
  * @brief A set of attributes controlling the appearance of grids
  */
class KDCHART_EXPORT LeveyJenningsGridAttributes
{
public:
    LeveyJenningsGridAttributes();
    LeveyJenningsGridAttributes(const LeveyJenningsGridAttributes &);
    LeveyJenningsGridAttributes &operator=(const LeveyJenningsGridAttributes &);

    ~LeveyJenningsGridAttributes();

    enum GridType {
        Expected,
        Calculated
    };

    enum Range {
        NormalRange,
        CriticalRange,
        OutOfRange
    };

    void setGridVisible(GridType type, bool visible);
    bool isGridVisible(GridType type) const;

    void setGridPen(GridType type, const QPen &pen);
    QPen gridPen(GridType type) const;

    void setRangeBrush(Range range, const QBrush &brush);
    QBrush rangeBrush(Range range) const;

    bool operator==(const LeveyJenningsGridAttributes &) const;
    inline bool operator!=(const LeveyJenningsGridAttributes &other) const
    {
        return !operator==(other);
    }

private:
    KDCHART_DECLARE_PRIVATE_BASE_VALUE(LeveyJenningsGridAttributes)
}; // End of class GridAttributes

}

KDCHART_DECLARE_SWAP_SPECIALISATION(KDChart::LeveyJenningsGridAttributes)

QT_BEGIN_NAMESPACE
Q_DECLARE_TYPEINFO(KDChart::LeveyJenningsGridAttributes, Q_MOVABLE_TYPE);
QT_END_NAMESPACE

Q_DECLARE_METATYPE(KDChart::LeveyJenningsGridAttributes)

#endif // KDCHARTLEVEYJENNINGSGRIDATTRIBUTES_H
