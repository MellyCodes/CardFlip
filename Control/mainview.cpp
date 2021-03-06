#include "Control/mainview.h"
#include "ui_mainview.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QString>
#include <QFont>
#include <View/cardqpushbutton.h>
#include <QLabel>


MainView::MainView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainView)
{
    srand(time(0));
    ui->setupUi(this);    

    deck = std::unique_ptr<Deck>(new Deck);
    deck->shuffle();


    game = new Game();
    //unique_ptr<Game> game;
    //game* std::unique_ptr <Game> = (new Game);

    //vertical layout
    auto vlmain = new QVBoxLayout(ui->centralWidget);

    //horizontal layout
    auto cardsLayout = new QGridLayout();
    vlmain->addLayout(cardsLayout);

    auto shuffleLayout = new QHBoxLayout();
    vlmain->addLayout(shuffleLayout);

    // add gridlayout **
    //QGridLayout* grid = new QGridLayout();
    QFont font;
    font.setPixelSize(40);

    for(int i=0;i<32;i++)
    {
        auto* btn = new CardQPushButton(i);

        game->setCardAtN(deck->drawCard());
        ////////////////////////////////
        btn->setFont(font);
        btn->setMinimumSize(QSize(128,192));
        btn->setMaximumSize(QSize(128,192));
        btn->setText("");
        btn->setStyleSheet("border-image:url(:/new/Media/Media/cardback.png)");

        cardsLayout->addWidget(btn,i%4,i/4); //set buttons on a grid
            connect(btn,
                    &CardQPushButton::clicked, //connect buttons to clicked event
                    this, //parent
                    &MainView::onCardClick); //clicked event calls onButtonClick code

            cardDisplayBtns.push_back(btn); //insert buttons in vector

            //grid->addWidget(cardDisplayBtns[i]);
    }

    //                          -> hlShuffle

    ui->centralWidget->setStyleSheet(QStringLiteral("background-color:rgb(23, 101, 17);"));

    // set up shuffleButton

   auto* newGameButton = new QPushButton();
   shuffleLayout->addWidget(newGameButton);
   newGameButton->setText("Shuffle");
   newGameButton->setMinimumSize(QSize(128,20));
   newGameButton->setMaximumSize(QSize(128,20));
   newGameButton->setStyleSheet(QStringLiteral("background-color:aliceblue"));

    connect(newGameButton,
            &QPushButton::clicked,
            this,
            &MainView::onNewGameClick);

    ///////////////////
    scoreLabel = new QLabel();
    shuffleLayout->addWidget(scoreLabel);
    scoreLabel->setMaximumWidth(100);
    scoreLabel->setText("SCORE:  0");
    scoreLabel->setStyleSheet(QStringLiteral("color:white"));

}

MainView::~MainView()
{
    delete ui;
}

void MainView::onCardClick(){

    CardQPushButton* btn = dynamic_cast<CardQPushButton*>(sender());

    game->selectCardN(btn->getIndex());


    scoreLabel->setText("SCORE:  " + QString::number(game->getScore()));

    drawView();
}


void MainView::onNewGameClick(){


    deck = std::unique_ptr<Deck>(new Deck);
    deck->shuffle();
    game = new Game();

    for (int i = 0 ; i<32;i++){

        game->setCardAtN(deck->drawCard());
    }

    scoreLabel->setText("SCORE:  0");
    drawView();

}

void MainView::drawView(){


    for(auto c : cardDisplayBtns)
    {
        //getCardN
        CardPtr card = game->getCardN(c->getIndex());

        if(card->isMatched())
        {
            if(card->getColor()== CardColor::Red){
               c->setStyleSheet("border-image:url(:/Media/cardfrontGray.png); "
                                             "color: red;");
            }
            else{
               c->setStyleSheet("border-image:url(:/Media/cardfrontGray.png); "
                                             "color: black;");
            }

            c->setText(QString::fromStdString(card->toString()));

        }else
        {
            if(card->isFlipped())
            {
                if(card->getColor()== CardColor::Red){
                   c->setStyleSheet("border-image:url(:/new/Media/Media/cardfront.png); "
                                                 "color: red;");
                }
                else{
                   c->setStyleSheet("border-image:url(:/new/Media/Media/cardfront.png); "
                                                 "color: black;");
                }

                c->setText(QString::fromStdString(card->toString()));

            }
            else
            {
                c->setStyleSheet("border-image:url(:/new/Media/Media/cardback.png);");
                c->setText("");

            }
        }
    }
}
