#include "VisualTree.hpp"
#include "../../../mem/symbols.hpp"

UIControl* VisualTree::getRoot() {
    return hat::member_at<UIControl*>(this, selaura::signatures::visualtree_root.resolve());
}