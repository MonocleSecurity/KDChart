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
#include <KDChartPolarDiagram>
#include <KDChartTextAttributes>
#include <KDChartDataValueAttributes>
#include <KDChartGridAttributes>
#include <KDChartMarkerAttributes>
#include <KDChartLegend>

#include <QDebug>
#include <QPainter>

using namespace KDChart;

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , m_currentFactor(0)
    , m_currentDirection(1)
    , m_currentSlice(0)
{
    setupUi(this);

    // instantiate the KD Chart classes
    initKDChartClasses();

    // insert the KDChart::Chart into Qt's layout
    QHBoxLayout *chartLayout = new QHBoxLayout(chartFrame);
    m_chart->setGlobalLeadingLeft(5);
    m_chart->setGlobalLeadingRight(5);
    chartLayout->addWidget(m_chart);

    // wire up the KD Chart classes
    wireUpKDChartClasses();

    // initialize the ItemModel and fill in some data
    m_model.insertRows(0, 40);
    m_model.insertColumns(0, 5);
    setItemModelData();
}

void MainWindow::initKDChartClasses()
{
    m_chart = new Chart();
    m_diagram = new PolarDiagram();
    m_polarPlane = new PolarCoordinatePlane();
}

void MainWindow::wireUpKDChartClasses()
{
    m_chart->replaceCoordinatePlane(m_polarPlane);
    //note: We need to set a valid item model to the diagram,
    //      before we can add it to the coordinate plane.
    m_diagram->setModel(&m_model);
    m_chart->coordinatePlane()->replaceDiagram(m_diagram);
}

void MainWindow::setItemModelData()
{
    // For a change we do not read data from a resource file here,
    // but we just fill in the cells manually
    int value = 0;
    for (int column = 0; column < m_model.columnCount(); ++column) {
        for (int row = 0; row < m_model.rowCount(); ++row) {
            QModelIndex index = m_model.index(row, column);
            m_model.setData(index, QVariant(value++));
        }
    }
}

void MainWindow::on_startPositionSB_valueChanged(double pos)
{
    const int intValue = static_cast<int>(pos);
    startPositionSL->blockSignals(true);
    startPositionSL->setValue(intValue);
    startPositionSL->blockSignals(false);
    // note: We use the global getter method here, it will fall back
    //       automatically to return the default settings.
    static_cast<PolarCoordinatePlane *>(m_chart->coordinatePlane())->setStartPosition(pos);
    update();
}

void MainWindow::on_startPositionSL_valueChanged(int pos)
{
    qreal qrealValue = static_cast<qreal>(pos);
    startPositionSB->blockSignals(true);
    startPositionSB->setValue(qrealValue);
    startPositionSB->blockSignals(false);
    // note: We use the global getter method here, it will fall back
    //       automatically to return the default settings.
    static_cast<PolarCoordinatePlane *>(m_chart->coordinatePlane())->setStartPosition(pos);
    update();
}

void MainWindow::on_circularGridCB_toggled(bool toggle)
{
    GridAttributes attrs(m_polarPlane->gridAttributes(true));
    attrs.setGridVisible(toggle);
    m_polarPlane->setGridAttributes(true, attrs);
    update();
}
void MainWindow::on_sagittalGridCB_toggled(bool toggle)
{
    GridAttributes attrs(m_polarPlane->gridAttributes(false));
    attrs.setGridVisible(toggle);
    m_polarPlane->setGridAttributes(false, attrs);
    update();
}
