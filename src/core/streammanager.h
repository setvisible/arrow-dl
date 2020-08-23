/* - DownZemAll! - Copyright (C) 2019-present Sebastien Vavassori
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CORE_STREAM_MANAGER_H
#define CORE_STREAM_MANAGER_H

#include <QtCore/QObject>
#include <QtCore/QString>

#include <Core/Stream>

class Settings;

class StreamManager : public QObject
{
    Q_OBJECT

public:
    explicit StreamManager(QObject *parent = nullptr);
    ~StreamManager() Q_DECL_OVERRIDE;

    Settings* settings() const;
    void setSettings(Settings *settings);

    static QString version();
    static QString website();


signals:

private slots:
    void onSettingsChanged();

private:
    Settings *m_settings;

    void setProxySettings(Settings *settings);
};

#endif // CORE_STREAM_MANAGER_H