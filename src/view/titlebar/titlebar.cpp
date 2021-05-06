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

#include "titlebar.h"

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

    m_titleLayout = new QHBoxLayout(this);
}

// 设置组件样式
void TitleBar::setWidgetStyle()
{
    this->setAutoFillBackground(true);
    this->setBackgroundRole(QPalette::Base);
}