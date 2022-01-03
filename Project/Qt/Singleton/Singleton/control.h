#pragma once
#include <QObject> 
#include <model.h> 
#include <Singleton.h> 
#include <QDebug> 

class Control : public QObject, public Singleton<Control> { 
	Q_OBJECT 
public slots: 
void click_btn(); 
public: Control(); 
}; 

void Control::click_btn() { int num = Model::Instance()->btnCount(); Model::Instance()->set_btnCount(num+1); qDebug() << " button"; } Control::Control() { }