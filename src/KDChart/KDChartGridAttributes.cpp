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

#include "KDChartGridAttributes.h"

#include <QPen>
#include <QDebug>

#include <KDABLibFakes>

#define d d_func()

using namespace KDChart;

class GridAttributes::Private
{
    friend class GridAttributes;

public:
    Private();

private:
    bool visible;
    KDChartEnums::GranularitySequence sequence;
    bool linesOnAnnotations;
    qreal stepWidth;
    qreal subStepWidth;
    bool adjustLower;
    bool adjustUpper;
    QPen pen;
    bool subVisible;
    QPen subPen;
    bool outerVisible;
    QPen zeroPen;
};

GridAttributes::Private::Private()
    : visible(true)
    , sequence(KDChartEnums::GranularitySequence_10_20)
    , linesOnAnnotations(false)
    , stepWidth(0.0)
    , subStepWidth(0.0)
    , adjustLower(true)
    , adjustUpper(true)
    , pen(QColor(0xa0, 0xa0, 0xa0))
    , subVisible(true)
    , subPen(QColor(0xd0, 0xd0, 0xd0))
    , outerVisible(true)
    , zeroPen(QColor(0x00, 0x00, 0x80))
{
    pen.setCapStyle(Qt::FlatCap);
    subPen.setCapStyle(Qt::FlatCap);
    zeroPen.setCapStyle(Qt::FlatCap);
}

GridAttributes::GridAttributes()
    : _d(new Private())
{
    // this block left empty intentionally
}

GridAttributes::GridAttributes(const GridAttributes &r)
    : _d(new Private(*r.d))
{
}

GridAttributes &GridAttributes::operator=(const GridAttributes &r)
{
    if (this == &r)
        return *this;

    *d = *r.d;

    return *this;
}

GridAttributes::~GridAttributes()
{
    delete _d;
    _d = nullptr;
}

bool GridAttributes::operator==(const GridAttributes &r) const
{
    return isGridVisible() == r.isGridVisible() && gridGranularitySequence() == r.gridGranularitySequence() && linesOnAnnotations() == r.linesOnAnnotations() && adjustLowerBoundToGrid() == r.adjustLowerBoundToGrid() && adjustUpperBoundToGrid() == r.adjustUpperBoundToGrid() && gridPen() == r.gridPen() && isSubGridVisible() == r.isSubGridVisible() && subGridPen() == r.subGridPen() && isOuterLinesVisible() == r.isOuterLinesVisible() && zeroLinePen() == r.zeroLinePen();
}

void GridAttributes::setGridVisible(bool visible)
{
    d->visible = visible;
}

bool GridAttributes::isGridVisible() const
{
    return d->visible;
}

void GridAttributes::setLinesOnAnnotations(bool b)
{
    d->linesOnAnnotations = b;
}

bool GridAttributes::linesOnAnnotations() const
{
    return d->linesOnAnnotations;
}

/**
  * Specifies the step width to be used for calculating
  * the grid lines.
  *
  * \note Step with can be set for Linear axis calculation mode only,
  * there is no way to specify a step width for Logarithmic axes.
  *
  * By default the GridAttributes class does not use a fixed step width,
  * but it uses KDChartEnums::GranularitySequence_10_20.
  *
  * \param stepWidth the step width to be used.
  * If this parameter is omitted (or set to Zero, resp.)
  * the automatic step width calculation will be done,
  * using the granularity sequence specified.
  * This is the default.
  *
  * \sa gridStepWidth, setGranularitySequence
  */
void GridAttributes::setGridStepWidth(qreal stepWidth)
{
    d->stepWidth = stepWidth;
}

/**
  * Returns the step width to be used for calculating
  * the grid lines.
  *
  * \sa setGridStepWidth
  */
qreal GridAttributes::gridStepWidth() const
{
    return d->stepWidth;
}

