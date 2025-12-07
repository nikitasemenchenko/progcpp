#include "TaskWidget.h"
#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WHBoxLayout.h>
#include <fstream>

TaskWidget::TaskWidget(const Wt::WString& text): Wt::WContainerWidget(), taskText(text) {
    auto box = std::make_unique<Wt::WHBoxLayout>();

    auto textWidget = box->addWidget(std::make_unique<Wt::WText>(taskText), 1);
    textWidget->setStyleClass("task-text");

    auto deleteButton = box->addWidget(std::make_unique<Wt::WPushButton>("Удалить"));
    deleteButton->setStyleClass("delete-button");
    deleteButton->clicked().connect(this, &TaskWidget::deleteTask);

    this->setLayout(std::move(box));
    this->setStyleClass("task");
}

void TaskWidget::deleteTask()
{

    std::ofstream file("tasks.txt", std::ios::trunc); // очищаем файл и записываем заново

    for (auto widget : this->parent()->children()) {
        auto task = dynamic_cast<TaskWidget*>(widget);
        if (task != nullptr && task != this) {
            file << task->getText().toUTF8() << "\n";
        }
    }

    file.close();

    this->removeFromParent();
}