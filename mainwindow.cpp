#include "mainwindow.h"
#include "hermite.h"
#include "Interval.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    mainLayout = new QVBoxLayout();
    QLabel *name = new QLabel("Interpolacja Hermite'a");
    name->setAlignment(Qt::AlignCenter);
    arithmeticLayout = new QHBoxLayout();

    floatingPoint = new QRadioButton("Arytmetyka zmiennopozycyjna");
    intervalArithmetic = new QRadioButton("Arytmetyka przedziałowa");
    intervalArithmetic2 = new QRadioButton("Arytmetyka przedziałowa (dane przedziałowe)");
    arithmeticGroup = new QButtonGroup();
    arithmeticGroup->addButton(floatingPoint);
    arithmeticGroup->addButton(intervalArithmetic);
    arithmeticGroup->addButton(intervalArithmetic2);
    arithmeticLayout->addWidget(floatingPoint);
    arithmeticLayout->addWidget(intervalArithmetic);
    arithmeticLayout->addWidget(intervalArithmetic2);

    numNodesLabel = new QLabel("Wpisz liczbę węzłów");
    numNodesEdit = new QLineEdit();
    arithmeticLayout->addWidget(numNodesLabel);
    arithmeticLayout->addWidget(numNodesEdit);
    //ZMIENNOPOZYCYJNA
    inputLayout = new QHBoxLayout();
    QVBoxLayout *nodesLayout = new QVBoxLayout();
    nodesLabel = new QLabel("Wpisz węzły interpolacji");
    nodesTextEdit = new QTextEdit();  // Initializing nodesTextEdit before using it
    nodesLayout->addWidget(nodesLabel);
    nodesLayout->addWidget(nodesTextEdit);

    QVBoxLayout *multiplicityLayout = new QVBoxLayout();
    nodeMultiplicityLabel = new QLabel("Wpisz krotności węzłów");
    nodeMultiplicityTextEdit = new QTextEdit();
    multiplicityLayout->addWidget(nodeMultiplicityLabel);
    multiplicityLayout->addWidget(nodeMultiplicityTextEdit);

    QVBoxLayout *valuesLayout = new QVBoxLayout();
    valuesAndDerivativesLabel = new QLabel("Wpisz wartości oraz pochodne wezłów");
    valuesAndDerivativesTextEdit = new QTextEdit();
    valuesLayout->addWidget(valuesAndDerivativesLabel);
    valuesLayout->addWidget(valuesAndDerivativesTextEdit);

    inputLayout->addLayout(nodesLayout);
    inputLayout->addLayout(multiplicityLayout);
    inputLayout->addLayout(valuesLayout);

    resultLayout = new QHBoxLayout();

    QVBoxLayout *left = new QVBoxLayout();
    inputValueLabel = new QLabel("Wpisz argument, dla którego chcesz obliczyć wartość wielomianu");
    inputValueEdit = new QLineEdit();
    //QDoubleValidator *validator = new QDoubleValidator();
    //inputValueEdit->setValidator(validator);
    outputValueLabel = new QLabel("Wartość wielomianu dla podnaego argumentu");
    outputValueEdit = new QLineEdit();
    outputValueEdit->setReadOnly(true);
        left->addWidget(inputValueLabel);
        left->addWidget(inputValueEdit);
        left->addWidget(outputValueLabel);
        left->addWidget(outputValueEdit);

    QVBoxLayout *right = new QVBoxLayout();
    QLabel *resultTextLabel = new QLabel("Współczynniki wielomianu");
    resultTextEdit = new QTextEdit();
    resultTextEdit->setReadOnly(true);
        right->addWidget(resultTextLabel);
        right->addWidget(resultTextEdit);


    resultLayout->addLayout(left);
    resultLayout->addLayout(right);

    computeButton = new QPushButton("OBLICZ");
    mainLayout->addWidget(name);
    mainLayout->addLayout(arithmeticLayout);
    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(resultLayout);
    mainLayout->addWidget(computeButton);

    centralWidget = new QWidget();
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    connect(arithmeticGroup, &QButtonGroup::buttonToggled,
            [=](QAbstractButton *button, bool checked) {
                if (checked) {
                    for (auto &otherButton : arithmeticGroup->buttons()) {
                        if (otherButton != button) {
                            otherButton->setChecked(false);
                        }
                    }
                }
            });

    // Initially hide all the widgets
    nodesLabel->hide();
    nodesTextEdit->hide();
    nodeMultiplicityLabel->hide();
    nodeMultiplicityTextEdit->hide();
    valuesAndDerivativesLabel->hide();
    valuesAndDerivativesTextEdit->hide();
    inputValueLabel->hide();
    inputValueEdit->hide();
    outputValueLabel->hide();
    outputValueEdit->hide();
    numNodesLabel->hide();
    numNodesEdit->hide();
    computeButton->hide();
    resultTextEdit->hide();
    resultTextLabel->hide();

    connect(arithmeticGroup, &QButtonGroup::buttonToggled,
            [=](QAbstractButton *button, bool checked) {
                if (checked) {
                    for (auto &otherButton : arithmeticGroup->buttons()) {
                        if (otherButton != button) {
                            otherButton->setChecked(false);
                        }
                    }
                    // Show or hide widgets based on selected radio button
                    if (button == floatingPoint) {
                        nodesLabel->show();
                        nodesTextEdit->show();
                        nodeMultiplicityLabel->show();
                        nodeMultiplicityTextEdit->show();
                        valuesAndDerivativesLabel->show();
                        valuesAndDerivativesTextEdit->show();
                        inputValueLabel->show();
                        inputValueEdit->show();
                        outputValueLabel->show();
                        outputValueEdit->show();
                        numNodesLabel->show();
                        numNodesEdit->show();
                        computeButton->show();
                        resultTextEdit->show();
                        resultTextLabel->show();
                    } else {
                        nodesLabel->hide();
                        nodesTextEdit->hide();
                        nodeMultiplicityLabel->hide();
                        nodeMultiplicityTextEdit->hide();
                        valuesAndDerivativesLabel->hide();
                        valuesAndDerivativesTextEdit->hide();
                        inputValueLabel->hide();
                        inputValueEdit->hide();
                        outputValueLabel->hide();
                        outputValueEdit->hide();
                        numNodesLabel->hide();
                        numNodesEdit->hide();
                        computeButton->hide();
                        resultTextEdit->hide();
                        resultTextLabel->hide();
                    }
                }
            });
    // Connect the "LICZ" button to a function that performs the calculations and updates the results text box.
    connect(computeButton, &QPushButton::clicked, this, &MainWindow::performCalculations);
