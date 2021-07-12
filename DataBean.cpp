#include <string>
#include "MenuHelper.h"
#include "DataBean.h"
#define BUFFER_SIZE 1024
#pragma warning(disable:4996)


using namespace std;


bool DataBean::operator==(const DataBean& dataBean) {
  return this->id == dataBean.id;
}

DataBean& DataBean::operator=(const DataBean& dataBean) {
  this->id               = dataBean.id;
  this->name             = dataBean.name;
  this->baseSalary       = dataBean.baseSalary;
  this->allowance        = dataBean.allowance;
  this->socialInsurance  = dataBean.socialInsurance;
  this->medicalInsurance = dataBean.medicalInsurance;
  this->accumulationFund = dataBean.accumulationFund;
  return *this;
}

bool DataBean::operator<(const DataBean& dataBean) {
  return this->id < dataBean.id;
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

  sprintf(buf,
          "员工号: %d [名称: %s] [实发工资 %.2f] [应发工资 %.2f] [合计扣款 %.2f] [基本工资 %.2f] [津贴 %.2f] [社保 %.2f] [医保 %.2f] [公积金 %.2f]",
          this->id,
          this->name.c_str(),
          this->getSalary(),
          this->getGrossSalary(),
          this->getDiscount(),
          this->baseSalary,
          this->allowance,
          this->socialInsurance,
          this->medicalInsurance,
          this->accumulationFund);
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
    printf("请输入教师号: ");
    id = MenuHelper::readIntergerCommand();
  }

  printf("请输入名称: ");
  string name = MenuHelper::readStringCommand();

  printf("请输入基本工资: ");
  double baseSalary = MenuHelper::readDoubleCommand();

  printf("请输入津贴: ");
  double allowance = MenuHelper::readDoubleCommand();

  printf("请输入社保: ");
  double socialInsurance = MenuHelper::readDoubleCommand();

  printf("请输入医保: ");
  double medicalInsurance = MenuHelper::readDoubleCommand();

  printf("请输入公积金: ");
  double   accumulationFund = MenuHelper::readDoubleCommand();
  DataBean dataBean(id, name, baseSalary, allowance, socialInsurance,
                    medicalInsurance, accumulationFund);

  return dataBean;
}

void DataBean::calcAndSaveToDisk() {
  // Data Flow.
  int id;
  double realSalary  = this->getGrossSalary() - this->getDiscount();
  double grossSalary = this->getGrossSalary();
  double discount    = this->getDiscount();

  // Save to Disk.
  FILE *file = fopen("CalcResults.dat", "w+");

  if (file == NULL) {
    printf("Cannot Open This File\n");
    return;
  }

  fprintf(file, "%d %lf %lf %lf", id, realSalary, grossSalary, discount);
  fclose(file);
}
