#include <string>
#include "MenuHelper.h"
#include "DataBean.h"
#define BUFFER_SIZE 1024
#pragma warning(disable:4996)


using namespace std;


    bool DataBean::operator== (const DataBean& dataBean) {
        if (this->id == dataBean.id) return true;
        return !this->name.compare(dataBean.name);
    }

    double DataBean::getGrossSalary() {
        return baseSalary + allowance;
    }

    double DataBean::getDiscount() {
        return socialInsurance + medicalInsurance + accumulationFund;
    }


    double DataBean::getSalary() {
        return getGrossSalary() - getDiscount();
    }


    string DataBean::getFormatedInfo() {
        char buf[BUFFER_SIZE];
        sprintf(buf, "Ա����: %d [����: %s] [ʵ������ %.2f] [Ӧ������ %.2f] [�ϼƿۿ� %.2f] [�������� %.2f] [���� %.2f] [�籣 %.2f] [ҽ�� %.2f] [������ %.2f]", this->id, this->name.c_str(),this->getSalary(), this->getGrossSalary(), this->getDiscount(), this->baseSalary, this->allowance, this->socialInsurance, this->medicalInsurance, this->accumulationFund);
        return string(buf);
    }

  void DataBean::printDataBean() {
        printf("%s\n", this->getFormatedInfo().c_str());
    }


    DataBean DataBean::readDataBean() {
        return DataBean::readDataBeanFromID(NULL);
    }

    DataBean DataBean::readDataBeanFromID(int id) {
        if (id == NULL) {
            printf("�������ʦ��: ");
            id = MenuHelper::readIntergerCommand();
        }

        printf("����������: ");
        string name = MenuHelper::readStringCommand();
        printf("�������������: ");
        double baseSalary = MenuHelper::readDoubleCommand();
        printf("���������: ");
        double allowance = MenuHelper::readDoubleCommand();
        printf("�������籣: ");
        double socialInsurance = MenuHelper::readDoubleCommand();
        printf("������ҽ��: ");
        double medicalInsurance = MenuHelper::readDoubleCommand();
        printf("�����빫����: ");
        double accumulationFund = MenuHelper::readDoubleCommand();
        DataBean dataBean(id, name, baseSalary, allowance, socialInsurance, medicalInsurance, accumulationFund);
        return dataBean;
    }

    void DataBean::calcAndSaveToDisk() {

        // Data Flow.
        int id;
        double realSalary = this->getGrossSalary() - this->getDiscount();
        double grossSalary = this->getGrossSalary();
        double discount = this->getDiscount();

        // Save to Disk.
        FILE * file = fopen("CalcResults.dat", "w+");
        if(file == NULL) {
            printf("Cannot Open This File\n");
            return;
        }

        fprintf(file, "%d %lf %lf %lf", id, realSalary, grossSalary, discount);
        fclose(file);
    }

