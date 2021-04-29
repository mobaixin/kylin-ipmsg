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

#ifndef LOCALINFO_H
#define LOCALINFO_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

#include "../common/globaldata.h"

class LocalInfo : public QWidget
{
    Q_OBJECT
public:
    explicit LocalInfo(QWidget *parent = nullptr);
    ~LocalInfo();

    // 初始化组件
    void setWidgetUi();

    // 设置组件样式
    void setWidgetStyle();
    
    QLabel *m_avatarLab;    // 头像
    QLabel *m_userIPLab;    // IP地址
    QLabel *m_userNameLab;  // 用户名
    
    QPushButton *m_changeNameBtn; // 修改本机昵称
    QPushButton *m_openFolderBtn; // 打开文件保存目录

    QLineEdit *m_searchEdit; // 搜索框

private:
    QVBoxLayout *m_localInfoLayout; // 本机信息总体布局
    QHBoxLayout *m_nameLayout;      // 本机昵称布局
    QVBoxLayout *m_ipLayout;        // 本机IP布局
    QHBoxLayout *m_avatarLayout;    // 本机头像布局
};




#endif // LOCALINFO_H