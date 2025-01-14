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

#ifndef KDCHARTLEVEYJENNINGSAXIS_H
#define KDCHARTLEVEYJENNINGSAXIS_H

#include <QList>

#include "KDChartCartesianAxis.h"

#include "KDChartLeveyJenningsGridAttributes.h"

namespace KDChart {

class LeveyJenningsDiagram;

/**
      * The class for levey jennings axes.
      *
      * For being useful, axes need to be assigned to a diagram, see
      * LeveyJenningsDiagram::addAxis and LeveyJenningsDiagram::takeAxis.
      *
      * \sa PolarAxis, AbstractCartesianDiagram
      */
class KDCHART_EXPORT LeveyJenningsAxis : public CartesianAxis
{
    Q_OBJECT

    Q_DISABLE_COPY(LeveyJenningsAxis)
    KDCHART_DECLARE_PRIVATE_DERIVED_PARENT(LeveyJenningsAxis, AbstractDiagram *)

public:
    /**
          * C'tor of the class for levey jennings axes.
          *
          * \note If using a zero parent for the constructor, you need to call
          * your diagram's addAxis function to add your axis to the diagram.
          * Otherwise, there is no need to call addAxis, since the constructor
          * does that automatically for you, if you pass a diagram as parameter.
          *
          * \sa AbstractCartesianDiagram::addAxis
          */
    explicit LeveyJenningsAxis(LeveyJenningsDiagram *diagram = nullptr);
    ~LeveyJenningsAxis() override;

    LeveyJenningsGridAttributes::GridType type() const;
    void setType(LeveyJenningsGridAttributes::GridType type);

    Qt::DateFormat dateFormat() const;
    void setDateFormat(Qt::DateFormat format);

    /**
         * Returns true if both axes have the same settings.
         */
    bool compare(const LeveyJenningsAxis *other) const;

    /** reimpl */
    void paintCtx(PaintContext *) override;

protected:
    virtual void paintAsOrdinate(PaintContext *);

    virtual void paintAsAbscissa(PaintContext *);
};

typedef QList<LeveyJenningsAxis *> LeveyJenningsAxisList;
}

#endif