intervalArithmeticLayout = new QHBoxLayout();

numNodesLabel2 = new QLabel("Wpisz liczbę węzłów");
numNodesEdit2 = new QLineEdit();
intervalArithmeticLayout->addWidget(numNodesLabel2);
intervalArithmeticLayout->addWidget(numNodesEdit2);

QHBoxLayout *intervalInputLayout = new QHBoxLayout();
QVBoxLayout *nodesLayout2 = new QVBoxLayout();
nodesLabel2 = new QLabel("Wpisz węzły interpolacji");
nodesTextEdit2 = new QTextEdit();
nodesLayout2->addWidget(nodesLabel2);
nodesLayout2->addWidget(nodesTextEdit2);

QVBoxLayout *multiplicityLayout2 = new QVBoxLayout();
nodeMultiplicityLabel2 = new QLabel("Wpisz krotności węzłów");
nodeMultiplicityTextEdit2 = new QTextEdit();
multiplicityLayout2->addWidget(nodeMultiplicityLabel2);
multiplicityLayout2->addWidget(nodeMultiplicityTextEdit2);

QVBoxLayout *valuesLayout2 = new QVBoxLayout();
valuesAndDerivativesLabel2 = new QLabel("Wpisz wartości oraz pochodne wezłów");
valuesAndDerivativesTextEdit2 = new QTextEdit();
valuesLayout2->addWidget(valuesAndDerivativesLabel2);
valuesLayout2->addWidget(valuesAndDerivativesTextEdit2);

intervalInputLayout->addLayout(nodesLayout2);
intervalInputLayout->addLayout(multiplicityLayout2);
intervalInputLayout->addLayout(valuesLayout2);

