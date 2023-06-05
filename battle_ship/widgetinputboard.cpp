#include <QLabel>
#include "widgetinputboard.h"

widgetInputBoard::widgetInputBoard(ptr_table_t table, QWidget *parent)
    : QWidget{parent}, myLayout(std::make_shared<QGridLayout>()), ptrTableShip(table),
    setShip(), lstChose(initLstChose()), numberOfHits(0), numberOfHitsOpponent(0),
    progressBarUsr(std::make_shared<QLabel>("Ваших кораблей осталось: 10")),
    progressBarOp(std::make_shared<QLabel>("Кораблей противника осталось: 10"))
{
    resize(800, 460);
    setMinimumSize(800, 460);
    setMaximumSize(800, 460);
    QLabel* labelFlot = new QLabel;
    labelFlot->setText("Флот противника:");
    myLayout->addWidget(labelFlot, 0, 0, 0, 10, Qt::AlignmentFlag::AlignTop);

    QLabel* labelFlotOp = new QLabel;
    labelFlotOp->setText("Ваш флот:");
    myLayout->addWidget(labelFlotOp, 0, 14, 0, 20, Qt::AlignmentFlag::AlignTop);

    myLayout->addWidget(progressBarOp.get(), 1, 0, 1, 10, Qt::AlignmentFlag::AlignTop);
    myLayout->addWidget(progressBarUsr.get(), 1, 14, 1, 25, Qt::AlignmentFlag::AlignTop);
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
    int x = 2;
    for(size_t i = 0; i < 10; ++i) {
        myLayout->addWidget(&label[i], 2, x, Qt::AlignmentFlag::AlignCenter | Qt::AlignmentFlag::AlignBottom);
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
    int y = 3;
    for(size_t i = 0; i < 10; ++i) {
        myLayout->addWidget(&labely[i], y, 0,  Qt::AlignmentFlag::AlignRight);
        ++y;
    }

    QLabel* labelxOp = new QLabel[10];

    labelxOp[0].setText("1");
    labelxOp[1].setText("2");
    labelxOp[2].setText("3");
    labelxOp[3].setText("4");
    labelxOp[4].setText("5");
    labelxOp[5].setText("6");
    labelxOp[6].setText("7");
    labelxOp[7].setText("8");
    labelxOp[8].setText("9");
    labelxOp[9].setText("10");
    x = 14;
    for(size_t i = 0; i < 10; ++i) {
        myLayout->addWidget(&labelxOp[i], 2, x, Qt::AlignmentFlag::AlignCenter | Qt::AlignmentFlag::AlignBottom);
        x++;
    }

    QLabel* labelyOp = new QLabel[10];

    labelyOp[0].setText("A");
    labelyOp[1].setText("B");
    labelyOp[2].setText("C");
    labelyOp[3].setText("D");
    labelyOp[4].setText("E");
    labelyOp[5].setText("F");
    labelyOp[6].setText("G");
    labelyOp[7].setText("H");
    labelyOp[8].setText("I");
    labelyOp[9].setText("J");
    y = 3;
    for(size_t i = 0; i < 10; ++i) {
        myLayout->addWidget(&labelyOp[i], y, 12,  Qt::AlignmentFlag::AlignRight);
        ++y;
    }
    // инициализация поля
    y = 2;
    for(size_t j = 0; j < 10; ++j) {
        int x = 3;
        for(size_t i = 0; i < 10;  ++i) {
            myLayout->addWidget(createButton(i, j), x, y);
            x += 1;
        }
        y += 1;
    }

    y = 14;
    for(size_t j = 0; j < 10; ++j) {
        int x = 3;
        for(size_t i = 0; i < 10;  ++i) {
            myLayout->addWidget(createInactiveButton(i, j), x, y);
            x += 1;
        }
        y += 1;
    }

    initializeShip(); // расположить рандомно корабли
    setLayout(myLayout.get());

}

QPushButton* widgetInputBoard::createButton(size_t i, size_t j) {
    QPushButton* pcmd = new QPushButton{""};
    pcmd->setMinimumSize(30, 30);
    pcmd->setMaximumSize(30, 30);
    connect(pcmd, SIGNAL(clicked()), this, SLOT(slotButtonClicked()));
    setShip[pcmd] = std::make_tuple(i, j, false);
    return pcmd;
}


void widgetInputBoard::choose(size_t i, size_t j) {
    auto& [ptrButton, isShip] = (*ptrTableShip)[i][j];
    if (isShip) {
        ++numberOfHitsOpponent;
        ptrButton->setStyleSheet("background-color:"+lstColor[RED].name());
        progressBarUsr->setText(tr("Ваших кораблей осталось: ") + QString::number(10 - numberOfHitsOpponent));
    } else {
        ptrButton->setStyleSheet("background-color:"+lstColor[YELLOW].name());
    }
}


void widgetInputBoard::slotButtonClicked() {
    auto ptrButton = reinterpret_cast<QPushButton*>(sender());
    // если попали, то ставить красный, иначе, жёлтый
    if (std::get<2>(setShip[ptrButton])) {
        ++numberOfHits;
        ptrButton->setStyleSheet("background-color:" + lstColor[RED].name());
        progressBarOp->setText(tr("Кораблей противника осталось: ") + QString::number(10 - numberOfHits));
    } else {
        ptrButton->setStyleSheet("background-color:" + lstColor[YELLOW].name());
    }
    ptrButton->setEnabled(false);
    // ход компьютера
    int index = rand() % lstChose.size();
    auto it = lstChose.begin();
    std::advance(it, index);
    choose(it->first, it->second);
    lstChose.erase(it);

    if (numberOfHits == 10) { // вы выйграли!!!
        QMessageBox msgBox;
        msgBox.setWindowTitle("Поздравление");
        msgBox.setText("Поздравляем, Вы выйграли!");
        msgBox.exec();
        std::for_each(std::begin(setShip), std::end(setShip), [](auto & el){
            auto& ptrBut = el.first;
            ptrBut->setEnabled(false);
        });
    } else if (numberOfHitsOpponent == 10) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Неудача");
        msgBox.setText("О нет, Вы проиграли, не расстраивайтесь!");
        msgBox.exec();
        std::for_each(std::begin(setShip), std::end(setShip), [](auto & el){
            auto& ptrBut = el.first;
            ptrBut->setEnabled(false);
        });
    }

}

