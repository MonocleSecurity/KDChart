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
#include <KDChartDataValueAttributes>

using namespace KDChart;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Widget widget;
    widget.resize(600, 600);

    QVector<qreal> vec0, vec1, vec2;

    vec0 << 5 << 1 << 3 << 4 << 1;
    vec1 << 3 << 6 << 2 << 4 << 8;
    vec2 << 2 << 7 << 1 << 2 << 1;

    widget.setDataset(0, vec0, "vec0");
    widget.setDataset(1, vec1, "vec1");
    widget.setDataset(2, vec2, "vec2");

    widget.lineDiagram()->setPen(Qt::NoPen);

    DataValueAttributes dva(widget.lineDiagram()->dataValueAttributes());
    MarkerAttributes ma(dva.markerAttributes());
    TextAttributes ta(dva.textAttributes());
    ma.setVisible(true);
    // display values or not
    ta.setVisible(false);
    dva.setTextAttributes(ta);
    dva.setMarkerAttributes(ma);
    dva.setVisible(true);

    widget.lineDiagram()->setDataValueAttributes(dva);
    widget.setGlobalLeading(10, 10, 10, 10);

    widget.show();

    return app.exec();
}
