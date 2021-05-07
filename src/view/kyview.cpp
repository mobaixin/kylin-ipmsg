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

#include "kyview.h"

// 生成静态实例
KyView *KyView::getInstance()
{   
    static KyView *instance = nullptr;
    if (nullptr == instance) {
        instance = new KyView();
    }
    return instance;
}

KyView::KyView(QWidget *parent)
    : QWidget(parent)
{

    // 初始化组件
    setWidgetUi();

    // 设置组件样式
    setWidgetStyle();
}

KyView::~KyView()
{
}

// 最小化状态下拉起主界面
void KyView::pullUpWindow()
{
    this->showNormal();
    this->raise();
    this->activateWindow();
}

// 初始化组件
void KyView::setWidgetUi()
{
    this->setFixedSize(WINDOWW, WINDOWH);

    // mainWid = new QWidget(this);

    m_mainLayout = new QVBoxLayout(this);

    // 标题栏
    m_titleBar = new TitleBar(this);
    m_titleBar->setFixedHeight(GlobalSizeData::TITLEBAR_HEIGHT);

    // 本机信息
    m_localInfo = new LocalInfo(this);
    m_localInfo->setText("bb-本机","123.123.132.123");

    // 好友列表
    m_friendListView = new FriendListView();

    // 将组件添加到布局中
    m_mainLayout->addWidget(m_titleBar, Qt::AlignTop);
    m_mainLayout->addWidget(m_localInfo, Qt::AlignTop);
    m_mainLayout->addWidget(m_friendListView, Qt::AlignTop);

    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(0);

}

// 设置组件样式
void KyView::setWidgetStyle()
{
    this->setAutoFillBackground(true);
    this->setBackgroundRole(QPalette::Base);

    // 毛玻璃效果
    // this->setProperty("useSystemStyleBur", true);
    // this->setAttribute(Qt::WA_TranslucentBackground, true);
}