/**
  * Specifies the sub-step width to be used for calculating
  * the grid sub-lines.
  *
  *
  * \param subStepWidth the sub-step width to be used.
  * If this parameter is omitted (or set to Zero, resp.)
  * the automatic calculation will be done, using the
  * granularity sequence specified.
  * This is the default.
  *
  * \sa gridSubStepWidth
  */

void GridAttributes::setGridSubStepWidth(qreal subStepWidth)
{
    d->subStepWidth = subStepWidth;
}

/**
  * Returns the sub-step width to be used for calculating
  * the sub-grid lines.
  *
  * \sa setGridStepWidth
  */
qreal GridAttributes::gridSubStepWidth() const
{
    return d->subStepWidth;
}

/**
  * Specifies the granularity sequence to be used for calculating
  * the grid lines.
  *
  * By default the GridAttributes class uses KDChartEnums::GranularitySequence_10_20.
  *
  * \note Granularity can be set for Linear axis calculation mode only,
  * there is no way to specify a step width for Logarithmic axes.
  *
  * \note The sequence specified by this method is ignored, if
  * a fixed step width was specified via setStepWidth.
  *
  * \param sequence one of the sequences declared in
  * KDChartEnums::GranularitySequence.
  *
  * \sa gridGranularitySequence, setStepWidth
  */
void GridAttributes::setGridGranularitySequence(KDChartEnums::GranularitySequence sequence)
{
    d->sequence = sequence;
}

/**
  * Returns the granularity sequence to be used for calculating
  * the grid lines.
  *
  * \sa setGridGranularitySequence
  */
KDChartEnums::GranularitySequence GridAttributes::gridGranularitySequence() const
{
    return d->sequence;
}

void GridAttributes::setAdjustBoundsToGrid(bool adjustLower, bool adjustUpper)
{
    d->adjustLower = adjustLower;
    d->adjustUpper = adjustUpper;
}
bool GridAttributes::adjustLowerBoundToGrid() const
{
    return d->adjustLower;
}
bool GridAttributes::adjustUpperBoundToGrid() const
{
    return d->adjustUpper;
}

void GridAttributes::setGridPen(const QPen &pen)
{
    d->pen = pen;
    d->pen.setCapStyle(Qt::FlatCap);
}

QPen GridAttributes::gridPen() const
{
    return d->pen;
}

void GridAttributes::setSubGridVisible(bool visible)
{
    d->subVisible = visible;
}

bool GridAttributes::isSubGridVisible() const
{
    return d->subVisible;
}

void GridAttributes::setSubGridPen(const QPen &pen)
{
    d->subPen = pen;
    d->subPen.setCapStyle(Qt::FlatCap);
}

QPen GridAttributes::subGridPen() const
{
    return d->subPen;
}

void GridAttributes::setOuterLinesVisible(bool visible)
{
    d->outerVisible = visible;
}

bool GridAttributes::isOuterLinesVisible() const
{
    return d->outerVisible;
}

void GridAttributes::setZeroLinePen(const QPen &pen)
{
    d->zeroPen = pen;
    d->zeroPen.setCapStyle(Qt::FlatCap);
}

QPen GridAttributes::zeroLinePen() const
{
    return d->zeroPen;
}

#if !defined(QT_NO_DEBUG_STREAM)
QDebug operator<<(QDebug dbg, const KDChart::GridAttributes &a)
{
    dbg << "KDChart::GridAttributes("
        << "visible=" << a.isGridVisible()
        << "subVisible=" << a.isSubGridVisible()
        // KDChartEnums::GranularitySequence sequence;
        << "stepWidth=" << a.gridStepWidth()
        << "subStepWidth=" << a.gridSubStepWidth()
        << "pen=" << a.gridPen()
        << "subPen=" << a.subGridPen()
        << "zeroPen=" << a.zeroLinePen()
        << ")";
    return dbg;
}
#endif /* QT_NO_DEBUG_STREAM */
