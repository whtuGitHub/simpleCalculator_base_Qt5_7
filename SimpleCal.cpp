#include "Calculator.h"

void MainWindow::numBtnAction() {
	QPushButton *btn = qobject_cast<QPushButton *>(this->sender());
	if (btn == btnG1_num_0) {
		numInput("0");
	}
	else if (btn == btnG1_num_1) {
		numInput("1");
	}
	else if (btn == btnG1_num_2) {
		numInput("2");
	}
	else if (btn == btnG1_num_3) {
		numInput("3");
	}
	else if (btn == btnG1_num_4) {
		numInput("4");
	}
	else if (btn == btnG1_num_5) {
		numInput("5");
	}
	else if (btn == btnG1_num_6) {
		numInput("6");
	}
	else if (btn == btnG1_num_7) {
		numInput("7");
	}
	else if (btn == btnG1_num_8) {
		numInput("8");
	}
	else if (btn == btnG1_num_9) {
		numInput("9");
	}
}

void MainWindow::bracketInput() {                              
	if (errorFlag || isOptComplete || isExponentialCal) {                
		return;
	}
	QPushButton *btn = qobject_cast<QPushButton*>(this->sender());
	storeNum();
	QString bracket;
	if (btn == btnG1_bracket_left) {
		bracket = "(";
	}
	else {
		bracket = ")";
	}
	m_strListInputGet->append(bracket);

	dispCtrl(bracket);
}

void MainWindow::signInput() {
	if (errorFlag || isOptComplete || isExponentialCal) {
		return;
	}
	QPushButton *btn = qobject_cast<QPushButton *>(this->sender());
	QString optType, optTypeTmp;
	storeNum();
	if (btn == btnG1_add) {
		optType = "+";
	}
	else if (btn == btnG1_minus) {
		optType = "-";
	}
	else if (btn == btnG1_multiply) {
		optType = "*";
	}
	else if (btn == btnG1_divide) {
		optType = "/";
	}
	if (m_Add_minus.contains(optType)) {                                                           //if input "+" or "-" at first, store the sign "+" or "-" to number, make it to be a part of operate number
		if (!m_strListInputGet->isEmpty()) {
			optTypeTmp = m_strListInputGet->at(m_strListInputGet->size()-1);
			if (m_map1.contains(optTypeTmp) && optTypeTmp != ")") {                                //if m_map1 contain current sign and it's not ")"
				if (m_Add_minus.contains(optTypeTmp)) {                                            //and if current sign is "+" or "-", make it to be a part of opt num
					m_strListInputGet->replace(m_strListInputGet->size() - 1, optType);
					dispData.chop(1);                                                              //sync display data
				}
				else {
					m_qstrNumTemp.append(optType);
				}
			}
			else {
				m_strListInputGet->append(optType);
			}
		}
		else {
			m_qstrNumTemp.append(optType);
		}
		dispCtrl(optType);
	}
	else if (m_divide_multi.contains(optType)) {                                                   //if last sign is "*" or "/" replace the last sign in m_strListInputGet,  like this:  ...89*  -----input / ------>  ...89/
		if (!m_strListInputGet->isEmpty()) {
			optTypeTmp = m_strListInputGet->at(m_strListInputGet->size()-1);
			if (m_map1.contains(optTypeTmp) && !m_bracket.contains(optTypeTmp)) {
				m_strListInputGet->removeAt(m_strListInputGet->size()-1);
				m_strListInputGet->append(optType);
				dispData.replace(dispData.length()-1, 1, optType);                                 //display data sync
				dispCtrl(NULL);
				return;
			}
			else {
				m_strListInputGet->append(optType);
				dispCtrl(optType);
			}
		}
	}
}

void MainWindow::x_nInput() {                                                                     //Exponential Calculate
	if (errorFlag || isOptComplete || isExponentialCal) {
		return;
	}
	storeNum();
	if (m_strListInputGet->size() > 1 || m_map1.contains(m_strListInputGet->at(0))) {
		return;
	}
	isExponentialCal = true;                                                                     //mark the sign
	dispCtrl("^");                                                                               //display sync
}

void MainWindow::storeNum() {
	if (m_qstrNumTemp == "+" || m_qstrNumTemp == "-") {                                          //if current number cache is just a sign, sync disp data and return
		m_qstrNumTemp.clear();
		dispData.chop(1);
		return;
	}
	if (!m_qstrNumTemp.isEmpty()) {
		m_strListInputGet->append(m_qstrNumTemp);
		m_qstrNumTemp.clear();                                                                  //clear numTemp after store num
	}
}

