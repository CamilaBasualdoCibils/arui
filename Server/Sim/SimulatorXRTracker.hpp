#pragma once

#include "Tracker/IXRTracker.hpp"
namespace ARUI {
class SimulatorXRTracker : public IXRTracker {

public:
  std::optional<TrackedPose> GetPose(std::string_view jointName) override {}

  size_t GetJoints(std::span<std::string_view> jointNames) override {}

  void PollEvents() override {}
};
} // namespace ARUI