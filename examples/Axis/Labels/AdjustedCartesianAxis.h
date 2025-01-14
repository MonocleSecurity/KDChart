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

#ifndef ADJUSTED_CARTESIAN_AXIS_H
#define ADJUSTED_CARTESIAN_AXIS_H

#include <KDChartCartesianAxis>
#include <KDChartGlobal>

class AdjustedCartesianAxis : public KDChart::CartesianAxis
{
    Q_OBJECT

    Q_DISABLE_COPY(AdjustedCartesianAxis)

public:
    explicit AdjustedCartesianAxis(KDChart::AbstractCartesianDiagram *diagram = nullptr);

    const QString customizedLabel(const QString &label) const override;

    void setBounds(qreal lower, qreal upper)
    {
        m_lowerBound = lower;
        m_upperBound = upper;
    }
    qreal lowerBound() const
    {
        return m_lowerBound;
    }
    qreal upperBound() const
    {
        return m_upperBound;
    }

private:
    qreal m_lowerBound;
    qreal m_upperBound;
};

#endif // ADJUSTED_CARTESIAN_AXIS_H
