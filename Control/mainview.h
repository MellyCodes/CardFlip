#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <Model/Card.h>
#include <Model/Deck.h>
#include <QMainWindow>
#include <vector>
#include <memory>
#include <QPushButton>
#include "Model/game.h"
#include <QLabel>


namespace Ui {
class MainView;
}

class CardQPushButton;

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = 0);
    ~MainView();

private slots:
    void onCardClick();

    void onNewGameClick();

//methods
private:

    void drawView();
//members
private:
    Ui::MainView *ui;

    std::unique_ptr<Deck> deck;


    QLabel* scoreLabel;

    std::vector<CardQPushButton*> cardDisplayBtns;
 //change to a vector. to deal 32 cards in a grid...refer to demo03 (tic tac toe)


    Game *game;


};

#endif // MAINVIEW_H