QHBoxLayout *intervalResultLayout = new QHBoxLayout();

QVBoxLayout *left2 = new QVBoxLayout();
inputValueLabel2 = new QLabel("Wpisz argument, dla którego chcesz obliczyć wartość wielomianu");
inputValueEdit2 = new QLineEdit();
outputValueLabel2 = new QLabel("Wartość wielomianu dla podnaego argumentu");
outputValueEdit2 = new QLineEdit();
outputValueEdit2->setReadOnly(true);
    left2->addWidget(inputValueLabel2);
    left2->addWidget(inputValueEdit2);
    left2->addWidget(outputValueLabel2);
    left2->addWidget(outputValueEdit2);

QVBoxLayout *right2 = new QVBoxLayout();
QLabel *resultTextLabel2 = new QLabel("Współczynniki wielomianu");
resultTextEdit2 = new QTextEdit();
resultTextEdit2->setReadOnly(true);
    right2->addWidget(resultTextLabel2);
    right2->addWidget(resultTextEdit2);

intervalResultLayout->addLayout(left2);
intervalResultLayout->addLayout(right2);

computeButton2 = new QPushButton("OBLICZ");
mainLayout->addLayout(intervalArithmeticLayout);
mainLayout->addLayout(intervalInputLayout);
mainLayout->addLayout(intervalResultLayout);
mainLayout->addWidget(computeButton2);

// Initially hide all the widgets
nodesLabel2->hide();
nodesTextEdit2->hide();
nodeMultiplicityLabel2->hide();
nodeMultiplicityTextEdit2->hide();
valuesAndDerivativesLabel2->hide();
valuesAndDerivativesTextEdit2->hide();
inputValueLabel2->hide();
inputValueEdit2->hide();
outputValueLabel2->hide();
outputValueEdit2->hide();
numNodesLabel2->hide();
numNodesEdit2->hide();
computeButton2->hide();
resultTextEdit2->hide();
resultTextLabel2->hide();

// Show or hide widgets based on selected radio button
connect(arithmeticGroup, &QButtonGroup::buttonToggled,
        [=](QAbstractButton *button, bool checked) {
            if (checked) {
                for (auto &otherButton : arithmeticGroup->buttons()) {
                    if (otherButton != button) {
                        otherButton->setChecked(false);
                    }
                }
                if (button == intervalArithmetic) {
                    nodesLabel2->show();
                    nodesTextEdit2->show();
                    nodeMultiplicityLabel2->show();
                    nodeMultiplicityTextEdit2->show();
                    valuesAndDerivativesLabel2->show();
                    valuesAndDerivativesTextEdit2->show();
                    inputValueLabel2->show();
                    inputValueEdit2->show();
                    outputValueLabel2->show();
                    outputValueEdit2->show();
                    numNodesLabel2->show();
                    numNodesEdit2->show();
                    computeButton2->show();
                    resultTextEdit2->show();
                    resultTextLabel2->show();
                } else {
                    nodesLabel2->hide();
                    nodesTextEdit2->hide();
                    nodeMultiplicityLabel2->hide();
                    nodeMultiplicityTextEdit2->hide();
                    valuesAndDerivativesLabel2->hide();
                    valuesAndDerivativesTextEdit2->hide();
                    inputValueLabel2->hide();
                    inputValueEdit2->hide();
                    outputValueLabel2->hide();
                    outputValueEdit2->hide();
                    numNodesLabel2->hide();
                    numNodesEdit2->hide();
                    computeButton2->hide();
                    resultTextEdit2->hide();
                    resultTextLabel2->hide();
                }
            }
        });

// Connect the "OBLICZ" button to a function that performs the calculations and updates the results text box.
connect(computeButton2, &QPushButton::clicked, this, &MainWindow::performIntervalCalculations);
intervalArithmeticLayout3 = new QHBoxLayout();

numNodesLabel3 = new QLabel("Wpisz liczbę węzłów");
numNodesEdit3 = new QLineEdit();
intervalArithmeticLayout3->addWidget(numNodesLabel3);
intervalArithmeticLayout3->addWidget(numNodesEdit3);

