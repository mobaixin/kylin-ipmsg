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
    this->setFixedHeight(GlobalData::LOCALINFO_HEIGHT);

    // 初始化组件及布局
    m_avatarLab = new QLabel(this);
    m_userIPLab = new QLabel(this);
    m_userNameLab = new QLabel(this);

    m_changeNameBtn = new QPushButton(this);
    m_openFolderBtn = new QPushButton(this);

    m_searchEdit = new QLineEdit(this);

    m_localInfoLayout = new QVBoxLayout(this);
    m_nameLayout = new QHBoxLayout();
    m_ipLayout   = new QVBoxLayout();
    m_avatarLayout = new QHBoxLayout();

    // 对组件进行布局
    m_nameLayout->addWidget(m_userNameLab, Qt::AlignBottom);
    m_nameLayout->addWidget(m_changeNameBtn, Qt::AlignBottom | Qt::AlignLeft);
    m_nameLayout->addStretch();
    m_nameLayout->addWidget(m_openFolderBtn, Qt::AlignBottom | Qt::AlignRight);
    m_nameLayout->setMargin(0);
    m_nameLayout->setSpacing(0);

    m_ipLayout->addLayout(m_nameLayout);
    m_ipLayout->addWidget(m_userIPLab, Qt::AlignTop);
    m_ipLayout->setMargin(0);
    m_ipLayout->setSpacing(0);

    m_avatarLayout->addWidget(m_avatarLab);
    m_avatarLayout->addLayout(m_ipLayout);
    m_avatarLayout->setMargin(0);
    m_avatarLayout->setSpacing(0);

    m_localInfoLayout->addLayout(m_avatarLayout);
    m_localInfoLayout->addWidget(m_searchEdit);
}

// 设置组件样式
void LocalInfo::setWidgetStyle()
{
    this->setAutoFillBackground(true);
    this->setBackgroundRole(QPalette::Base);

    // 本机头像
    m_avatarLab->setFixedSize(GlobalData::AVATAR_LAB_SIZE);

    QPalette avatarLabPe;
    avatarLabPe.setColor(QPalette::Background, QColor("#3D6BE5"));
    avatarLabPe.setColor(QPalette::WindowText, QColor("#FFFFFF"));
    m_avatarLab->setPalette(avatarLabPe);
    m_avatarLab->setStyleSheet("border-radius:30px;background:#3D6BE5;color:#FFFFFF;");
    
    QFont avatarLabFont("SourceHanSansCN-Light", 28, 400);
    m_avatarLab->setFont(avatarLabFont);
    m_avatarLab->setAlignment(Qt::AlignCenter);

    m_userNameLab->setFixedSize(GlobalData::USER_NAME_LAB_SIZE);

    m_userIPLab->setFixedSize(GlobalData::USER_IP_LAB_SIZE);

    m_changeNameBtn->setIcon(QIcon::fromTheme("document-edit-symbolic"));
    m_changeNameBtn->setIconSize(GlobalData::CHANGE_NAME_BTN_ICON);
    m_changeNameBtn->setFixedSize(GlobalData::CHANGE_NAME_BTN_SIZE);
    m_changeNameBtn->setProperty("isWindowButton", 0x1);
    m_changeNameBtn->setProperty("useIconHighlightEffect", 0x2);
    m_changeNameBtn->setFlat(true);
    
    m_openFolderBtn->setIcon(QIcon::fromTheme("document-open-symbolic"));
    m_openFolderBtn->setIconSize(GlobalData::OPEN_FOLDER_BTN_ICON);
    m_openFolderBtn->setFixedSize(GlobalData::OPEN_FOLDER_BTN_SIZE);
    m_openFolderBtn->setProperty("isWindowButton", 0x1);
    m_openFolderBtn->setProperty("useIconHighlightEffect", 0x2);
    m_openFolderBtn->setFlat(true);
    
    m_avatarLab->setText("S");
    m_userNameLab->setText("沈剑心");
    m_userIPLab->setText("172.17.7.99");

}