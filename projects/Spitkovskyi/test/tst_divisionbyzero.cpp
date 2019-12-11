#include <QtTest>

// add necessary includes here
#include "../calculator/calculator.h"
class divisionbyzero : public QObject
{
    Q_OBJECT

public:
    divisionbyzero();
    ~divisionbyzero();

private slots:
    void test_case1();

};

divisionbyzero::divisionbyzero()
{
    Calculator calc;
    QTest::keyClick(calc, calc.digitButtons[6]);
    QTest::keyClick(calc, calc.digitButtons[0]);
    QTest::keyClick(calc, calc.equalButton);
    QCOMPARE(calc.display->text(), "####");
}

divisionbyzero::~divisionbyzero()
{

}

void divisionbyzero::test_case1()
{

}

QTEST_APPLESS_MAIN(divisionbyzero)

#include "tst_divisionbyzero.moc"
