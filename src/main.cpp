#include "material_segmentation/base_segmentation.h"
#include "material_segmentation/super_clustering_segmentation.h"

std::unique_ptr<BaseSegmentation> segmentation_type = NULL;

bool set_segmentation_method(std::string segmentation_method) {
  if (segmentation_method.compare("base") == 0) {
    ROS_INFO("Using base class segmentation");
    segmentation_type.reset(new BaseSegmentation());
  } else if (segmentation_method.compare("superclustering") == 0) {
    ROS_INFO("Using supervoxel clustering segmentation");
    segmentation_type.reset(new SuperClusteringSegmentation());
  } else {
    ROS_ERROR("Segmentation algorithm %s is not implemented.",
              segmentation_method.c_str());
    return false;
  }
  return true;
}

bool change_segmentation_method(
    material_segmentation::ChangeSegmentationMethod::Request &req,
    material_segmentation::ChangeSegmentationMethod::Response &res) {
  bool success = set_segmentation_method(req.segmentation_method);

  res.success = success;
  return success;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "material_segmentation");
  std::string segmentation_method;
  ros::NodeHandle nh("~");
  ros::AsyncSpinner spinner(2);
  spinner.start();
  nh.getParam("segmentation_algorithm", segmentation_method);

  set_segmentation_method(segmentation_method);

  ros::ServiceServer service =
      nh.advertiseService("material_segmentation/change_segmentation_method",
                          change_segmentation_method);
  ros::waitForShutdown();
}
