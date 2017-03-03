#include "Calculator.h"

void MainWindow::fun2_gradeNumBtnAction() {                                           //score input action
	if (!isGradeInputMode || isErrorDetected || isGotResult) {
		return;
	}

	QPushButton *btn = qobject_cast<QPushButton *>(this->sender());

	if (btn == btnG2_num_0) {
		if (!m_qstrCurrGrade.isEmpty() && m_qstrCurrGrade.toFloat() == 0) {          //in order to rule out the situation: 00...
		
		}
		else {
			m_qstrCurrGrade.append("0");
		}
	}
	else if (btn == btnG2_num_1) {
		m_qstrCurrGrade.append("1");                                                 //store num
	}
	else if (btn == btnG2_num_2) {
		m_qstrCurrGrade.append("2");
	}
	else if (btn == btnG2_num_3) {
		m_qstrCurrGrade.append("3");
	}
	else if (btn == btnG2_num_4) {
		m_qstrCurrGrade.append("4");
	}
	else if (btn == btnG2_num_5) {
		m_qstrCurrGrade.append("5");
	}
	else if (btn == btnG2_num_6) {
		m_qstrCurrGrade.append("6");
	}
	else if (btn == btnG2_num_7) {
		m_qstrCurrGrade.append("7");
	}
	else if (btn == btnG2_num_8) {
		m_qstrCurrGrade.append("8");
	}
	else if (btn == btnG2_num_9) {
		m_qstrCurrGrade.append("9");
	}

	if (m_qstrCurrGrade.toFloat() > 100) {                                          //if detected that grade is over 100, disp a warning at statusBar
		ui.statusBar->showMessage("grade [" + m_qstrCurrGrade + "]" + "     WARNING: current grade don't conform to the normal situation(0~100)", 10000);
	}
	else {                                                                          //else display the value
		ui.statusBar->showMessage("current data: grade [" + m_qstrCurrGrade + "]", 10000);
	}
}

void MainWindow::fun2_creditNumBtnAction() {                                        //credits input
	if (isErrorDetected || isGotResult) {                                           //if already got the result or an error was detected, return                                       
		return;
	}
	if (m_qstrCurrGrade.isEmpty()) {                                                //if input the credits while grade is null, return
		ui.statusBar->showMessage("please enter the grade first!", 5000);
		return;
	}

	QPushButton *btn = qobject_cast<QPushButton *>(this->sender());

	if (btn == btnG2_point_1d0) {
		m_qstrCurrCredit = "1.0";
	}
	else if (btnG2_point_1d5 == btn) {
		m_qstrCurrCredit = "1.5";
	}
	else if (btnG2_point_2d0 == btn) {
		m_qstrCurrCredit = "2.0";
	}
	else if (btnG2_point_2d5 == btn) {
		m_qstrCurrCredit = "2.5";
	}
	else if (btnG2_point_3d0 == btn) {
		m_qstrCurrCredit = "3.0";
	}
	else if (btnG2_point_3d5 == btn) {
		m_qstrCurrCredit = "3.5";
	}
	else if (btnG2_point_4d0 == btn) {
		m_qstrCurrCredit = "4.0";
	}
	else if (btnG2_point_4d5 == btn) {
		m_qstrCurrCredit = "4.5";
	}
	else if (btnG2_point_5d0 == btn) {
		m_qstrCurrCredit = "5.0";
	}
	else if (btnG2_point_5d5 == btn) {
		m_qstrCurrCredit = "5.5";
	}
	else if (btnG2_point_6d0 == btn) {
		m_qstrCurrCredit = "6.0";
	}
	else if (btnG2_point_6d5 == btn) {
		m_qstrCurrCredit = "6.5";
	}
	else if (btnG2_point_7d0 == btn) {
		m_qstrCurrCredit = "7.0";
	}
	isGradeInputMode = true;                                                          //mark the grade input status
	ui.statusBar->showMessage("current data: grade [" + m_qstrCurrGrade + "]  credits [" + m_qstrCurrCredit + "]", 5000);
	fun2_listViewCtrl();
}

void MainWindow::fun2_listViewCtrl() {                                                //list display control
	list_Grade->append(m_qstrCurrGrade);                                              //store the data to QString List(The data-base of ListView)
	list_Credits->append(m_qstrCurrCredit);
	
	QString temp_0 = static_cast<QString>(list_Grade->at(m_iItemCnt));                //get the data from String list
	QString temp_1 = static_cast<QString>(list_Credits->at(m_iItemCnt));

	QStandardItem *gradeItem = new QStandardItem(temp_0);                             
	QStandardItem *creditItem = new QStandardItem(temp_1);

	if (m_iItemCnt % 2 == 0) {                                                        //set item background
		QLinearGradient qg(QPoint(0, 0), QPoint(120, 0));                             //declare a Linear Gradient
		qg.setColorAt(0, LIGHT_BLUE);
		qg.setColorAt(1, LIGHT_GREEN);
		QBrush qb(qg);
		gradeItem->setBackground(qb);
		creditItem->setBackground(qb);
	}

	if (m_qstrCurrGrade.toFloat() > 100) {                                            //if the value is over 100, mark it to red
		gradeItem->setForeground(Qt::red);
	}

	m_iItemCnt++;
	fun2_GradeModel->appendRow(gradeItem);                                            //add new row to item model
	fun2_CreditModel->appendRow(creditItem);
	fun2_ListView->scrollToBottom();                                                  //let list view scroll to the last item
	fun2_ListView_1->scrollToBottom();

	m_qstrCurrCredit.clear();                                                         //clear temporary data
	m_qstrCurrGrade.clear();
}

