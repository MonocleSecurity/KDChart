#!/usr/bin/env python

##
## This file is part of the KD Chart library.
##
## SPDX-FileCopyrightText: 2019-2021 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>
##
## SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDAB-KDChart OR LicenseRef-KDAB-KDChart-US
##
## Licensees holding valid commercial KD Chart licenses may use this file in
## accordance with the KD Chart Commercial License Agreement provided with
## the Software.
##
## Contact info@kdab.com if any conditions of this licensing are not
## clear to you.
##

from PySide2.QtCore import Qt, QModelIndex, QDateTime
from PySide2.QtWidgets import QDialog
from PyKDChart import KDGantt

from ui_entrydialog import Ui_EntryDialog


class EntryDialog(QDialog):
    def __init__(self, model, parent = None, f = Qt.WindowFlags()):
        super(EntryDialog, self).__init__(parent, f)

        self.indexList = []
        self.ui = Ui_EntryDialog()
        self.ui.setupUi(self)
        self.model = model
        self.init()

    def init(self):
        self.ui.type.addItem("Event", KDGantt.TypeEvent)
        self.ui.type.addItem("Task", KDGantt.TypeTask)
        self.ui.type.addItem("Summary", KDGantt.TypeSummary)
        self.ui.type.addItem("Multi", KDGantt.TypeMulti)

        for row in range(0, self.model.rowCount()):
            self.addDependItem(self.model, self.model.index(row, 0))

        self.ui.startDate.dateTimeChanged.connect(self.updateEndDate)
        self.ui.readOnly.toggled.connect(self.disableEditing)
        self.ui.startDate.setDateTime(QDateTime.currentDateTime())

    def initFrom(self, index, constraintModel):
        row = index.row()
        parent = index.parent()

        self.ui.name.setText(self.model.data(self.model.index(row, 0, parent)).toString())
        self.ui.legend.setText(self.model.data(self.model.index(row, 5, parent)).toString())
        
        idx = self.ui.type.findData(self.model.data(self.model.index(row, 1, parent)).toInt())
        self.ui.type.setCurrentIndex(idx)
        self.ui.startDate.setDateTime(self.model.data(self.model.index(row, 2, parent)).toDateTime())
        self.ui.endDate.setDateTime(self.model.data(self.model.index(row, 3, parent)).toDateTime())
        self.ui.completion.setValue(self.model.data(self.model.index(row, 4, parent)).toInt())
        self.ui.readOnly.setChecked(not (self.model.flags(self.model.index(row, 0, parent)) & Qt.ItemIsEditable))
    
        constraints = constraintModel.constraintsForIndex(self.model.index(row, 0, parent))
        if constraints.isEmpty():
            return
    
        constraintIndex = QModelIndex()
        for i in range(0, constraints.size()):
            constraint = constraints[i]
            if constraint.endIndex() == index:
                constraintIndex = constraint.startIndex()
                break

        if not constraintIndex.isValid():
            return

        self.ui.depends.setCurrentIndex(indexList.indexOf(constraintIndex) + 1 )


    def addDependItem(self, model, index, indent):
        self.indexList.insert(QPersistentModelIndex(index))
        str_ = "".ljust(indent) + model.data(index).toString()
        self.ui.depends.addItem(str_)

        for row in range(0, model.rowCount(index)):
            self.addDependItem(model, model.index(row, 0, index), indent + 2)


    def name(self):
        return self.ui.name.text()

    def type(self):
        return self.ui.type.itemData(self.ui.type.currentIndex())

    def startDate(self):
        return self.ui.startDate.dateTime()

    def endDate(self):
        return self.ui.endDate.dateTime()

    def completion(self):
        return self.ui.completion.value()

    def updateEndDate(self, startDate):
        self.ui.endDate.setMinimumDate(startDate.date())
        self.ui.endDate.setMinimumTime(startDate.time())

    def readOnly(self):
        return self.ui.readOnly.isChecked()

    def depends(self):
        if self.ui.depends.currentIndex() == 0:
            return QModelIndex()

        index = self.indexList[self.ui.depends.currentIndex() - 1]
        if index.isValid():
            return index

        return QModelIndex()

    def legend(self):
        return self.ui.legend.text()

    def disableEditing(self, disable):
        self.ui.name.setEnabled(not disable)
        self.ui.type.setEnabled(not disable)
        self.ui.completion.setEnabled(not disable)
        self.ui.startDate.setEnabled(not disable)
        self.ui.endDate.setEnabled(not disable)
        self.ui.depends.setEnabled(not disable)

