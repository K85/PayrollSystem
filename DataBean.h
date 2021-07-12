#pragma once
#include <string>

#include "MenuHelper.h"
#define BUFFER_SIZE 1024
using namespace std;
class DataBean {
 public:
  int id;
  string name;
  double baseSalary;
  double allowance;
  double socialInsurance;
  double medicalInsurance;
  double accumulationFund;

  // Equals for SearchOperation.
  bool operator==(const DataBean &dataBean);

  // Assignment Constructor for ModifyOperation.

  DataBean &operator=(const DataBean &dataBean);

  // Operator < for Sort.
  bool operator<(const DataBean &dataBean);

  DataBean(int id) : id(id) {}

  DataBean(string name) : name(name) {}

  DataBean(int id, string name, double baseSalary, double allowance,
           double socialInsurance, double medicalInsurance,
           double accumulationFund)
      : id(id),
        name(name),
        baseSalary(baseSalary),
        allowance(allowance),
        socialInsurance(socialInsurance),
        medicalInsurance(medicalInsurance),
        accumulationFund(accumulationFund) {}

  double getGrossSalary();

  double getDiscount();

  double getSalary();

  string getFormatedInfo();

  void printDataBean();

  static DataBean readDataBean();

  static DataBean readDataBeanFromID(int id);

  void calcAndSaveToDisk();

  void outputToFile(FILE *file);

  static void inputFromFile(FILE *file);
};
