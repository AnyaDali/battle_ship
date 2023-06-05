
#ifndef WIDGETINPUTBOARD_H
#define WIDGETINPUTBOARD_H


#include <QWidget>
#include <QPushButton>
#include <QVector>
#include <QGridLayout>
#include <memory>
#include <unordered_map>
#include <QMessageBox>
class widgetInputBoard : public QWidget
{
    Q_OBJECT
public:
    using table_t = QVector<QVector<std::pair<QPushButton*, bool>>>;
    using ptr_table_t = std::shared_ptr<table_t>;
protected:
    enum colorCell {GRAY, YELLOW, RED, GREEN};
    const QColor lstColor[4] = {"#acb1bd", "#fcef5d", "#f52c43", "#68f29f"};
    std::shared_ptr<QGridLayout> myLayout;
    ptr_table_t ptrTableShip;
    std::unordered_map<QPushButton*, std::tuple<int, int, bool>> setShip;
    std::list<std::pair<int, int>> lstChose;
    size_t numberOfHits;
    size_t numberOfHitsOpponent;
    std::list<std::pair<int, int>> initLstChose();
    void choose(size_t, size_t);
    std::shared_ptr<QLabel> progressBarUsr;
    std::shared_ptr<QLabel> progressBarOp;

public:
    explicit widgetInputBoard(ptr_table_t, QWidget *parent = nullptr);
    ~widgetInputBoard();
    QPushButton* createButton(size_t, size_t);
    QPushButton* createInactiveButton(size_t, size_t);
    void initializeShip();
    size_t getNumberOfHints() const noexcept;
public slots:
    void slotButtonClicked();
};

#endif // WIDGETINPUTBOARD_H
