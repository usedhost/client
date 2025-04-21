#pragma once

#include <memory>
#include <stdexcept>

namespace selaura::bedrock {
    namespace Bedrock {
        class EnableNonOwnerReferences {
        public:
            struct ControlBlock {
                bool is_valid;
            };
            EnableNonOwnerReferences()
            {
                control_block_ = std::make_shared<ControlBlock>();
                control_block_->is_valid = true;
            }
            virtual ~EnableNonOwnerReferences()
            {
                control_block_->is_valid = false;
            }

        private:
            template <typename T>
            friend class NonOwnerPointer;

            std::shared_ptr<ControlBlock> control_block_;
        };
    }
};