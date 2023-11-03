/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "customlistwidget.h"

QT_BEGIN_NAMESPACE

class Ui_Clicker
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_4;
    CustomListWidget *visualizarpassos;
    QListWidget *listaconjuntopassos;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_8;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *clickSpeed;
    QSpacerItem *horizontalSpacer_5;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *repeticoes;
    QSpacerItem *horizontalSpacer_7;
    QGroupBox *groupMsgRecord;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *gravacaolayout;
    QSpacerItem *horizontalSpacer_3;
    QLabel *labelRecord;
    QLabel *recordIcon;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *recordButton;
    QPushButton *reset;
    QPushButton *start;
    QSpacerItem *horizontalSpacer_6;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Clicker)
    {
        if (Clicker->objectName().isEmpty())
            Clicker->setObjectName("Clicker");
        Clicker->resize(800, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8("1536475.png"), QSize(), QIcon::Normal, QIcon::Off);
        Clicker->setWindowIcon(icon);
        centralwidget = new QWidget(Clicker);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, -1, 0, -1);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(350, 70));
        label->setMaximumSize(QSize(0, 0));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(24);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label, 0, Qt::AlignTop);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(0, 0, -1, -1);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(200, 50));
        label_2->setMaximumSize(QSize(16777215, 100));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial")});
        font1.setPointSize(18);
        label_2->setFont(font1);
        label_2->setMargin(0);
        label_2->setIndent(10);

        horizontalLayout_5->addWidget(label_2);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMaximumSize(QSize(16777215, 100));
        label_3->setFont(font1);

        horizontalLayout_5->addWidget(label_3);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalLayout_4->setContentsMargins(-1, 0, -1, -1);
        visualizarpassos = new CustomListWidget(centralwidget);
        visualizarpassos->setObjectName("visualizarpassos");
        visualizarpassos->setMinimumSize(QSize(300, 150));
        visualizarpassos->setAcceptDrops(true);
        visualizarpassos->setStyleSheet(QString::fromUtf8(""));
        visualizarpassos->setProperty("showDropIndicator", QVariant(true));
        visualizarpassos->setDragDropOverwriteMode(true);
        visualizarpassos->setDragDropMode(QAbstractItemView::DropOnly);
        visualizarpassos->setDefaultDropAction(Qt::CopyAction);

        horizontalLayout_4->addWidget(visualizarpassos);

        listaconjuntopassos = new QListWidget(centralwidget);
        listaconjuntopassos->setObjectName("listaconjuntopassos");
        listaconjuntopassos->setEnabled(true);
        listaconjuntopassos->setMinimumSize(QSize(300, 150));
        listaconjuntopassos->setAcceptDrops(false);
        listaconjuntopassos->setProperty("showDropIndicator", QVariant(false));
        listaconjuntopassos->setDragEnabled(true);
        listaconjuntopassos->setDragDropOverwriteMode(true);
        listaconjuntopassos->setDragDropMode(QAbstractItemView::DragOnly);
        listaconjuntopassos->setDefaultDropAction(Qt::CopyAction);
        listaconjuntopassos->setResizeMode(QListView::Adjust);

        horizontalLayout_4->addWidget(listaconjuntopassos);


        verticalLayout->addLayout(horizontalLayout_4);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        horizontalLayout_8 = new QHBoxLayout(groupBox_3);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        groupBox = new QGroupBox(groupBox_3);
        groupBox->setObjectName("groupBox");
        horizontalLayout_6 = new QHBoxLayout(groupBox);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        clickSpeed = new QLineEdit(groupBox);
        clickSpeed->setObjectName("clickSpeed");
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(clickSpeed->sizePolicy().hasHeightForWidth());
        clickSpeed->setSizePolicy(sizePolicy1);
        clickSpeed->setMinimumSize(QSize(150, 30));

        horizontalLayout_6->addWidget(clickSpeed);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);


        horizontalLayout_8->addWidget(groupBox);

        groupBox_2 = new QGroupBox(groupBox_3);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setMinimumSize(QSize(0, 60));
        horizontalLayout_7 = new QHBoxLayout(groupBox_2);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        repeticoes = new QLineEdit(groupBox_2);
        repeticoes->setObjectName("repeticoes");
        sizePolicy1.setHeightForWidth(repeticoes->sizePolicy().hasHeightForWidth());
        repeticoes->setSizePolicy(sizePolicy1);
        repeticoes->setMinimumSize(QSize(150, 30));

        horizontalLayout_7->addWidget(repeticoes);

        horizontalSpacer_7 = new QSpacerItem(188, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);


        horizontalLayout_8->addWidget(groupBox_2);


        verticalLayout->addWidget(groupBox_3);

        groupMsgRecord = new QGroupBox(centralwidget);
        groupMsgRecord->setObjectName("groupMsgRecord");
        groupMsgRecord->setEnabled(false);
        verticalLayout_2 = new QVBoxLayout(groupMsgRecord);
        verticalLayout_2->setObjectName("verticalLayout_2");
        gravacaolayout = new QHBoxLayout();
        gravacaolayout->setObjectName("gravacaolayout");
        gravacaolayout->setContentsMargins(-1, 0, -1, -1);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gravacaolayout->addItem(horizontalSpacer_3);

        labelRecord = new QLabel(groupMsgRecord);
        labelRecord->setObjectName("labelRecord");
        labelRecord->setMinimumSize(QSize(100, 0));
        labelRecord->setMaximumSize(QSize(100, 16777215));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Arial")});
        font2.setPointSize(16);
        labelRecord->setFont(font2);

        gravacaolayout->addWidget(labelRecord);

        recordIcon = new QLabel(groupMsgRecord);
        recordIcon->setObjectName("recordIcon");
        sizePolicy.setHeightForWidth(recordIcon->sizePolicy().hasHeightForWidth());
        recordIcon->setSizePolicy(sizePolicy);
        recordIcon->setMaximumSize(QSize(60, 60));
        recordIcon->setPixmap(QPixmap(QString::fromUtf8("3998038.png")));
        recordIcon->setScaledContents(true);

        gravacaolayout->addWidget(recordIcon);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gravacaolayout->addItem(horizontalSpacer_4);


        verticalLayout_2->addLayout(gravacaolayout);


        verticalLayout->addWidget(groupMsgRecord);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(-1, 0, -1, -1);
        recordButton = new QPushButton(centralwidget);
        recordButton->setObjectName("recordButton");
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(100);
        sizePolicy2.setVerticalStretch(100);
        sizePolicy2.setHeightForWidth(recordButton->sizePolicy().hasHeightForWidth());
        recordButton->setSizePolicy(sizePolicy2);
        recordButton->setMinimumSize(QSize(150, 40));
        recordButton->setMaximumSize(QSize(200, 50));
        recordButton->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_2->addWidget(recordButton);

        reset = new QPushButton(centralwidget);
        reset->setObjectName("reset");
        sizePolicy2.setHeightForWidth(reset->sizePolicy().hasHeightForWidth());
        reset->setSizePolicy(sizePolicy2);
        reset->setMinimumSize(QSize(150, 40));
        reset->setMaximumSize(QSize(200, 50));
        reset->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_2->addWidget(reset);

        start = new QPushButton(centralwidget);
        start->setObjectName("start");
        sizePolicy2.setHeightForWidth(start->sizePolicy().hasHeightForWidth());
        start->setSizePolicy(sizePolicy2);
        start->setMinimumSize(QSize(150, 40));
        start->setMaximumSize(QSize(200, 50));
        start->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_2->addWidget(start);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_3->addLayout(verticalLayout);

        Clicker->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Clicker);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        Clicker->setMenuBar(menubar);
        statusbar = new QStatusBar(Clicker);
        statusbar->setObjectName("statusbar");
        Clicker->setStatusBar(statusbar);

        retranslateUi(Clicker);

        QMetaObject::connectSlotsByName(Clicker);
    } // setupUi

    void retranslateUi(QMainWindow *Clicker)
    {
        Clicker->setWindowTitle(QCoreApplication::translate("Clicker", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("Clicker", "Automatiza\303\247\303\243o de click", nullptr));
        label_2->setText(QCoreApplication::translate("Clicker", "Passos: ", nullptr));
        label_3->setText(QCoreApplication::translate("Clicker", "Ultmos salvos:", nullptr));
        groupBox_3->setTitle(QString());
        groupBox->setTitle(QCoreApplication::translate("Clicker", "Velocidade do click(Milissegundos)", nullptr));
        clickSpeed->setText(QCoreApplication::translate("Clicker", "100", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Clicker", "Repeti\303\247\303\265es", nullptr));
        repeticoes->setText(QCoreApplication::translate("Clicker", "1", nullptr));
        groupMsgRecord->setTitle(QCoreApplication::translate("Clicker", "Mensagem", nullptr));
        labelRecord->setText(QCoreApplication::translate("Clicker", "Gravando", nullptr));
        recordIcon->setText(QString());
        recordButton->setText(QCoreApplication::translate("Clicker", "Gravar Passos", nullptr));
        reset->setText(QCoreApplication::translate("Clicker", "Resetar", nullptr));
        start->setText(QCoreApplication::translate("Clicker", "Come\303\247ar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Clicker: public Ui_Clicker {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
