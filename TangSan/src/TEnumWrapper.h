/*!
 * \file TEnumWrapper.h
 * \brief 枚举相关
 */
#ifndef TENUMWRAPPER_H
#define TENUMWRAPPER_H
#include <QObject>

class TEnumWrapper : public QObject {
    Q_OBJECT
    Q_CLASSINFO("RegisterEnumClassesUnscoped", "false")
  public:
    explicit TEnumWrapper(QObject* parent = nullptr) : QObject(parent) {}
    ~TEnumWrapper() {}

    // 基本元素
    enum BasicElements {
        BE_Item,
        BE_Rectangle,
        BE_Text,
        BE_Image,
        BE_Button,
        BE_NUM  // 总数
    };
    Q_ENUM(BasicElements)

    // 组件封装
    enum Components {
        CO_Button,
        CO_Text,
        CO_Image,
        CO_NUM  // 总数
    };
    Q_ENUM(Components)
};

#endif  // TENUMWRAPPER_H

/*
 * 使用枚举类时，可以有多个使用相同标识符的枚举。 未注册的注册将被最后注册的枚举覆盖。
 *  对于包含此类名称冲突的类，可以通过使用特殊的Q_CLASSINFO宏注释类来禁用无范围的注册。
 *  将名称RegisterEnumClassesUnscoped与false一起使用，以防止将作用域枚举合并到相同的名称空间中。
 */
