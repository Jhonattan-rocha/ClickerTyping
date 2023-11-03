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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Clicker)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


std::vector<POINT> MainWindow::passos;  // Defina a variável estática aqui
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
            QJsonArray clicks = jsonObject["clicks"].toArray();
            for(int i = 0; i<clicks.size(); i++){
                QJsonArray click = clicks[i].toArray();
                ui->visualizarpassos->addItem("X: " + click[0].toString() + ", Y: " + click[1].toString());
                POINT p;
                p.x = click[0].toInt();
                p.y = click[1].toInt();
                this->passos.push_back(p);
            }
        }
    }
}


void MainWindow::recordClicks() {

    std::mt19937 gerador(std::random_device{}());

    // Crie uma distribuição uniforme entre um valor mínimo e máximo
    std::uniform_int_distribution<int> distribuicao(1, 100);

    // Gere um número aleatório
    int numero_aleatorio = distribuicao(gerador);

    QJsonObject jsonObject;

    QJsonArray Passos;

    for (int i = 0; i < passos.size(); i++) {
        QJsonArray cods;

        // Crie objetos QJsonValue com os valores inteiros x e y
        QJsonValue xValue(QJsonValue::fromVariant(QVariant::fromValue(passos[i].x)));
        QJsonValue yValue(QJsonValue::fromVariant(QVariant::fromValue(passos[i].y)));

        // Adicione os objetos QJsonValue ao QJsonArray cods
        cods.append(xValue);
        cods.append(yValue);

        // Adicione o QJsonArray cods ao QJsonArray Passos
        Passos.append(cods);
    }


    jsonObject["clicks"] = Passos;

    QJsonDocument jsonDoc(jsonObject);
    QString fileName = QString::number(numero_aleatorio) + "dados.json";
    QFile file("..\\PassosSalvos\\"+fileName);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(jsonDoc.toJson());
        file.close();
    }

    this->updateClikSaves();
}

void MainWindow::showMsgRecord() {
    if(recording){
        ui->groupMsgRecord->setVisible(true);
        ui->recordButton->setText("Parar Gravação");
        QMessageBox::information(nullptr, "Gravando", "Gravando clickes");
        recording = false;
        installMouseHook();
    }else{
        recording = true;
        ui->groupMsgRecord->setVisible(false);
        ui->recordButton->setText("Gravar Passos");
        QMessageBox::information(nullptr, "Parando gravação", "Parando a gravação clickes");
        removeMouseHook();
        recordClicks();
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
    int i = ui->repeticoes->text().toInt();
    for(int j = 0; j<i; j++){
        for (int i = 0; i < passos.size(); i++) {
            SetCursorPos(passos[i].x, passos[i].y);
            click();
            Sleep(ui->clickSpeed->text().toInt());
        }
    }
}

void MainWindow::resetClicks(){
    UiStatic->ui->visualizarpassos->clear();
    passos.clear();
}


void MainWindow::click() {
    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}


void MainWindow::pressKey(WORD keyCode, bool shift) {
    INPUT input[2];
    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wScan = 0;
    input[0].ki.time = 0;
    input[0].ki.dwExtraInfo = 0;
    input[0].ki.wVk = shift ? VK_SHIFT : 0; // Se shift for verdadeiro, pressione a tecla Shift
    input[0].ki.dwFlags = 0; // 0 para pressionar a tecla

    input[1] = input[0];
    input[1].ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP para liberar a tecla

    SendInput(2, input, sizeof(INPUT));

    if (keyCode != 0) {
        input[0].ki.wVk = keyCode;
        SendInput(1, input, sizeof(INPUT));
        input[1].ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, input, sizeof(INPUT));
    }
}

void MainWindow::typeText(const std::string& text, int delay) {
    for (char t : text) {
        WORD keyCode = VkKeyScan(t);
        if (keyCode) {
            // Verifique se é uma letra maiúscula e ative o Shift, se necessário
            bool isUpperCase = (keyCode & 0x0100) != 0;
            if (isUpperCase) {
                pressKey(VK_SHIFT);
            }
            // Pressione a tecla correspondente ao caractere
            pressKey(keyCode & 0xFF);
            Sleep(delay);
            // Libere o Shift, se ativado
            if (isUpperCase) {
                pressKey(VK_SHIFT, true);
            }
        }
    }
}

void MainWindow::updateClikSaves(){
    fs::path dic = "..\\PassosSalvos";
    if(!fs::exists(dic)){
        dic = ".\\PassosSalvos";
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
