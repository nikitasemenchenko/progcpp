#pragma once
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>

class ToDoList: public Wt::WApplication {
public:
    ToDoList(const Wt::WEnvironment& env);
    
private:
    Wt::WLineEdit *taskAddField; 
    Wt::WContainerWidget *taskList; //хранилище виджетов задач
    void addTask();
    void loadTasks(); //загрузить задачи из txt файла
};