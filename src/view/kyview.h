/*
 * Copyright (C) 2020, KylinSoft Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef KYVIEW_H
#define KYVIEW_H

#include <QWidget>
#include <QApplication>

class KyView : public QWidget
{
    Q_OBJECT

public:
    explicit KyView(QWidget *parent = 0);
    ~KyView();

    // 生成静态实例
    static KyView *getInstance();

    // 初始化组件
    // void setWidgetUi();

    // 设置组件样式
    // void setWidgetStyle();

    // 最小化状态下拉起主界面
    void pullUpWindow();
private:
    /* data */
};




#endif // KYVIEW_H
