#include "mainwindow.h"
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
#include <QString>
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
#include <exception>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Clicker)
{
    ui->setupUi(this);
    UiStatic = this;
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::vector<Action> MainWindow::actions;  // Defina a variável estática aqui
MainWindow *MainWindow::UiStatic;

void MainWindow::recoverClicks(fs::path path){
    QFile file(path);
    ui->reset->click();
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        if (jsonDoc.isObject()) {
            QJsonObject jsonObject = jsonDoc.object();
            QJsonArray dados = jsonObject["passos"].toArray();
            for(int i = 0; i<dados.size(); i++){
                if(dados[i].isString()){
                    POINT p;
                    long vkCode = std::stoi(dados[i].toString().toStdString(), nullptr, 16);
                    ui->visualizarpassos->addItem(QString::fromStdString("key: " + dados[i].toString().toStdString()));
                    this->actions.push_back(Action(Action::KeyPress, p, vkCode));
                }else{
                    QJsonArray click = dados[i].toArray();
                    ui->visualizarpassos->addItem("X: " + click[0].toString() + ", Y: " + click[1].toString());
                    long x = click[0].toString().toLong();
                    long y = click[1].toString().toLong();
                    POINT p;
                    p.x = x;
                    p.y = y;
                    this->actions.push_back(Action(Action::Click, p, 0));
                }
            }
        }
    }

    removeKeyboardHook();
    removeMouseHook();
}


void MainWindow::recordClicks() {

    std::mt19937 gerador(std::random_device{}());

    // Crie uma distribuição uniforme entre um valor mínimo e máximo
    std::uniform_int_distribution<int> distribuicao(1, 100);

    // Gere um número aleatório
    int numero_aleatorio = distribuicao(gerador);

    QJsonObject jsonObject;

    QJsonArray Passos;

    for (int i = 0; i < actions.size(); i++) {
        if(actions[i].type == Action::Click){
            QJsonArray cods;

            // Crie objetos QJsonValue com os valores inteiros x e y
            QJsonValue xValue(QJsonValue::fromVariant(QVariant::fromValue(actions[i].cord.x)));
            QJsonValue yValue(QJsonValue::fromVariant(QVariant::fromValue(actions[i].cord.y)));

            // Adicione os objetos QJsonValue ao QJsonArray cods
            cods.append(xValue);
            cods.append(yValue);

            // Adicione o QJsonArray cods ao QJsonArray Passos
            Passos.append(cods);
        }else{
            std::stringstream ss;
            ss << "0x" << std::hex << actions[i].key;
            std::string vkCodeStr = ss.str();
            QJsonValue vkCodeQValue(QString::fromStdString(vkCodeStr));

            Passos.append(vkCodeQValue);
        }
    }


    jsonObject["passos"] = Passos;

    QJsonDocument jsonDoc(jsonObject);
    QString fileName = QString::number(numero_aleatorio) + "dados.json";
    QFile file("..\\PassosSalvos\\"+fileName);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(jsonDoc.toJson());
        file.close();
    }

    this->updateClikSaves();

    removeKeyboardHook();
    removeMouseHook();
}

void MainWindow::showMsgRecord() {
    try{
        if(recording){
            ui->groupMsgRecord->setVisible(true);
            ui->recordButton->setText("Parar Gravação");
    //        QMessageBox::information(nullptr, "Gravando", "Gravando clickes");
            recording = false;
            installMouseHook();
            installKeyboardHook();
        }else{
            recording = true;
            ui->groupMsgRecord->setVisible(false);
            ui->recordButton->setText("Gravar Passos");
    //        QMessageBox::information(nullptr, "Parando gravação", "Parando a gravação clickes");
            removeMouseHook();
            removeKeyboardHook();
            recordClicks();
        }
    }catch(const std::exception& e){
        QMessageBox::information(nullptr, "Gravando", "Erro inesperado ocorreu: " + QString::fromStdString(e.what()));
        removeMouseHook();
        removeKeyboardHook();
    }
}

