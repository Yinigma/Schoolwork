/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "diagramscene.h"
#include "arrow.h"

#include <QTextCursor>
#include <QGraphicsSceneMouseEvent>

//! [0]
DiagramScene::DiagramScene(QMenu *itemMenu, QObject *parent)
    : QGraphicsScene(parent)
{
    myItemMenu = itemMenu;
    myMode = MoveItem;
    myItemType = DiagramItem::Step;
    line = 0;
    textItem = 0;
    myItemColor = Qt::white;
    myTextColor = Qt::black;
    myLineColor = Qt::black;
}
//! [0]

//! [1]
void DiagramScene::setLineColor(const QColor &color)
{
    myLineColor = color;
    if (isItemChange(Arrow::Type)) {

        Arrow *item = qgraphicsitem_cast<Arrow *>(selectedItems().first());
        item->setColor(myLineColor);
        update();
    }
}
//! [1]

//! [2]
void DiagramScene::setTextColor(const QColor &color)
{
    myTextColor = color;
    if (isItemChange(DiagramTextItem::Type)) {

        DiagramTextItem *item = qgraphicsitem_cast<DiagramTextItem *>(selectedItems().first());
        item->setDefaultTextColor(myTextColor);
    }
}
//! [2]

//! [3]
void DiagramScene::setItemColor(const QColor &color)
{
    myItemColor = color;
    if (isItemChange(DiagramItem::Type)) {

        DiagramItem *item = qgraphicsitem_cast<DiagramItem *>(selectedItems().first());
        item->setBrush(myItemColor);
    }
}
//! [3]

//! [4]
void DiagramScene::setFont(const QFont &font)
{
    myFont = font;

    if (isItemChange(DiagramTextItem::Type)) {
        QGraphicsTextItem *item = qgraphicsitem_cast<DiagramTextItem *>(selectedItems().first());
        //At this point the selection can change so the first selected item might not be a DiagramTextItem
        if (item)

            item->setFont(myFont);
    }
}
//! [4]

void DiagramScene::setMode(Mode mode)
{
    myMode = mode;
}

void DiagramScene::setItemType(DiagramItem::DiagramType type)
{
    myItemType = type;
}

//! [5]
void DiagramScene::editorLostFocus(DiagramTextItem *item)
{
    QTextCursor cursor = item->textCursor();
    cursor.clearSelection();
    item->setTextCursor(cursor);

    if (item->toPlainText().isEmpty()) {
        removeItem(item);
        item->deleteLater();
    }
}
//! [5]

//! [6]
void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    DiagramItem *item;
    switch (myMode) {
        case InsertItem:

            item = new DiagramItem(myItemType, myItemMenu);
            item->setBrush(myItemColor);
            addItem(item);
            item->setPos(mouseEvent->scenePos());
            emit itemInserted(item);
            break;
//! [6] //! [7]
        case InsertLine:

            line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                        mouseEvent->scenePos()));
            line->setPen(QPen(myLineColor, 2));
            addItem(line);
            break;
//! [7] //! [8]
        case InsertText:

            textItem = new DiagramTextItem();
            textItem->setFont(myFont);
            textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
            textItem->setZValue(1000.0);
            connect(textItem, SIGNAL(lostFocus(DiagramTextItem*)),
                    this, SLOT(editorLostFocus(DiagramTextItem*)));
            connect(textItem, SIGNAL(selectedChange(QGraphicsItem*)),
                    this, SIGNAL(itemSelected(QGraphicsItem*)));
            addItem(textItem);
            textItem->setDefaultTextColor(myTextColor);
            textItem->setPos(mouseEvent->scenePos());
            emit textInserted(textItem);
//! [8] //! [9]
    default:
        ;
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}
//! [9]

//! [10]
void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (myMode == InsertLine && line != 0) {

        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
    } else if (myMode == MoveItem) {

        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}
//! [10]

