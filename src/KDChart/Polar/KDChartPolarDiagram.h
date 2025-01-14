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

#ifndef KDCHARTPOLARDIAGRAM_H
#define KDCHARTPOLARDIAGRAM_H

#include "KDChartPosition.h"
#include "KDChartAbstractPolarDiagram.h"

QT_BEGIN_NAMESPACE
class QPolygonF;
QT_END_NAMESPACE

namespace KDChart {

/**
  * @brief PolarDiagram defines a common polar diagram
  */
class KDCHART_EXPORT PolarDiagram : public AbstractPolarDiagram
{
    Q_OBJECT

    Q_DISABLE_COPY(PolarDiagram)
    KDCHART_DECLARE_DERIVED_DIAGRAM(PolarDiagram, PolarCoordinatePlane)

public:
    explicit PolarDiagram(
        QWidget *parent = nullptr, PolarCoordinatePlane *plane = nullptr);
    ~PolarDiagram() override;

protected:
    // Implement AbstractDiagram
    /** \reimpl */
    void paint(PaintContext *paintContext) override;

public:
    /** \reimpl */
    void resize(const QSizeF &area) override;

    // Implement AbstractPolarDiagram
    /** \reimpl */
    qreal valueTotals() const override;
    /** \reimpl */
    qreal numberOfValuesPerDataset() const override;
    /** \reimpl */
    qreal numberOfGridRings() const override;

    virtual PolarDiagram *clone() const;

    /** \deprecated Use PolarCoordinatePlane::setStartPosition( qreal degrees ) instead. */
    void setZeroDegreePosition(int degrees);
    /** \deprecated Use qreal PolarCoordinatePlane::startPosition instead. */
    int zeroDegreePosition() const;

    void setRotateCircularLabels(bool rotateCircularLabels);
    bool rotateCircularLabels() const;

    /** Close each of the data series by connecting the last point to its
     * respective start point
     */
    void setCloseDatasets(bool closeDatasets);
    bool closeDatasets() const;

    void setShowDelimitersAtPosition(Position position,
                                     bool showDelimiters);
    void setShowLabelsAtPosition(Position position,
                                 bool showLabels);

    bool showDelimitersAtPosition(Position position) const;

    bool showLabelsAtPosition(Position position) const;

    virtual void paint(PaintContext *paintContext,
                       bool calculateListAndReturnScale,
                       qreal &newZoomX, qreal &newZoomY); // KDChart 3: references -> pointers

protected:
    /** \reimpl */
    const QPair<QPointF, QPointF> calculateDataBoundaries() const override;
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *) override;
    virtual void paintPolarMarkers(PaintContext *ctx, const QPolygonF &polygon);

}; // End of class PolarDiagram

}

#endif // KDCHARTPOLARDIAGRAM_H
