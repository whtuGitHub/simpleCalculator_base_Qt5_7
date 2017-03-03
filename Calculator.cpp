#include "Calculator.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.statusBar->showMessage("Welcome", 3000);

	initSimpleCalUI();
	initGradeCalUI();

	//Build the operator precedence map
	m_map1.insert(")", 0);
	m_map1.insert("-", 1);
	m_map1.insert("+", 1);
	m_map1.insert("*", 3);
	m_map1.insert("/", 3);
	m_map1.insert("(", 5);

	m_map2.insert(")", 0);
	m_map2.insert("-", 2);
	m_map2.insert("+", 2);
	m_map2.insert("*", 4);
	m_map2.insert("/", 4);
	m_map2.insert("(", 0);

	m_Add_minus.append("+");
	m_Add_minus.append("-");

	m_bracket.append("(");
	m_bracket.append(")");

	m_divide_multi.append("/");
	m_divide_multi.append("*");

	clearAll();
	fun2_allClear();

	SIGNAL_SLOT_Config();
}

void MainWindow::SIGNAL_SLOT_Config() {
	/*******************action*******************/
	connect(ui.actionSimple_calculate,         SIGNAL(triggered(bool)), this, SLOT(moveToSimpleCal()));
	connect(ui.actionGradepoint_calculate,     SIGNAL(triggered(bool)), this, SLOT(moveToGradePointCal()));
	connect(ui.actionAbout_Dev,                SIGNAL(triggered(bool)), this, SLOT(aboutDev()));
	connect(ui.actionAbout_Qt,                 SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));
	connect(ui.actionSimple_calculator_config, SIGNAL(triggered(bool)), this, SLOT(settingDialogShow()));

    /****************fun1_simple_cal******************/
	connect(btnG1_num_0,     SIGNAL(clicked(bool)), this, SLOT(numBtnAction()));
	connect(btnG1_num_1,     SIGNAL(clicked(bool)), this, SLOT(numBtnAction()));
	connect(btnG1_num_2,     SIGNAL(clicked(bool)), this, SLOT(numBtnAction()));
	connect(btnG1_num_3,     SIGNAL(clicked(bool)), this, SLOT(numBtnAction()));
	connect(btnG1_num_4,     SIGNAL(clicked(bool)), this, SLOT(numBtnAction()));
	connect(btnG1_num_5,     SIGNAL(clicked(bool)), this, SLOT(numBtnAction()));
	connect(btnG1_num_6,     SIGNAL(clicked(bool)), this, SLOT(numBtnAction()));
	connect(btnG1_num_7,     SIGNAL(clicked(bool)), this, SLOT(numBtnAction()));
	connect(btnG1_num_8,     SIGNAL(clicked(bool)), this, SLOT(numBtnAction()));
	connect(btnG1_num_9,     SIGNAL(clicked(bool)), this, SLOT(numBtnAction()));

	connect(btnG1_AC,        SIGNAL(clicked(bool)), this, SLOT(clearAll()));
	connect(btnG1_add,       SIGNAL(clicked(bool)), this, SLOT(signInput()));
	connect(btnG1_minus,     SIGNAL(clicked(bool)), this, SLOT(signInput()));
	connect(btnG1_multiply,  SIGNAL(clicked(bool)), this, SLOT(signInput()));
	connect(btnG1_divide,    SIGNAL(clicked(bool)), this, SLOT(signInput()));
	connect(btnG1_equal,     SIGNAL(clicked(bool)), this, SLOT(getResult()));
	connect(btnG1_backspace, SIGNAL(clicked(bool)), this, SLOT(backspaceAction()));
	connect(btnG1_dot,       SIGNAL(clicked(bool)), this, SLOT(btnDotAction()));
	connect(btnG1_CE,        SIGNAL(clicked(bool)), this, SLOT(btnCEAction()));
	connect(btnG1_x_n,       SIGNAL(clicked(bool)), this, SLOT(x_nInput()));
	connect(btnG1_root,      SIGNAL(clicked(bool)), this, SLOT(btnRootAction()));
	connect(btnG1_bracket_left, SIGNAL(clicked(bool)), this, SLOT(bracketInput()));
	connect(btnG1_bracket_right, SIGNAL(clicked(bool)), this, SLOT(bracketInput()));
	connect(btnG1_useResult, SIGNAL(clicked()), this, SLOT(useResult()));

	connect(settingDialog->okButton, SIGNAL(clicked(bool)), this, SLOT(effectiveLenSet()));
	/****************fun2_grade_point_cal******************/
	connect(btnG2_num_0, SIGNAL(clicked(bool)), this, SLOT(fun2_gradeNumBtnAction()));
	connect(btnG2_num_1, SIGNAL(clicked(bool)), this, SLOT(fun2_gradeNumBtnAction()));
	connect(btnG2_num_2, SIGNAL(clicked(bool)), this, SLOT(fun2_gradeNumBtnAction()));
	connect(btnG2_num_3, SIGNAL(clicked(bool)), this, SLOT(fun2_gradeNumBtnAction()));
	connect(btnG2_num_4, SIGNAL(clicked(bool)), this, SLOT(fun2_gradeNumBtnAction()));
	connect(btnG2_num_5, SIGNAL(clicked(bool)), this, SLOT(fun2_gradeNumBtnAction()));
	connect(btnG2_num_6, SIGNAL(clicked(bool)), this, SLOT(fun2_gradeNumBtnAction()));
	connect(btnG2_num_7, SIGNAL(clicked(bool)), this, SLOT(fun2_gradeNumBtnAction()));
	connect(btnG2_num_8, SIGNAL(clicked(bool)), this, SLOT(fun2_gradeNumBtnAction()));
	connect(btnG2_num_9, SIGNAL(clicked(bool)), this, SLOT(fun2_gradeNumBtnAction()));

	connect(btnG2_point_1d0, SIGNAL(clicked(bool)), this, SLOT(fun2_creditNumBtnAction()));
	connect(btnG2_point_1d5, SIGNAL(clicked(bool)), this, SLOT(fun2_creditNumBtnAction()));
	connect(btnG2_point_2d0, SIGNAL(clicked(bool)), this, SLOT(fun2_creditNumBtnAction()));
	connect(btnG2_point_2d5, SIGNAL(clicked(bool)), this, SLOT(fun2_creditNumBtnAction()));
	connect(btnG2_point_3d0, SIGNAL(clicked(bool)), this, SLOT(fun2_creditNumBtnAction()));
	connect(btnG2_point_3d5, SIGNAL(clicked(bool)), this, SLOT(fun2_creditNumBtnAction()));
	connect(btnG2_point_4d0, SIGNAL(clicked(bool)), this, SLOT(fun2_creditNumBtnAction()));
	connect(btnG2_point_4d5, SIGNAL(clicked(bool)), this, SLOT(fun2_creditNumBtnAction()));
	connect(btnG2_point_5d0, SIGNAL(clicked(bool)), this, SLOT(fun2_creditNumBtnAction()));
	connect(btnG2_point_5d5, SIGNAL(clicked(bool)), this, SLOT(fun2_creditNumBtnAction()));
	connect(btnG2_point_6d0, SIGNAL(clicked(bool)), this, SLOT(fun2_creditNumBtnAction()));
	connect(btnG2_point_6d5, SIGNAL(clicked(bool)), this, SLOT(fun2_creditNumBtnAction()));
	connect(btnG2_point_7d0, SIGNAL(clicked(bool)), this, SLOT(fun2_creditNumBtnAction()));

	connect(btnG2_AC, SIGNAL(clicked(bool)), this, SLOT(fun2_allClear()));
	connect(btnG2_deleteItem, SIGNAL(clicked(bool)), this, SLOT(fun2_deleteBtnAction()));
	connect(btnG2_equal, SIGNAL(clicked(bool)), this, SLOT(fun2_getResult()));
	connect(btnG2_saveAsFile, SIGNAL(clicked(bool)), this, SLOT(fun2_saveAs()));

}

