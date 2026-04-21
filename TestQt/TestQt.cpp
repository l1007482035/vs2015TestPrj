#include "stdafx.h"
#include "TestQt.h"
#include <QtConcurrent>
#include <QFuture>

TestQt::TestQt(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	progressBar->setRange(0, 100);
}


/*
QApplication::processEvents() 的主要作用是手动触发 Qt 事件循环处理待处理的事件以保持界面响应
在长耗时的位置调用QApplication::processEvents()，可以多次调用
*/
void TestQt::on_pushButton_clicked()
{
#if 1
	// 模拟耗时操作
	for (int i = 0; i <= 100; ++i) {
		QThread::msleep(50); // 模拟耗时任务
		progressBar->setValue(i);
		QApplication::processEvents(); // 处理事件以保持界面响应
	}
	pushButton->setText("Finished");

#endif


#if 0
	QApplication::setOverrideCursor(Qt::WaitCursor);
	QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
	DWORD dwtick = GetTickCount();
	int nVal = 0;
	
	while (true)
	{
		QApplication::processEvents();
		nVal++;
		DWORD dwtick2 = GetTickCount();
		if (dwtick2 - dwtick > 10000)
		{
			break;
		}
	}

	QApplication::restoreOverrideCursor();
#endif
}

int TestQt::longTimeFunc(int nVal, QString qsStr)
{
	DWORD dwtick = GetTickCount();
	int nVal1 = 0;
	int nGG = 24;

	while (true)
	{
		QApplication::processEvents();
		nVal1++;
		DWORD dwtick2 = GetTickCount();
		if (dwtick2 - dwtick > 10000)
		{
			break;
		}
	}

	return nGG;
}


//演示QFuture处理异步并行
void TestQt::on_pushButton_2_clicked()
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	QFuture<int> future = QtConcurrent::run(this, &TestQt::longTimeFunc, 10, QString("abc"));
	while (!future.isFinished())
	{
		QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
	}
	QApplication::restoreOverrideCursor();
	int nRet = future.result();

}


void TestQt::longRunningTask()
{
	for (int i = 0; i <= 100; ++i) 
	{
		QThread::msleep(50); // Simulate work being done
		emit progressValueChanged(i);
	}
}

void TestQt::handleFinished() 
{
	// Handle any post-processing after the task is finished
	QMessageBox::information(this, tr("Completed"), tr("The operation is completed."));
	progressBar->setValue(100);
}



//演示QFuture处理异步并行
void TestQt::on_pushButton_3_clicked()
{
	progressBar->setRange(0, 100);
	futureWatcher = new QFutureWatcher<void>(this);
	// Connect the QFutureWatcher signals to our slots

	connect(futureWatcher, &QFutureWatcherBase::progressValueChanged,
		progressBar, &QProgressBar::setValue);
	connect(futureWatcher, &QFutureWatcher<void>::finished, this, &TestQt::handleFinished);
	// Start a long-running task
	// Run the task and set it to be watched by the QFutureWatcher
	QFuture<void> future = QtConcurrent::run(this, &TestQt::longRunningTask);
	futureWatcher->setFuture(future);

}
