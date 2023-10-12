#ifndef MYGRAPHICSWRAPPEREADI_H
#define MYGRAPHICSWRAPPEREADI_H

#include <QQuickItem>


#include <QGraphicsView>
#include <QGraphicsScene>
class MyGraphicsWrapperEADI : public QQuickItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    MyGraphicsWrapperEADI(QQuickItem *parent = nullptr);
//    void paint(QPainter *painter);
//    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;
QGraphicsView *graphicsView;
private:
    QGraphicsScene *scene;




private slots:
    void handleSizeChange();

protected:
    void componentComplete() override;
signals:

};



#endif // MYGRAPHICSVIEWWRAPPER_H
