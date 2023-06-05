
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

class widgetFillBoard : public QWidget
{
    Q_OBJECT
    enum colorCell {GRAY, YELLOW, RED};
    const QColor lstColor[3] = {"#acb1bd", "#fcef5d", "#f52c43"};
    std::shared_ptr<QGridLayout> myLayout;
    QVector<QVector<std::pair<QPushButton*, bool>>> tableShip;
    size_t countShip;
    size_t numberOfHits;
    std::shared_ptr<QStatusBar> statusBar;
public:
    explicit widgetFillBoard(QWidget *parent = nullptr);
    ~widgetFillBoard();
    QPushButton* createButton(size_t, size_t);
    void choose(size_t, size_t);
    bool ready() const noexcept;
    size_t getNumberOfHints() const noexcept;
public slots:
    void slotButtonClicked();
    void slotButtonAccept();
};

#endif // WIDGETFILLBOARD_H
