#ifndef DIAGRAMRECORD
#define DIAGRAMRECORD

#include<QList>

QT_BEGIN_NAMESPACE
class DiagramItem;
class DiagramTextItem;
class Arrow;
class DiagramScene;
class QGraphicsItem;
QT_END_NAMESPACE

class DiagramRecord
{
public:
    DiagramRecord(QList<QGraphicsItem *>);
    const int getNumItems(){return numItems;}
    //const char* getRecord[](){return record;}

    void printRecord();
private:
    int numItems;
    const static char* record[];
};

#endif // DIAGRAMRECORD

