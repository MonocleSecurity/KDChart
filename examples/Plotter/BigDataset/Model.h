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

#ifndef MODEL_H
#define MODEL_H

#include <QAbstractItemModel>
#include <QTimer>
#include <QVector>

class Model : public QAbstractItemModel
{
    Q_OBJECT
public:
    enum Function {
        SineFunction = 0,
        TriangleFunction,
        SquareFunction,
        NoiseFunction,
        OneDivSineFunction,
        SineOneDivFunction
    };
    Model();

    int columnCount(const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    void setFunction(Function f);

    void appendPoints(int numPoints);

public slots:
    void setRunning(bool);

private slots:
    void appendPoint();

private:
    qreal nextFunctionValue();

    qreal m_x;
    Function m_function;
    QVector<qreal> m_data;
    QTimer m_appendTimer;
};

#endif
