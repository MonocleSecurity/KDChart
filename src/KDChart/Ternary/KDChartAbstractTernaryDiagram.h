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

#ifndef KDCHARTABSTRACTTERNARYDIAGRAM_H
#define KDCHARTABSTRACTTERNARYDIAGRAM_H

#include "KDChartAbstractDiagram.h"
#include "KDChartTernaryAxis.h"

namespace KDChart {

class TernaryCoordinatePlane;
class TernaryAxis;

/**
      * @brief Base class for diagrams based on a ternary coordinate plane.
      */
class KDCHART_EXPORT AbstractTernaryDiagram : public AbstractDiagram
{
    Q_OBJECT
    Q_DISABLE_COPY(AbstractTernaryDiagram)
    KDCHART_DECLARE_DERIVED_DIAGRAM(AbstractTernaryDiagram,
                                    TernaryCoordinatePlane)

public:
    explicit AbstractTernaryDiagram(QWidget *parent = nullptr,
                                    TernaryCoordinatePlane *plane = nullptr);
    ~AbstractTernaryDiagram() override;

    void resize(const QSizeF &area) override = 0;
    void paint(PaintContext *paintContext) override;

    virtual void addAxis(TernaryAxis *axis);
    virtual void takeAxis(TernaryAxis *axis);
    virtual TernaryAxisList axes() const;

protected:
    const QPair<QPointF, QPointF> calculateDataBoundaries() const override = 0;
};

}

#endif