QHBoxLayout *intervalInputLayout3 = new QHBoxLayout();
QVBoxLayout *nodesLayout3 = new QVBoxLayout();
nodesLabel3 = new QLabel("Wpisz węzły interpolacji");
nodesTextEdit3 = new QTextEdit();
nodesLayout3->addWidget(nodesLabel3);
nodesLayout3->addWidget(nodesTextEdit3);

QVBoxLayout *multiplicityLayout3 = new QVBoxLayout();
nodeMultiplicityLabel3 = new QLabel("Wpisz krotności węzłów");
nodeMultiplicityTextEdit3 = new QTextEdit();
multiplicityLayout3->addWidget(nodeMultiplicityLabel3);
multiplicityLayout3->addWidget(nodeMultiplicityTextEdit3);

QVBoxLayout *valuesLayout3 = new QVBoxLayout();
valuesAndDerivativesLabel3 = new QLabel("Wpisz wartości oraz pochodne wezłów");
valuesAndDerivativesTextEdit3 = new QTextEdit();
valuesLayout3->addWidget(valuesAndDerivativesLabel3);
valuesLayout3->addWidget(valuesAndDerivativesTextEdit3);

intervalInputLayout3->addLayout(nodesLayout3);
intervalInputLayout3->addLayout(multiplicityLayout3);
intervalInputLayout3->addLayout(valuesLayout3);

QHBoxLayout *intervalResultLayout3 = new QHBoxLayout();

QVBoxLayout *left3 = new QVBoxLayout();
inputValueLabel3 = new QLabel("Wpisz argument, dla którego chcesz obliczyć wartość wielomianu");
inputValueEdit3 = new QLineEdit();
outputValueLabel3 = new QLabel("Wartość wielomianu dla podnaego argumentu");
outputValueEdit3 = new QLineEdit();
outputValueEdit3->setReadOnly(true);
    left3->addWidget(inputValueLabel3);
    left3->addWidget(inputValueEdit3);
    left3->addWidget(outputValueLabel3);
    left3->addWidget(outputValueEdit3);

QVBoxLayout *right3 = new QVBoxLayout();
QLabel *resultTextLabel3 = new QLabel("Współczynniki wielomianu");
resultTextEdit3 = new QTextEdit();
resultTextEdit3->setReadOnly(true);
    right3->addWidget(resultTextLabel3);
    right3->addWidget(resultTextEdit3);

intervalResultLayout3->addLayout(left3);
intervalResultLayout3->addLayout(right3);

computeButton3 = new QPushButton("OBLICZ");
mainLayout->addLayout(intervalArithmeticLayout3);
mainLayout->addLayout(intervalInputLayout3);
mainLayout->addLayout(intervalResultLayout3);
mainLayout->addWidget(computeButton3);

// Hide all the widgets initially
nodeMultiplicityLabel3->hide();
nodeMultiplicityTextEdit3->hide();
valuesAndDerivativesLabel3->hide();
valuesAndDerivativesTextEdit3->hide();
inputValueLabel3->hide();
inputValueEdit3->hide();
outputValueLabel3->hide();
outputValueEdit3->hide();
numNodesLabel3->hide();
numNodesEdit3->hide();
computeButton3->hide();
resultTextEdit3->hide();
resultTextLabel3->hide();
nodesLabel3->hide();
nodesTextEdit3->hide();


