#pragma once
#include <string>
#include "MenuHelper.h"
#define BUFFER_SIZE 1024
using namespace std;
class DataBean {
public:

  int id;

  // 应发工资 = 基本工资 + 津贴
  string name;
  double baseSalary;
  double allowance;

  // 合计扣款 = 社保 + 医保 + 公积金
  double socialInsurance;
  double medicalInsurance;
  double accumulationFund;

  // Equals for SearchOperation.

public:

  bool operator==(const DataBean& dataBean);

  // Assignment Constructor for ModifyOperation.

public:

  DataBean& operator=(const DataBean& dataBean);

  // Operator < for Sort.

public:

  bool operator<(const DataBean& dataBean);

public:

  DataBean(int id) : id(id) {}

public:

  DataBean(string name) : name(name) {}

public:

  DataBean(int    id,
           string name,
           double baseSalary,
           double allowance,
           double socialInsurance,
           double medicalInsurance,
           double accumulationFund) : id(id), name(name), baseSalary(baseSalary),
    allowance(allowance), socialInsurance(socialInsurance),
    medicalInsurance(medicalInsurance), accumulationFund(accumulationFund) {}

public:

  double getGrossSalary();

public:

  double getDiscount();

public:

  double getSalary();

public:

  string getFormatedInfo();

public:

  void printDataBean();

public:

  static DataBean readDataBean();

public:

  static DataBean readDataBeanFromID(int id);

public:

  void calcAndSaveToDisk();
};
