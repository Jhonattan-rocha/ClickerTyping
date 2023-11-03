#include "customlistwidget.h"
#include "mainWindowInstance.h"
#include <filesystem>

namespace fs = std::filesystem;

CustomListWidget::CustomListWidget(QWidget *parent)
    : QListWidget{parent}
{
    this->setW(w);
}

void CustomListWidget::updatePaths(fs::path path){
    w->resetClicks();
    w->recoverClicks(path);
}
