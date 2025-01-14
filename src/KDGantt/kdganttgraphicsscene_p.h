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

#ifndef KDGANTTGRAPHICSSCENE_P_H
#define KDGANTTGRAPHICSSCENE_P_H

#include <QPersistentModelIndex>
#include <QHash>
#include <QPointer>
#include <QItemSelectionModel>
#include <QAbstractProxyModel>

#include "kdganttgraphicsscene.h"
#include "kdganttconstraintmodel.h"
#include "kdganttdatetimegrid.h"

namespace KDGantt {
class GraphicsScene::Private
{
public:
    explicit Private(GraphicsScene *);

    void resetConstraintItems();
    void createConstraintItem(const Constraint &c);
    void deleteConstraintItem(ConstraintGraphicsItem *citem);
    void deleteConstraintItem(const Constraint &c);
    ConstraintGraphicsItem *findConstraintItem(const Constraint &c) const;

    void recursiveUpdateMultiItem(const Span &span, const QModelIndex &idx);

    GraphicsScene *q;

    QHash<QPersistentModelIndex, GraphicsItem *> items;
    GraphicsItem *dragSource;

    QPointer<ItemDelegate> itemDelegate;
    AbstractRowController *rowController;
    DateTimeGrid default_grid;
    QPointer<AbstractGrid> grid;
    bool readOnly;

    /* printing related members */
    bool isPrinting;
    bool drawColumnLabels;
    qreal labelsWidth;

    QPointer<QAbstractProxyModel> summaryHandlingModel;

    QPointer<ConstraintModel> constraintModel;

    QPointer<QItemSelectionModel> selectionModel;
};

GraphicsScene::GraphicsScene(GraphicsScene::Private *d)
    : _d(d)
{
    init();
}
}

#endif /* KDGANTTGRAPHICSSCENE_P_H */