void MainWindow::btnCEAction() {
	if (errorFlag || isOptComplete || isExponentialCal) {
		clearAll();
		return;
	}
	storeNum();
	if (isOptComplete || m_strListInputGet->isEmpty()) {
		isOptComplete = false;
		clearAll();
		return;
	}
	else {
		QString temp = m_strListInputGet->at(m_strListInputGet->size() - 1);                    //btn CE remove a item at one step
		m_strListInputGet->removeAt(m_strListInputGet->size() - 1);
		dispData.chop(temp.length());                                                           //remove the same length data from diaplay data
		if (dispData.isEmpty()) {                                                               //if display data is null now, clear all and return
			clearAll();
			return;
		}
		else {
			dispCtrl(NULL);
		}
	}
}

void MainWindow::btnDotAction() {         
	if (errorFlag || isOptComplete) {
		return;
	}
	m_qstrNumTemp.append(".");
	
	dispCtrl(".");
}

void MainWindow::numInput(QString num) {
	if (errorFlag) {
		return;
	}
	if (isOptComplete) {
		isOptComplete = false;
		clearAll();
	}
	if (m_qstrNumTemp.toFloat() == 0 && m_qstrNumTemp.length() == 1 && num == "0") {         //To rule out the situation : 00...
		return;
	}
	m_qstrNumTemp.append(num);

	if (num.at(0) == "+" || num.at(0) == "-") {
		num.remove(0,0);
	}
	dispCtrl(num);
}

void MainWindow::backspaceAction() {
	if (isOptComplete || m_strListInputGet->isEmpty() || errorFlag) {
		isOptComplete = false;
		clearAll();
		return;
	}
	else {
		QString temp = m_strListInputGet->at(m_strListInputGet->size() - 1);                 //get the tail element
		temp.chop(1);                                                                        //delete last character
		m_strListInputGet->removeAt(m_strListInputGet->size() - 1);                          //remove last element
		if (temp.length() != 0) {
			m_strListInputGet->append(temp);                                                 //if length isn't zero, add element after changing 
		}

		dispData.chop(1);                                                                    //sync disply data
		text_disp->setText(dispData);                                                        //refresh disply detail
	}
}

void MainWindow::dispCtrl(QString detail) {
	if (detail != NULL) {
		dispData.append(detail);
	}
	text_disp->setText(dispData);
	if (isOptComplete) {
		listViewCtrl();
	}
	if (dispData.length() >= 18) {                                                          //if here is no enough space to display the data, let the font point size of text_disp to 16
		QFont qf;
		qf.setPointSize(DISP_TEXT_SIZE_SMALL);
		text_disp->setFont(qf);
	}
}

void MainWindow::clearAll() {
	dispData.clear();
	m_qstrNumTemp.clear();
	m_qstrResult.clear();
	m_strListInputGet->clear();
	m_stackNum.clear();
	m_stackSign.clear();
	m_PostFix.clear();
	m_dResult = 0;
	isOptComplete = false;
	errorFlag = false;
	isExponentialCal = false;

	QFont qf;                                                                              //restore the font size while all clear
	qf.setPointSize(DISP_TEXT_SIZE);
	text_disp->setFont(qf);
	text_disp->setTextColor(Qt::black);
	text_disp->setText("0");
}

void MainWindow::getResult() {
	storeNum();
	if (m_strListInputGet->isEmpty() || isOptComplete) {
		return;
	}
	double resultCache = 0;
	if (isExponentialCal) {                                                               //if now is exponential calculate
		if (m_strListInputGet->size() <= 1) {
			errorOutput("error: here is no enough operate number");
			return;
		}
		for (int i = 0; i < 2; i++) {                                                     // if here is not only opt num, throw an error
			if (m_map1.contains(m_strListInputGet->at(i))) {
				errorOutput("error: please check up your input");
				return;
			}
		}
		resultCache = pow(m_strListInputGet->at(0).toDouble(), m_strListInputGet->at(1).toDouble());          //else go on the cal   (math pow())
		dispData.append(QString("=%1").arg(resultCache));                                //display data refresh
		isOptComplete = true;
		dispCtrl(NULL);
		return;
	}


	infixToPostFix();                                                                   //infix expression convert postfix expression
	if (errorFlag) {
		return;
	}
	
#ifdef USING_DEBUG
	QString debugDisp;
	for (int i = 0; i < m_PostFix.size(); i++) debugDisp.append(static_cast<QString>(m_PostFix.at(i)));
	ui.statusBar->showMessage(debugDisp);
#endif // USING_DEBUG

	QString temp;
	for (int i = 0; i < m_PostFix.size(); i++) {
		temp = m_PostFix.at(i);
		if (m_map1.contains(temp)) {
			if (m_stackNum.size() <= 1) {                                              //if get an opt sign but number stack rest only a number, throw an error and return
				errorOutput("please check up your input!");
				return;
			}
			resultCache = singleStepCalculate(m_stackNum.pop(), m_stackNum.pop(), temp);  //if nothing error here, go on cal
			if (errorFlag) {                                                           
				return;
			}
			m_stackNum.push(resultCache);                                              //after one step cal, push the resultCache to stack
		}
		else {
			m_stackNum.push(temp.toDouble());
		}
	}
	/*if (m_stackNum.size() > 1) {
		errorOutput("error: please check up your input!");
		return;
	}*/
	isOptComplete = true;                                                              //mark the successful sign
	m_dResult = m_stackNum.pop();                                                      //get the final result from num stack
	m_qstrResult = QString().setNum(m_dResult, 'g', effective_len);
	dispData.append("=" + m_qstrResult);                                               //disp data refresh
	dispCtrl(NULL);
}

