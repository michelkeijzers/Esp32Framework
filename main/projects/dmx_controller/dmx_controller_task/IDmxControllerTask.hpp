#pragma once

#include "../../../common/tasks/IRtosTask.hpp"

class IDmxControllerTask : public IRtosTask
{
  public:
    virtual ~IDmxControllerTask() = default;
};