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
#include <KDChartLineDiagram>
#include <KDChartGridAttributes>

#include <QDebug>
#include <QPainter>

using namespace KDChart;

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);

    QHBoxLayout *chartLayout = new QHBoxLayout(chartFrame);
    m_chart = new Chart();
    chartLayout->addWidget(m_chart);

    // Use the new Layout-system.
    m_chart->setUseNewLayoutSystem(true);

    m_model.loadFromCSV(":/data");
    m_model2.loadFromCSV(":/data2");

    // Set up the diagram
    m_lines = new LineDiagram();
    m_lines->setModel(&m_model);

    m_lines2 = new LineDiagram();
    m_lines2->setModel(&m_model2);

    // The by default built-in plane.
    KDChart::CartesianCoordinatePlane *plane1 = static_cast<KDChart::CartesianCoordinatePlane *>(m_chart->coordinatePlane());

    // We call this "plane2" just for remembering, that we use it
    // in addition to the plane, that's built-in by default.
    plane2 = new CartesianCoordinatePlane(m_chart);

    CartesianAxis *xAxis = new CartesianAxis(m_lines);
    CartesianAxis *yAxis = new CartesianAxis(m_lines);
    CartesianAxis *yAxis2 = new CartesianAxis(m_lines2);

    QList<qreal> ticks;
    ticks.append(5);
    ticks.append(10);
    ticks.append(15);
    xAxis->setCustomTicks(ticks);

    QMultiMap<qreal, QString> annotations;
    annotations.insert(5, "Five");
    annotations.insert(10, "Ten");
    annotations.insert(15, "Fifteen");
    xAxis->setAnnotations(annotations);

    xAxis->setPosition(KDChart::CartesianAxis::Top);
    yAxis->setPosition(KDChart::CartesianAxis::Left);
    yAxis2->setPosition(KDChart::CartesianAxis::Right);

    m_lines->addAxis(xAxis); // shared axis, add to m_lines
    m_lines->addAxis(yAxis);
    m_lines2->addAxis(xAxis); // and add to m_lines2
    m_lines2->addAxis(yAxis2);

    m_chart->coordinatePlane()->replaceDiagram(m_lines);
    m_chart->setGlobalLeading(20, 20, 20, 20);
    plane2->replaceDiagram(m_lines2);
    m_chart->addCoordinatePlane(plane2);

    // Enable the annotations in both planes.
    KDChart::GridAttributes grid1 = plane1->gridAttributes(Qt::Horizontal);
    grid1.setLinesOnAnnotations(true);
    plane1->setGridAttributes(Qt::Horizontal, grid1);
    KDChart::GridAttributes grid2 = plane2->gridAttributes(Qt::Horizontal);
    grid2.setLinesOnAnnotations(true);
    plane2->setGridAttributes(Qt::Horizontal, grid2);
    m_chart->update();
}
