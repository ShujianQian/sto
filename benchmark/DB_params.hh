#pragma once

#include <iostream>
#include <cstring>

namespace db_params {

// Benchmark parameters
constexpr const char *db_params_id_names[] = {
    "none", "default", "opaque", "2pl", "adaptive", "swiss", "tictoc", "mvcc"};

enum class db_params_id : int {
    None = 0, Default, Opaque, TwoPL, Adaptive, Swiss, TicToc, MVCC
};

inline std::ostream &operator<<(std::ostream &os, const db_params_id &id) {
    os << db_params_id_names[static_cast<int>(id)];
    return os;
}

inline db_params_id parse_dbid(const char *id_string) {
    if (id_string == nullptr || (*id_string) == '\0')
        return db_params_id::None;
    for (size_t i = 0; i < arraysize(db_params_id_names); ++i) {
        if (!strncmp(id_string, db_params_id_names[i], strlen(db_params_id_names[i]) + 1)) {
            auto selected = static_cast<db_params_id>(i);
            std::cout << "Selected \"" << selected << "\" as DB concurrency control." << std::endl;
            return selected;
        }
    }
    return db_params_id::None;
}

constexpr const char *db_split_names[] = {"none", "static", "adaptive"};

enum class db_split_type : int {
    Invalid = -1, None = 0, Static, Adaptive
};

inline std::ostream &operator<<(std::ostream &os, const db_split_type& split) {
    os << db_split_names[static_cast<int>(split)];
    return os;
}

inline db_split_type parse_split_type(const char *id_string) {
    if (id_string == nullptr || (*id_string) == '\0')
        return db_split_type::Invalid;
    for (size_t i = 0; i < arraysize(db_split_names); ++i) {
        if (!strncmp(id_string, db_split_names[i], strlen(db_split_names[i]) + 1)) {
            auto selected = static_cast<db_split_type>(i);
            std::cout << "Timestamp splitting strategy: " << selected << std::endl;
            return selected;
        }
    }
    return db_split_type::Invalid;
}

class db_default_params {
public:
    static constexpr db_params_id Id = db_params_id::Default;
    static constexpr bool RdMyWr = false;
    static constexpr bool TwoPhaseLock = false;
    static constexpr bool Adaptive = false;
    static constexpr bool Opaque = false;
    static constexpr bool Swiss = false;
    static constexpr bool TicToc = false;
    static constexpr bool MVCC = false;
    static constexpr bool NodeTrack = false;
    static constexpr bool Commute = false;
    static constexpr db_split_type Split = db_split_type::None;
    static constexpr bool UseATS = false;
};

class db_default_sts_params : public db_default_params {
public:
    static constexpr db_split_type Split = db_split_type::Static;
};

class db_default_ats_params : public db_default_params {
public:
    static constexpr db_split_type Split = db_split_type::Adaptive;
    static constexpr bool UseATS = true;
};

class db_default_commute_params : public db_default_params {
public:
    static constexpr bool Commute = true;
};

class db_default_sts_commute_params : public db_default_sts_params {
public:
    static constexpr bool Commute = true;
};

class db_default_ats_commute_params : public db_default_ats_params {
public:
    static constexpr bool Commute = true;
};

class db_opaque_params : public db_default_params {
public:
    static constexpr db_params_id Id = db_params_id::Opaque;
    static constexpr bool Opaque = true;
};

class db_opaque_commute_params : public db_opaque_params {
public:
    static constexpr bool Commute = true;
};

class db_2pl_params : public db_default_params {
public:
    static constexpr db_params_id Id = db_params_id::TwoPL;
    static constexpr bool TwoPhaseLock = true;
};

class db_adaptive_params : public db_default_params {
public:
    static constexpr db_params_id Id = db_params_id::Adaptive;
    static constexpr bool Adaptive = true;
};

class db_swiss_params : public db_default_params {
public:
    static constexpr db_params_id Id = db_params_id::Swiss;
    static constexpr bool Swiss = true;
};

class db_tictoc_params : public db_default_params {
public:
    static constexpr db_params_id Id = db_params_id::TicToc;
    static constexpr bool TicToc = true;
};

class db_tictoc_commute_params : public db_tictoc_params {
public:
    static constexpr bool Commute = true;
};

class db_tictoc_node_params : public db_tictoc_params {
public:
    static constexpr bool NodeTrack = true;
};

class db_tictoc_commute_node_params : public db_tictoc_commute_params {
public:
    static constexpr bool NodeTrack = true;
};

class db_mvcc_params : public db_default_params {
public:
    static constexpr db_params_id Id = db_params_id::MVCC;
    static constexpr bool Opaque = true;
    static constexpr bool MVCC = true;
};

class db_mvcc_sts_params : public db_mvcc_params {
public:
    static constexpr db_split_type Split = db_split_type::Static;
};

class db_mvcc_ats_params : public db_mvcc_params {
public:
    static constexpr db_split_type Split = db_split_type::Adaptive;
    static constexpr bool UseATS = true;
};

class db_mvcc_commute_params : public db_mvcc_params {
public:
    static constexpr bool Commute = true;
};

class db_mvcc_sts_commute_params : public db_mvcc_sts_params {
public:
    static constexpr bool Commute = true;
};

class db_mvcc_ats_commute_params : public db_mvcc_ats_params {
public:
    static constexpr bool Commute = true;
};

class db_default_node_params : public db_default_params {
public:
    static constexpr bool NodeTrack = true;
};

class db_default_commute_node_params : public db_default_commute_params {
public:
    static constexpr bool NodeTrack = true;
};

class db_mvcc_node_params : public db_mvcc_params {
public:
    static constexpr bool NodeTrack = true;
};

class db_mvcc_commute_node_params : public db_mvcc_commute_params {
public:
    static constexpr bool NodeTrack = true;
};


class constants {
public:
    static constexpr double million = 1000000.0;
    static constexpr double billion = 1000.0 * million;
    static double& processor_tsc_frequency() { // in GHz
        static double frequency = 0;
        return frequency;
    }
};

}; // namespace db_params
