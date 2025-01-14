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

#ifndef KDCHART_STOCK_DIAGRAM_H
#define KDCHART_STOCK_DIAGRAM_H

#include "KDChartAbstractCartesianDiagram.h"
#include "KDChartCartesianCoordinatePlane.h"
#include "KDChartStockBarAttributes.h"
#include "KDChartThreeDBarAttributes.h"

namespace KDChart {
class PaintContext;

class KDCHART_EXPORT StockDiagram : public AbstractCartesianDiagram
{
    Q_OBJECT

    Q_DISABLE_COPY(StockDiagram)

    KDCHART_DECLARE_DERIVED_DIAGRAM(StockDiagram, CartesianCoordinatePlane)

public:
    enum Type {
        HighLowClose,
        OpenHighLowClose,
        Candlestick
    };

    explicit StockDiagram(QWidget *parent = nullptr, CartesianCoordinatePlane *plane = nullptr);
    ~StockDiagram() override;

    void setType(Type type);
    Type type() const;

    void setStockBarAttributes(const StockBarAttributes &attr);
    StockBarAttributes stockBarAttributes() const;

    void setStockBarAttributes(int column, const StockBarAttributes &attr);
    StockBarAttributes stockBarAttributes(int column) const;

    void setThreeDBarAttributes(const ThreeDBarAttributes &attr);
    ThreeDBarAttributes threeDBarAttributes() const;

    void setThreeDBarAttributes(int column, const ThreeDBarAttributes &attr);
    ThreeDBarAttributes threeDBarAttributes(int column) const;

    void setLowHighLinePen(const QPen &pen);
    QPen lowHighLinePen() const;

    void setLowHighLinePen(int column, const QPen &pen);
    QPen lowHighLinePen(int column) const;

    void setUpTrendCandlestickBrush(const QBrush &brush);
    QBrush upTrendCandlestickBrush() const;

    void setDownTrendCandlestickBrush(const QBrush &brush);
    QBrush downTrendCandlestickBrush() const;

    void setUpTrendCandlestickBrush(int column, const QBrush &brush);
    QBrush upTrendCandlestickBrush(int column) const;

    void setDownTrendCandlestickBrush(int column, const QBrush &brush);
    QBrush downTrendCandlestickBrush(int column) const;

    void setUpTrendCandlestickPen(const QPen &pen);
    QPen upTrendCandlestickPen() const;

    void setDownTrendCandlestickPen(const QPen &pen);
    QPen downTrendCandlestickPen() const;

    void setUpTrendCandlestickPen(int column, const QPen &pen);
    QPen upTrendCandlestickPen(int column) const;

    void setDownTrendCandlestickPen(int column, const QPen &pen);
    QPen downTrendCandlestickPen(int column) const;

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0) && defined(Q_COMPILER_MANGLES_RETURN_TYPE)
    virtual const int numberOfAbscissaSegments() const;
    virtual const int numberOfOrdinateSegments() const;
#else
    int numberOfAbscissaSegments() const override;
    int numberOfOrdinateSegments() const override;
#endif

    void paint(PaintContext *paintContext) override;

    void resize(const QSizeF &size) override;

    qreal threeDItemDepth(int column) const override;
    qreal threeDItemDepth(const QModelIndex &index) const override;

protected:
    const QPair<QPointF, QPointF> calculateDataBoundaries() const override;
};

} // Namespace KDChart

#endif // KDCHART_STOCK_DIAGRAM_H
