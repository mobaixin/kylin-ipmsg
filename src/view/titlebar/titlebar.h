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

#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "menumodule.h"
#include "../common/globalsizedata.h"

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = nullptr);
    ~TitleBar();

    // 初始化组件
    void setWidgetUi();

    // 设置组件样式
    void setWidgetStyle();

private:
    // 整体界面布局
    QHBoxLayout *pLayout;

    QPushButton *m_pIconBtn;        // 应用图标
    QLabel *m_pFuncLabel;           // 界面标识
    menuModule *menuBar;            /*菜单按钮*/
    QPushButton *m_pMinimizeButton; /*最小化按钮*/
    QPushButton *m_pCloseButton;    /*关闭按钮*/

protected:

#ifdef __V10__
    // 进行鼠标界面的拖动
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
#endif

private slots:

    // 进行置顶、最小化、关闭操作
    void onClicked();
};


#endif // TITLEBAR_H
