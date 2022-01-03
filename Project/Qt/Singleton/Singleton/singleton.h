#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_singleton.h"

template <class T>
class Singleton : public QMainWindow
{
    Q_OBJECT

public:
    static T* Instance() {
        if (!m_pInstance) {
            m_bInitialized = true;
            m_pInstance = new T;
        }
        assert(m_pInstance != NULL);
        return m_pInstance;
    }

    static void destroyInstance() {
        if (m_pInstance) {
            delete m_pInstance;
            m_pInstance = NULL;
        }
    }

protected:
    Singleton(QWidget *parent = Q_NULLPTR);

private:
    static T* m_pInstance;
    Singleton(Singleton const&);
    Singleton& operator = (Singleton const&);
    Ui::SingletonClass ui;
};

template <class T> T* Singleton<T>::m_pInstance = NULL;
template <class T> bool Singleton<T>::m_bInitialized = false;