double MainWindow::singleStepCalculate(double num1, double num2, QString optType) {
	double resultCache = 0;
	if (optType == "+") {
		resultCache = num1 + num2;
	}
	else if (optType == "-") {
		resultCache = num1 - num2;
	}
	else if (optType == "*") {
		resultCache = num1 * num2;
	}
	else if (optType == "/") {
		if (num2 == 0) {
			errorOutput("an error detected: some computing makes divisor zero.");
			return 0;
		}
		resultCache = num1 / num2;
	}
	return resultCache;
}

void MainWindow::completeExpression() {
	/*****************all of the change in this function won't display in text edit******************/
	int i = 0;
	for (i = 0; i < m_strListInputGet->size(); i++) {
		if (m_strListInputGet->at(i) == "(" && i != 0) {                                //if "(" is in the first position, ignore this
			if (!m_map1.contains(m_strListInputGet->at(i - 1))) {                       //if here is a num before "(", insert a "*" between them, like this: 1+2(  --->  1+2*(
				m_strListInputGet->insert(i, "*");
			}
		}
		if (m_strListInputGet->at(i) == ")" && i + 1 != m_strListInputGet->size()) {    //if ")" is in the last position, ignore this
			if (!m_map1.contains(m_strListInputGet->at(i + 1))) {                       //if here is a num behind ")", insert a "*" between them, like this: ...)2+2  --->  ...)*2+2
				m_strListInputGet->insert(i+1, "*");
			}
		}
	}
}

//bool MainWindow::errorDetect() {
//	int i = 0, len = m_strListInputGet->size();
//	bool last_is_Sign = false;
//	QString temp1, temp2;
//	for (i = 0; i < len; i++) {
//		temp1 = m_strListInputGet->at(i);
//		/*if (m_map1.contains(temp1)) {
//			if (last_is_Sign) {
//				if (temp1 == "(" && i + 1 != len) {
//					temp2 = m_strListInputGet->at(i + 1);
//					if (m_map1.contains(temp2)) {
//						if (temp2 == "/" || temp2 == "*" || temp2 == ")") {
//							return false;
//						}
//					}
//				}
//				else {
//					return false;
//				}
//			}
//			else {
//				if (temp1 == "(" && i + 1 != len) {
//					temp2 = m_strListInputGet->at(i+1);
//					if (m_map1.contains(temp2)) {
//						if (temp2 == "/" || temp2 == "*" || temp2 == ")") {
//							return false;
//						}
//					}
//				}
//			}
//		}
//		else {
//			last_is_Sign = false;
//		}*/
//		if (i == 0 && m_divide_multi.contains(temp1)) {
//			return true;
//		}
//		else if () {
//		........
//		}
//	}
//}

bool MainWindow::bracketRuleDetect() {                                     //brackets matching detection
	int i = 0, len = m_strListInputGet->size();
	m_stackSign.clear();
	for (i = 0; i < len; i++) {
		if (m_strListInputGet->at(i) == "(") {
			m_stackSign.push("(");
		}
		else if(m_strListInputGet->at(i) == ")"){
			if (!m_stackSign.isEmpty()) {
				m_stackSign.pop();
			}
			else {
				return false;
			}
		}
	}

	if (!m_stackSign.isEmpty()) {
		return false;
	}
	return true;
}

