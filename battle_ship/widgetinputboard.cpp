
#include "widgetinputboard.h"

widgetInputBoard::widgetInputBoard(ptr_table_t table, QWidget *parent)
    : QWidget{parent}, myLayout(std::make_shared<QGridLayout>()), ptrTableShip(table),
    setShip(), lstChose(initLstChose()), numberOfHits(0)
{
    resize(800, 400);
    int y = 1;
    for(size_t j = 0; j < 10; ++j) {
        int x = 1;
        for(size_t i = 0; i < 10;  ++i) {
            myLayout->addWidget(createButton(i, j), x, y, Qt::AlignmentFlag::AlignBottom | Qt::AlignmentFlag::AlignLeft);
            x += 1;
        }
        y += 1;
    }

    y = 14;
    for(size_t j = 0; j < 10; ++j) {
        int x = 1;
        for(size_t i = 0; i < 10;  ++i) {
            myLayout->addWidget(createInactiveButton(i, j), x, y, Qt::AlignmentFlag::AlignBottom | Qt::AlignmentFlag::AlignRight);
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
    connect(pcmd, SIGNAL(clicked()), this, SLOT(slotButtonClicked()));
    setShip[pcmd] = std::make_tuple(i, j, false);
    return pcmd;
}


void widgetInputBoard::choose(size_t i, size_t j) {
    auto& [ptrButton, isShip] = (*ptrTableShip)[i][j];
    if (isShip) {
        ++numberOfHits;
        ptrButton->setStyleSheet("background-color:"+lstColor[RED].name());
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
    } else {
        ptrButton->setStyleSheet("background-color:" + lstColor[YELLOW].name());
    }
    ptrButton->setEnabled(false);
    if (numberOfHits == 10) { // вы выйграли!!!
        QMessageBox msgBox;
        msgBox.setWindowTitle("Поздравление");
        msgBox.setText("Поздравляем, Вы выйграли!");
        msgBox.exec();
        std::for_each(std::begin(setShip), std::end(setShip), [](auto & el){
            auto& ptrBut = el.first;
            ptrBut->setEnabled(false);
        });
    }
    // ход компьютера
    int index = rand() % lstChose.size();
    auto it = lstChose.begin();
    std::advance(it, index);
    choose(it->first, it->second);
    lstChose.erase(it);

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
    pcmd->setEnabled(false);
    (*ptrTableShip)[i][j].first = pcmd; // связать поле и кнопку
    if ((*ptrTableShip)[i][j].second) {
        pcmd->setStyleSheet("background-color:" + lstColor[GRAY].name());
    }
    return pcmd;
}

widgetInputBoard::~widgetInputBoard() {}
