#pragma once

#include <memory>
#include <stdexcept>

namespace bedrock {
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

        template <typename T = EnableNonOwnerReferences>
        class NonOwnerPointer {
        private:
            std::shared_ptr<EnableNonOwnerReferences::ControlBlock> controlBlock;

        public:
            NonOwnerPointer() : controlBlock(nullptr) {}

            explicit NonOwnerPointer(T* ptr) : controlBlock(ptr->controlBlock) {}

            NonOwnerPointer(const NonOwnerPointer<T>& other) : controlBlock(other.controlBlock) {}

            NonOwnerPointer& operator=(const NonOwnerPointer<T>& other)
            {
                this->controlBlock = other.controlBlock;
                return *this;
            }

            NonOwnerPointer& operator=(T* ptr)
            {
                this->controlBlock = ptr->controlBlock;
                return *this;
            }

            T* operator->() const
            {
                return static_cast<T*>(this->controlBlock.get()->ptr);
            }

            T& operator*() const
            {
                return *this->operator->();
            }

            bool operator==(void*) const
            {
                return this->controlBlock == nullptr;
            }

            bool operator!=(void*) const
            {
                return this->controlBlock != nullptr;
            }

            T* get() const
            {
                static_assert(std::is_base_of<EnableNonOwnerReferences, T>::value, "T must derive from EnableNonOwnerReferences");
                return static_cast<T*>(this->controlBlock ? this->controlBlock->ptr : nullptr);
            }
        };

    }
};