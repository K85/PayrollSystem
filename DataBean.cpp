#include "DataBean.h"

#include <string>

#include "MenuHelper.h"
#include "SystemInterface.h"
#define BUFFER_SIZE 1024
#pragma warning(disable : 4996)

using namespace std;

bool DataBean::operator==(const DataBean& dataBean) {
  return this->id == dataBean.id;
}

DataBean& DataBean::operator=(const DataBean& dataBean) {
  this->id = dataBean.id;
  this->name = dataBean.name;
  this->baseSalary = dataBean.baseSalary;
  this->allowance = dataBean.allowance;
  this->socialInsurance = dataBean.socialInsurance;
  this->medicalInsurance = dataBean.medicalInsurance;
  this->accumulationFund = dataBean.accumulationFund;
  return *this;
}

bool DataBean::operator<(const DataBean& dataBean) {
  return this->id < dataBean.id;
}

double DataBean::getGrossSalary() { return baseSalary + allowance; }

double DataBean::getDiscount() {
  return socialInsurance + medicalInsurance + accumulationFund;
}

double DataBean::getSalary() { return getGrossSalary() - getDiscount(); }

string DataBean::getFormatedInfo() {
  char buf[BUFFER_SIZE];

  sprintf(
      buf,
      "Ա����: %d [����: %s] [ʵ������ %.2f] [Ӧ������ %.2f] [�ϼƿۿ� %.2f] "
      "[�������� %.2f] [���� %.2f] [�籣 %.2f] [ҽ�� %.2f] [������ %.2f]",
      this->id, this->name.c_str(), this->getSalary(), this->getGrossSalary(),
      this->getDiscount(), this->baseSalary, this->allowance,
      this->socialInsurance, this->medicalInsurance, this->accumulationFund);
  return string(buf);
}

void DataBean::printDataBean() {
  printf("%s\n", this->getFormatedInfo().c_str());
}

DataBean DataBean::readDataBean() { return DataBean::readDataBeanFromID(NULL); }

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
  DataBean dataBean(id, name, baseSalary, allowance, socialInsurance,
                    medicalInsurance, accumulationFund);

  return dataBean;
}

void DataBean::calcAndSaveToDisk() {
  // Data Flow.
  int id;
  double realSalary = this->getGrossSalary() - this->getDiscount();
  double grossSalary = this->getGrossSalary();
  double discount = this->getDiscount();

  // Save to Disk.
  FILE* file = fopen("CalcResults.dat", "w+");

  if (file == NULL) {
    printf("Cannot Open This File\n");
    return;
  }

  fprintf(file, "%d %lf %lf %lf", id, realSalary, grossSalary, discount);
  fclose(file);
}

void DataBean::outputToFile(FILE* file) {
  fprintf(file, "%d %s %lf %lf %lf %lf %lf\n", this->id, this->name.c_str(),
          this->baseSalary, this->allowance, this->socialInsurance,
          this->medicalInsurance, this->accumulationFund);
}

void DataBean::inputFromFile(FILE* file) {
  int id;
  char name_buf[BUFFER_SIZE];
  double baseSalary;
  double allowance;
  double socialInsurance;
  double medicalInsurance;
  double accumulationFund;

  while (fscanf(file, "%d %s %lf %lf %lf %lf %lf\n", &id, &name_buf,
                &baseSalary, &allowance, &socialInsurance, &medicalInsurance,
                &accumulationFund) != EOF) {
    SystemInterface::getInstance().getDataBeans().push_back(
        DataBean(id, string(name_buf), baseSalary, allowance, socialInsurance,
                 medicalInsurance, accumulationFund));
  }
}
