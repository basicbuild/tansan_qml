#include "TSystemBase.h"

CSystemBase::CSystemBase(QObject* parent) : QObject(parent) {}

QStringList CSystemBase::basicElementsList() {
    m_basicElementsList << "Item"
                        << "Rectangle"
                        << "Text"
                        << "Image"
                        << "Button";
    return m_basicElementsList;
}

void CSystemBase::setBasicElementsList(const QStringList& value) {
    m_basicElementsList = value;
    emit basicElementsListChanged();
}

QStringList CSystemBase::positioningElementList(){
    m_positioningElementList << "Row"
                        << "Column"
                        << "Grid"
                        << "Flow";
    return m_positioningElementList;
}

void CSystemBase::setPositioningElementList(const QStringList& value){
    m_positioningElementList = value;
    emit positioningElementListChanged();
}

QStringList CSystemBase::componentList() {
    m_componentList << "Button"
                    << "Text"
                    << "Image";
    return m_componentList;
}

void CSystemBase::setComponentList(const QStringList& value) {
    m_componentList = value;
    emit componentListChanged();
}

QStringList CSystemBase::modelList() {
    m_modelList << "QStringList"
                << "QList"
                << "Button"
                << "Button"
                << "Image";
    return m_modelList;
}

void CSystemBase::setModelList(const QStringList& value) {
    m_modelList = value;
    emit modelListChanged();
}

QStringList CSystemBase::featuresList(){
    m_featuresList << "弹窗方式1"
                << "弹窗方式1"
                << "弹窗方式1"
                << "弹窗方式1"
                << "弹窗方式1";
    return m_featuresList;
}

void CSystemBase::setFeaturesList(const QStringList& value){
    m_featuresList = value;
    emit featuresListChanged();
}

QStringList CSystemBase::resourcesList(){
    m_resourcesList << "《QmlBook》In Chinese"
                << "色值"
                << "Button"
                << "Button"
                << "Image";
    return m_resourcesList;
}

void CSystemBase::setResourcesList(const QStringList& value){
    m_resourcesList = value;
    emit resourcesListChanged();
}
