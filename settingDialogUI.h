#pragma once

#ifndef UI_SETTINGDIALOG_H
#define UI_SETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
	QWidget *layoutWidget;
	QHBoxLayout *hboxLayout;
	QSpacerItem *spacerItem;
	QPushButton *okButton;
	QPushButton *cancelButton;
	QWidget *horizontalLayoutWidget;
	QHBoxLayout *horizontalLayout;
	QLabel *label;
	QSpinBox *spinBox;

	void setupUi(QDialog *Dialog)
	{
		if (Dialog->objectName().isEmpty())
			Dialog->setObjectName(QStringLiteral("Dialog"));
		Dialog->resize(400, 300);
		Dialog->setMinimumSize(QSize(400, 300));
		Dialog->setMaximumSize(QSize(400, 300));
		layoutWidget = new QWidget(Dialog);
		layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
		layoutWidget->setGeometry(QRect(20, 250, 351, 33));
		hboxLayout = new QHBoxLayout(layoutWidget);
		hboxLayout->setSpacing(6);
		hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
		hboxLayout->setContentsMargins(0, 0, 0, 0);
		spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

		hboxLayout->addItem(spacerItem);

		okButton = new QPushButton(layoutWidget);
		okButton->setObjectName(QStringLiteral("okButton"));

		hboxLayout->addWidget(okButton);

		cancelButton = new QPushButton(layoutWidget);
		cancelButton->setObjectName(QStringLiteral("cancelButton"));

		hboxLayout->addWidget(cancelButton);

		horizontalLayoutWidget = new QWidget(Dialog);
		horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
		horizontalLayoutWidget->setGeometry(QRect(30, 20, 171, 41));
		horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
		horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
		horizontalLayout->setContentsMargins(0, 0, 0, 0);
		label = new QLabel(horizontalLayoutWidget);
		label->setObjectName(QStringLiteral("label"));

		horizontalLayout->addWidget(label);

		spinBox = new QSpinBox(horizontalLayoutWidget);
		spinBox->setObjectName(QStringLiteral("spinBox"));
		QFont font;
		font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
		font.setPointSize(11);
		font.setBold(true);
		font.setWeight(75);
		spinBox->setFont(font);
		spinBox->setMinimum(2);
		spinBox->setMaximum(16);
		spinBox->setValue(8);

		horizontalLayout->addWidget(spinBox);


		retranslateUi(Dialog);
		QObject::connect(okButton, SIGNAL(clicked()), Dialog, SLOT(accept()));
		QObject::connect(cancelButton, SIGNAL(clicked()), Dialog, SLOT(reject()));

		QMetaObject::connectSlotsByName(Dialog);
	} // setupUi

	void retranslateUi(QDialog *Dialog)
	{
		Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", Q_NULLPTR));
		okButton->setText(QApplication::translate("Dialog", "OK", Q_NULLPTR));
		cancelButton->setText(QApplication::translate("Dialog", "Cancel", Q_NULLPTR));
		label->setText(QApplication::translate("Dialog", "\350\256\276\347\275\256\346\234\211\346\225\210\346\225\260\345\255\227\351\225\277\345\272\246\357\274\232", Q_NULLPTR));
	} // retranslateUi

};

namespace Ui {
	class settingDialog : public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H