//! [11]
void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (line != 0 && myMode == InsertLine) {

        QList<QGraphicsItem *> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();

        removeItem(line);
        delete line;
//! [11] //! [12]

        if (startItems.count() > 0 && endItems.count() > 0 &&
            startItems.first()->type() == DiagramItem::Type &&
            endItems.first()->type() == DiagramItem::Type &&
            startItems.first() != endItems.first()) {
            DiagramItem *startItem = qgraphicsitem_cast<DiagramItem *>(startItems.first());
            DiagramItem *endItem = qgraphicsitem_cast<DiagramItem *>(endItems.first());
            Arrow *arrow = new Arrow(startItem, endItem);
            arrow->setColor(myLineColor);
            startItem->addArrow(arrow);
            endItem->addArrow(arrow);
            arrow->setZValue(-1000.0);
            addItem(arrow);
            arrow->updatePosition();
        }
    }
//! [12] //! [13]
    line = 0;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}
//! [13]

//! [14]
bool DiagramScene::isItemChange(int type)
{
    foreach (QGraphicsItem *item, selectedItems()) {
        if (item->type() == type)
            return true;
    }
    return false;
}
//! [14]

void DiagramScene::printItems(){
    //Welcom to brute force, the TV show
}

void DiagramScene::addToHistory(QList<QGraphicsItem*> itemList, QStringList* strlst){//QList<QStringList>* itemStrings){

    for(int i = 0; i<itemList.size(); i++){

        QString* str = new QString();
        strlst->append(*str);

        if(DiagramItem* d = dynamic_cast<DiagramItem*>(itemList.at(i))){
            strlst->last().append("Item,");
            strlst->last().append(QString::number(itemList.indexOf(d)))+=",";
            strlst->last().append(d->enumStrings[d->diagramType()])+=",";
            strlst->last().append(QString::number(d->pos().toPoint().x()))+=",";
            strlst->last().append(QString::number(d->pos().toPoint().y()))+=",";
            strlst->last().append(QString::number(d->brush().color().red()))+=",";
            strlst->last().append(QString::number(d->brush().color().green()))+=",";
            strlst->last().append(QString::number(d->brush().color().blue()))+=",";
            strlst->last().append(QString::number(d->pen().color().red()))+=",";
            strlst->last().append(QString::number(d->pen().color().green()))+=",";
            strlst->last().append(QString::number(d->pen().color().blue()))+=",";
            //printf("%s\n",strlst->last().toLocal8Bit().constData());
        }
        else if(DiagramTextItem* d = dynamic_cast<DiagramTextItem*>(itemList.at(i))){
            int bold  = (int) (d->font().bold());
            int italic  = (int) (d->font().italic());
            int underline  = (int) (d->font().underline());
            strlst->last().append("Text,");
            strlst->last().append(QString::number(itemList.indexOf(d)))+=",";
            strlst->last().append(QString::number(d->pos().toPoint().x()))+=",";
            strlst->last().append(QString::number(d->pos().toPoint().y()))+=",";
            strlst->last().append(d->toPlainText())+=",";
            strlst->last().append(d->font().family())+=",";
            strlst->last().append(QString::number(bold))+=",";
            strlst->last().append(QString::number(italic))+=",";
            strlst->last().append(QString::number(underline))+=",";
            strlst->last().append(QString::number(d->defaultTextColor().red()))+=",";
            strlst->last().append(QString::number(d->defaultTextColor().green()))+=",";
            strlst->last().append(QString::number(d->defaultTextColor().blue()));
        }

        else if(Arrow* a = dynamic_cast<Arrow*>(itemList.at(i))){
            strlst->last()+="Arrow,";
            strlst->last().append(QString::number(itemList.indexOf(a->startItem())))+=",";
            strlst->last().append(QString::number(itemList.indexOf(a->endItem())))+=",";
            strlst->last().append(QString::number(a->pen().color().red()))+=",";
            strlst->last().append(QString::number(a->pen().color().green()))+=",";
            strlst->last().append(QString::number(a->pen().color().blue()));
        }
    }
}

