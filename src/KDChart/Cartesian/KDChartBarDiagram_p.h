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

#ifndef KDCHARTBARDIAGRAM_P_H
#define KDCHARTBARDIAGRAM_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the KD Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "KDChartBarDiagram.h"

#include <QPainterPath>

#include "KDChartAbstractCartesianDiagram_p.h"
#include "KDChartThreeDBarAttributes.h"

#include <KDABLibFakes>

namespace KDChart {

class PaintContext;

/**
 * \internal
 */
class BarDiagram::Private : public AbstractCartesianDiagram::Private
{
    friend class BarDiagram;
    friend class BarDiagramType;

public:
    Private();
    Private(const Private &rhs);
    ~Private() override;

    void setOrientationAndType(Qt::Orientation, BarDiagram::BarType);

    Qt::Orientation orientation;

    BarDiagramType *implementor; // the current type
    BarDiagramType *normalDiagram;
    BarDiagramType *stackedDiagram;
    BarDiagramType *percentDiagram;
    BarDiagramType *normalLyingDiagram;
    BarDiagramType *stackedLyingDiagram;
    BarDiagramType *percentLyingDiagram;
};

KDCHART_IMPL_DERIVED_DIAGRAM(BarDiagram, AbstractCartesianDiagram, CartesianCoordinatePlane)

class BarDiagram::BarDiagramType
{
public:
    explicit BarDiagramType(BarDiagram *d)
        : m_private(d->d_func())
    {
    }
    virtual ~BarDiagramType()
    {
    }
    virtual BarDiagram::BarType type() const = 0;
    virtual const QPair<QPointF, QPointF> calculateDataBoundaries() const = 0;
    virtual void paint(PaintContext *ctx) = 0;
    BarDiagram *diagram() const;

protected:
    // make some elements of m_private available to derived classes:
    AttributesModel *attributesModel() const;
    QModelIndex attributesModelRootIndex() const;
    ReverseMapper &reverseMapper();
    CartesianDiagramDataCompressor &compressor() const;

    void paintBars(PaintContext *ctx, const QModelIndex &index, const QRectF &bar, qreal maxDepth);
    void calculateValueAndGapWidths(int rowCount, int colCount,
                                    qreal groupWidth,
                                    qreal &barWidth,
                                    qreal &spaceBetweenBars,
                                    qreal &spaceBetweenGroups);

    BarDiagram::Private *m_private;
};
}

#endif /* KDCHARTBARDIAGRAM_P_H */
