#ifndef ACTIVITIESLISTWIDGET_H
#define ACTIVITIESLISTWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QScrollArea>

#include "strategy.h"
#include "navbar.h"

class ActivitiesListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ActivitiesListWidget(QWidget *parent = nullptr);

    Strategy *strategy() const;
    void setStrategy(Strategy *strategy);
    void updateList();

signals:
    void selectActivity(const Activity &activity);
    void wantNewActivity();
    void activityRemoved(const Activity &activity);
    void wantToEditActivity(const Activity &activity);
public slots:

private:
    void paintEvent(QPaintEvent *) override;

    QStackedWidget *parentStackedWidget();
    void getBack();
    void sendWantNewActivity();

    QScrollArea *scrollArea;
    QWidget *listWidget;
    QWidget *navWidget;
    Strategy *_strategy;
};

#endif // ACTIVITIESLISTWIDGET_H