std::list<std::pair<int, int>> widgetInputBoard::initLstChose() {
    std::list<std::pair<int, int>> lstRes;
    for(size_t i = 0; i < 10; ++i) {
        for(size_t j = 0; j < 10; ++j) {
            lstRes.emplace_back(std::make_pair(i, j));
        }
    }
    return lstRes;
}

void widgetInputBoard::initializeShip() {
    QList<std::pair<int, int>> listCoord;
    listCoord.reserve(10 * 10);
    for(size_t i = 0; i < 10; ++i) {
        for(size_t j = 0; j < 10; ++j) {
            listCoord.emplaceBack(i, j);
        }
    }
    const size_t count = 10; // кол-во кораблей
    for(size_t i = 0; i < count; ++i) {
        size_t index = std::rand() % listCoord.size();
        auto it = listCoord.begin();
        std::advance(it, index);

        auto ship_iter = std::find_if(std::begin(setShip), std::end(setShip), [&it](const auto &el){
            const auto&[i, j, ignore_val] = el.second;
            if (i == it->first && j == it->second) {
                return true;
            } else {
                return false;
            }
        });
        std::get<2>(ship_iter->second) = true;
        listCoord.erase(it);
    }
}

size_t widgetInputBoard::getNumberOfHints() const noexcept {
    return numberOfHits;
}

QPushButton* widgetInputBoard::createInactiveButton(size_t i, size_t j) {
    QPushButton* pcmd = new QPushButton{""};
    pcmd->setMinimumSize(30, 30);
    pcmd->setMaximumSize(30, 30);
    pcmd->setEnabled(false);
    (*ptrTableShip)[i][j].first = pcmd; // связать поле и кнопку
    if ((*ptrTableShip)[i][j].second) {
        pcmd->setStyleSheet("background-color:" + lstColor[GRAY].name());
    }
    return pcmd;
}

widgetInputBoard::~widgetInputBoard() {}
