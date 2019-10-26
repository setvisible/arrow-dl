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

#include "customstyle.h"

#include <Core/IDownloadItem>
#include <Widgets/CustomStyleOptionProgressBar>

#include <QtCore/QtMath>
#include <QtGui/QPainter>
#include <QtWidgets/QStyleOption>


#define C_ICON_SIZE               16
#define C_ICON_WIDTH              19

static const QColor s_darkGrey     = QColor(160, 160, 160);
static const QColor s_lightGrey     = QColor(240, 240, 240);

static const char* xpm[] = {
    "16 16 2 1",
    "   c #F0F0F0",         // light grey
    "+  c #AAE061",         // light green
    "++++++++        ",
    " ++++++++       ",
    "  ++++++++      ",
    "   ++++++++     ",
    "    ++++++++    ",
    "     ++++++++   ",
    "      ++++++++  ",
    "       ++++++++ ",
    "        ++++++++",
    "+        +++++++",
    "++        ++++++",
    "+++        +++++",
    "++++        ++++",
    "+++++        +++",
    "++++++        ++",
    "+++++++        +"};

/*!
 * \class CustomStyle
 * \brief TheCustomStyle  wraps a QProxyStyle (the default system style) for the purpose
 * of dynamically overriding the application painting.
 *
 */

CustomStyle::CustomStyle() : QProxyStyle()
{
    m_textureImage = QImage(xpm);
}

CustomStyle::~CustomStyle()
{    
}

void CustomStyle::drawControl(ControlElement element, const QStyleOption *opt,
                              QPainter *p, const QWidget *widget) const
{  
    switch (element) {
    case CE_ProgressBar:
        if (const CustomStyleOptionProgressBar *pb
                = qstyleoption_cast<const CustomStyleOptionProgressBar *>(opt)) {

            /* Draw the selection background */
            if (pb->state & State_Selected) {
                QColor bgColor = pb->palette.color(QPalette::Normal, QPalette::Highlight);
                p->setPen(Qt::NoPen);
                p->setBrush(bgColor);
                p->drawRect(pb->rect);
            }

            /* Draw the icon */
            {
                int size = C_ICON_SIZE;
                int margin = (qMax(size, pb->rect.height()) - size ) / 2;
                QRect iconRect = QRect(pb->rect.x() + margin , pb->rect.y() + margin, size, size);
                p->drawPixmap(iconRect, pb->icon.pixmap(C_ICON_SIZE));
            }

            /* Draw the progress bar */
            {
                /* Draw the progress bar frame */
                const int marginV = 3;
                const int marginH = 5;
                QRect frameRect = pb->rect;
                frameRect.setTop(frameRect.top() + marginV);
                frameRect.setBottom(frameRect.bottom() - marginV);
                frameRect.setLeft(frameRect.left() + marginH + C_ICON_WIDTH);
                frameRect.setRight(frameRect.right() - marginH);

                p->setPen(QPen(s_darkGrey, 1));
                p->setBrush(s_lightGrey);
                p->drawRect(frameRect);

                /* Draw the progress bar indicator */
                qint64 minimum = qint64(pb->minimum);
                qint64 maximum = qint64(pb->maximum);
                qint64 progress = qint64(pb->progress);

                QColor color = pb->color;
                QBrush brush;

                const int margin = 2;
                QRect indicatorRect = frameRect;
                indicatorRect.setTop(indicatorRect.top() + margin);
                indicatorRect.setBottom(indicatorRect.bottom() + 1 - margin);
                indicatorRect.setLeft(indicatorRect.left() + margin);
                indicatorRect.setRight(indicatorRect.right() + 1 - margin);

                if (progress < 0 || (minimum == 0 && maximum == 0)) {
                    QRgb rgb = color.rgb();
                    QImage textureImage = m_textureImage;
                    textureImage.setColor(1, rgb);
                    QPixmap pixmap = QPixmap::fromImage(textureImage);
                    brush.setTexture(pixmap);

                } else {
                    qreal p_v = progress - minimum;
                    qreal t_s = (maximum - minimum) ? (maximum - minimum) : qreal(1);
                    qreal r = p_v / t_s;
                    int w = qMax(qCeil(r * indicatorRect.width()), 1);
                    indicatorRect.setWidth(w);
                    brush.setStyle(Qt::SolidPattern);
                    brush.setColor(color);
                }
                p->setPen(Qt::NoPen);
                p->setBrush(brush);
                p->drawRect(indicatorRect);
            }

        } else {
            QProxyStyle::drawControl(element, opt, p, widget);
        }
        break;
    default:
        QProxyStyle::drawControl(element, opt, p, widget);
        break;
    }
}