// Show or hide widgets based on selected radio button
connect(arithmeticGroup, &QButtonGroup::buttonToggled,
        [=](QAbstractButton *button, bool checked) {
            if (checked) {
                for (auto &otherButton : arithmeticGroup->buttons()) {
                    if (otherButton != button) {
                        otherButton->setChecked(false);
                    }
                }
                if (button == intervalArithmetic2) {
                    nodesLabel3->show();
                    nodesTextEdit3->show();
                    nodeMultiplicityLabel3->show();
                    nodeMultiplicityTextEdit3->show();
                    valuesAndDerivativesLabel3->show();
                    valuesAndDerivativesTextEdit3->show();
                    inputValueLabel3->show();
                    inputValueEdit3->show();
                    outputValueLabel3->show();
                    outputValueEdit3->show();
                    numNodesLabel3->show();
                    numNodesEdit3->show();
                    computeButton3->show();
                    resultTextEdit3->show();
                    resultTextLabel3->show();
                } else {
                    nodesLabel3->hide();
                    nodesTextEdit3->hide();
                    nodeMultiplicityLabel3->hide();
                    nodeMultiplicityTextEdit3->hide();
                    valuesAndDerivativesLabel3->hide();
                    valuesAndDerivativesTextEdit3->hide();
                    inputValueLabel3->hide();
                    inputValueEdit3->hide();
                    outputValueLabel3->hide();
                    outputValueEdit3->hide();
                    numNodesLabel3->hide();
                    numNodesEdit3->hide();
                    computeButton3->hide();
                    resultTextEdit3->hide();
                    resultTextLabel3->hide();
                }
            }
        });

// Connect the "OBLICZ" button to a function that performs the calculations and updates the results text box.
connect(computeButton3, &QPushButton::clicked, this, &MainWindow::performIntervalCalculations2);




}

void MainWindow::performCalculations() {
    bool conversionOk1;
    int numNodes = numNodesEdit->text().toInt(&conversionOk1);
    if (!conversionOk1) {
        resultTextEdit->setText("Wprowadzono nieprawidłowe dane");
        return;
    }

    QString nodesText = nodesTextEdit->toPlainText();
    QStringList nodesStringList = nodesText.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

    // Create a dynamic array to hold the numbers
    int size = nodesStringList.size();
    long double *nodes = new long double[size];

    // Convert each string to a long double and add it to the array
    for (int i = 0; i < size; ++i) {
        nodes[i] = nodesStringList[i].toDouble(&conversionOk1);
        if (!conversionOk1) {
            resultTextEdit->setText("Wprowadzono nieprawidłowe dane");
            return;
        }
    }

    QString multiplicityText = nodeMultiplicityTextEdit->toPlainText();
    QStringList multiplicityStringList = multiplicityText.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

    // Create a dynamic array to hold the numbers
    int multiplicitySize = multiplicityStringList.size();
    int *multiplicities = new int[multiplicitySize];

    // Convert each string to an int and add it to the array
    for (int i = 0; i < multiplicitySize; ++i) {
        multiplicities[i] = multiplicityStringList[i].toInt(&conversionOk1);
        if (!conversionOk1) {
            resultTextEdit->setText("Wprowadzono nieprawidłowe dane");
            return;
        }
    }

    QString valuesText = valuesAndDerivativesTextEdit->toPlainText();
    QStringList valuesStringList = valuesText.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

    // Create a dynamic array to hold the numbers
    int valuesSize = valuesStringList.size();
    long double *values = new long double[valuesSize];

    // Convert each string to a long double and add it to the array
    for (int i = 0; i < valuesSize; ++i) {
        values[i] = valuesStringList[i].toDouble(&conversionOk1);
        if (!conversionOk1) {
            resultTextEdit->setText("Wprowadzono nieprawidłowe dane");
            return;
        }
    }

    // Obliczanie sumy krotności
    int sumMultiplicity = 0;
    for (int i = 0; i < multiplicitySize; i++) {
        sumMultiplicity += multiplicities[i];
    }

    // Wywołanie funkcji oblicz_wspolczynniki_wielomianu
    oblicz_wspolczynniki_wielomianu(nodes, values, multiplicities, sumMultiplicity, numNodes);

    QString results;
    for (int i = 0; i < sumMultiplicity; ++i) {
        results += "f[" + QString::number(i) + "]=" + QString::number(values[i], 'e', 16) + "\n";
    }

    resultTextEdit->setText(results);



    // Pobierz wartość z inputValueEdit i skonwertuj na liczbę rzeczywistą
    QString inputValue = inputValueEdit->text();
    bool conversionOk2;
    long double inputValueNumber = inputValue.toDouble(&conversionOk2);

    if (conversionOk2 && conversionOk1) {
        // Wywołanie funkcji oblicz_wartosc_wielomianu
        long double wynik = oblicz_wartosc_wielomianu(values, sumMultiplicity - 1, inputValueNumber);

        // Zamień wynik na notację naukową
        QString scientificNotation = QString::number(wynik, 'e', 16);

        // Wyświetl wynik w okienku outputValueEdit
        outputValueEdit->setText(scientificNotation);
    } else {
        // Jeśli konwersja na liczbę nie powiodła się, wyświetl komunikat o błędzie
        outputValueEdit->setText("Wprowadzono nieprawidłowe dane");
    }


//    QString results;
//    for (int i = 0; i < sumMultiplicity; ++i) {
//        results += QString::number(values[i], 'e', 16) + "\n";  // Dodaj wartość w notacji naukowej i nową linię
//    }

    // Don't forget to free the memory when you're done with the arrays
    delete[] nodes;
    delete[] multiplicities;
    delete[] values;

    // Here, you will perform the necessary calculations and then update
    // the resultTextEdit field with the results. This is just a placeholder
    // and the actual implementation will depend on your application logic.
    //resultTextEdit->setText(results);

}