MainWindow::~MainWindow(){
	delete widget1;
	delete widget2;
}

void MainWindow::aboutDev() {
	QDialog *qd = new QDialog();
	dialog = new Ui::Dialog();
	qd->setFixedSize(400, 300);
	dialog->setupUi(qd);
	dialog->retranslateUi(qd);

	qd->setWindowTitle("about this application");

	qd->show();
	qd->exec();
}

void MainWindow::settingDialogShow() {
	settingWindow->show();
	settingWindow->exec();
}

void MainWindow::moveToSimpleCal() {
	widget2->hide();
	widget2->move(WIDGET_MOVE_TO_X, WIDGET_INDEX_Y);
	widget1->move(WIDGET_INDEX_X, WIDGET_INDEX_Y);
	widget1->show();
}

void MainWindow::moveToGradePointCal() {
	widget1->hide();
	widget1->move(WIDGET_MOVE_TO_X, WIDGET_INDEX_Y);
	widget2->move(WIDGET_INDEX_X, WIDGET_INDEX_Y);
	widget2->show();
}

void MainWindow::initSimpleCalUI() {
	widget1 = new QWidget(this);
	widget1->setGeometry(WIDGET_INDEX_X, WIDGET_INDEX_Y, WIDGET_WIDTH, WIDGET_HEIGHT);
	//widget1->setMinimumSize(QSize(600, 400));
	QVBoxLayout *vbox1 = new QVBoxLayout();
	QHBoxLayout *hbox1 = new QHBoxLayout();
	QHBoxLayout *hbox2 = new QHBoxLayout();
	QHBoxLayout *hbox3 = new QHBoxLayout();
	QHBoxLayout *hbox4 = new QHBoxLayout();
	QHBoxLayout *hbox5 = new QHBoxLayout();
	QHBoxLayout *hbox6 = new QHBoxLayout();
	QHBoxLayout *hboxMain = new QHBoxLayout(widget1);

	text_disp = new QTextEdit();
	text_disp->setAutoFillBackground(true);
	QFont qf;
	qf.setPointSize(DISP_TEXT_SIZE);
	text_disp->setFont(qf);

	optCnt = 0;
	effective_len = 8;

	myListView = new QListView();
	myListView->setModel(&m_itemModel);
	

	m_strListInputGet = new QStringList();

	settingDialog = new Ui::settingDialog();
	settingWindow = new QDialog();
	settingDialog->setupUi(settingWindow);
	settingDialog->retranslateUi(settingWindow);
	settingWindow->setWindowTitle("effective length setting");

	btnG1_num_0 = new QPushButton("0");
	btnG1_num_1 = new QPushButton("1");
	btnG1_num_2 = new QPushButton("2");
	btnG1_num_3 = new QPushButton("3");
	btnG1_num_4 = new QPushButton("4");
	btnG1_num_5 = new QPushButton("5");
	btnG1_num_6 = new QPushButton("6");
	btnG1_num_7 = new QPushButton("7");
	btnG1_num_8 = new QPushButton("8");
	btnG1_num_9 = new QPushButton("9");
	btnG1_dot   = new QPushButton(".");
	btnG1_add   = new QPushButton("+");
	btnG1_minus = new QPushButton("-");
	btnG1_divide = new QPushButton("/");
	btnG1_multiply = new QPushButton("x");
	btnG1_AC = new QPushButton("AC");
	btnG1_backspace = new QPushButton("<-");
	btnG1_equal = new QPushButton("=");
	btnG1_CE = new QPushButton("CE");
	btnG1_useResult = new QPushButton("use result");
	btnG1_x_n = new QPushButton("x^n");
	btnG1_root = new QPushButton("sqrt(");
	btnG1_bracket_left = new QPushButton("(");
	btnG1_bracket_right = new QPushButton(")");

	btnG1_num_0->setFixedSize(QSize(BTNWIDTH, BTNHEIGHT));
	btnG1_num_1->setFixedSize(QSize(BTNWIDTH, BTNHEIGHT));
	btnG1_num_2->setFixedSize(QSize(BTNWIDTH, BTNHEIGHT));
	btnG1_num_3->setFixedSize(QSize(BTNWIDTH, BTNHEIGHT));
	btnG1_num_4->setFixedSize(QSize(BTNWIDTH, BTNHEIGHT));
	btnG1_num_5->setFixedSize(QSize(BTNWIDTH, BTNHEIGHT));
	btnG1_num_6->setFixedSize(QSize(BTNWIDTH, BTNHEIGHT));
	btnG1_num_7->setFixedSize(QSize(BTNWIDTH, BTNHEIGHT));
	btnG1_num_8->setFixedSize(QSize(BTNWIDTH, BTNHEIGHT));
	btnG1_num_9->setFixedSize(QSize(BTNWIDTH, BTNHEIGHT));
	btnG1_dot->setFixedSize(QSize(BTNWIDTH, BTNHEIGHT));
	btnG1_add->setFixedSize(QSize(BTNWIDTH, BTNHEIGHT));
	btnG1_minus->setFixedSize(QSize(BTNWIDTH, BTNHEIGHT));
	btnG1_divide->setFixedSize(QSize(BTNWIDTH, BTNHEIGHT));
	btnG1_multiply->setFixedSize(QSize(BTNWIDTH, BTNHEIGHT));
	btnG1_AC->setFixedSize(QSize(BTNWIDTH, BTNHEIGHT));
	btnG1_backspace->setFixedSize(QSize(BTNWIDTH, BTNHEIGHT));
	btnG1_equal->setFixedSize(QSize(BTNWIDTH, BTNHEIGHT));
	btnG1_CE->setFixedSize(QSize(BTNWIDTH, BTNHEIGHT));
	btnG1_useResult->setFixedSize(QSize(BTNWIDTH, BTNHEIGHT));
	btnG1_x_n->setFixedSize(QSize(BTNWIDTH, BTNHEIGHT));
	btnG1_root->setFixedSize(QSize(BTNWIDTH, BTNHEIGHT));
	btnG1_bracket_left->setFixedSize(QSize(BTNWIDTH, BTNHEIGHT));
	btnG1_bracket_right->setFixedSize(QSize(BTNWIDTH, BTNHEIGHT));

	hbox1->addWidget(btnG1_AC);
	hbox1->addWidget(btnG1_CE);
	hbox1->addWidget(btnG1_backspace);
	hbox1->addWidget(btnG1_root);
						  
	hbox2->addWidget(btnG1_num_7);
	hbox2->addWidget(btnG1_num_8);
	hbox2->addWidget(btnG1_num_9);
	hbox2->addWidget(btnG1_minus);
						  
	hbox3->addWidget(btnG1_num_4);
	hbox3->addWidget(btnG1_num_5);
	hbox3->addWidget(btnG1_num_6);
	hbox3->addWidget(btnG1_multiply);
						  
	hbox4->addWidget(btnG1_num_1);
	hbox4->addWidget(btnG1_num_2);
	hbox4->addWidget(btnG1_num_3);
	hbox4->addWidget(btnG1_divide);
						  
	hbox5->addWidget(btnG1_useResult);
	hbox5->addWidget(btnG1_num_0);
	hbox5->addWidget(btnG1_dot);
	hbox5->addWidget(btnG1_equal);
	
	hbox6->addWidget(btnG1_x_n);
	hbox6->addWidget(btnG1_bracket_left);
	hbox6->addWidget(btnG1_bracket_right);
	hbox6->addWidget(btnG1_add);

	vbox1->addWidget(text_disp);
	vbox1->addSpacing(10);
	vbox1->addLayout(hbox1);
	vbox1->addLayout(hbox6);
	vbox1->addLayout(hbox2);
	vbox1->addLayout(hbox3);
	vbox1->addLayout(hbox4);
	vbox1->addLayout(hbox5);

	hboxMain->addWidget(myListView, 1);
	hboxMain->addLayout(vbox1, 1);

	widget1->setLayout(hboxMain);
	//widget1->hide();
}

