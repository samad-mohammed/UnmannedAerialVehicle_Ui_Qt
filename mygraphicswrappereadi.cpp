#include <QGraphicsView>
#include <QGraphicsScene>
#include <QQuickItem>

MyGraphicsWrapperEADI::MyGraphicsWrapperEADI(QQuickItem *parent) : QQuickItem(parent)
{
    // Create a QGraphicsScene
    scene = new QGraphicsScene(this);

    // Create a QGraphicsView with the scene as its parent
    graphicsView = new QGraphicsView(scene);

    // Set the graphicsView as the item's rendering item
    setFlag(QQuickItem::ItemHasContents);
}

//void MyGraphicsWrapperEADI::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
//{
//    QQuickItem::geometryChanged (newGeometry, oldGeometry);

//    // Adjust the QGraphicsView's size when the item's size changes
//    graphicsView->setGeometry(0, 0, newGeometry.width(), newGeometry.height());
//}


void MyGraphicsWrapperEADI::componentComplete()
{
    QQuickItem::componentComplete();

    // Monitor changes in the item's size
    connect(this, &QQuickItem::widthChanged, this, &MyGraphicsWrapperEADI::handleSizeChange);
    connect(this, &QQuickItem::heightChanged, this, &MyGraphicsWrapperEADI::handleSizeChange);
}

void MyGraphicsWrapperEADI::handleSizeChange()
{
    // Adjust the QGraphicsView's size when the item's size changes
    graphicsView->setGeometry(0, 0, width(), height());
}
