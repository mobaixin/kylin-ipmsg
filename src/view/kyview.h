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

#define WINDOWW 350      //窗口宽度
#define WINDOWH 686      //窗口高度
#define TITLEH 40        //标题栏高度
#define LOCALINFOH 140   //本机信息高度
#define FRIENDSLISTH 506 //好友列表高度

#include <QApplication>
#include <QVBoxLayout>

#include "titlebar/titlebar.h"
#include "localinfo/localinfo.h"

class KyView : public QWidget
{
    Q_OBJECT

public:
    explicit KyView(QWidget *parent = nullptr);
    ~KyView();

    // 生成静态实例
    static KyView *getInstance();

    // 初始化组件
    void setWidgetUi();

    // 设置组件样式
    void setWidgetStyle(); 

    // 最小化状态下拉起主界面
    void pullUpWindow();

private:
    // 整体界面窗体
    QWidget *m_mainWid;

    // 标题栏
    TitleBar *m_titleBar;

    // 本机信息
    LocalInfo *m_localInfo;

    // 整体界面布局
    QVBoxLayout *m_mainLayout;
};




#endif // KYVIEW_H
