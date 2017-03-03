#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Calculator.h"
#include "misc.h"
#include "ui_DialogAboutDev.h"
#include "settingDialogUI.h"

#define BTNWIDTH 80
#define BTNHEIGHT 40
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 445
#define WIDGET_INDEX_X 0
#define WIDGET_INDEX_Y 35
#define WIDGET_WIDTH 600
#define WIDGET_HEIGHT 400
#define WIDGET_MOVE_TO_X 600
#define DISP_TEXT_SIZE 22
#define DISP_TEXT_SIZE_SMALL 16

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
    ~MainWindow();

private slots:
    void moveToSimpleCal();
	void moveToGradePointCal();
	void aboutDev();
	void numBtnAction();
	//void signChanged();
	void getResult();
	void clearAll();
	void backspaceAction();
	void btnDotAction();
	void btnCEAction();
	void settingDialogShow();
	void effectiveLenSet();
	void btnRootAction();
	void bracketInput();
	void signInput();
	void x_nInput();
	void useResult();

	/*fun2 SLOTS*/
	void fun2_gradeNumBtnAction();
	void fun2_creditNumBtnAction();
	void fun2_allClear();
	void fun2_getResult();
	void fun2_saveAs();
	void fun2_deleteBtnAction();


private:
	void numInput(QString num);
	void initSimpleCalUI();
	void initGradeCalUI();
	void SIGNAL_SLOT_Config();
	void dispCtrl(QString detail);
	void errorOutput(QString errorDetail);
	void listViewCtrl();
	void storeNum();
	void infixToPostFix();
	double singleStepCalculate(double num1, double num2, QString optType);
	void completeExpression();
	bool bracketRuleDetect();
	void autoClear();
	//bool errorDetect();

	void fun2_listViewCtrl();
	void errorPrint(QString errorMsg);
	float weightAnalyse(float score);
	void dataSave();
	void showMsg(QString txt);

	/************simpleCal prameter************/
	bool isOptComplete;
	bool isBtnRootEnvent;
	bool errorFlag;
	bool isExponentialCal;

	int optCnt;
	int effective_len;

	QString m_qstrNumTemp;
	QString m_qstrResult;
	QString dispData;
	double m_dResult;
	QStringList m_qstrList1;
	QStringList m_Add_minus;
	QStringList m_divide_multi;
	QStringList m_bracket;
	QStandardItemModel m_itemModel;
	QStringList *m_strListInputGet;
	QStringList m_PostFix;
	QStack<QString> m_stackSign;                          //store the operate sign when converting Infix expression to postfix expression
	QStack<double> m_stackNum;                            //store the operate number when converting Infix expression to postfix expression
	QMap<QString, unsigned char> m_map1;
	QMap<QString, unsigned char> m_map2;



	Ui::QtGuiApplication2Class ui;
	Ui::Dialog *dialog;
	Ui::settingDialog *settingDialog;
	QDialog *settingWindow;
	QWidget *widget1;
	QWidget *widget2;
	QWidget *gradePointShow;

	//QLabel *text_disp;
	QTextEdit *text_disp;

	QListView *myListView;
	
	QPushButton *btnG1_num_0;
	QPushButton *btnG1_num_1;
	QPushButton *btnG1_num_2;
	QPushButton *btnG1_num_3;
	QPushButton *btnG1_num_4;
	QPushButton *btnG1_num_5;
	QPushButton *btnG1_num_6;
	QPushButton *btnG1_num_7;
	QPushButton *btnG1_num_8;
	QPushButton *btnG1_num_9;
	QPushButton *btnG1_dot;
	QPushButton *btnG1_add;
	QPushButton *btnG1_minus;
	QPushButton *btnG1_divide;
	QPushButton *btnG1_multiply;
	QPushButton *btnG1_AC;
	QPushButton *btnG1_backspace;
	QPushButton *btnG1_equal;
	QPushButton *btnG1_CE;
	QPushButton *btnG1_useResult;
	QPushButton *btnG1_x_n;
	QPushButton *btnG1_root;
	QPushButton *btnG1_bracket_left;
	QPushButton *btnG1_bracket_right;

	/************gradePointCal prameter************/

	int m_iItemCnt;
	float m_fResult;
	int calCnt;

	QString m_qstrCurrGrade;
	QString m_qstrCurrCredit;

	bool isGradeInputMode;
	bool isErrorDetected;
	bool isGotResult;

	QStringList *list_Grade;
	QStringList *list_Credits;

	QStandardItemModel *fun2_GradeModel;
	QStandardItemModel *fun2_CreditModel;

	QListView *fun2_ListView;
	QListView *fun2_ListView_1;
	QLabel *resultShow;

	QPushButton *btnG2_point_1d5;
	QPushButton *btnG2_point_2d0;
	QPushButton *btnG2_point_2d5;
	QPushButton *btnG2_point_3d0;
	QPushButton *btnG2_point_3d5;
	QPushButton *btnG2_point_4d0;
	QPushButton *btnG2_point_4d5;
	QPushButton *btnG2_point_5d0;
	QPushButton *btnG2_point_5d5;
	QPushButton *btnG2_point_6d0;
	QPushButton *btnG2_point_6d5;
	QPushButton *btnG2_point_7d0;
	QPushButton *btnG2_equal;
	QPushButton *btnG2_deleteItem;
	QPushButton *btnG2_AC;
	QPushButton *btnG2_saveAsFile;
	QPushButton *btnG2_num_0;
	QPushButton *btnG2_num_1;
	QPushButton *btnG2_num_2;
	QPushButton *btnG2_num_3;
	QPushButton *btnG2_num_4;
	QPushButton *btnG2_num_5;
	QPushButton *btnG2_num_6;
	QPushButton *btnG2_num_7;
	QPushButton *btnG2_num_8;
	QPushButton *btnG2_num_9;
	QPushButton *btnG2_point_1d0;
};
