/*
 * This source file is part of ARK
 * For the latest info, see https://github.com/ArkNX
 *
 * Copyright (c) 2013-2020 ArkNX authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"),
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#pragma once

#include "base/AFPluginManager.hpp"
#include "utility/include/AFScheduler.hpp"
#include "utility/interface/AFIScheduleModule.hpp"

namespace ark {

class AFCScheduleModule final : public AFIScheduleModule
{
    ARK_DECLARE_MODULE_FUNCTIONS
public:
    bool Init() override;

protected:
    void AddIntervalSchedule(const std::chrono::system_clock::duration interval, SCHEDULER_FUNCTOR&& cb) override;

    void AddAtSchedule(const std::string& target_time, SCHEDULER_FUNCTOR&& cb) override;
    void AddCronSchedule(const std::string& cron_expression, SCHEDULER_FUNCTOR&& cb) override;

private:
    std::shared_ptr<AFScheduler> scheduler{nullptr};
};

} // namespace ark
