#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include "DataBean.h"
#include "SystemInterface.h"
using namespace std;



// Singleton
SystemInterface & SystemInterface::getInstance() {
        static SystemInterface instance;
        return instance;
    }

vector<DataBean> & SystemInterface::getDataBeans() {
        return this->dataBeans;
    }

void SystemInterface::addDataBean(DataBean dataBean) {
        this->dataBeans.push_back(dataBean);

        // Save To Disk.
        this->saveDataBeansToDisk();
    }

void SystemInterface::deleteDataBean(DataBean dataBean) {
        for (vector<DataBean>::iterator iter = this->dataBeans.begin(); iter != this->dataBeans.end(); iter++) {
            if (iter->id == dataBean.id) {
                this->dataBeans.erase(iter);
                return;
            }
         }

        // Save To Disk.
        this->saveDataBeansToDisk();
    }

void SystemInterface::modifyDataBean(DataBean dataBean) {
        // Find DataBean By ID.
        vector<DataBean>::iterator iter = searchDataBean(dataBean);
        printf("员工的旧数据: %s\n", iter->getFormatedInfo().c_str());

        // Modify Values.
        iter->baseSalary = dataBean.baseSalary;
        iter->allowance = dataBean.allowance;
        iter->socialInsurance = dataBean.socialInsurance;
        iter->medicalInsurance = dataBean.medicalInsurance;
        iter->accumulationFund = dataBean.accumulationFund;
        printf("修改完成, 新数据: %s\n", iter->getFormatedInfo().c_str());

        // Save To Disk.
        this->saveDataBeansToDisk();
    }


    vector<DataBean>::iterator SystemInterface::searchDataBean(DataBean dataBean) {
        vector<DataBean>::iterator iter = find(dataBeans.begin(), dataBeans.end(), dataBean);
        return iter;
    }


    bool SystemInterface::existDataBean(DataBean dataBean) {
        return SystemInterface::getInstance().searchDataBean(dataBean) != SystemInterface::getInstance().getDataBeans().end();
    }


    void SystemInterface::saveDataBeansToDisk() {

        FILE * file = fopen("DataBeans.dat", "w+");

        if(file == NULL) {
            printf("Cannot Open This File\n");
            return;
        }

        for(DataBean dataBean : dataBeans) {
            fprintf(file, "%d %s %lf %lf %lf %lf %lf\n", dataBean.id,  dataBean.name.c_str(),dataBean.baseSalary, dataBean.allowance, dataBean.socialInsurance, dataBean.medicalInsurance, dataBean.accumulationFund);
        }

        fclose(file);
    }


    void SystemInterface::loadDataBeansFromDisk(bool clearDetaBeansInMemory, string fileName) {

        // Clear DataBeans in Memory.
        if (clearDetaBeansInMemory) this->dataBeans.clear();


        // Read DataBeans from Disk.
        FILE * file = fopen(fileName.c_str(), "r");

        if(file == NULL) {
            printf("Cannot Open This File\n");
            return;
        }

        // Dim DataBean Attributes.
        int id;
        char name_buf[BUFFER_SIZE];
        double baseSalary;
        double allowance;
        double socialInsurance;
        double medicalInsurance;
        double accumulationFund;

        while (fscanf(file, "%d %s %lf %lf %lf %lf %lf\n", &id, &name_buf, &baseSalary, &allowance, &socialInsurance, &medicalInsurance, &accumulationFund) != EOF) {
            this->dataBeans.push_back(DataBean(id, string(name_buf),baseSalary, allowance, socialInsurance, medicalInsurance, accumulationFund));
        }

        fclose(file);
    }

     void SystemInterface::loadDataBeansFromDisk() {
         SystemInterface::loadDataBeansFromDisk(true, "DataBeans.dat");
     }
