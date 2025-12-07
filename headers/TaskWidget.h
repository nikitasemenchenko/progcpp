#pragma once
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>

class TaskWidget: public Wt::WContainerWidget {
public:
    TaskWidget(const Wt::WString& taskText);
    Wt::WString getText() const { return taskText; }
private:
    Wt::WString taskText;
    void deleteTask();

};