#ifndef TSYSTEMBASE_H
#define TSYSTEMBASEL_H

#include <QObject>
#include <QStringList>

#include "TSingleton.h"

class TSystemBase : public QObject {
    Q_OBJECT
    Q_PROPERTY(QStringList basicElementsList READ basicElementsList WRITE setBasicElementsList NOTIFY basicElementsListChanged)
    Q_PROPERTY(QStringList positioningElementList READ positioningElementList WRITE setPositioningElementList NOTIFY positioningElementListChanged)
    Q_PROPERTY(QStringList componentList READ componentList WRITE setComponentList NOTIFY componentListChanged)
    Q_PROPERTY(QStringList modelList READ modelList WRITE setModelList NOTIFY modelListChanged)
    Q_PROPERTY(QStringList featuresList READ featuresList WRITE setFeaturesList NOTIFY featuresListChanged)
    Q_PROPERTY(QStringList resourcesList READ resourcesList WRITE setResourcesList NOTIFY resourcesListChanged)
public:
    explicit TSystemBase(QObject* parent = nullptr);

    /**
     * @brief 基本元素
     *
     * @param {QString} key - 查询的关键字
     * @return
     */
    Q_INVOKABLE QStringList basicElementsList();
    Q_INVOKABLE void setBasicElementsList(const QStringList& value);

    /**
     * @brief 定位元素
     */
    Q_INVOKABLE QStringList positioningElementList();
    Q_INVOKABLE void setPositioningElementList(const QStringList& value);

    /**
     * @brief 组件封装
     */
    Q_INVOKABLE QStringList componentList();
    Q_INVOKABLE void setComponentList(const QStringList& value);

    /**
     * @brief mode view
     */
    Q_INVOKABLE QStringList modelList();
    Q_INVOKABLE void setModelList(const QStringList& value);

    /**
     * @brief 功能演示
     */
    Q_INVOKABLE QStringList featuresList();
    Q_INVOKABLE void setFeaturesList(const QStringList& value);

    /**
     * @brief 资料相关
     */
    Q_INVOKABLE QStringList resourcesList();
    Q_INVOKABLE void setResourcesList(const QStringList& value);

signals:
    void basicElementsListChanged();
    void positioningElementListChanged();
    void componentListChanged();
    void modelListChanged();
    void featuresListChanged();
    void resourcesListChanged();

private:
    QStringList m_basicElementsList = {};
    QStringList m_positioningElementList = {};
    QStringList m_componentList = {};
    QStringList m_modelList = {};
    QStringList m_featuresList = {};
    QStringList m_resourcesList = {};
};

#define SYSTEMBASE TSingleton<TSystemBase>::instance()
#endif  // TSYSTEMBASEL_H
