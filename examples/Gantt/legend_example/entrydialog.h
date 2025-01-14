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

#ifndef ENTRYDIALOG_H
#define ENTRYDIALOG_H

#include <QDateTime>
#include <QDialog>
#include <QModelIndex>

QT_BEGIN_NAMESPACE
class QAbstractItemModel;
namespace Ui {
class EntryDialog;
}
QT_END_NAMESPACE

namespace KDGantt {
class ConstraintModel;
}

class EntryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EntryDialog(const QAbstractItemModel *model, QWidget *parent = nullptr, Qt::WindowFlags f = {});
    void initFrom(const QModelIndex &index, const KDGantt::ConstraintModel *constraintModel);

    QString name() const;
    int type() const;
    QDateTime startDate() const;
    QDateTime endDate() const;
    int completion() const;
    bool readOnly() const;
    QModelIndex depends() const;
    QString legend() const;

private slots:
    void updateEndDate(const QDateTime &startDate);
    void disableEditing(bool disable);
    void typeChanged(int index);

private:
    void init();
    void addDependItem(const QAbstractItemModel *model, const QModelIndex &index, int indent = 0);

    QList<QPersistentModelIndex> indexList;
    const QAbstractItemModel *model;
    Ui::EntryDialog *ui;
};

#endif /* ENTRYDIALOG_H */
