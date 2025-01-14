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

#ifndef PLOTTERDIAGRAMCOMPRESSOR_P_H
#define PLOTTERDIAGRAMCOMPRESSOR_P_H

#include "KDChartPlotterDiagramCompressor.h"

#include <QtCore/QPointF>
#include <QtCore/QDateTime>

typedef QPair<QPointF, QPointF> Boundaries;

namespace KDChart {

class PlotterDiagramCompressor::Private : public QObject
{
    Q_OBJECT
public:
    Private(PlotterDiagramCompressor *parent);
    QModelIndexList mapToModel(const CachePosition &pos);
    void calculateDataBoundaries();
    void setBoundaries(const Boundaries &bound);
    bool forcedBoundaries(Qt::Orientation orient) const;
    bool inBoundaries(Qt::Orientation orient, const PlotterDiagramCompressor::DataPoint &dp) const;
    PlotterDiagramCompressor *m_parent;
    QAbstractItemModel *m_model;
    qreal m_mergeRadius;
    qreal m_maxSlopeRadius;
    QVector<QVector<DataPoint>> m_bufferlist;
    Boundaries m_boundary;
    QPair<qreal, qreal> m_forcedXBoundaries;
    QPair<qreal, qreal> m_forcedYBoundaries;
    QDateTime m_timeOfLastInvalidation;
    PlotterDiagramCompressor::CompressionMode m_mode;
    QVector<qreal> m_accumulatedDistances;
    //QVector< PlotterDiagramCompressor::Iterator > exisitingIterators;
public Q_SLOTS:
    void rowsInserted(const QModelIndex &parent, int start, int end);
    void clearBuffer();
    void setModelToZero();
};

}

#endif // PLOTTERDIAGRAMCOMPRESSOR_P_H
