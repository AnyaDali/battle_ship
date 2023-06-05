
#ifndef WIDGETFILLBOARD_H
#define WIDGETFILLBOARD_H

#include <QDialog>
#include <QGridLayout>
#include <unordered_map>
#include <QPushButton>
#include <QVector>
#include <QLabel>
#include <QString>
#include <QStatusBar>
//#include "widgetinputboard.h"

class widgetFillBoard : public QWidget
{
    Q_OBJECT
public:
    using table_t = QVector<QVector<std::pair<QPushButton*, bool>>>;
    using ptr_table_t = std::shared_ptr<table_t>;
private:
    enum colorCell {GRAY};
    const QColor lstColor[1] = {"#acb1bd"};
    std::shared_ptr<QGridLayout> myLayout;
    ptr_table_t tableShip;
    size_t countShip;
    size_t numberOfHits;
    std::shared_ptr<QStatusBar> statusBar;

public:
    explicit widgetFillBoard(QWidget *parent = nullptr);
    ~widgetFillBoard();
    QPushButton* createButton(size_t, size_t);
    bool ready() const noexcept;
    size_t getNumberOfHints() const noexcept;
    ptr_table_t getTableShip() noexcept;
public slots:
    void slotButtonClicked();
    void slotButtonAccept();
};

#endif // WIDGETFILLBOARD_H
