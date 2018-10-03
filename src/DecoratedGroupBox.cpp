/**
MIT License

Copyright (c) 2018 Michael Scopchanov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "DecoratedGroupBox.h"
#include <QStyleOptionGroupBox>
#include <QPainter>

StyleOptionDecoratedGroupBox::StyleOptionDecoratedGroupBox() :
	QStyleOptionGroupBox(),
	offset(0),
	leftSpace(0),
	rightSpace(0)
{

}

CustomStyle::CustomStyle() :
	QCommonStyle()
{

}

void CustomStyle::drawComplexControl(QStyle::ComplexControl cc, const QStyleOptionComplex *opt, QPainter *p, const QWidget *widget) const
{
	if (const StyleOptionDecoratedGroupBox *groupBox = qstyleoption_cast<const StyleOptionDecoratedGroupBox *>(opt)) {
		QRect textRect = proxy()->subControlRect(CC_GroupBox, opt, SC_GroupBoxLabel, widget);
		QRect checkBoxRect = proxy()->subControlRect(CC_GroupBox, opt, SC_GroupBoxCheckBox, widget);
		int decorationOffset = 0;
		int pixmapRectWidth = 0;
		int pixmapHeight = 0;
		int textOffset = 0;

		if (!groupBox->pixmap.isNull()) {
			decorationOffset = groupBox->offset;
			pixmapRectWidth = groupBox->leftSpace
							+ groupBox->pixmap.width()
							+ groupBox->rightSpace;
			pixmapHeight = groupBox->pixmap.height();
			textOffset = decorationOffset + pixmapRectWidth;
		}

		textRect.adjust(textOffset, 0, textOffset, 0);

		// Draw frame
		if (groupBox->subControls & QStyle::SC_GroupBoxFrame) {
			QStyleOptionFrame frame;
			frame.QStyleOption::operator=(*groupBox);
			frame.features = groupBox->features;
			frame.lineWidth = groupBox->lineWidth;
			frame.midLineWidth = groupBox->midLineWidth;
			frame.rect = proxy()->subControlRect(CC_GroupBox, opt, SC_GroupBoxFrame, widget);
			p->save();
			QRegion region(groupBox->rect);
			if (!groupBox->text.isEmpty()) {
				bool ltr = groupBox->direction == Qt::LeftToRight;
				QRect finalRect;
				if (groupBox->subControls & QStyle::SC_GroupBoxCheckBox) {
					finalRect = checkBoxRect.united(textRect);
					finalRect.adjust(ltr ? -4 : 0, 0, ltr ? 0 : 4, 0);
				} else {
					finalRect = textRect;
				}
				region -= finalRect;
			}
			p->setClipRegion(region);
			proxy()->drawPrimitive(PE_FrameGroupBox, &frame, p, widget);
			p->restore();
		}

		// Draw icon
		if (!groupBox->pixmap.isNull()) {
			p->fillRect(decorationOffset, 0, pixmapRectWidth, pixmapHeight, opt->palette.window().color());
			proxy()->drawItemPixmap(p, QRect(decorationOffset, 0, pixmapRectWidth, pixmapHeight),
									Qt::AlignCenter, groupBox->pixmap);
		}

		// Draw title
		if ((groupBox->subControls & QStyle::SC_GroupBoxLabel) && !groupBox->text.isEmpty()) {
			QColor textColor = groupBox->textColor;
			if (textColor.isValid())
				p->setPen(textColor);
			int alignment = int(groupBox->textAlignment);
			if (!proxy()->styleHint(QStyle::SH_UnderlineShortcut, opt, widget))
				alignment |= Qt::TextHideMnemonic;
			proxy()->drawItemText(p, textRect,  Qt::TextShowMnemonic | Qt::AlignHCenter | alignment,
								  groupBox->palette, groupBox->state & State_Enabled, groupBox->text,
								  textColor.isValid() ? QPalette::NoRole : QPalette::WindowText);
			if (groupBox->state & State_HasFocus) {
				QStyleOptionFocusRect fropt;
				fropt.QStyleOption::operator=(*groupBox);
				fropt.rect = textRect;
				proxy()->drawPrimitive(PE_FrameFocusRect, &fropt, p, widget);
			}
		}
	} else {
		QCommonStyle::drawComplexControl(cc, opt, p, widget);
	}
}

DecoratedGroupBox::DecoratedGroupBox(const QString &title, QWidget *parent) :
	QGroupBox(title, parent),
	m_offset(5),
	m_leftSpace(3),
	m_rightSpace(3)
{

}

QPixmap DecoratedGroupBox::pixmap() const
{
	return m_pixmap;
}

void DecoratedGroupBox::setPixmap(const QPixmap &pixmap)
{
	m_pixmap = pixmap;
	update();
}

int DecoratedGroupBox::offset() const
{
	return m_offset;
}

void DecoratedGroupBox::setOffset(int offset)
{
	m_offset = offset;
	update();
}

int DecoratedGroupBox::leftSpace() const
{
	return m_leftSpace;
}

void DecoratedGroupBox::setLeftSpace(int leftSpace)
{
	m_leftSpace = leftSpace;
	update();
}

int DecoratedGroupBox::rightSpace() const
{
	return m_rightSpace;
}

void DecoratedGroupBox::setRightSpace(int rightSpace)
{
	m_rightSpace = rightSpace;
	update();
}

void DecoratedGroupBox::setSpaces(int leftSpace, int rightSpace)
{
	setLeftSpace(leftSpace);
	setRightSpace(rightSpace);
}

void DecoratedGroupBox::paintEvent(QPaintEvent * /*event*/)
{
	CustomStyle style;
	QPainter painter(this);
	StyleOptionDecoratedGroupBox option;

	initStyleOption(&option);
	option.pixmap = m_pixmap;
	option.offset = m_offset;
	option.leftSpace = m_leftSpace;
	option.rightSpace = m_rightSpace;

	style.drawComplexControl(QStyle::CC_GroupBox, &option, &painter, this);
}
