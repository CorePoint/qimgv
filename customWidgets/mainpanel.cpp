#include "mainpanel.h"

MainPanel::MainPanel(QWidget *parent) : SlideHPanel(parent) {
    // buttons stuff
    buttonsWidget.setAccessibleName("panelButtonsWidget");

    openButton.setPixmap(QPixmap(":/images/res/icons/open.png"));
    openButton.setAction("open");
    settingsButton.setPixmap(QPixmap(":/images/res/icons/settings.png"));
    settingsButton.setAction("openSettings");
    exitFullscreenButton.setPixmap(QPixmap(":/images/res/icons/exit-fullscreen.png"));
    exitFullscreenButton.setAction("toggleFullscreen");
    exitButton.setPixmap(QPixmap(":/images/res/icons/close.png"));
    exitButton.setAction("exit");

    buttonsLayout.setDirection(QBoxLayout::BottomToTop);
    buttonsLayout.setSpacing(0);
    buttonsLayout.setContentsMargins(0,0,0,0);
    buttonsLayout.addWidget(&settingsButton);
    buttonsLayout.addWidget(&openButton);
    buttonsLayout.addStretch(0);
    //buttonsLayout.addWidget(&exitFullscreenButton);
    buttonsLayout.addWidget(&exitButton);

    buttonsWidget.setLayout(&buttonsLayout);
    layout.addWidget(&buttonsWidget, 0, 1);

    readSettings();
    connect(settings, SIGNAL(settingsChanged()), this, SLOT(readSettings()));
    // button actions
    connect(&openButton, SIGNAL(clicked()), this, SIGNAL(openClicked()));
    connect(&exitFullscreenButton, SIGNAL(clicked()), this, SIGNAL(exitFullscreenClicked()));
    connect(&settingsButton, SIGNAL(clicked()), this, SIGNAL(settingsClicked()));
    connect(&exitButton, SIGNAL(clicked()), this, SIGNAL(exitClicked()));
}

void MainPanel::setPosition(PanelHPosition newPosition) {
    position = newPosition;
    if(position == TOP) {
        layout.setContentsMargins(0,0,0,invisibleMargin);
    }
    else {
        layout.setContentsMargins(0,2,0,0);
    }
    recalculateGeometry();
}

void MainPanel::readSettings() {
    panelHeight = settings->mainPanelSize();
    setPosition(settings->panelPosition());
}

// draw separator line at bottom or top
void MainPanel::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);
    QPainter p(this);
    if(position == PanelHPosition::TOP) {
        p.setPen(QColor(QColor(110, 110, 110)));
        p.drawLine(rect().bottomLeft() - QPoint(0, invisibleMargin - 1), rect().bottomRight() - QPoint(0, invisibleMargin - 1));
        p.setPen(QColor(QColor(40, 40, 40)));
        p.drawLine(rect().bottomLeft() - QPoint(0, invisibleMargin - 2), rect().bottomRight() - QPoint(0, invisibleMargin - 2));
    } else {
        p.setPen(QColor(QColor(40, 40, 40)));
        p.drawLine(rect().topLeft(), rect().topRight());
        p.drawLine(rect().topLeft() + QPoint(0,1), rect().topRight() + QPoint(0,1));
    }
}