void MainWindow::infixToPostFix() {
	if (!bracketRuleDetect()) {
		errorOutput("***brackets is not match");
		return;
	}
	completeExpression();
	QString temp_1;                                                  //new read cache
	QString temp_2;                                                  //stack item cache
	for (int i = 0; i < m_strListInputGet->size(); i++) {
		temp_1 = m_strListInputGet->at(i);
		if (!m_map1.contains(temp_1)) {                              //if current element is a operate number
			m_PostFix.append(temp_1);                                //then append to postfix expression
			continue;
		}
		if (!m_stackSign.isEmpty()) {
			temp_2 = m_stackSign.top();                              //if the sign_stack is not empty, get the top element
		}
		else {
			m_stackSign.push(temp_1);                                //else push the new read element
			continue;
		}

		if (m_map1[temp_1] > m_map2[temp_2]) {                       //if the priority of stack element is lower than the new read element         
			m_stackSign.push(temp_1);
			continue;
		}
		else if (temp_1 == ")" && temp_2 == "(") {                   //To rule out the situation: ()
			m_stackSign.pop();
			continue;
		}
		else if (m_map1[temp_1] < m_map2[temp_2]) {                  //if the priority of stack element is higher than the new read element  
			m_PostFix.append(m_stackSign.pop());                     //pop the top element and add to postfix expression
			while (true) {
				if (m_stackSign.isEmpty()) {
					m_stackSign.push(temp_1);
					break;
				}
				temp_2 = m_stackSign.top();
				if (temp_1 == ")" && temp_2 == "(") {                //To rule out the situation: ()
					m_stackSign.pop();
					break;
				}
				if (m_map1[temp_1] > m_map2[temp_2]) {               //if the priority of the new read item is higher than the stack element
					m_stackSign.push(temp_1);                        //push the new read element to stack, and then break
					break;
				}
				else {
					m_PostFix.append(m_stackSign.pop());
					continue;
				}
			}
		}
	}
	while (!m_stackSign.isEmpty()) {                                 //after traversing string list, add remaining elements in the stack to the postfix expression
		m_PostFix.append(m_stackSign.pop());
	}
}

void MainWindow::listViewCtrl() {
	if (dispData.isEmpty()) {
		return;
	}
	m_qstrList1.append(dispData);
	QString temp = m_qstrList1.at(optCnt++);
	QStandardItem *item = new QStandardItem(temp);
	if (optCnt % 2 == 1) {
		QLinearGradient qg(QPoint(0, 0), QPoint(120, 0));            //set a new linear gradient
		qg.setColorAt(0, LIGHT_PINK);
		qg.setColorAt(1, LIGHT_YELLOW);
		QBrush qb(qg);
		item->setBackground(qb);
	}
	m_itemModel.appendRow(item);                                     //add new row to model
	myListView->scrollToBottom();
}

void MainWindow::effectiveLenSet() {                            
	effective_len = settingDialog->spinBox->value();
}

void MainWindow::btnRootAction() {                                  //sqrt()
	if (errorFlag) {
		return;
	}
	else if (isOptComplete) {
		m_strListInputGet->clear();
		m_qstrNumTemp = m_qstrResult;
	}
	if (!m_qstrNumTemp.isEmpty() && m_strListInputGet->isEmpty()) {
		if (m_qstrNumTemp.toFloat() < 0) {
			dispData = "sqrt(" + QString("%1").arg(m_qstrNumTemp) + ")";
			errorOutput("error: The operand cannot be negative!");
			return;
		}
		else {                                                     //Due to various reasons,,,,, the app is not support multiStep calculate with root action, You know! ###^_^###
			m_qstrResult = QString("%1").arg(sqrt(m_qstrNumTemp.toDouble()));
			dispData = "sqrt(" + QString("%1").arg(m_qstrNumTemp) + ")=" + m_qstrResult;
			isOptComplete = true;
		}
		dispCtrl(NULL);
	}
}

void MainWindow::useResult() {                                    //Continuous operation with result at last cal
	if (errorFlag || !isOptComplete) {
		return;
	}

	isOptComplete = false;
    QString str = m_qstrResult;
	clearAll();
	m_qstrNumTemp = str;
	dispData = str;
	dispCtrl(NULL);
}

void MainWindow::autoClear() {                                   //you can also change allClear() to adapt your thought
	m_qstrNumTemp.clear();
	m_qstrResult.clear();
	m_strListInputGet->clear();
	m_stackNum.clear();
	m_stackSign.clear();
	m_PostFix.clear();
	m_dResult = 0;
	isOptComplete = false;
	isExponentialCal = false;
}

void MainWindow::errorOutput(QString errorDetail) {
	autoClear();
	errorFlag = true;

	QFont qf;
	qf.setPointSize(DISP_TEXT_SIZE_SMALL);
	text_disp->setFont(qf);
	text_disp->setTextColor(Qt::red);
	text_disp->setText(dispData + "=error\n" + errorDetail);
}