void MainWindow::initGradeCalUI() {
	widget2 = new QWidget(this);
	widget2->setGeometry(WIDGET_MOVE_TO_X, WIDGET_INDEX_Y, WIDGET_WIDTH, WIDGET_HEIGHT);
	//widget2->setGeometry(WIDGET_INDEX_X, WIDGET_INDEX_Y, WIDGET_WIDTH, WIDGET_HEIGHT);

	QVBoxLayout *vBoxMain = new QVBoxLayout(widget2);
	QVBoxLayout *vbox1 = new QVBoxLayout();
	QVBoxLayout *vbox2 = new QVBoxLayout();

	QHBoxLayout *hbox1 = new QHBoxLayout();
	QHBoxLayout *hbox2 = new QHBoxLayout();
	QHBoxLayout *hbox3 = new QHBoxLayout();
	QHBoxLayout *hbox4 = new QHBoxLayout();
	QHBoxLayout *hbox5 = new QHBoxLayout();
	QHBoxLayout *hbox6 = new QHBoxLayout();
	QHBoxLayout *hbox7 = new QHBoxLayout();
	QHBoxLayout *hbox8 = new QHBoxLayout();
	QHBoxLayout *hbox9 = new QHBoxLayout();
	QHBoxLayout *hbox11 = new QHBoxLayout();
	QHBoxLayout *hbox12 = new QHBoxLayout();

	QHBoxLayout *hbox_resultShow = new QHBoxLayout();

	list_Grade = new QStringList();
	list_Credits = new QStringList();
	fun2_GradeModel = new QStandardItemModel();
	fun2_CreditModel = new QStandardItemModel();
	fun2_ListView = new QListView();
	fun2_ListView_1 = new QListView();
	fun2_ListView->setModel(fun2_GradeModel);
	fun2_ListView_1->setModel(fun2_CreditModel);

	m_iItemCnt = 0;
	calCnt = 0;

	btnG2_num_0 = new QPushButton("0");
	btnG2_num_1 = new QPushButton("1");
	btnG2_num_2 = new QPushButton("2");
	btnG2_num_3 = new QPushButton("3");
	btnG2_num_4 = new QPushButton("4");
	btnG2_num_5 = new QPushButton("5");
	btnG2_num_6 = new QPushButton("6");
	btnG2_num_7 = new QPushButton("7");
	btnG2_num_8 = new QPushButton("8");
	btnG2_num_9 = new QPushButton("9");
	btnG2_point_1d0 = new QPushButton("1.0");
	btnG2_point_1d5 = new QPushButton("1.5");
	btnG2_point_2d0 = new QPushButton("2.0");
	btnG2_point_2d5 = new QPushButton("2.5");
	btnG2_point_3d0 = new QPushButton("3.0");
	btnG2_point_3d5 = new QPushButton("3.5");
	btnG2_point_4d0 = new QPushButton("4.0");
	btnG2_point_4d5 = new QPushButton("4.5");
	btnG2_point_5d0 = new QPushButton("5.0");
	btnG2_point_5d5 = new QPushButton("5.5");
	btnG2_point_6d0 = new QPushButton("6.0");
	btnG2_point_6d5 = new QPushButton("6.5");
	btnG2_point_7d0 = new QPushButton("7.0");
	btnG2_equal = new QPushButton("=");
	btnG2_deleteItem = new QPushButton("delCurrItem");
	btnG2_AC = new QPushButton("AC");
	btnG2_saveAsFile = new QPushButton("SAVE AS...");

	btnG2_num_0->setFixedSize(QSize(90, 40));
	btnG2_num_1->setFixedSize(QSize(90, 40));
	btnG2_num_2->setFixedSize(QSize(90, 40));
	btnG2_num_3->setFixedSize(QSize(90, 40));
	btnG2_num_4->setFixedSize(QSize(90, 40));
	btnG2_num_5->setFixedSize(QSize(90, 40));
	btnG2_num_6->setFixedSize(QSize(90, 40));
	btnG2_num_7->setFixedSize(QSize(90, 40));
	btnG2_num_8->setFixedSize(QSize(90, 40));
	btnG2_num_9->setFixedSize(QSize(90, 40));
	btnG2_point_1d0->setFixedSize(QSize(90, 40));
	btnG2_point_1d5->setFixedSize(QSize(90, 40));
	btnG2_point_2d0->setFixedSize(QSize(90, 40));
	btnG2_point_2d5->setFixedSize(QSize(90, 40));
	btnG2_point_3d0->setFixedSize(QSize(90, 40));
	btnG2_point_3d5->setFixedSize(QSize(90, 40));
	btnG2_point_4d0->setFixedSize(QSize(90, 40));
	btnG2_point_4d5->setFixedSize(QSize(90, 40));
	btnG2_point_5d0->setFixedSize(QSize(90, 40));
	btnG2_point_5d5->setFixedSize(QSize(90, 40));
	btnG2_point_6d0->setFixedSize(QSize(90, 40));
	btnG2_point_6d5->setFixedSize(QSize(90, 40));
	btnG2_point_7d0->setFixedSize(QSize(90, 40));
	btnG2_equal->setFixedSize(QSize(90, 40));
	btnG2_deleteItem->setFixedSize(QSize(90, 40));
	btnG2_AC->setFixedSize(QSize(90, 40));
	btnG2_saveAsFile->setFixedSize(QSize(90, 40));

	btnG2_saveAsFile->setToolTip("Save as ...");
	btnG2_deleteItem->setToolTip("delete current item.");
	btnG2_equal->setToolTip("get result.");

	hbox1->addWidget(fun2_ListView);
	hbox1->addWidget(fun2_ListView_1);

	hbox2->addWidget(btnG2_num_7);
	hbox2->addWidget(btnG2_num_8);
	hbox2->addWidget(btnG2_num_9);

	hbox3->addWidget(btnG2_num_4);
	hbox3->addWidget(btnG2_num_5);
	hbox3->addWidget(btnG2_num_6);

	hbox4->addWidget(btnG2_num_1);
	hbox4->addWidget(btnG2_num_2);
	hbox4->addWidget(btnG2_num_3);

	hbox5->addWidget(btnG2_AC);
	hbox5->addWidget(btnG2_num_0);
	hbox5->addWidget(btnG2_deleteItem);

	hbox6->addWidget(btnG2_point_1d0);
	hbox6->addWidget(btnG2_point_1d5);
	hbox6->addWidget(btnG2_point_2d0);

	hbox7->addWidget(btnG2_point_2d5);
	hbox7->addWidget(btnG2_point_3d0);
	hbox7->addWidget(btnG2_point_3d5);

	hbox8->addWidget(btnG2_point_4d0);
	hbox8->addWidget(btnG2_point_4d5);
	hbox8->addWidget(btnG2_point_5d0);
		 
	hbox9->addWidget(btnG2_point_5d5);
	hbox9->addWidget(btnG2_point_6d0);
	hbox9->addWidget(btnG2_point_6d5);

	hbox11->addWidget(btnG2_point_7d0);
	hbox11->addWidget(btnG2_equal);
	hbox11->addWidget(btnG2_saveAsFile);

	QLabel *label = new QLabel("--------- grade ---------");
	QLabel *label_1 = new QLabel("--------- credits ---------");
	label->setAlignment(Qt::AlignBottom | Qt::AlignCenter);
	label_1->setAlignment(Qt::AlignBottom | Qt::AlignCenter);

	vbox1->addWidget(label);
	vbox1->addLayout(hbox2);   
	vbox1->addLayout(hbox3);
	vbox1->addLayout(hbox4);
	vbox1->addLayout(hbox5);
	


	vbox2->addWidget(label_1);
	vbox2->addLayout(hbox6);
	vbox2->addLayout(hbox7);
	vbox2->addLayout(hbox8);
	vbox2->addLayout(hbox9);
	vbox2->addLayout(hbox11);

	hbox12->addLayout(vbox1);
	hbox12->addLayout(vbox2);

	vBoxMain->addLayout(hbox1, 1);
	vBoxMain->addLayout(hbox12, 2);

	widget2->setLayout(vBoxMain);

	gradePointShow = new QWidget(widget2);
	gradePointShow->setGeometry(180, 140, 300, 50);
	resultShow = new QLabel(gradePointShow);
	resultShow->setGeometry(5, 5, 290, 40);
	QPalette qp;
	qp.setColor(QPalette::WindowText, Qt::red);
	resultShow->setPalette(qp);
	QFont qf;
	qf.setPointSize(14);
	resultShow->setFont(qf);
	hbox_resultShow->addWidget(resultShow);
	gradePointShow->setLayout(hbox_resultShow);
	gradePointShow->move(600, 0);
}