#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "action.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QListWidgetItem>
#include <QFile>
#include <QMessageBox>
#include <QStringList>
#include <QJsonValue>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <locale.h>
#include <vector>
#include <iterator>
#include <windows.h>
#include <unordered_map>
#include <conio.h>
#include <random>
#include <thread>

namespace fs = std::filesystem;

QT_BEGIN_NAMESPACE
namespace Ui { class Clicker; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void recordClicks();
    void recoverClicks(fs::path path);
    void showMsgRecord();
    std::vector<std::string> LerArquivo(std::string dic);
    std::vector<std::string> listDir(fs::path diretorio);
    void execMacroClick();
    void resetClicks();
    void click();
    void pressKeys(const std::vector<WORD>& keyCodes);
    void typeText(const long keyCode, int delay = 100);
    void onItemPressed(QListWidgetItem* item);
    void onItemDropped(QListWidgetItem* item);
    void updateClikSaves();

    void startMacro(){
        macro = std::thread(&MainWindow::execMacroClick, this);
    }

public slots:

    void initialize(){
        ui->groupMsgRecord->setVisible(false);

        connect(ui->recordButton, SIGNAL(clicked()), this, SLOT(showMsgRecord()));
        connect(ui->start, SIGNAL(clicked()), this, SLOT(startMacro()));
        connect(ui->reset, SIGNAL(clicked()), this, SLOT(resetClicks()));
        connect(ui->update, SIGNAL(clicked()), this, SLOT(updateClikSaves()));
//        connect(ui->tecladobutton, SIGNAL(clicked()), this, SLOT(teclado()));
        //        ui->listaconjuntopassos
        //        ui->visualizarpassos

        if(!fs::exists("..\\PassosSalvos")){
            fs::path passos = "..\\PassosSalvos";
            bool success = fs::create_directory(passos);
            if(!success){
                QMessageBox msgBox;
                msgBox.setText("Erro ao criar o diretório de passos salvos");

                    // Adicione botões personalizados usando setStandardButtons
                QPushButton* customButton1 = msgBox.addButton("Criar aqui", QMessageBox::ActionRole);
                QPushButton* customButton2 = msgBox.addButton("Cancelar", QMessageBox::ActionRole);

                // Defina os botões padrão (opcional)
                msgBox.setDefaultButton(customButton1);

                msgBox.exec();

                if (msgBox.clickedButton() == customButton1) {
                    fs::path passos = ".\\PassosSalvos";
                    bool success = fs::create_directory(passos);
                    if(!success){
                        QMessageBox::information(nullptr, "Erro", "Erro ao criar o diretório de passos salvos");
                    }
                } else if (msgBox.clickedButton() == customButton2) {
                    msgBox.hide();
                }
            }
        }
    }

private:
    Ui::Clicker *ui;

    bool recording = true;
    bool tel = true;
    HHOOK mouseHook;
    HHOOK keyboardHook;
    static MainWindow *UiStatic;
    static std::vector<Action> actions;
    std::thread macro;

    void installMouseHook() {
        mouseHook = SetWindowsHookEx(WH_MOUSE_LL, mouseHookProc, GetModuleHandle(nullptr), 0);
        if (mouseHook == nullptr) {
            QMessageBox::critical(this, "Error", "Failed to install mouse hook.");
            QApplication::quit();
        }
    }

    void removeMouseHook() {
        if (mouseHook != nullptr) {
            UnhookWindowsHookEx(mouseHook);
            mouseHook = nullptr; // Marque como removido
        }
    }

    static LRESULT CALLBACK mouseHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
        if (nCode == HC_ACTION) {
            if (wParam == WM_LBUTTONDOWN) {
                POINT click;
                GetCursorPos(&click);
                actions.push_back(Action(Action::Click, click, 0));

                QString item = "X: " + QString::number(click.x) + ", Y: " + QString::number(click.y);
                UiStatic->ui->visualizarpassos->addItem(item);
            }
        }
        return CallNextHookEx(nullptr, nCode, wParam, lParam);
    }

    void installKeyboardHook() {
        keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboardHookProc, GetModuleHandle(nullptr), 0);
        if (keyboardHook == nullptr) {
            QMessageBox::critical(this, "Error", "Failed to install keyboard hook.");
            QApplication::quit();
        }
    }

    void removeKeyboardHook() {
        if (keyboardHook != nullptr) {
            UnhookWindowsHookEx(keyboardHook);
            keyboardHook = nullptr;
        }
    }

    static LRESULT CALLBACK keyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
        if (nCode == HC_ACTION) {
            if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
                KBDLLHOOKSTRUCT* pkbhs = (KBDLLHOOKSTRUCT*)lParam;
                int key = pkbhs->vkCode;
                POINT nul;

                QString item = "Key: " + QString::number(key);
                UiStatic->ui->visualizarpassos->addItem(item);
                actions.push_back(Action(Action::KeyPress, nul, key));

                // Converter int para string
                // std::stringstream ss;
                // ss << "0x" << std::hex << key;
                // std::string vkCodeStr = ss.str();

                // Converter a string hexadecimal de volta para o valor vkCode
                // int vkCode = std::stoi(vkCodeStr, nullptr, 16);
            }
        }
        return CallNextHookEx(nullptr, nCode, wParam, lParam);
    }
};
#endif // MAINWINDOW_H
