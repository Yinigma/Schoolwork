#include<diagramrecord.h>


DiagramRecord::DiagramRecord(QList<QGraphicsItem *>){
    numItems = items().size;
    record = new char* [numItems];
    foreach(char* s, record){
        s = (char*) malloc(300*sizeof(char));
    }
    for(int i = 0; i<numItems; i++){
        QGraphicsItem item = scene->items.at(i);
        if(DiagramItem* d = dynamic_cast<DiagramItem*>(item)){
            records[i] << "Item,"<<items().indexOf(d)<<","<<d->enumStrings[d->diagramType()]<<","<<d->pos().toPoint().x()<<","<<d->pos().toPoint().y()<<",";
            records[i] << d->brush().color().red()<< ",";
            records[i] << d->brush().color().green()<< ",";
            records[i] << d->brush().color().blue()<< ",";
            records[i] << d->pen().color().red()<< ",";
            records[i] << d->pen().color().green()<< ",";
            records[i] << d->pen().color().blue();
        }
        else if(DiagramTextItem* d = dynamic_cast<DiagramTextItem*>(item)){
            records[i] <<"Text,"<<items().indexOf(d)<<","<<d->pos().toPoint().x()<<","<<d->pos().toPoint().y()<<",";
            records[i] <<d->toPlainText().toLocal8Bit().constData()<<",";
            records[i] <<d->defaultTextColor().red()<<",";
            records[i] <<d->defaultTextColor().green()<<",";
            records[i] <<d->defaultTextColor().blue()<<",";
        }
        else if(Arrow* a = dynamic_cast<Arrow*>(item)){
            records[i] <<"Arrow,"<<items().indexOf(a->startItem())<<","<<items().indexOf(a->endItem());
        }
    }
}

void DiagramRecord::printRecord(){
    for(int i = 0; i<numItems; i++){
        cout<<records[i]<<"\n";
    }
}
