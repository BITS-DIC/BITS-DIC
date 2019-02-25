#include "setroi.h"
#include "opencv2/highgui.hpp"
#include "ui_setroi.h"
#include "utils.h"
#include <QDebug>
#include <QDir>
#include <QFileDialog>

SetROI::SetROI(QWidget *parent, Dic *dic) : QDialog(parent),
                                  ui(new Ui::SetROI) {
    ui->setupUi(this);

    this->dic = dic;
    class_logical_array mask = dic->roi.mask;
    if(mask.height == 0 || mask.width == 0) {
        //image not set earlier
    } else {
        //for(int i = 0; i < mask.height; i++) {
         //   for(int j = 0; j < mask.width; j++) {

         //   }
        //}
    }
}

SetROI::~SetROI() {
    delete ui;
}

void SetROI::on_setRoiLoadFromFile_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Select Reference Image File"),
                                                    QDir::homePath(),
                                                    "Images (*.png *.jpg *.jpeg *.tif *.tiff);;All Files (*)",
                                                    nullptr,
                                                    QFileDialog::DontUseNativeDialog);
    if (fileName.length() == 0) {
        qDebug() << "No File Selected";
        return;
    }
    //TODO check for data consistency if images are larger/smaller than roi we can have issue

    //Display ROI data
    cv::Mat roiImageMat = cv::imread(fileName.toStdString(), cv::IMREAD_GRAYSCALE);

    Utils::loadImage(Utils::matToQImage(roiImageMat), ui->setRoiImageDisplay);

    rows = roiImageMat.rows;
    cols = roiImageMat.cols;

    roi.mask.alloc(rows, cols);
    roi.mask.reset();

    //create roi mask
    visited.alloc(rows, cols);
    visited.reset();

    region_mask.alloc(rows, cols);
    region_mask.reset();

    num_region = 0;

    for (int r = 0; r < rows; r++) {
        const uchar *Mi = roiImageMat.ptr<uchar>(r);
        for (int c = 0; c < cols; c++) {
            if (Mi[c] != 0) {
                roi.mask.value[r + c * rows] = 1;
            } else {
                roi.mask.value[r + c * rows] = 0;
                visited.value[r + c * rows] = true;
                region_mask.value[r + c * rows] = num_region;
            }
        }
    }
    roiImageMat.release();

    //all negative space at region - 0
    //increment region for upcoming regions
    num_region++;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (roi.mask.value[r + c * rows] == 1 && !visited.value[r + c * rows]) {
                //found top left not visited pixel of a region not visited yet
                //begin bfs of region
                bfs(r, c);

                //reset .. target next region
                num_region++;
            }
        }
    }

    num_region--;

    //painting region mask

    //all regions painted
    //extract nodelist and ranges
    //total regions = num_region
    std::vector<std::vector<int>> nodelist;
    std::vector<std::vector<int>> noderange;
    for (int i = 1; i <= num_region; i++) {
        roi.region.push_back(class_region());
        nodelist.push_back(std::vector<int>());
        noderange.push_back(std::vector<int>());
    }
    //find ranges first for all regions
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (region_mask.value[r + c * rows] != 0) {
                int reg = region_mask.value[r + c * rows];
                roi.region[reg - 1].leftbound = std::min(c, roi.region[reg - 1].leftbound);
                roi.region[reg - 1].upperbound = std::min(r, roi.region[reg - 1].upperbound);
                roi.region[reg - 1].lowerbound = std::max(r, roi.region[reg - 1].lowerbound);
                roi.region[reg - 1].rightbound = std::max(c, roi.region[reg - 1].rightbound);
                roi.region[reg - 1].totalpoints++;
            }
        }
    }

    for (int reg = 1; reg <= num_region; reg++) {
        class_region *region = &roi.region[reg - 1];
        int h = region->rightbound - region->leftbound + 1;
        region->noderange.alloc(h, 1);
        std::vector<std::vector<int>> nodelist;
        int max = 0;
        for (int c = region->leftbound; c <= region->rightbound; c++) {
            std::vector<int> list;
            bool reg_start = false;
            for (int r = region->upperbound; r <= region->lowerbound; r++) {
                if (region_mask.value[r + c * rows] == reg) {
                    if (!reg_start) {
                        reg_start = true;
                        list.push_back(r);
                    }
                    if (r == region->lowerbound) {
                        list.push_back(r);
                        reg_start = false; //not needed
                    }
                } else {
                    if (reg_start)
                        list.push_back(r - 1);
                    reg_start = false;
                }
            }
            nodelist.push_back(list);
            max = std::max(max, static_cast<int>(list.size()));
        }
        region->nodelist.alloc(h, max);
        region->nodelist.reset();
        for (int i = 0; i < nodelist.size(); i++) {
            for (int j = 0; j < nodelist[i].size(); j++)
                region->nodelist.value[i + j * nodelist.size()] = nodelist[i][j];
            for (int j = nodelist[i].size(); j < max; j++)
                region->nodelist.value[i + j * nodelist.size()] = 0;
            region->noderange.value[i] = nodelist[i].size();
        }
    }

    std::ofstream of("./roidata.txt");
    of << "Total regions " << roi.region.size();
    of << "Outputting roi.mask array\n";
    for (int i = 0; i < rows * cols; i++)
        of << roi.mask.value[i] << " ";
    of << "\nOutputting roi.region[0].nodelist\n";
    for (int i = 0; i < roi.region[0].nodelist.height * roi.region[0].nodelist.width; i++)
        of << roi.region[0].nodelist.value[i] << " ";
    of << "\nOutputting roi.region[0].noderange\n";
    for (int i = 0; i < roi.region[0].noderange.height * roi.region[0].noderange.width; i++)
        of << roi.region[0].noderange.value[i] << " ";
    of << "\nroi.region[0].totalpoints = " << roi.region[0].totalpoints;
    of << "\nroi.region[0].lowerbound = " << roi.region[0].lowerbound;
    of << "\nroi.region[0].upperbound = " << roi.region[0].upperbound;
    of << "\nroi.region[0].leftbound = " << roi.region[0].leftbound;
    of << "\nroi.region[0].rightbound = " << roi.region[0].rightbound;
    of.close();
}

void SetROI::bfs(int row, int col) {
    std::pair<int, int> seed(row, col);
    std::queue<std::pair<int, int>> q;
    q.push(seed);
    while (!q.empty()) {
        std::pair<int, int> point = q.front();
        q.pop();
        int r = point.first;
        int c = point.second;
        if (c < 0 || r < 0 || r >= rows || c >= cols || visited.value[r + c * rows] || !roi.mask.value[r + c * rows]) {
            //do nothing
        } else {
            visited.value[r + c * rows] = true;
            region_mask.value[r + c * rows] = num_region;
            //add adjoining 8 points

            q.push(std::pair<int, int>(r - 1, c - 1)); //top left
            q.push(std::pair<int, int>(r - 1, c));     //top
            q.push(std::pair<int, int>(r - 1, c + 1)); //top right
            q.push(std::pair<int, int>(r, c - 1));     //left
            q.push(std::pair<int, int>(r, c + 1));     //right
            q.push(std::pair<int, int>(r + 1, c - 1)); //bottom left
            q.push(std::pair<int, int>(r + 1, c));     //bottom
            q.push(std::pair<int, int>(r + 1, c + 1)); //bottom right
        }
    }
}

void SetROI::on_setRoiButtonBox_accepted() {
    //Send ROI data
    //No checking is done here for validity of data as ref and curr images may not have been set up
    qDebug() << "Sending roi mat data";
    emit onRoiSet(roi);
}
