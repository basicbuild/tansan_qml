#include "TSystemBase.h"

TSystemBase::TSystemBase(QObject* parent) : QObject(parent) {}

QStringList TSystemBase::basicElementsList() {
    m_basicElementsList << "Item"
                        << "Rectangle"
                        << "Text"
                        << "Image"
                        << "Button";
    return m_basicElementsList;
}

void TSystemBase::setBasicElementsList(const QStringList& value) {
    m_basicElementsList = value;
    emit basicElementsListChanged();
}

QStringList TSystemBase::positioningElementList(){
    m_positioningElementList << "Row"
                        << "Column"
                        << "Grid"
                        << "Flow";
    return m_positioningElementList;
}

void TSystemBase::setPositioningElementList(const QStringList& value){
    m_positioningElementList = value;
    emit positioningElementListChanged();
}

QStringList TSystemBase::componentList() {
    m_componentList << "Button"
                    << "Text"
                    << "Image";
    return m_componentList;
}

void TSystemBase::setComponentList(const QStringList& value) {
    m_componentList = value;
    emit componentListChanged();
}

QStringList TSystemBase::modelList() {
    m_modelList << "QStringList"
                << "QList"
                << "Button"
                << "Button"
                << "Image";
    return m_modelList;
}

void TSystemBase::setModelList(const QStringList& value) {
    m_modelList = value;
    emit modelListChanged();
}

QStringList TSystemBase::featuresList(){
    m_featuresList << "弹窗方式1"
                << "弹窗方式1"
                << "弹窗方式1"
                << "弹窗方式1"
                << "弹窗方式1";
    return m_featuresList;
}

void TSystemBase::setFeaturesList(const QStringList& value){
    m_featuresList = value;
    emit featuresListChanged();
}

QStringList TSystemBase::resourcesList(){
    m_resourcesList << "《QmlBook》In Chinese"
                << "色值"
                << "Button"
                << "Button"
                << "Image";
    return m_resourcesList;
}

void TSystemBase::setResourcesList(const QStringList& value){
    m_resourcesList = value;
    emit resourcesListChanged();
}