void MainWindow::performIntervalCalculations() {
    bool conversionOk1;
    int numNodes = numNodesEdit2->text().toInt(&conversionOk1);
    if (!conversionOk1) {
        resultTextEdit2->setText("Wprowadzono nieprawidłowe dane");
            return;
    }

    QString nodesText = nodesTextEdit2->toPlainText();
    QStringList nodesStringList = nodesText.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

    int size = nodesStringList.size();
    interval_arithmetic::Interval<long double> *nodes = new interval_arithmetic::Interval<long double>[size];

    for (int i = 0; i < size; ++i) {
        nodes[i] = interval_arithmetic::IntRead<long double>(nodesStringList[i].toStdString());
    }

    QString multiplicityText = nodeMultiplicityTextEdit2->toPlainText();
    QStringList multiplicityStringList = multiplicityText.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

    int multiplicitySize = multiplicityStringList.size();
    int *multiplicities = new int[multiplicitySize];

    for (int i = 0; i < multiplicitySize; ++i) {
        multiplicities[i] = multiplicityStringList[i].toInt(&conversionOk1);
        if (!conversionOk1) {
            resultTextEdit2->setText("Wprowadzono nieprawidłowe dane");
                return;
        }
    }

    QString valuesText = valuesAndDerivativesTextEdit2->toPlainText();
    QStringList valuesStringList = valuesText.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

    int valuesSize = valuesStringList.size();
    interval_arithmetic::Interval<long double> *values = new interval_arithmetic::Interval<long double>[valuesSize];

    for (int i = 0; i < valuesSize; ++i) {
        values[i] = interval_arithmetic::IntRead<long double>(valuesStringList[i].toStdString());
    }

    int sumMultiplicity = 0;
    for (int i = 0; i < multiplicitySize; i++) {
        sumMultiplicity += multiplicities[i];
    }

    oblicz_wspolczynniki_wielomianu2(nodes, values, multiplicities, sumMultiplicity, numNodes);

    QString results;
    for (int i = 0; i < sumMultiplicity; ++i) {
        string left, right;
        values[i].IEndsToStrings(left, right);
        QString qLeft = QString::fromStdString(left);
        QString qRight = QString::fromStdString(right);
        results += "f[" + QString::number(i) + "]=[" + qLeft + ", " + qRight + "]\n";
    }

    resultTextEdit2->setText(results);

    QString inputValue = inputValueEdit2->text();
    bool conversionOk2;
    interval_arithmetic::Interval<long double> inputValueNumber = interval_arithmetic::IntRead<long double>(inputValue.toStdString());

    if (conversionOk1) {
        interval_arithmetic::Interval<long double> wynik = oblicz_wartosc_wielomianu2(values, sumMultiplicity - 1, inputValueNumber);
        string left, right;
        wynik.IEndsToStrings(left, right);
        QString qLeft = QString::fromStdString(left);
        QString qRight = QString::fromStdString(right);
        outputValueEdit2->setText("[" + qLeft + ", " + qRight + "]");
    } else {
        outputValueEdit2->setText("Wprowadzono nieprawidłowe dane");
    }

    delete[] nodes;
    delete[] multiplicities;
    delete[] values;
}