void DiagramScene::addToHistory(){
    QStringList* strlst = new QStringList();
    history.append(*strlst);
    this->addToHistory(items(),&history.last());
}

void DiagramScene::parseData(QString *qstr, double ZValue){
    QStringList tokens = qstr->split(",",QString::SkipEmptyParts);
    if(tokens.first().compare("Item",Qt::CaseInsensitive)==0){
        DiagramItem *item;
        DiagramItem::DiagramType t;
        QColor *fill = new QColor(tokens.at(5).toInt(),tokens.at(6).toInt(),tokens.at(7).toInt());
        QColor *pen = new QColor(tokens.at(8).toInt(),tokens.at(9).toInt(),tokens.at(10).toInt());
        if(tokens.at(2).compare("Step",Qt::CaseInsensitive)==0){
            t = DiagramItem::Step;
        }
        else if(tokens.at(2).compare("Conditional",Qt::CaseInsensitive)==0){
            t = DiagramItem::Conditional;
        }
        else if(tokens.at(2).compare("StartEnd",Qt::CaseInsensitive)==0){
            t = DiagramItem::StartEnd;
        }
        else if(tokens.at(2).compare("Io",Qt::CaseInsensitive)==0){
            t = DiagramItem::Io;
        }
        else if(tokens.at(2).compare("Terminal",Qt::CaseInsensitive)==0){
            t = DiagramItem::Terminal;
        }
        else if(tokens.at(2).compare("Preparation",Qt::CaseInsensitive)==0){
            t = DiagramItem::Preparation;
        }
        else{
            t = DiagramItem::Offpage;
        }

        item = new DiagramItem(t, myItemMenu);
        item->setBrush(*fill);
        item->setPen(*pen);
        addItem(item);
        item->setPos(tokens.at(3).toInt(),tokens.at(4).toInt());
        item->setZValue(ZValue);
        emit itemInserted(item);
    }
    else if(tokens.first().compare("Text",Qt::CaseInsensitive)==0){
        textItem = new DiagramTextItem();
        QFont *parsedFont = new QFont;
        QColor *color = new QColor(tokens.at(9).toInt(),tokens.at(10).toInt(),tokens.at(11).toInt());
        parsedFont->setFamily(tokens.at(5));
        parsedFont->setBold((bool)(tokens.at(6).toInt()));
        parsedFont->setItalic((bool)(tokens.at(7).toInt()));
        parsedFont->setUnderline((bool)(tokens.at(8).toInt()));
        textItem->setFont(*parsedFont);
        textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
        textItem->setZValue(1000.0);
        connect(textItem, SIGNAL(lostFocus(DiagramTextItem*)),
                this, SLOT(editorLostFocus(DiagramTextItem*)));
        connect(textItem, SIGNAL(selectedChange(QGraphicsItem*)),
                this, SIGNAL(itemSelected(QGraphicsItem*)));
        addItem(textItem);
        textItem->setPlainText(tokens.at(4));
        textItem->setDefaultTextColor(*color);
        textItem->setPos(tokens.at(2).toInt(),tokens.at(3).toInt());
        emit textInserted(textItem);
    }
    else if(tokens.first().compare("Arrow",Qt::CaseInsensitive)==0){
        DiagramItem *startItem = dynamic_cast<DiagramItem*>(items().at(tokens.at(1).toInt()));
        DiagramItem *endItem = dynamic_cast<DiagramItem*>(items().at(tokens.at(2).toInt()));
        QColor *color = new QColor(tokens.at(3).toInt(),tokens.at(4).toInt(),tokens.at(5).toInt());
        Arrow *arrow = new Arrow(startItem, endItem);
        arrow->setColor(*color);
        startItem->addArrow(arrow);
        endItem->addArrow(arrow);
        arrow->setZValue(-1000.0);
        addItem(arrow);
        arrow->updatePosition();
    }

}