void MainWindow::fun2_allClear() {                                                    //all clear, initial the grade function
	gradePointShow->move(600, 0);
	m_qstrCurrCredit.clear();
	m_qstrCurrGrade.clear();
	isGradeInputMode = true;
	isGotResult = false;
	isErrorDetected = false;
	m_iItemCnt = 0;
	m_fResult = 0;
	fun2_GradeModel->clear();
	fun2_CreditModel->clear();
	list_Grade->clear();
	list_Credits->clear();
}

float MainWindow::weightAnalyse(float score) {
	if (score < 60) {
		return 0;
	}
	else if (score < 65) {
		return 1.0;
	}
	else if (score < 70) {
		return 1.5;
	}
	else if (score < 75) {
		return 2.0;
	}
	else if (score < 80) {
		return 2.5;
	}
	else if (score < 85) {
		return 3.0;
	}
	else if (score < 90) {
		return 3.5;
	}
	else if (score < 95) {
		return 4.0;
	}
	else if (score <= 100) {
		return 4.5;
	}
	else {
		isErrorDetected = true;                                               //if value is over 100, mark the error
		return 0;
	}
}

void MainWindow::fun2_getResult() {
	if (isErrorDetected || isGotResult) {                                 
		return;
	}
	if (list_Credits->size() != list_Grade->size()) {                        
		ui.statusBar->showMessage("warning: Number does not match!", 3000);
		return;
	}
	int len = list_Credits->size();
	float credits = 0, temp = 0;
	QVector<double> qvector;
	for (int i = 0; i < len; i++) {
		qvector.append(weightAnalyse(list_Grade->at(i).toFloat()));          //store the weight of every item
		if (isErrorDetected) {                                               //if detected an error, return
			ui.statusBar->showMessage("warning: please check up your input!", 3000);
			return;
		}
		qvector.replace(i, qvector.at(i)*list_Credits->at(i).toFloat());
		credits += list_Credits->at(i).toFloat();
		temp += qvector.at(i);
	}

	m_fResult = temp / credits;
	dataSave();                                                              //store data
	showMsg("***" + QString("%1").arg(m_fResult));
	isGotResult = true;
}

void MainWindow::errorPrint(QString errorMsg) {
	ui.statusBar->showMessage(errorMsg, 5000);
}

void MainWindow::showMsg(QString txt) {
	resultShow->setText(txt);
	gradePointShow->move(10, 140);
}

void MainWindow::fun2_deleteBtnAction() {                                     //btn_deleteItem action
	if (isGotResult) {
		return;
	}
	isErrorDetected = false;
	if (!m_qstrCurrGrade.isEmpty()) {
		ui.statusBar->showMessage("clear current input...", 2000);
		m_qstrCurrGrade.clear();
	}
	else if(m_iItemCnt == 0){
		ui.statusBar->showMessage("error: current list is empty!", 5000);
	}
	else {
		m_iItemCnt--;
		ui.statusBar->showMessage("delete an item:  " + list_Grade->at(m_iItemCnt) + "< --- >" + list_Credits->at(m_iItemCnt));

		list_Grade->removeAt(m_iItemCnt);                                    //delete item from string list
		list_Credits->removeAt(m_iItemCnt);
		fun2_GradeModel->removeRow(m_iItemCnt);                              //delete from model at the same time
		fun2_CreditModel->removeRow(m_iItemCnt);
	}
}

void MainWindow::dataSave() {
	QFile f("history.dat");
	if (!f.open(QIODevice::WriteOnly | QIODevice::Text | QFile::Append))
	{
		showMsg("error: file open failed!");
		return;
	}

	QTextStream txtOutput(&f);
	txtOutput.atEnd();
	calCnt++;
	txtOutput << "************************[" << calCnt << "]**************************\ngrade:";
	for (int i = 0; i < list_Grade->size(); i++) {
		if (i != 0) {
			txtOutput << "   \\";
		}
		txtOutput << list_Grade->at(i);
	}
	txtOutput << "\ncredit:";
	for (int i = 0; i < list_Credits->size(); i++) {
		if (i != 0) {
			txtOutput << "   \\";
		}
		txtOutput << list_Credits->at(i);
	}
	txtOutput << "\ngradePoint:" << m_fResult << "\n";

	f.close();
}

void MainWindow::fun2_saveAs() {
	if (!isGotResult) {
		return;
	}
	QFile f("result.txt");
	if (!f.open(QIODevice::WriteOnly | QIODevice::Text | QFile::Append))
	{
		showMsg("error: file open failed!");
		return;
	}

	QTextStream txtOutput(&f);
	txtOutput << "\ngrade:";
	for (int i = 0; i < list_Grade->size(); i++) {
		if (i != 0) {
			txtOutput << "   \\";
		}
		txtOutput << list_Grade->at(i);
	}
	txtOutput << "\ncredit:";
	for (int i = 0; i < list_Credits->size(); i++) {
		if (i != 0) {
			txtOutput << "   \\";
		}
		txtOutput << list_Credits->at(i);
	}
	txtOutput << "\ngradePoint:" << m_fResult << "\n";
	showMsg("save complete: result.txt");
	f.close();
}
