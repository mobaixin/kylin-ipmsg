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

#include "localinfo.h"
#include <QDebug>
#include <QEvent>

LocalInfo::LocalInfo(QWidget *parent)
    : QWidget(parent)
{
    // 初始化组件
    setWidgetUi();

    // 设置组件样式
    setWidgetStyle();
}

LocalInfo::~LocalInfo()
{
}

// 初始化组件
void LocalInfo::setWidgetUi()
{
    this->setFixedHeight(GlobalSizeData::LOCALINFO_HEIGHT);

    // 初始化组件及布局
    u_LabelIcon = new QLabel(this);
    u_LabelName = new QLabel(this);
    u_LabelIp = new QLabel(this);
    u_ButtonUpdate = new QPushButton(this);
    u_ButtonFile = new QPushButton(this);

    s_LabelIcon = new QLabel(this);
    s_EditSearch=new QLineEdit(this);

    // 设置空间大小
    u_LabelIcon->setFixedSize(60,60);
    u_ButtonUpdate->setFixedSize(20,20);
    u_ButtonFile->setFixedSize(20,20);
    s_EditSearch->setFixedSize(334, 36);
    w = s_EditSearch->width();
    h = s_EditSearch->height();
    s_LabelIcon->setFixedSize(w/2-5,h);

    QMargins margins = s_EditSearch->textMargins();
    s_EditSearch->setTextMargins(margins.left(), margins.top(), s_LabelIcon->width(), margins.bottom());
    s_EditSearch->setPlaceholderText(tr("搜索"));//提示文字
    s_EditSearch->setMaxLength(30);//字数限制
    s_EditSearch->setTextMargins(s_LabelIcon->width(), 1, 1 , 1);// 设置输入框中文件输入区，不让输入的文字在被隐藏在按钮下


    m_localInfoLayout = new QVBoxLayout(this);
    m_nameLayout = new QHBoxLayout();
    m_ipLayout   = new QVBoxLayout();
    m_avatarLayout = new QHBoxLayout();
    m_searchLayout = new QHBoxLayout();
    // 对组件进行布局
    m_nameLayout->addWidget(u_LabelName, Qt::AlignBottom);
    m_nameLayout->addWidget(u_ButtonUpdate, Qt::AlignBottom | Qt::AlignLeft);
    m_nameLayout->addStretch();
    m_nameLayout->addWidget(u_ButtonFile, Qt::AlignBottom | Qt::AlignRight);
    m_nameLayout->setMargin(0);
    m_nameLayout->setSpacing(0);

    m_ipLayout->addLayout(m_nameLayout);
    m_ipLayout->addWidget(u_LabelIp, Qt::AlignTop);
    m_ipLayout->setMargin(0);
    m_ipLayout->setSpacing(0);

    m_avatarLayout->addWidget(u_LabelIcon);
    m_avatarLayout->addLayout(m_ipLayout);
//    m_avatarLayout->setMargin(0);
//    m_avatarLayout->setSpacing(0);

    m_localInfoLayout->addLayout(m_avatarLayout);
    m_localInfoLayout->addWidget(s_EditSearch);

    m_searchLayout->addWidget(s_LabelIcon);
    m_searchLayout->addStretch();
    m_searchLayout->setSpacing(0);/*各部件的相邻距离*/
    m_searchLayout->setContentsMargins(0, 0, 0, 0);
    s_EditSearch->setLayout(m_searchLayout);

    this->installEventFilter(this);//安装过滤器
    s_EditSearch->installEventFilter(this);


    // 设置对象名
    u_LabelIcon->setObjectName("usericon");
    u_LabelIp->setObjectName("userip");
    u_LabelName->setObjectName("username");
    u_ButtonUpdate->setObjectName("updatename");
    u_ButtonFile->setObjectName("uploadfile");

    // 设置信号和槽函数
    connect(u_ButtonUpdate, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(u_ButtonFile,    SIGNAL(clicked(bool)), this, SLOT(onClicked()));
}

// 设置组件样式
void LocalInfo::setWidgetStyle()
{
    this->setAutoFillBackground(true);
    this->setBackgroundRole(QPalette::Base);

    // 设置图片
    //u_LabelName->setText("王晓晓-本机");
//    u_LabelName->setStyleSheet("color:#262626;font:16px;");
    QFont fontName;
    fontName.setPixelSize(16);
    u_LabelName->setFont(fontName);
    u_LabelName->setAlignment(Qt::AlignBottom);//文字向下对齐
    u_LabelName->setMargin(0);
    u_LabelName->setFixedSize(GlobalSizeData::USER_NAME_LAB_SIZE);

    //u_LabelIp->setText("123.123.123.123");
    u_LabelIp->setStyleSheet("color:#8c8c8c;font:14px;");
    u_LabelIp->setFixedSize(GlobalSizeData::USER_IP_LAB_SIZE);

    //u_LabelIcon->setText("王");
    u_LabelIcon->setAlignment(Qt::AlignCenter);
    u_LabelIcon->setStyleSheet("background-color: #6495ED;border-radius:30px;padding:2px 4px;border-style: outset;color:white;font:36px;");
    u_LabelIcon->setFixedSize(GlobalSizeData::AVATAR_LAB_SIZE);

    u_ButtonUpdate->setIcon(QIcon::fromTheme("document-edit-symbolic"));/*修改名字*/
    u_ButtonUpdate->setIconSize(GlobalSizeData::OPEN_FOLDER_BTN_ICON);
    u_ButtonUpdate->setFixedSize(GlobalSizeData::OPEN_FOLDER_BTN_SIZE);
    u_ButtonUpdate->setProperty("isWindowButton", 0x1);
    u_ButtonUpdate->setProperty("useIconHighlightEffect", 0x2);
    u_ButtonUpdate->setFlat(true);

    u_ButtonFile->setIcon(QIcon::fromTheme("document-open-symbolic"));/*传输文件*/
    u_ButtonFile->setIconSize(GlobalSizeData::OPEN_FOLDER_BTN_ICON);
    u_ButtonFile->setFixedSize(GlobalSizeData::OPEN_FOLDER_BTN_SIZE);
    u_ButtonFile->setProperty("isWindowButton", 0x1);
    u_ButtonFile->setProperty("useIconHighlightEffect", 0x2);
    u_ButtonFile->setFlat(true);

    QFont font;
    font.setPixelSize(14);
    s_EditSearch->setFont(font);

    QIcon searchIcon = QIcon::fromTheme("preferences-system-search-symbolic");
    s_LabelIcon->setPixmap(searchIcon.pixmap(searchIcon.actualSize(QSize(20,20))));
    s_LabelIcon->setProperty("isWindowButton", 0x1);
    s_LabelIcon->setProperty("useIconHighlightEffect", 0x2);
    s_LabelIcon->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
}

bool LocalInfo::eventFilter(QObject *watch,QEvent *e)
{
    if(e->type() == QEvent::MouseButtonPress && watch !=  s_EditSearch)
    {
        this->setFocus();
        s_LabelIcon->setFixedSize(w/2-5,h);
        s_LabelIcon->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        s_EditSearch->setAlignment(Qt::AlignLeft);
        s_EditSearch->setTextMargins(s_LabelIcon->width(), 1, 1 , 1);//没有取消按钮的时候
        qDebug()<<"MouseButtonPress";
    }
    if(e->type() == QEvent::MouseButtonPress && watch ==  s_EditSearch)
    {
        s_LabelIcon->setFixedSize(30, 30);
        s_EditSearch->setAlignment(Qt::AlignLeft);
        s_EditSearch->setTextMargins(s_LabelIcon->width(), 1, 1 , 1);//没有取消按钮的时候
        s_EditSearch->setFocus();
        s_EditSearch->setPlaceholderText("搜索");//提示文字
             qDebug()<<"youdian";
    }
}

void LocalInfo::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        if (pButton == u_ButtonUpdate)
        {
            qDebug()<<"~~~~~~~~~~~~修改名字~~~~~~~~~~~~";
        }
        else if (pButton == u_ButtonFile)
        {
            qDebug()<<"~~~~~~~~~~~~文件夹~~~~~~~~~~~~";
        }
    }
}


void LocalInfo::setText(QString name,QString IP)
{
    if(QString(name.at(0))>='a'&&QString(name.at(0))<='z'){

        u_LabelIcon->setText(QString(name.at(0)).toUpper());
        u_LabelIcon->setStyleSheet("background-color: #6495ED;border-radius:30px;padding:2px 4px;border-style: outset;color:white;font:28px;");
        u_LabelIcon->setAlignment(Qt::AlignCenter);

    }
    else{
        u_LabelIcon->setText(QString(name.at(0)));
        u_LabelIcon->setStyleSheet("background-color: #6495ED;border-radius:30px;padding:2px 4px;border-style: outset;color:white;font:28px;");
        u_LabelIcon->setAlignment(Qt::AlignCenter);
    }
    u_LabelName->setText(name);
    u_LabelIp->setText(IP);

}
