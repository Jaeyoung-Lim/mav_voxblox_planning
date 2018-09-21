#ifndef MAV_PLANNING_BENCHMKARK_GLOBAL_PLANNING_BENCHMARK_H_
#define MAV_PLANNING_BENCHMKARK_GLOBAL_PLANNING_BENCHMARK_H_

#include <mav_planning_common/physical_constraints.h>
#include <voxblox_rrt_planner/voxblox_ompl_rrt.h>
#include <voxblox_skeleton_planner/path_shortening.h>
#include <voxblox_skeleton/skeleton_planner.h>
#include <voxblox_skeleton/sparse_graph_planner.h>

namespace mav_planning {

struct GlobalBenchmarkResult {
  int trial_number = 0;
  int seed = 0;
  std::string map_name;
  double robot_radius_m = 0.0;
  int global_planning_method;
  int smoothing_method;
  bool has_collisions = false;
  double computation_time_sec = 0.0;
  double total_path_time_sec = 0.0;
  double total_path_length_m = 0.0;
  double straight_line_path_length_m = 0.0;
};

class GlobalPlanningBenchmark {
 public:
  GlobalPlanningBenchmark(const ros::NodeHandle& nh,
                          const ros::NodeHandle& nh_private);

  void loadMap(const std::string& base_path, const std::string& esdf_name,
               const std::string& sparse_graph_name);

  void runBenchmark(int num_trials);

  void outputResults(const std::string& filename);

 private:
  ros::NodeHandle nh_;
  ros::NodeHandle nh_private_;

  // Settings for physical constriants.
  PhysicalConstraints constraints_;

  // General settings.
  bool verbose_;
  bool visualize_;
  std::string frame_id_;

  // Voxblox Server!
  std::unique_ptr<voxblox::EsdfServer> esdf_server_;

  // Global Planners!
  VoxbloxOmplRrt rrt_planner_;
  voxblox::SkeletonAStar skeleton_planner_;
  voxblox::SparseGraphPlanner sparse_graph_planner_;
  EsdfPathShortener path_shortener_;

  // Path Smoothers!
  LocoSmoother loco_smoother_;

  // Results.
  std::vector<GlobalBenchmarkResult> results_;
};

}  // namespace mav_planning

#endif  // MAV_PLANNING_BENCHMKARK_GLOBAL_PLANNING_BENCHMARK_H_
