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

#include "mainwindow.h"

#include <KDChartChart>
#include <KDChartAbstractCoordinatePlane>
#include <KDChartCartesianAxis>
#include <KDChartBarDiagram>

#include <QDebug>
#include <QPen>
#include <QHBoxLayout>

using namespace KDChart;

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout *chartLayout = new QHBoxLayout(this);
    m_chart = new Chart();
    chartLayout->addWidget(m_chart);

    m_model.loadFromCSV(":/data");

    // Set up the diagram
    m_bars = new BarDiagram();
    m_bars->setModel(&m_model);
    m_bars->addAxis(new CartesianAxis(m_bars));

    m_chart->coordinatePlane()->replaceDiagram(m_bars);

    CartesianCoordinatePlane *plane = dynamic_cast<CartesianCoordinatePlane *>(m_chart->coordinatePlane());
    Q_ASSERT(plane);
    // The values in the model are all zero, so set the size of the plane
    // to something that is non-zero manually
    plane->setVerticalRange(QPair<qreal, qreal>(-2.0, 2.0));
}
