
#include "widgetfillboard.h"
#include "widgetinputboard.h"

widgetFillBoard::widgetFillBoard(QWidget *parent) :
    QWidget(parent), myLayout(std::make_shared<QGridLayout>()),
    tableShip(std::make_shared<table_t>(10, QVector<std::pair<QPushButton*, bool>>(10))),
    countShip(0), numberOfHits(0), statusBar(std::make_shared<QStatusBar>())
{
    resize(430, 500);
    QLabel* label = new QLabel[10];

    label[0].setText("1");
    label[1].setText("2");
    label[2].setText("3");
    label[3].setText("4");
    label[4].setText("5");
    label[5].setText("6");
    label[6].setText("7");
    label[7].setText("8");
    label[8].setText("9");
    label[9].setText("10");

    QPushButton* butAccept = new QPushButton{"Подтвердить"};
    butAccept->setMinimumSize(80, 30);
    connect(butAccept, SIGNAL(clicked()), this, SLOT(slotButtonAccept()));
    myLayout->addWidget(butAccept, 0, 7, 0, 10, Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignTop);
    //statusBar->messageChanged("Осталось расставить кораблей: 10");
    statusBar->setStyleSheet("QStatusBar { background-color: white; border: 1px solid #000; }");
    statusBar->showMessage("Разместите 10 кораблей на поле.");
    myLayout->addWidget(statusBar.get(), 1, 0, 1, 10, Qt::AlignmentFlag::AlignTop);

    int x = 1;
    for(size_t i = 0; i < 10; ++i) {
        myLayout->addWidget(&label[i], 1, x, Qt::AlignmentFlag::AlignCenter | Qt::AlignmentFlag::AlignBottom);
        x++;
    }

    QLabel* labely = new QLabel[10];

    labely[0].setText("A");
    labely[1].setText("B");
    labely[2].setText("C");
    labely[3].setText("D");
    labely[4].setText("E");
    labely[5].setText("F");
    labely[6].setText("G");
    labely[7].setText("H");
    labely[8].setText("I");
    labely[9].setText("J");
    int y = 2;
    for(size_t i = 0; i < 10; ++i) {
        myLayout->addWidget(&labely[i], y, 0);
        ++y;
    }

    y = 1;

    for(size_t j = 0; j < 10; ++j) {
        x = 2;
        for(size_t i = 0; i < 10;  ++i) {
            myLayout->addWidget(createButton(i, j), x, y);
            ++x;
        }
        ++y;
    }


    setLayout(myLayout.get());
}

QPushButton* widgetFillBoard::createButton(size_t i, size_t j) {
    QPushButton* pcmd = new QPushButton{""};
    pcmd->setMinimumSize(30, 30);
    connect(pcmd, SIGNAL(clicked()), this, SLOT(slotButtonClicked()));
    (*tableShip)[i][j] = std::make_pair(pcmd, false);
    return pcmd;
}

void widgetFillBoard::slotButtonAccept() {
    if (countShip == 10) {
        widgetInputBoard* w = new widgetInputBoard{tableShip};
        w->show();

        this->close();
    } else {
        statusBar->showMessage("Вам необходимо расставить ещё " + QString::number(10 - countShip) + " кораблей.");
    }
}

void widgetFillBoard::slotButtonClicked() {

    auto ptrButton = reinterpret_cast<QPushButton*>(sender());
    for(auto& line : *tableShip) {
        for(auto& [ptr, flag] : line) {
            if (ptr == ptrButton) {
                flag = true;
            }
        }
    }
    ptrButton->setStyleSheet("background-color:"+lstColor[GRAY].name());
    ++countShip;
    if (countShip >= 10) {
        for(auto& line : *tableShip) {
            for(auto& [ptrB, flag] : line) {
                ptrB->setEnabled(false);
            }
        }
    }

    if (countShip < 10) {
        statusBar->showMessage("Кораблей осталось разместить: " + QString::number(10 - countShip));
    } else {
        statusBar->showMessage("Корабли размещены. Нажмите \"Подтвердить\"");
    }
    ptrButton->setEnabled(false);
}

std::shared_ptr<QVector<QVector<std::pair<QPushButton*, bool>>>> widgetFillBoard::getTableShip() noexcept {
    auto ptrRet = tableShip;
    return ptrRet;
}

size_t widgetFillBoard::getNumberOfHints() const noexcept {
    return numberOfHits;
}

bool widgetFillBoard::ready() const noexcept {
    return countShip == 10;
}


widgetFillBoard::~widgetFillBoard() {}
