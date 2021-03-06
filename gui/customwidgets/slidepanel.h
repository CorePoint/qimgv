#ifndef SLIDEPANEL_H
#define SLIDEPANEL_H

#include <QtGlobal>
#include <QTimeLine>
#include <QGraphicsOpacityEffect>
#include <QPainter>
#include <QGridLayout>
#include <QTimer>
#include <QTimeLine>
#include "overlaywidget.h"
#include "settings.h"
#include <QDebug>
#include <ctime>

class SlidePanel : public OverlayWidget {
    Q_OBJECT
public:
    explicit SlidePanel(OverlayContainerWidget *parent);
    ~SlidePanel();
    bool hasWidget();
    void setWidget(std::shared_ptr<QWidget> w);
    // Use visibleGeometry instead of geometry() here.
    // If this is called mid-animation then geometry() will be all wrong.
    virtual QRect triggerRect() = 0;

public slots:
    void show();
    void hide();

private slots:
    void onAnimationFinish();

    void animationUpdate(int frame);
protected:
    QGridLayout mLayout;
    QGraphicsOpacityEffect *fadeEffect;
    int panelSize, slideAmount;
    std::shared_ptr<QWidget> mWidget;
    QPoint startPosition, endPosition;
    QRect mTriggerRect;
    virtual void updateTriggerRect() = 0;
    void leaveEvent(QEvent *event);
    void saveStaticGeometry(QRect geometry);
    QRect staticGeometry();

    QTimer timer;
    QTimeLine timeline;
    QEasingCurve outCurve;

private:
    QRect mStaticGeometry;
    qreal panelVisibleOpacity = 1.0;

};

#endif // SLIDEPANEL_H
