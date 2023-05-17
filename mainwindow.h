#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QButtonGroup>
#include <QDoubleValidator>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void performCalculations();
    void performIntervalCalculations();
    void performIntervalCalculations2();

private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *arithmeticLayout, *inputLayout, *resultLayout;
    QRadioButton *floatingPoint, *intervalArithmetic, *intervalArithmetic2;
    QButtonGroup *arithmeticGroup;
    QLabel *nodesLabel, *nodeMultiplicityLabel, *valuesAndDerivativesLabel, *inputValueLabel, *outputValueLabel, *numNodesLabel;
    QTextEdit *nodesTextEdit, *nodeMultiplicityTextEdit, *valuesAndDerivativesTextEdit, *resultTextEdit;
    QLineEdit *inputValueEdit, *outputValueEdit, *numNodesEdit;
    QPushButton *computeButton;
    QWidget *centralWidget;
    QHBoxLayout *intervalArithmeticLayout;
    QLabel *numNodesLabel2;
    QLineEdit *numNodesEdit2;

    QLabel *nodesLabel2;
    QTextEdit *nodesTextEdit2;

    QLabel *nodeMultiplicityLabel2;
    QTextEdit *nodeMultiplicityTextEdit2;

    QLabel *valuesAndDerivativesLabel2;
    QTextEdit *valuesAndDerivativesTextEdit2;

    QLabel *inputValueLabel2;
    QLineEdit *inputValueEdit2;
    QLabel *outputValueLabel2;
    QLineEdit *outputValueEdit2;

    QLabel *resultTextLabel2;
    QTextEdit *resultTextEdit2;

    QPushButton *computeButton2;
    // Interval Arithmetic 3 UI elements
    QHBoxLayout *intervalArithmeticLayout3;
    QLabel *numNodesLabel3;
    QLineEdit *numNodesEdit3;
    QHBoxLayout *intervalInputLayout3;
    QVBoxLayout *nodesLayout3;
    QLabel *nodesLabel3;
    QTextEdit *nodesTextEdit3;
    QVBoxLayout *multiplicityLayout3;
    QLabel *nodeMultiplicityLabel3;
    QTextEdit *nodeMultiplicityTextEdit3;
    QVBoxLayout *valuesLayout3;
    QLabel *valuesAndDerivativesLabel3;
    QTextEdit *valuesAndDerivativesTextEdit3;
    QHBoxLayout *intervalResultLayout3;
    QVBoxLayout *left3;
    QLabel *inputValueLabel3;
    QLineEdit *inputValueEdit3;
    QLabel *outputValueLabel3;
    QLineEdit *outputValueEdit3;
    QVBoxLayout *right3;
    QLabel *resultTextLabel3;
    QTextEdit *resultTextEdit3;
    QPushButton *computeButton3;
    QLabel *name;

};

#endif // MAINWINDOW_H
