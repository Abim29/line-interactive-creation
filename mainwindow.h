#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define pdd pair<int, int>
#include <QMainWindow>
#include <QPainter>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void Mouse_Pressed();

    void on_resetButton_clicked();

    void on_singleButton_clicked();

    void on_multiButton_clicked();

private:
    Ui::MainWindow *ui;
    bool isSingleLine = true;
    std::pdd lineIntersection(std::pdd A, std::pdd B, std::pdd C, std::pdd D)
    {
        // Line AB represented as a1x + b1y = c1
        double a1 = B.second - A.second;
        double b1 = A.first - B.first;
        double c1 = a1*(A.first) + b1*(A.second);

        // Line CD represented as a2x + b2y = c2
        double a2 = D.second - C.second;
        double b2 = C.first - D.first;
        double c2 = a2*(C.first)+ b2*(C.second);

        double determinant = a1*b2 - a2*b1;

        if (determinant == 0)
        {
            // The lines are parallel. This is simplified
            // by returning a pair of FLT_MAX
            return std::make_pair(INT_MAX, INT_MAX);
        }
        else
        {
            double x = (b2*c1 - b1*c2)/determinant;
            double y = (a1*c2 - a2*c1)/determinant;
            return std::make_pair(x, y);
        }
    }

    int fact(int n) {
       if (n == 0 || n == 1)
       return 1;
       else
       return n * fact(n - 1);
    }
};
#endif // MAINWINDOW_H
