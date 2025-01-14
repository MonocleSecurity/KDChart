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

#include <QApplication>
#include <KDChartWidget>
#include <KDChartLineDiagram>
#include <KDChartLegend>

using namespace KDChart;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Widget widget;
    widget.resize(600, 600);

    QVector<qreal> vec0, vec1, vec2;

    vec0 << 5 << 1 << 3 << 4 << 1;
    vec1 << 3 << 6 << 2 << 4 << 8;
    vec2 << 0 << 7 << 1 << 2 << 1;

    widget.setDataset(0, vec0, "vec0");
    widget.setDataset(1, vec1, "vec1");
    widget.setDataset(2, vec2, "vec2");
    widget.setSubType(Widget::Percent);

    //Configure a pen and draw a line
    //a dot line for column 1
    QPen pen;
    QBrush brush;
    pen.setWidth(3);
    pen.setStyle(Qt::DotLine);
    pen.setColor(Qt::yellow);
    brush.setColor(Qt::yellow);
    // call your diagram and set the new pen
    // and brush
    widget.lineDiagram()->setPen(1, pen);
    widget.lineDiagram()->setBrush(1, brush);

    //set up a legend
    Legend *legend = new Legend(&widget);
    legend->setPosition(Position::East);
    legend->setAlignment(Qt::AlignCenter);
    legend->setOrientation(Qt::Vertical);
    legend->setLegendStyle(Legend::LinesOnly);
    legend->setShowLines(true);
    widget.addLegend(legend);
    //Set up your Attributes
    //display areas
    LineAttributes la(widget.lineDiagram()->lineAttributes());
    la.setDisplayArea(true);
    la.setTransparency(25);
    widget.lineDiagram()->setLineAttributes(la);

    widget.show();

    return app.exec();
}
