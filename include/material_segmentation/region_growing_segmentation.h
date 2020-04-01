/** * Copyright (c) Aalto  - All Rights Reserved
 * Created on: 7/4/19
 *     Author: Jens Lundell <jens.lundell@aalto.fi>
 */

#ifndef REGION_GROWING_SEGMENTATION_H
#define REGION_GROWING_SEGMENTATION_H

#include <material_segmentation/RegionGrowingSegParams.h>
#include <material_segmentation/base_segmentation.h>
class RegionGrowingSegmentation : public BaseSegmentation {
public:
  RegionGrowingSegmentation();
  virtual void segment_scene(PointCloudPtr, std::vector<pcl::PointIndices> &,
                             std::vector<PointCloud> &);
  bool
  update_parameters_cb(material_segmentation::RegionGrowingSegParams::Request &,
                       material_segmentation::RegionGrowingSegParams::Response &);

private:
  int min_cluster_size;
  int max_cluster_size;
  int number_of_neighbors;
  float smoothness_threshold;
  float curvature_threshold;
  ros::ServiceServer update_params_srv;
};

#endif // REGION_GROWING_SEGMENTATION_H
