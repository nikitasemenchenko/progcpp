#include "ToDoList.h"
#include "TaskWidget.h"
#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <memory>
#include <string>
#include <fstream>

ToDoList::ToDoList(const Wt::WEnvironment &env): WApplication(env)
{
    setTitle("ToDoList"); // заголовок страницы
    useStyleSheet(Wt::WLink("ui/style.css"));

    auto appBox = root()->addWidget(std::make_unique<Wt::WContainerWidget>());
    appBox->setStyleClass("app-container");

    appBox->addWidget(std::make_unique<Wt::WText>("<div class='app-title'>Список задач</div>", Wt::TextFormat::XHTML));
    appBox->addWidget(std::make_unique<Wt::WText>("<div>Добавьте новую задачу:</div>", Wt::TextFormat::XHTML));
    appBox->addWidget(std::make_unique<Wt::WBreak>());

    auto inputContainer = appBox->addWidget(std::make_unique<Wt::WContainerWidget>());
    inputContainer->setStyleClass("input-container");

    taskAddField = inputContainer->addWidget(std::make_unique<Wt::WLineEdit>());
    taskAddField->setPlaceholderText("Введите новую задачу...");
    taskAddField->setTextSize(50);
    taskAddField->setFocus();
    taskAddField->setStyleClass("task-input");

    auto button = inputContainer->addWidget(std::make_unique<Wt::WPushButton>("+"));
    button->setStyleClass("add-button");

    taskList = appBox->addWidget(std::make_unique<Wt::WContainerWidget>());
    taskList->setStyleClass("tasks-container");

    button->clicked().connect(this, &ToDoList::addTask);
    taskAddField->enterPressed().connect(this, &ToDoList::addTask);

    loadTasks();
}
void ToDoList::addTask() {
    if(taskAddField->text().empty()) return;


    taskList->addWidget(std::make_unique<TaskWidget>(taskAddField->text()));
    
    auto text = taskAddField->text().toUTF8();
    std::ofstream file("tasks.txt", std::ios::app); // идем в конец файла и записываем
    file << text << "\n";
    file.close();

    taskAddField->setText("");
}

void ToDoList::loadTasks() {
    std::ifstream file("tasks.txt");
    if (!file.is_open()) return;

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty()) {
            taskList->addWidget(std::make_unique<TaskWidget>(line));
        }
    }

    file.close();
};
