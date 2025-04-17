#include "leddemowindow.h"
#include "ui_leddemowindow.h"
#include "led_app_adapter.h"

QPixmap create_pixmap(const char* addr){
    return QPixmap(addr).scaled(200, 200);
}

LEDDemoWindow::LEDDemoWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LEDDemoWindow)
{
    ui->setupUi(this);

    handle = std::make_unique<LEDHandle>("charlies_led");
    handle->open();

    if(!handle->available()){
        ui->pushButton->setText("Led is not available!");
        ui->pushButton->setEnabled(false);
    }else{
        LEDHandle::status st = handle->get_status();
        set_ui_status(st);
    }
}

void LEDDemoWindow::set_ui_status(const LEDHandle::status st)
{
    if(st == LEDHandle::status::LED_ON){
        ui->status_btn->setText("Current_status: ON");
        ui->label->setPixmap(create_pixmap(":/image/images/open.png"));
    }else{
        ui->status_btn->setText("Current_status: OFF");
        ui->label->setPixmap(create_pixmap(":/image/images/closed.png"));
    }
}



LEDDemoWindow::~LEDDemoWindow()
{
    delete ui;
}

void LEDDemoWindow::on_pushButton_clicked()
{
    LEDHandle::status st = handle->get_status();
    if(st == LEDHandle::status::LED_ON){
        qDebug() << "At here as ready off";
        st = LEDHandle::status::LED_OFF;
    }else{
        qDebug() << "At here as ready on";
        st = LEDHandle::status::LED_ON;
    }
    handle->set_status(st);
    qDebug() << (int)handle->get_status();
    set_ui_status(handle->get_status());
}

