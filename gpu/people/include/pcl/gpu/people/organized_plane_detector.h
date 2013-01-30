/*
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2011, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *
 * @author: Koen Buys
 */

#ifndef PCL_GPU_PEOPLE_ORGANIZED_PLANE_DETECTOR_H_
#define PCL_GPU_PEOPLE_ORGANIZED_PLANE_DETECTOR_H_

#include <pcl/pcl_exports.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>

#include <pcl/features/integral_image_normal.h>
#include <pcl/segmentation/organized_multi_plane_segmentation.h>
#include <pcl/common/transforms.h>

#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>

namespace pcl
{
  namespace gpu
  {
    namespace people
    {
      class OrganizedPlaneDetector
      {
        protected:
          pcl::IntegralImageNormalEstimation<pcl::PointXYZRGB, pcl::Normal>               ne_;
          pcl::OrganizedMultiPlaneSegmentation<pcl::PointXYZRGB, pcl::Normal, pcl::Label> mps_;

          float   ne_NormalSmoothingSize_;
          float   ne_MaxDepthChangeFactor_;

          int     mps_MinInliers_;
          double  mps_AngularThreshold_;
          double  mps_DistanceThreshold_;
          bool    mps_use_planar_refinement_;

        public:
          typedef boost::shared_ptr<OrganizedPlaneDetector> Ptr;
          //typedef DeviceArray2D<unsigned char> Labels;
          //typedef DeviceArray2D<unsigned short> Depth;
          //typedef DeviceArray2D<pcl::RGB> Image;

          /** \brief This is the constructor **/
          OrganizedPlaneDetector ();

          /** \brief Process step, this wraps Organized Plane Segmentation code **/
          void process (const PointCloud<PointXYZRGB>::ConstPtr &cloud);

          double getMpsAngularThreshold () const
          {
            return mps_AngularThreshold_;
          }

          void setMpsAngularThreshold (double mpsAngularThreshold)
          {
            mps_AngularThreshold_ = mpsAngularThreshold;
            mps_.setAngularThreshold (mps_AngularThreshold_);
          }

          double getMpsDistanceThreshold () const
          {
            return mps_DistanceThreshold_;
          }

          void setMpsDistanceThreshold (double mpsDistanceThreshold)
          {
            mps_DistanceThreshold_ = mpsDistanceThreshold;
            mps_.setDistanceThreshold (mps_DistanceThreshold_);
          }

          int getMpsMinInliers () const
          {
            return mps_MinInliers_;
          }

          void setMpsMinInliers (int mpsMinInliers)
          {
            mps_MinInliers_ = mpsMinInliers;
            mps_.setMinInliers (mps_MinInliers_);


          }

          float getNeMaxDepthChangeFactor () const
          {
            return ne_MaxDepthChangeFactor_;
          }

          void setNeMaxDepthChangeFactor (float neMaxDepthChangeFactor)
          {
            ne_MaxDepthChangeFactor_ = neMaxDepthChangeFactor;
            ne_.setMaxDepthChangeFactor (ne_MaxDepthChangeFactor_);
          }

          float getNeNormalSmoothingSize () const
          {
            return ne_NormalSmoothingSize_;
          }

          void setNeNormalSmoothingSize (float neNormalSmoothingSize)
          {
            ne_NormalSmoothingSize_ = neNormalSmoothingSize;
            ne_.setNormalSmoothingSize (ne_NormalSmoothingSize_);
          }

        private:
          void allocate_buffers(int rows = 480, int cols = 640);

      };
    }
  }
}

#endif /* PCL_GPU_PEOPLE_FACE_DETECTOR_H_ */