/* - DownZemAll! - Copyright (C) 2019 Sebastien Vavassori
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

#ifndef IPC_INTER_PROCESS_COMMUNICATION_H
#define IPC_INTER_PROCESS_COMMUNICATION_H

#include <QtCore/QString>

class Model;

class InterProcessCommunication
{
public:
    static QString readMessageFromLauncher();

    static QString clean(const QString &message);

    static bool isUrl(const QString &message);
    static bool isCommandOpenManager(const QString &message);
    static bool isCommandShowPreferences(const QString &message);
    static bool isCommandOpenUrl(const QString &message);
    static QString getCurrentUrl(const QString &message);

    static void parseMessage(const QString &message, Model *model);

};

#endif // IPC_INTER_PROCESS_COMMUNICATION_H