#include <list>
#include <iterator>
#include "DataBean.h"
#include "SystemInterface.h"
using namespace std;

// Singleton
SystemInterface& SystemInterface::getInstance() {
  static SystemInterface instance;

  return instance;
}

list<DataBean>& SystemInterface::getDataBeans() {
  return this->dataBeans;
}

void SystemInterface::addDataBean(DataBean& dataBean) {
  this->dataBeans.push_back(dataBean);

  // Save To Disk.
  this->saveDataBeansToDisk();
}

void SystemInterface::deleteDataBean(DataBean& dataBean) {
  for (list<DataBean>::iterator iter = this->dataBeans.begin();
       iter != this->dataBeans.end(); iter++) {
    // Use Operator ==
    if (*iter == dataBean) {
      this->dataBeans.erase(iter);
      return;
    }
  }

  // Save To Disk.
  this->saveDataBeansToDisk();
}

void SystemInterface::modifyDataBean(DataBean& dataBean) {
  // Find DataBean By PrimaryKey.
  list<DataBean>::iterator iter = searchDataBean(dataBean);

  // Modify DataBean (Using Assignment Constructor).
  *iter = dataBean;

  // Save To Disk.
  this->saveDataBeansToDisk();
}

list<DataBean>::iterator SystemInterface::searchDataBean(DataBean& dataBean) {
  list<DataBean>::iterator iter = find(dataBeans.begin(),
                                       dataBeans.end(),
                                       dataBean);

  return iter;
}

bool SystemInterface::existDataBean(DataBean& dataBean) {
  return SystemInterface::getInstance().searchDataBean(dataBean) !=
         SystemInterface::getInstance().getDataBeans().end();
}

bool SystemInterface::saveDataBeansToDisk() {
  FILE *file = fopen(SystemInterface::DATABEANS_FILE_NAME.c_str(), "w+");

  if (file == NULL) {
    printf("Cannot Open This File\n");
    return false;
  }

  /* Write DataBean Attributes. */
  for (DataBean dataBean : dataBeans) {
    fprintf(file,
            "%d %s %lf %lf %lf %lf %lf\n",
            dataBean.id,
            dataBean.name.c_str(),
            dataBean.baseSalary,
            dataBean.allowance,
            dataBean.socialInsurance,
            dataBean.medicalInsurance,
            dataBean.accumulationFund);
  }

  fclose(file);
  return true;
}

bool SystemInterface::loadDataBeansFromDisk(bool   clearDetaBeansInMemory,
                                            string fileName) {
  // Clear DataBeans in Memory.
  if (clearDetaBeansInMemory) this->dataBeans.clear();

  // Read DataBeans from Disk.
  FILE *file = fopen(fileName.c_str(), "r");

  if (file == NULL) {
    printf("Cannot Open This File\n");
    return false;
  }

  /* Read DataBean Attributes. */
  int    id;
  char   name_buf[BUFFER_SIZE];
  double baseSalary;
  double allowance;
  double socialInsurance;
  double medicalInsurance;
  double accumulationFund;

  while (fscanf(file, "%d %s %lf %lf %lf %lf %lf\n", &id, &name_buf, &baseSalary,
                &allowance, &socialInsurance, &medicalInsurance,
                &accumulationFund) != EOF) {
    this->dataBeans.push_back(DataBean(id, string(name_buf), baseSalary,
                                       allowance, socialInsurance,
                                       medicalInsurance, accumulationFund));
  }

  fclose(file);
  return true;
}

bool SystemInterface::loadDataBeansFromDisk() {
  return SystemInterface::loadDataBeansFromDisk(true,
                                                SystemInterface::DATABEANS_FILE_NAME.c_str());
}

string& SystemInterface::filter(string& raw) {
  for (char& ch : raw) {
    if ((ch == ' ') || (ch == '\n') || (ch == '\t')) ch = '_';
  }
  return raw;
}

template<typename _Predicate>
list<list<DataBean>::iterator>SystemInterface::searchDataBeans(
  _Predicate predicator) {
  // Do Search.
  list<DataBean>::iterator curIter =
    SystemInterface::getInstance().getDataBeans().begin();
  list<DataBean>::iterator endIter =
    SystemInterface::getInstance().getDataBeans().end();
  list<list<DataBean>::iterator> searchedDataBeans;

  while (true) {
    curIter = find_if(curIter,
                      endIter, predicator);

    if (curIter != endIter) {
      searchedDataBeans.push_back(curIter);
    }

    if ((curIter == endIter) || (++curIter == endIter)) break;
  }

  return searchedDataBeans;
}