void MainWindow::performIntervalCalculations2() {
    bool conversionOk1;
    int numNodes = numNodesEdit3->text().toInt(&conversionOk1);
    if (!conversionOk1) {
        resultTextEdit3->setText("Wprowadzono nieprawidłowe dane");
            return;
    }

    QString nodesText = nodesTextEdit3->toPlainText();
    QStringList nodesStringList = nodesText.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

    int size = nodesStringList.size();
    interval_arithmetic::Interval<long double> *nodes = new interval_arithmetic::Interval<long double>[size];

    for (int i = 0; i < size; ++i) {
            QStringList intervalBounds = nodesStringList[i].split(',');
            if (intervalBounds.size() != 2) {
                resultTextEdit3->setText("Wprowadzono nieprawidłowe dane");
                    return;
            }
            nodes[i].a = interval_arithmetic::LeftRead<long double>(intervalBounds[0].toStdString());
            nodes[i].b = interval_arithmetic::RightRead<long double>(intervalBounds[1].toStdString());
    }

    QString multiplicityText = nodeMultiplicityTextEdit3->toPlainText();
    QStringList multiplicityStringList = multiplicityText.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

    int multiplicitySize = multiplicityStringList.size();
    int *multiplicities = new int[multiplicitySize];

    for (int i = 0; i < multiplicitySize; ++i) {
        multiplicities[i] = multiplicityStringList[i].toInt(&conversionOk1);
        if (!conversionOk1) {
                resultTextEdit3->setText("Wprowadzono nieprawidłowe dane");
                    return;
        }
    }

    QString valuesText = valuesAndDerivativesTextEdit3->toPlainText();
    QStringList valuesStringList = valuesText.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

    int valuesSize = valuesStringList.size();
    interval_arithmetic::Interval<long double> *values = new interval_arithmetic::Interval<long double>[valuesSize];

    for (int i = 0; i < valuesSize; ++i) {
        QStringList intervalBounds = valuesStringList[i].split(',');
        if (intervalBounds.size() != 2) {
                    resultTextEdit3->setText("Wprowadzono nieprawidłowe dane");
                        return;
        }
        values[i].a = interval_arithmetic::LeftRead<long double>(intervalBounds[0].toStdString());
        values[i].b = interval_arithmetic::RightRead<long double>(intervalBounds[1].toStdString());
    }

    int sumMultiplicity = 0;
    for (int i = 0; i < multiplicitySize; i++) {
        sumMultiplicity += multiplicities[i];
    }

    oblicz_wspolczynniki_wielomianu2(nodes, values, multiplicities, sumMultiplicity, numNodes);

    QString results;
    for (int i = 0; i < sumMultiplicity; ++i) {
        string left, right;
        values[i].IEndsToStrings(left, right);
        QString qLeft = QString::fromStdString(left);
        QString qRight = QString::fromStdString(right);
        results += "f[" + QString::number(i) + "]=[" + qLeft + ", " + qRight + "]\n";
    }

    resultTextEdit3->setText(results);

    QString inputValue = inputValueEdit3->text();
    QStringList inputIntervalBounds = inputValue.split(',');

    if (inputIntervalBounds.size() != 2) {
        outputValueEdit3->setText("Wprowadzono nieprawidłowe dane");
            return;
    }

    interval_arithmetic::Interval<long double> inputValueNumber;
    inputValueNumber.a = interval_arithmetic::LeftRead<long double>(inputIntervalBounds[0].toStdString());
    inputValueNumber.b = interval_arithmetic::RightRead<long double>(inputIntervalBounds[1].toStdString());

    interval_arithmetic::Interval<long double> wynik = oblicz_wartosc_wielomianu2(values, sumMultiplicity - 1, inputValueNumber);
    string left, right;
    wynik.IEndsToStrings(left, right);
    QString qLeft = QString::fromStdString(left);
    QString qRight = QString::fromStdString(right);
    outputValueEdit3->setText("[" + qLeft + ", " + qRight + "]");

    delete[] nodes;
    delete[] multiplicities;
    delete[] values;
}

