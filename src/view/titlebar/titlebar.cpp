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
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include "titlebar.h"
#include "../kyview.h"
#include "../common/xatom-helper.h"

TitleBar::TitleBar(QWidget *parent) 
    : QWidget(parent)
{
    // 初始化组件
    setWidgetUi();

    // 设置组件样式
    setWidgetStyle();
}

TitleBar::~TitleBar()
{
}

// 初始化组件
void TitleBar::setWidgetUi()
{
    this->setFixedHeight(GlobalSizeData::TITLEBAR_HEIGHT);
    // 窗体透明
//    this->setAttribute(Qt::WA_TranslucentBackground, true);
//    this->setFixedHeight(38);       /*固定高度*/

    // 按钮初始化

    m_pIconBtn   = new QPushButton(this);
    m_pFuncLabel = new QLabel(this);
    m_pMinimizeButton = new QPushButton(this);
    m_pCloseButton = new QPushButton(this);

    // 设置空间大小

    menuBar = new menuModule(this);

    // 设置按钮布局
    pLayout = new QHBoxLayout(this);
    pLayout->setContentsMargins(0, 0, 0, 0);
    pLayout->setSpacing(1);/*各部件的相邻距离*/
    pLayout->addSpacing(2);/*插入间距*/
    pLayout->addWidget(m_pIconBtn);
    pLayout->addSpacing(4);
    pLayout->addWidget(m_pFuncLabel);
    pLayout->addStretch();/*表示加了弹簧*/
    pLayout->addWidget(menuBar->menuButton);
    pLayout->addSpacing(4);
    pLayout->addWidget(m_pMinimizeButton);
    pLayout->addSpacing(4);
    pLayout->addWidget(m_pCloseButton);


    this->setLayout(pLayout);

    // 设置信号和槽函数
    connect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pCloseButton,    SIGNAL(clicked(bool)), this, SLOT(onClicked()));
}

// 设置组件样式
void TitleBar::setWidgetStyle()
{
    this->setAutoFillBackground(true);
    this->setBackgroundRole(QPalette::Base);
    // 设置对象名
    m_pFuncLabel->setObjectName("whiteLabel");
    m_pMinimizeButton->setObjectName("minimizeButton");
    m_pCloseButton->setObjectName("closeButton");

    // 设置悬浮提示
    m_pMinimizeButton->setToolTip(tr("Minimize"));
    m_pCloseButton->setToolTip(tr("Close"));

    // 设置图片
    m_pFuncLabel->setText("麒麟传书");/*给label设置信息*/
    QFont font;
    font.setPixelSize(14);
    m_pFuncLabel->setFont(font);

    m_pIconBtn->setIconSize(QSize(21.11, 21.11));/*设置ico类型图片大小*/
    m_pIconBtn->setIcon(QIcon::fromTheme("kylin-ipmsg"));/*使用fromTheme函数调用库中的图片*/

    m_pMinimizeButton->setIcon(QIcon::fromTheme("window-minimize-symbolic"));
    m_pMinimizeButton->setIconSize(QSize(16, 16));
    m_pMinimizeButton->setProperty("isWindowButton", 0x1);
    m_pMinimizeButton->setProperty("useIconHighlightEffect", 0x2);
    m_pMinimizeButton->setFlat(true);

    m_pCloseButton->setIcon(QIcon::fromTheme("window-close-symbolic"));
    m_pCloseButton->setIconSize (QSize(16, 16));
    m_pCloseButton->setProperty("isWindowButton", 0x2);
    m_pCloseButton->setProperty("useIconHighlightEffect", 0x8);
    m_pCloseButton->setFlat(true);

    // 设置按钮样式
    QString btnStyle = "QPushButton{border:0px;border-radius:4px;background:transparent;}"
                       "QPushButton:Hover{border:0px;border-radius:4px;background:transparent;background-color:rgba(0,0,0,0.1);}"
                       "QPushButton:Pressed{border:0px;border-radius:4px;background:transparent;background-color:rgba(0,0,0,0.15);}";
    m_pIconBtn->setStyleSheet(btnStyle);

//    if (WidgetStyle::themeColor == 0) {
//        QString btnStyle = "QPushButton{border:0px;border-radius:4px;background:transparent;}"
//                           "QPushButton:Hover{border:0px;border-radius:4px;background:transparent;background-color:rgba(0,0,0,0.1);}"
//                           "QPushButton:Pressed{border:0px;border-radius:4px;background:transparent;background-color:rgba(0,0,0,0.15);}";
//        m_pIconBtn->setStyleSheet(btnStyle);
//    }
//    else if (WidgetStyle::themeColor == 1) {
//        QString btnStyle = "QPushButton{border:0px;border-radius:4px;background:transparent;}"
//                           "QPushButton:Hover{border:0px;border-radius:4px;background:transparent;background-color:rgba(0,0,0,0.1);}"
//                           "QPushButton:Pressed{border:0px;border-radius:4px;background:transparent;background-color:rgba(0,0,0,0.15);}";
//        m_pIconBtn->setStyleSheet(btnStyle);

//    }

}

void TitleBar::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        if (pButton == m_pMinimizeButton)
        {
            pWindow->showMinimized();
            m_pMinimizeButton->update();
            m_pCloseButton->update();
        }
        else if (pButton == m_pCloseButton)
        {
            pWindow->close();
        }
    }
}
