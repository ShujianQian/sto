#pragma once

#include <queue>

#include "../Logics.hh"
#include "Operator.hh"

namespace storia {

template <typename T, typename B=void>
class Filter : Operator<T> {
private:
    typedef Operator<T> Base;

public:
    using typename Base::arg_type;
    using typename Base::entry_type;
    using typename Base::input_type;
    using typename Base::output_type;
    using typename Base::ret_type;
    using typename Base::value_type;

    typedef B base_type;
    typedef Predicate<input_type, base_type> predicate_type;

    Filter(const predicate_type& predicate) : predicate_(predicate) {}
    Filter(const typename predicate_type::comp_type& comparator)
        : predicate_(PredicateUtil::Make<input_type, base_type>(comparator)) {}

    void consume(arg_type update) {
        if (predicate_.eval(update)) {
            updates_.emplace(update);
        }
    }

    ret_type produce() {
        if (updates_.empty()) {
            return std::nullopt;
        }

        auto next = updates_.front();
        updates_.pop();
        return next;
    }

private:
    const predicate_type predicate_;
    std::queue<output_type> updates_;
};

};  // namespace storia