std::vector<std::string> MainWindow::LerArquivo(std::string dic) {
    try {

        std::vector<std::string> linhas;

        std::ifstream arquivo;
        arquivo.open(dic);

        if (arquivo.is_open()) {
            std::istream_iterator<std::string> it(arquivo);
            std::istream_iterator<std::string> feof;

            while (it != feof) {
                linhas.push_back(*it);
                ++it;
            }
            arquivo.close();
        }

        return linhas;
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw std::runtime_error("Erro ao abrir o arquivo");
    }
}


std::vector<std::string> MainWindow::listDir(fs::path diretorio) {
    try {
        std::vector<std::string> dirs;

        if (fs::exists(diretorio)) {
            for (const auto& pt : fs::directory_iterator(diretorio)) {
                dirs.push_back(pt.path().string());
            }
        }

        return dirs;  // Adicione esta linha para retornar o vetor
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        throw std::runtime_error("Erro ao abrir o arquivo");
    }
}


void MainWindow::execMacroClick(){
    macro.detach();

    int i = ui->repeticoes->text().toInt();
    for(int j = 0; j<i; j++){
        for (int i = 0; i < actions.size(); i++) {
            if(actions[i].type == Action::Click){
                SetCursorPos(actions[i].cord.x, actions[i].cord.y);
                click();
                Sleep(ui->clickSpeed->text().toInt());
            }else{
                int v = ui->clickSpeed->text().toInt();
                typeText(actions[i].key, v);
            }
        }
    }
}

void MainWindow::resetClicks(){
    UiStatic->ui->visualizarpassos->clear();
    actions.clear();
    removeMouseHook();
    removeKeyboardHook();
}


void MainWindow::click() {
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}


void MainWindow::pressKeys(const std::vector<WORD>& keyCodes) {
    std::vector<INPUT> inputs;
    inputs.reserve(keyCodes.size() * 2);

    for (WORD keyCode : keyCodes) {
        INPUT pressEvent = {0};
        pressEvent.type = INPUT_KEYBOARD;
        pressEvent.ki.wVk = keyCode;

        INPUT releaseEvent = {0};
        releaseEvent.type = INPUT_KEYBOARD;
        releaseEvent.ki.wVk = keyCode;
        releaseEvent.ki.dwFlags = KEYEVENTF_KEYUP;

        inputs.push_back(pressEvent);
        inputs.push_back(releaseEvent);
    }

    SendInput(static_cast<UINT>(inputs.size()), inputs.data(), sizeof(INPUT));
}

void MainWindow::typeText(const long keyCode, int delay) {
    if (keyCode) {
        std::vector<WORD> keyCodes;
        keyCodes.push_back(keyCode);
        pressKeys(keyCodes);
        Sleep(delay);
    }
}

void MainWindow::updateClikSaves(){
    fs::path dic = "..\\PassosSalvos";
    UiStatic->ui->listaconjuntopassos->clear();
    if(!fs::exists(dic)){
        dic = "..\\PassosSalvos";
        if(fs::exists(dic)){
            std::vector<std::string> paths = listDir(dic);

            if(paths.size() == 0){
                return;
            }
            for(int i = 0;  i<paths.size(); i++){
                QString val = QString::fromStdString(paths[i]);
                UiStatic->ui->listaconjuntopassos->addItem(val);
            }
        }else{
            QMessageBox::information(nullptr, "Erro", "Erro ao criar o diretório de passos salvos");
        }
    }else{
        std::vector<std::string> paths = listDir(dic);

        if(paths.size() == 0){
            return;
        }
        for(int i = 0;  i<paths.size(); i++){
            QString val = QString::fromStdString(paths[i]);
            UiStatic->ui->listaconjuntopassos->addItem(val);
        }
    }
}

void MainWindow::onItemPressed(QListWidgetItem* item){

}

void MainWindow::onItemDropped(QListWidgetItem* item) {
    QMessageBox::information(nullptr, "Item", item->text());
}
